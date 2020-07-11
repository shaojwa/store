#### 总体概述
1. Unistor 2.0 是全闪架构
1. 在RADOS-Client和OSD之间，增加了Engine层，Engine是独立进程。
1. Engine进程中实现，dcache，row，重删，压缩功能。
1. ROW就是将多个随机小IO合并成一个顺序大IO，提高写性能。

#### 功能需求
1. dse进程中，每个存储池4个engine实例，实例上的bucket数量和平均值误差在1/10以内。
1. dse进程中存在op分发模块。
1. dse进程故障后，其中的engine实例需要重新分配。dse进程故障导致业务归零时间在15秒以内。
1. 节点扩容。
1. dse进程各个engine实例中，各个流程的IO信息统计。
1. dse进程中engine实例相关调试命令。
1. UserObj的ROW支持重删压缩（写重定向，分布式RocksDB，重删，预缩）。
1. UserObj的IO操作。
1. ROW支持垃圾回收。
1. ROW故障切换与恢复

#### 问题
 
 1. dse进程故障时，engine实例的迁移，是所有的engine都会迁到一个节点上还是以实例为单位分散到不同的节点上？
 1. 一个pool对应的engine在一个节点上可能存在多个？
 1. 什么是ROW的重删。
 1. 什么是ROW的数据压缩？为什么需要数据压缩？
 1. ROW中的对象的垃圾量，有效数据是什么概念？有多少个单位被标记为垃圾？
