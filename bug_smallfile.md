[ceph cluster arch](https://access.redhat.com/documentation/en-us/red_hat_ceph_storage/3/html/architecture_guide/arch-cluster-arch)

[cache pool](https://docs.ceph.com/docs/master/dev/cache-pool/)

#### 关于 memstore
    
    Memstore: A developer implementation for testing read/write operations directly in RAM.

#### memstor 使用

* 从0.76版本就已经开始支持
* 不要在生产环境中使用
* 在ceph.conf文件中添加 osd objectstore = memstore


#### memstor配置

    storage_type = memstore
    osd_objectstore = memstore

