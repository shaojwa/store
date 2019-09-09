
#### 海量小文件的主要难点

* 元数据管理
* 数据布局
* IO管理
* cache管理
* 网路开销


#### 常见的几种优化


* 同一个目录中的文件inode放在一起存取。（元数据层优化）
* 文件名隐含部分元数据。（元数据层优化）
* 部分元数据预先加载到内存。（元数据层优化）
* 小于1K的小文件，数据直接存在元数据中。（数据层优化）
* 多个逻辑文件共享一个物理文件。（数据层优化）
* 添加缓存层。（访问方式）


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

