-t 参数的意思是concurrent_operations，或者说是并发IO的数量，那么是不是线程数么？[ceph以前的官方文档说是线程数](https://tracker.ceph.com/projects/ceph/wiki/benchmark_ceph_cluster_performance)，但是我通过ps和top看到的并非如此。

## 源码中的-t

rados.cc 中`bencher.aio_bench()`中对应的参数是concurrent_ios，对应到obj_bencher.cc中的`write_bench()`，
RadosBencher重载ObjBencher中的`completion_init()`可以看到，只是有这么多的Aio队列（compitions）。
