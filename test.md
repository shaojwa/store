#### enable/disable compress
```
ceph compress set_switch pool Poolname on/off
```

#### enable/disable online-dedup  
```
ceph dedup set pool Poolname online on/off
```
#### enable/disable offline-dedup  
```
ceph dedup set pool Poolname offline on/off
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
