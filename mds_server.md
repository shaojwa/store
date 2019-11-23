## openc 流程分析

1. ceph_flags_to_mode() 将openc的标记转为mode字段，如果转化得到的mode不对，就返回EINVAL。

O_ACCMODE 就是个加掩码mask，值是0x3，判断是只读还是只写，还是读写都有。

2. 判断有没有O_EXCL

open系统调用中，O_EXCL用来确保创建一个文件，如果文件已经存在，open就会返回错误。
所以，如果没有这个标记，通过path_traverse()来确认是否存在文件。
如果返回结果 > 0 表示MDS状态对，比如目录冻结，元数据还未读取到等，或者正在打快照，目录不完整，权威模糊等，直接返回，因为mdr已经放到某个等待队列。
如果文件存在就用 handle_client_open() 处理。
如果报错，且不是不存在错误，那就进行异常处理，处理的方式是：如果返回时STALE错误，则并调用处理接口构建回调，如果是其他错误码，或者直接返回失败。

3. 通过rdlocks, wrlocks, xlocks集合，准备需要获取的锁，通过rdlock_path_xlock_dentry()。

rdlock_path_xlock_dentry() 最终会返回一个可用的dentry。
此时各层dentry（包括新创建的dentry）要rdlock，新创建的dentry也需要xlock。
新创建dentry所在的dir的inode的filelock要加入wrlock，以尝试获取到wrlock，因为本质上是在写目录inode的内容。
新创建的dentr所在的dir的inode的nestlock锁要加入wrlock，因为要更新inode中的rstat结构里的信息。

4. 设置layout，如果 rdlock_path_xlock_dentry() 返回特定的layout，就选用特定的layout，否则用默认的。

5. 多数据池时是否需要自动平衡，默认情况下不进行。

自动平衡就是对原先是某个pool_id的文件，随机分配到某个pool_id集合中的另外一个。

6. 设置默认的cap，access = MAY_WRITE

7. 把客户端发送关于layout的配置填入layout，如果layout有变化，那需要 bit-OR 上 MAY_SET_VXATTR 权限。

校验layout的有效性，判断pool_id的是否为data_pool。

8. 判断是不是创建 /.rmdir 目录

9. 获取目录inode的authlock

之前 rdlock_path_xlock_dentry 针对的是目录dentry中的lock，以及目录inode的filelock，nestlock。
这里是针对目录inode的authlock，所以汇总起来就是：

各层dentry的lock的rdlock，父目录dentry的xlock，这里上层目录只需要读取，不做更新，所以rdlock就可以。
父目录inode的filelock，nestlock的wrlock，因为这创建操作需要写inode内容，以及更新rstat，所以需要获取wrlock。
父目录inode的authlock的rdlock，authlock，auth主要针对ower，group，mode，这个不做修改，只需要读取。

10. 调用acquire_locks() 执行获取操作。

11. 执行check_access() 确认访问权限。

这个接口主要的工作接口是MDSAuthCaps::is_capable(), 具体工作是是对uid, gid, mode字段的校验。
不清楚这个校验为什么不是在acquire_lock()之前进行。

12. 校验是否达到分片最大数，默认10000。

达到分片最大数，难道只是返回ENOSPC？不重新分配新的分片么？

13. 得到linkage并校验，如果这个linkage有指向的inode，那么就上报EEXIST错误，此时是inode已经存在。

如果觉得为什么在O_EXCL 的之后，dentry如果已经存在会怎么样，那么代码应该在rdlock_path_xlock_dentry()中求证。
但是，如果dentry已经存在，和这里的inode已经存在应该是一个概念。所以这里的exist其实就是dentry已经存在。
因为dentry存在，就有对应的inode，不存在没有inode的dentry。

14. 创建inode节点

15. 准备提交日志

16. 执行open

这一步主要的操作是 issue_new_caps(), 这个接口中会判断。
如果当前是权威mds，那么自己就分配，先调用eval() 评估一下，然后issue_caps()向客户端发送授予的权限。
如果是副本mds，那就消息告诉权威，权威会给client发送对应的caps。看起来，cap都是权威授予的。

最后，把authlock设置成EXCL状态，xattrlock也是EXCL，这里的inode是新创建的inode，不是父目录的inode。

17. journal_and_reply()，其中按需early_reply并提交日志。

18. maybe_fragment() 

这是目录分片么？为什么在最后执行？


#### unlink

unlink dentry，会将请求发送到dentry所在的权威节点，即dentry所在目录的inode权威节点。

#### rdlock_path_xlock_dentry()

#### 当前MDS如果没有CInode/CDir/CDentry缓存时如何处理

尝试命中缓存接口：
```
mds->balancer->hit_inode()
```

#### 流程

通过 MDSRank::handle_deferrable_message进入, 根据 message type进行分发：
                    
    server->dispatch()
    Server::handle_client_session()
    Server::handle_client_request()
    Server::handle_slave_request()
    Server::handle_mds_rmdirfrag() // 为什么单独处理？
    
####  handle_client_request()

    mdr = mdcache->request_start(req)
    Server::dispatch_client_request(mdr)
        // switch by req->get_op() to handle_client_xxxx()
        Server::handle_client_readdir()
        Server::handle_client_getattr()
        Server::handle_client_open()
            // steps of handle_client_xxxx() 
            mds->locker->acquire_locks() // got locks
            mdlog->start_entry(le) // make log
            mdlog->submit_entry(le) // submit log
            // if journal needed
            Server::journal_and_reply()  // call  Server::respond_to_request in finisher callbacks
            // or no journal needed
            Server::respond_to_request()

#### 关于has_journaled_slaves标记

这个标记在三个接口中设置为true，handle_slave_link_prep_ack，handle_slave_rmdir_prep_ack，handle_slave_rename_prep_ack。这和我们之前说的。
有的操作会影响到多威权威mds上的元数据，典型的三个操作就是link，unlink，rename。具体的说就是，比如link，源dnetry和目的inode是由两个不同的权威mds在维护。此时当前的MDS就会发送一个 slave request 给inode 所在的 MDS，请求 增加 link count。

而一般的情况下，一个文件的inode和dentry都是在一个权威mds上的，因为子树的划分是目录，一个目录下的dentry和这些dentry对应的inode都是在同一个权威mds上。

#### 关于 slave 的 two-phase commit

slave mds先对prepare 写日志，当所有的slave都写完成的时候，主mds对update记入日志。然后commit事务，最后所有的slave会记录committed事件来结束事务。

#### Server::handle_client_unlink

删除文件和删除目录都是用的这一个接口，通过请求的OP是否为CEPH_MDS_OP_RMDIR来判断是还不是rmdir操作。所以rmdir也是在unlink里做的。

#### 日志相关上下文类

    // 大部分都是这个context
    ServerLogContext::MDSLogContextBase
    
    ServerIOContext::MDSLogContextBase

