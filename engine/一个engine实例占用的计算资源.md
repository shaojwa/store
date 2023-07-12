要查看这个节点上每个dcache是实例占用线程的个数，就要查看 processer_allocation 配置项：
```
[SDS_Admin@node80 ~]$ sudo ceph daemon dse.node80 config show | grep processer_alloc
    "processer_allocation": "dse=1, csd=3, dcache=2, dedup_front_read=2, dedup_front_write=2, dedup_back=2, dedup_control=1,
     compress=2, gc=1, gc_mark=1, row_service_front=1, row_service_front_dedup=1, row_service_back=1, row_service_common=1,
     rocksdb=1, snap=1, row_control=1, dedup_coldfptable=1, dse_back=1"，
```
我们可以看到，当前集群内，一共可以分成19种角色，一个dcache实例会运行在2个processer上。
