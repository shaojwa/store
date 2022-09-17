- https://daosio.atlassian.net/wiki/spaces/DC/pages/4836661105/Roadmap
- https://github.com/daos-stack/daos

#### 什么是DAOS
- 为了高性能运算
- 为了发挥硬件的性能。
- 全用户态。
- CS类型分布式存储系统。
- 基于PEM和NVMe-SSD设计实现的。
- 不支持DiskDrive。
- 是一个完整的存储系统。

#### 主要特点
- 简化IO栈。
- PMEM，以字节为单位进行读写。
- 引入的三大构建：PMEM，NVMe-SSD（全部PMEM成本太高），高速网络（DAOS在用户态访问应用程序地址空间内的数据，实现无内存拷贝）。
- 更灵活的API

#### 工具链
- PMDK
- SPDK（DAOS完全在用户态向SSD提交IO）

#### 实现细节
- DAOS-Control-Plane
- 元数据都存在PMEM中。
- 对齐的大块数据，放到SSD中
- 小块非对齐部分，放到PMEM中
- 索引放到PMEM中
- PMEM的数据也会迁移到SSD中

## 软件栈
- 第三方应用->DataModels(POSIX I/O, HDFS,Spark, MPI-IO)->DAOS-Storage-Engine.
- 为了减轻软件栈带来的IO延迟，DAOS-client是一个用户库。
- DAOS-Storage-Engine是一个用户态进程。
- 混合的存储模型是的DAOS的存储可以以字节为单位对齐。
- 多级KV-API

## 潜在的应用场景（Use Case）

#### DAOS的部署方式
#### DAOS服务器的硬件配置
- 通常有两个socket
- PMEM/DRAM
- CLX/ICX
- intel UPI
- PCIe * lane/
- PMEM是CPU直接通过内存通道访问的
- SSD通过PCIe访问
- 建议在一台服务器上建议运行两个完全独立的storage engine，来避免跨socket的频繁访问。
- 建议装两个网络适配器连接到各自的CPU-socket上
- 建议两个PCIe上的SSD的数量也是一样的
- 最后，一台服务器拆成两个完全独立的数据引擎
- 对称设计可以简化数据分布策略算法的简化

#### DAOS的存储管理
- DAOS内部大量使用B+ tree, EV-tree 来存储DAOS系统的元数据。
- 小于4K的io放到PMEM中
- PMEM的最低容量要求，在一台服务器上的容量比例达到3%到6%
- PMEM耗尽之后，那台节点就处于停滞状态。

#### DAOS的后台服务
- PMEM中数据到SSD的迁移，减少PMEM的压力
- SSD中数据的合并，来减少SSD的碎片化，还可以减少PMEM中的索引。
- 数据和元数据的比例，估算是3%-6%的比例。
- 我们的元数据是PMDK的allocator，有一些overhead。
- PMEM容量不够，元数据会放到PMEM中。
- 一个pool是一个大的pool。
- container和application的关系。
- container相当于私用文件系统中的一个mount。
- 一个pool和一个用户对应，pool内的container相当于这个用户的不同application。
- PMEM中为以pool为单位分配空间。
- 一个container最好给一个应用，不要多个应用，因为conatiner内没有分布式的锁。

#### DAOS用户接口和生态系统
- libdaos之上有一个lib就是libdfs，libdfs是一个插件。
- 整个分布式存储容量中的一部分且给你做为一个pool，而daos-container是一个pool中的数据集，这个数据集是有类型的，比如posix文件系统，或者HDFS file。
- 每一个数据集可以创建一个container，分配给某一个应用。这个应用可以是分布式应用，跑在100个，1000个节点上。
- 容器也是共享的，是逻辑上的，是分布式的。

#### pool
- pool只需要connect一次，pool-handle可以共享给其他的进程。

#### DAOS的MariaDB存储引擎
