#### 测试在PG down的情况下MDS是否会重发请求给OSD

     ceph daemon mds.mds1 dump_blocked_ops

显示有请求卡住，而在NAS节点上，查看osdc 没有请求：

    [root@node92 65263f05-fb97-4655-8237-14eda227ff7c.client1328753]# cat osdc
    REQUESTS 0 homeless 0
    LINGER REQUESTS
    BACKOFFS
     
#### mds处理的几个关键event点

    "event": "throttled"
    "event": "all_read"
    "event": "dispatched"
    "event": "initiated"
    "event": "acquired locks"  
    "event": "early_replied"
    "event": "submit entry: journal_and_reply"
