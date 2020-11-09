[ceph cluster arch](https://access.redhat.com/documentation/en-us/red_hat_ceph_storage/3/html/architecture_guide/arch-cluster-arch)
[cache pool](https://docs.ceph.com/docs/master/dev/cache-pool/)

#### 海量小文件的主要难点

* 元数据管理低效

        (1) dentry,inode,data 三次独立的访问导致大量的磁盘随机访问，最终导致小文件性能很差。    
        (2) hash数，B+树等数据结构，对于单个目录海量文件来说，会显著降低性能，因为不能再大目录中很好得扩展。

* 数据布局
    
        (1) 元数据与数据的分离存储，为了获得可扩展性和高并发性。
        
* IO访问流程

        （1）VFS系统调用机制不利于LOSF
 
* 网路开销

        （1）对分布式文件系统来说，客户端和元数据服务器之间的网络传输开销很大。

* cache管理

        （1） 从集群读取数据后，按page缓存在客户端的内存中，因为是小文件，所以page的利用率会降低。


#### 常见的几种优化

* 同一个目录中的文件inode放在一起存取。（元数据层优化）
* 文件名隐含部分元数据。（元数据层优化）
* 部分元数据预先加载到内存。（元数据层优化）
* 小于1K的小文件，数据直接存在元数据中。（数据层优化）
* 多个逻辑文件共享一个物理文件。（数据层优化）
* 添加缓存层。（访问方式）

#### 关于 memstore
    
    Memstore: A developer implementation for testing read/write operations directly in RAM.

#### memstor 使用

* 从0.76版本就已经开始支持
* 不要在生产环境中使用
* 在ceph.conf文件中添加 osd objectstore = memstore


#### memstor配置

    storage_type = memstore
    osd_objectstore = memstore

