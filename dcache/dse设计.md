#### 总体概述
1. Unistor 2.0 是全闪架构
1. 在RADOS-Client和OSD之间，增加了DSE层，DSE是独立进程。
1. DSE进程中实现，dcache，row，重删，压缩功能。
1. ROW就是将多个随机小IO合并成一个顺序大IO，提高写性能。

#### 系统
1. 通过dse达到集群拓扑管理（节点增删，存储池增删）
1. dse进程中，每个存储池4个engine实例（engine拓扑管理）
1. dse中的bucket分布（数据路由，路由到正确的engine上），实例上的bucket数量和平均值偏差在1/10以内。
1. dse进程中存在op分发模块，对象op路由到指定的engine上进行处理。
1. dse进程故障处理（节点故障，或者进程重启，触发engine实例切换），其中的engine实例需要重新分配，dse进程故障导致业务归零时间在15秒以内。
1. 节点扩容，新节点上创建engine，触发部分bucket迁移到新的engine上。
1. dse进程各个engine实例中，各个流程的IO信息统计，调试命令。
----
1. 聚合IO重定向写（比如刷盘写，透写等）。
1. UserObj的ROW支持重删压缩（重删，压缩，分布式RocksDB），RocksDB记录写产生的元数据的记录到RocksDB，RocksDB 有专门的元数据池。
1. UserObj的IO操作（支持所有OP，性能优化）。
----
1. ROW支持垃圾回收（垃圾回收，垃圾合并，回收对象选择，有效数据识别，有效数据转移，垃圾回收流控）。
1. ROW故障切换与回切。
1. ROW扩容。（部分数据会有新的engine来处理，此时就需要考虑一致性问题）
1. ROW内部个流程的IO信息统计。
1. ROW调试定位命令（UserObj元数据查询，attr，omap，快照上下文信息，到RowObj的映射查关系查询）。
----
1. 快照读写回滚支持。ROW必然支持快照，DCache支持么？ROW支持读取某个时间点的对象快照创建。
----
1. 部署、升级。
1. IPv4和IPv6支持。

#### 功能

1. dse中engine的部署，触发条件包括节点的增减，还包括存储池的增减。
1. engine的故障切换，是指框架部分的业务处理，不包括dcache，ROW，dedup等子模块的处理。

#### 问题
 
 1. dse进程故障时，engine实例的迁移，是所有的engine都会迁到一个节点上还是以实例为单位分散到不同的节点上？
 1. 一个pool对应的engine在一个节点上可能存在多个？
 1. pool和engine是多对多的映射关系？
 1. 什么是ROW的重删？去重么？
 1. 什么是ROW的数据压缩？为什么需要数据压缩？
 1. 删除，压缩都是针对写的？
 1. ROW中的对象的垃圾量，有效数据是什么概念？有多少个单位被标记为垃圾？
 1. ROW必然支持快照，DCache支持么？
 1. 大快照时候的逻辑对象是指什么？ 是UserObj而不是RowObj的意思吧？
 1. UserObj的数据，attr，omap的信息存储如何实现？
 1. 什么是ROCKDB compaction流程？
 1. 将需要处理的IO按照访问区域进行空间隔离，保证多线程间访问的区域相互隔离而不会产生冲突。怎么做到？
 
 #### 说明
 1. UserObject Hash 到 bucket(类似于PG)， bucket 再通过类似CRUSh映射到engine（类似于OSD），节点增加后，部分bucket就会映射到新的engine。
 1. engine id 全集群唯一。
 1. engineClient类似osdc，在engine模块上层的service模块找。
 1. 一个engine实例目前规划四个线程。
