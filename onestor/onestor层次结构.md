
#### ONEStor 组件
onestor的架构中组件较多，分以下几层：

pool层概念，这个pool是分布式的，所以有metapool，datapool，还有一个为了加速用的cachepool(为了避免混乱，现在已经不叫cachetier)。
在这里，就有一个加速，就是cachepool是给datapool加速用的。

pool之下，就是osd，这个是承载pool的基础组件，osd负责管理操作一块磁盘。

osd进程内，可以分为多个而组件，从上到下是osd，store bdev，rockdb, bluefs，bluestore。
其中，store，rocksdb，bluestore就都是本地的数据管理，不是分布式的。

#### OSD来管理一个磁盘
每块磁盘（不管HDD,SSD,还是NVMe）都会有一个osd进程，也不管什么pool，都是基于osd来做。所以，我们可以看到，元数据池对应的磁盘有osd支撑，数据池也一样。

#### 全闪小IO处理
小IO先写dcache，然后等待下刷。

#### 全闪大IO处理
ROW在一定聚合时间内，会等待，等到到满4M，如果不满，就补齐到条带对齐后写入（比如条带大小是128K）。

#### root概念
一个root就是一个硬盘池，或者更准确说是一个分区池。

#### 元数据的概念
落盘时才会有元数据的需求

#### OSD中的层次
```
OSD-pg
OSD-rep/EC
----
OSD:scache
OSD:nlueStore-rocksdb-bluefs
block-dev
```

#### 元数据分离部署
就是对象的元数据(rocksdb中)和对象的数据(bluestore)管理分开，不在同一个磁盘上。

#### 全闪和元数据分离部署的关系
没有关系，3.0或者5.0版本，与元数据是否分离没有必然关系。全闪下，也可以有元数据分离部署。

#### ROW池的作用
ROW池给分布式rocksdb用。

#### scache的作用
scache是bluestore之上的一层，存储的是pg角度看到的对象的数据和元数据，此时，没有bluestore参与（应该没有涉及rockdb）。

scache是只有一个盘，为多个HDD盘做加速，所以SCache组件所在的盘一般为SSD，osd进程会将数据线写入scache, 然后再异步将数据从scache所在的SSD转入HDD。

scache一般可以通过osd目录下的fcache_uuid找到partuuid，然后在`/dev/disk/by-partuuid`下找到软链接，最后就能找到分区，大小一般为几十G。

#### osd下的block连接
block链接的是数据盘。

#### block分区和scache的关系
block分区会和scache进行绑定。


#### 元数据分离部署时中osd目录下多出的2个链接
元数据分离部署情况下多出来的block.db, block.wal
```
block.db    存放rocksdb中的数据, 分区大小一般为16/32G。
block.wal   存放rockdb的日志，分区大小一般为2G。
```

#### 对象存储在block-dev上的位置等信息也是放在rocksdb中么
是的

#### 其他参考
参考1：[混闪缓存盘为什么压力比较大](/2021/202110混闪缓存盘为什么压力比较大.md)
