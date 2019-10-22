#### 关于has_journaled_slaves标记

这个标记在三个接口中设置为true，handle_slave_link_prep_ack，handle_slave_rmdir_prep_ack，handle_slave_rename_prep_ack。这和我们之前说的。
有的操作会影响到多威权威mds上的元数据，典型的三个操作就是link，unlink，rename。具体的说就是，比如link，源dnetry和目的inode是由两个不同的权威mds在维护。此时当前的MDS就会发送一个 slave request 给inode 所在的 MDS，请求 增加 link count。

而一般的情况下，一个文件的inode和dentry都是在一个权威mds上的，因为子树的划分是目录，一个目录下的dentry和这些dentry对应的inode都是在同一个权威mds上。

#### 关于 slave 的 two-phase commit

slave mds先对prepare 写日志，当所有的slave都写完成的时候，主mds对update记入日志。然后commit事务，最后所有的slave会记录committed事件来结束事务。

#### Server::handle_client_unlink

删除文件和删除目录都是用的这一个接口，通过请求的OP是否为CEPH_MDS_OP_RMDIR来判断是还不是rmdir操作。所以rmdir也是在unlink里做的。

#### 日志相关上下文类

    ServerLogContext::MDSLogContextBase // 大部分都是这个context
    ServerIOContext::MDSLogContextBase

