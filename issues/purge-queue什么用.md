## purge-queue 什么作用

文件删除后，放到stray 目录，删除的文件越多，stray 目录越大。删除的inode也会放到purge-queue中，等待清理其数据（比如文件）。
原先删除的dentry，inode是pin在内存里的，且purge-queue并不保证purge的速度。
（But there is no guarantee that the queue progresses quickly, and everything in the queue is pinned in the cache）
现在，删除的文件inode会放到purge-queue里。purge-queue是一个持久化的工作队列，用一个单独的线程去清理它。
对应的处理模块是StrayManager。
STRAY 放的是目录的路径相关信息 600开头的对象， purge_queue存放的对象是500开头。

参考：
https://tracker.ceph.com/issues/11950
https://github.com/ceph/ceph/pull/8582
https://github.com/ceph/ceph/pull/12786
