#### 从组建角度看 onestor架构
onestor的架构中组件较多，分一下几层：
1. pool层概念，这个pool是分布式的，所以有metapool，datapool，还有一个为了加速用的cachepool(为了避免混乱，现在已经不叫cachetier)。在这里，就有一个加速，就是cachepool是给datapool加速用的。
2. pool之下，就是osd，这个是承载pool的基础组件，osd负责管理操作一块磁盘。
3. osd进程内，可以分为多个而组件，从上到下是osd，store，rockdb, bluefs，bluestore。store，rocksdb，bluestore就都是本地的数据管理，不是分布式的。

#### 从进程角度看 onestor架构
每块磁盘（不管HDD,SSD,还是NVMe）都会有一个osd进程，也不管什么什么pool，都是基于osd来做。
所以，我们可以看到，元数据池对应的磁盘有osd支撑，数据池也一样。
