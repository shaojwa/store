### 预写式日志 WriteAhead Log

### LogEvent 提交

* 提供接口submit_entry()，后被Server，Locker，MDCache，Migrator等模块封装使用。

### MDLog的提交的主要流程

* 模块接口函数是MDLog::submit_entry()， 工作函数是MDLog::_submit_entry()

MDLog::submit_entry()主要是对MDLog::_submit_entry()增加锁机制后的封装。

MDS处理元数据请求过程中，实际通过Server::submit_mdlog_entry()来提交日志。
而 Server::submit_mdlog_entry()，主要在Server::journal_and_reply()中调用，所以主要流程是：

    Server::journal_and_reply()
        \-Server::submit_mdlog_entry() 
            \-MDLog::submit_entry()
                \-MDLog::_submit_entry()


Server::journal_and_reply()一些通用操作以完成请求。
Server::submit_mdlog_entry()对MDLog::submit_entry()增加TrackedOp模块对event进行跟踪之后的封装。

除了以上的主流程，其他流程调用submit_mdlog_entry()主要是以下几种情况：

* slave 相关处理
* snap 相关处理
* rollback 相关处理
* 处理内部op的dispatch_fragment_dir

这几个都不是处理一般情况下的client发起的正常业务流程。

#### 问题，为什么有的handle_client_xxxx函数直接调用submit_mdlog_entry() 而有的需要通过journal_and_reply()

使用场景的区别是什么？


## MDLog 中的 flush 下刷

### MDLog中的flush的含义

MDLog的flush接口只是把event写到日志里并落盘（写到日志对象中），而不是把元数据日志转为元数据写入到对象中。
但是命令ceph daemon mds.mdsX flush journal中不只是MDLog的flush，还有MDLog的trim（trim_all），所以会将日志中的元数据转为元数据对象。

### mdslog flush过程

* 获取提交锁
* 如果等待队列pending_event非空，提交一个特殊的event，用来触发下刷。
* 给提交线程发信号，此时就不再执行journaler->flush()
* 如果pending_event为空，则执行journaler->flush()
* 释放提交锁

#### 问题：如果pending_event队列为空，为什么还需要执行journaler->flush()

MDLog.flush在持有submit_mutex的时候去比较unflushed的值。
MDLog在pending_event为空时，依然调用journaler->flush()的前提是unflush大于0。
unflushed增加在两个地方：

* _submit_entry()接口，在这里，会把LogEvent放到pending_events中，所以这不是原因。
* _submit_thread()线程主函数中，如果data.flush 不为true的event，是不会flush的。

unflushed++没有置零的场景也有两：

* data.flush 不为 true时， unflushed不会置0。
* data.flush 不为 true且data.le非空, 此时 unflushed 非但没有置0，还要增加。

所以很关键的一种event是 flush 不为 true。就是PendingEvent的默认值，结果发现大部分event都不是true。
只有专用的PendingEvent(NULL, NULL, true) 的才是true。所以大多数时候只是把Event放到journaler中，而没有下刷。
所以，回答刚才的问题，flush把event都放到了journaler中，不一定下刷，两种情况下下刷：

* 收到标记下刷的Event。
* 如果pengding_events列表已经为空，表示全部放到journaler对象中，触发下刷。

### submit_thread 做什么

submit_thread 主要干的事是：

* 把event放到journaler中，journaler->append_entry()
* 设置回调函数，journaler->wait_for_flush(fin)
* 执行 journaler->flush()

        submit 线程循环处理：
            （1）判断daemon是否正在停止或者pending_event已经为空。
            （2）拿到pending_event这个map的第一个元素（key为log segment）
            （3）拿到第一个需要处理的PendingEvent，记为data。
                （a）如果data中的log_event字段不为空则：
                     回放的顺序记录LogEvent为le；
                     记录le中的segment为ls；
                     把le编码为bl。
                     得到journaler的write_pos；
                     将ls中的开始偏移量start_off设置为write_pos；
                     如果event的类型是SUBTREEMAP：
                             那么把ls的offset也设置为write_pos；
                     把bl追加到journaler中，并返回新的写入位置：new_write_pos；（写日志成功）
                     如果data.fin非空：
                             将data.fin动态转型为MDSLogContextBase，并吧new_write_pos值设置到fin中
                     如果data.info为空：
                             则创建新的额MDL_Flushed上下文，并赋值给fin
                     journaler将fin把回调上下文放到回调列表（日志下刷完成后调用，这里不是同步等）
                     如果data.flush为真：
                             journaler下刷日志（下刷的意思是把日志写入到日志盘，而不是把日志转为元数据）
                （b）如果data中的log_event字段不为空（一般是强制下刷事件)
                     如果data.fin非空（表示有回调事件）
                             构建C_MDL_Flushed回调事件
                             把回调上下文放到回调列表（日志下刷完成后调用）
                     如果data.flush为真：
                             journaler下刷日志

#### mdlog的flush只是下刷日志到磁盘而没有更新到元数据对象

data本身的inode是1099511627777，十六进制10000000001，在data下写文件，那么这些文件信息应该会记录到10000000001开头的对象中。
但是实际上一开始并没有，我们看到的只是日志对象，大小增长：

    [root@node90 ~]# rados -p .capfs.metadata.Metadata ls | grep 200
    200.00000000
    200.00000001
    200.00000002
    [root@node90 ~]# rados -p .capfs.metadata.Metadata stat 200.00000001
    .capfs.metadata.Metadata/200.00000001 mtime 2019-09-11 11:55:11.000000, size 4194304
    [root@node90 ~]# rados -p .capfs.metadata.Metadata stat 200.00000002
    .capfs.metadata.Metadata/200.00000002 mtime 2019-09-14 16:26:55.000000, size 3374365
    [root@node90 ~]# rados -p .capfs.metadata.Metadata stat 200.00000002
    .capfs.metadata.Metadata/200.00000002 mtime 2019-09-14 16:28:15.000000, size 3416798
    [root@node90 ~]#

如果接下去执行 flush journal，我们会看到，日志对象少了，目录对象生成了：
  
    [root@node90 ~]# rados -p .capfs.metadata.Metadata ls | grep 200.
    200.00000000
    200.00000002
    [root@node90 ~]# rados -p .capfs.metadata.Metadata ls | grep 10000000001
    10000000001.00000000
    [root@node90 ~]# rados -p .capfs.metadata.Metadata stat 10000000001.00000000
    .capfs.metadata.Metadata/10000000001.00000000 mtime 2019-09-14 16:39:39.000000, size 0

Server，Locker等等很多地方都会调用mdlog的flush，但不可能每个地方都会吧元数据日志转为元数据更新到元数据对象中。

flush journal之所以会创建新的 元数据对象是因为 flush journal命令中 有trim_all操作，更新元数据到对象中。
