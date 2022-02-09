#### 全闪小IO处理
小IO先写dcache，然后等待下刷。

#### 全闪大IO处理
ROW在一定聚合时间内，会等待，等到到满4M，如果不满，就补齐到条带对齐后写入（比如条带大小是128K）。


#### onestor组件
onestor的架构中组件较多，分以下几层：

pool层概念，这个pool是分布式的，所以有metapool，datapool，还有一个为了加速用的cachepool(为了避免混乱，现在已经不叫cachetier)。
在这里，就有一个加速，就是cachepool是给datapool加速用的。

pool之下，就是osd，这个是承载pool的基础组件，osd负责管理操作一块磁盘。

osd进程内，可以分为多个而组件，从上到下是osd，store bdev，rockdb, bluefs，bluestore。
其中，store，rocksdb，bluestore就都是本地的数据管理，不是分布式的。

#### OSD中的scache
scache是只有一个盘，为多个HDD盘做加速，所以scache组件所在的盘一般为SSD，osd进程会将数据线写入scache, 然后再异步将数据从scache所在的SSD转入HDD。

#### OSD来管理一个磁盘
每块磁盘（不管HDD,SSD,还是NVMe）都会有一个osd进程，也不管什么pool，都是基于osd来做。所以，我们可以看到，元数据池对应的磁盘有osd支撑，数据池也一样。
