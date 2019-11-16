
## client 缓存 mds 分配的caps


#### dirty cap 相关

dirty cap 是什么含义？

内核中把 cap 标脏的接口是__ceph_mark_dirty_caps，调用的地方有__ceph_setattr，__ceph_setxattr 等。

可以重点读一下__ceph_setattr 代码：

* 最初 dirtied = 0
* atime, dirtied |= CEPH_CAP_FILE_EXCL


#### client 写数据的大概流程

    参考这里：https://docs.ceph.com/docs/master/architecture/
        

#### client和pool的连接

    集群通信的时候，是一定和一个pool链接的。
