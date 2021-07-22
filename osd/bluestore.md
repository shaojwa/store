https://ceph.io/en/news/blog/2017/new-luminous-bluestore/

#### bluestore做到了什么
mBlueStore 是ceph的一种新的存储后端，两倍的性能提升，算数据的校验和，以及内建的压缩，是ceph osd 默认的存储后端。

#### 多快？
相对于FileStore有两倍的性能提升，以及更低的长尾延时。
- 大文件写。我们避免了FileStore的双写。
- 小块随机写。就算相比有日志的FileStore，我们还是获得很明显的提升。
- 对于 key/value 数据，我们得到了3倍提升。
- 避免了FileStore中可能出现的吞吐量坍塌问题。
- 使用librados的原生小文件顺序读性能有所下降，那是因为BlueStore本身没有实现预读，原因是基于BlueStore的上层模块有实现。
- BlueStore使用COW，这个和FileStore不同。

#### OSD 的职责
OSD主要就干两件事情：(1) 将副本数据通过网络传到其他的OSD。（2）将数据存在本地设备上，比如硬盘，SSD，或者两者的混合。


#### BlueStor如何工作
