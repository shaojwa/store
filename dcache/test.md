#### run fio
```
fio -direct=1 -ioengine=rbd -group_reporting -name=mytest -bs=8K -iodepth 10 -numjobs 1 -size=10G -rw=randread -pool=.111.rbd -rbdname=test10g5
```

#### test block seq flow
1. add `rbd_readahead2 = True` in /etc/ceph/ceph.conf
2. kill all **tgtd** process

#### DCache_get_thread_id()
1. define DCACHE_GTEST_CTRL 

#### DCacheInstance::DCache_module_init()
1. disable destage
1. disable lsm

#### DCache_shutdown()
1. disable destage
1. disable lsm
