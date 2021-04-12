## 概要
1. dcache是全闪系统的一部分，属于加速系统。
1. 聚合小IO以及启用ROW来发挥后端盘的读写能力。

## 需求描述
1. 对象以及数据的增删改查，对象以及数据信息缓存在DRAM中，32G写Cache。
1. 数据以及对象的的日志写入，对象写入DRAM的同时，以日志形式写入AEP或者SSD。
1. 从DCache下刷到后端主存，刷盘成功后才可以删日志和缓存数据。
1. 基于AEP构建分布式日志资源池。
1. 基于SSD构建分布式日志资源池。

1. 快照特性支持。用ROW完成快照回滚功能。
1. 故障切换和恢复。故障发生时，新的节点快速接管业务，故障恢复之后快速切换。
1. 支持系统扩容或缩容时业务切换。
1. 支持查缓存区与日志区的对象信息。可以检测缓存区与日志区，日志区不同副本之间数据的一致性。
1. 支持刷盘水位配置以及配额配置。
1. 支持强制刷盘。

1. 根据预取策略来将数据预取到DCache中。
1. 支持DCache内部各流程的IO信息统计，支撑挂IO问题的定位以及后续性能的优化。（CPU占用率控制在1%以内）

## DM 如何处理补齐读task的销毁
DM中的task创建之后，发送请求给ROW，同步等响应，得到响应之后写入DM之后就返回，没有task的销毁。

## DM多processors实现参考
DM用到dcache中多个processors，通过hash将不同的对象处理映射到不同的task。

参考get_data_obj_info() (cstore_template.h) 代码

## dm如何处理truncate的数据一致性问题
truncate操作如何让ROW清除原有的数据。truncate之后，DM中有对元数据的维护，访问DM就知道最新元数据信息，下刷之后，在回调函数中删除DM的对象。

## 补齐读如何避免多次触发
对slab进行filling标记，每个slab在filling时加上标记，避免对同一个slab的多次filling操作。

## 后续工作
1. opproc/DM/LSM 之间用同一个数据结构，do_transection在DM中做。
2. dcache中各个模块的多线程处理，对object进行hash，是的某个object只能在一个processor上处理，但是多个object可以并发。
