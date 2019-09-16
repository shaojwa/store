

#### MDLog中的flush的含义

MDLog的flush接口只是把event写到日志里去并落盘（写到日志对象中），而不是把元数据日志转为元数据写入到对象中。

但是命令是 ceph daemon mds.mdsX flush journal中不只是MDLog的flush，还有MDLog的trim（trim_all），所以会将日志中的元数据转为元数据对象。

#### 如何证明mdlog的flush只是下刷日志到磁盘而没有更新到元数据对象

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
