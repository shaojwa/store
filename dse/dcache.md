# 设计
## dcache中LSM对象的元数据和数据怎么管理？
日志对象写入dcache池，日志对象里存储user_obj的操作（op，user_obj的元数据，user_obj的数据），让CSD收到CSDC的请求之后，cstore解决本地存储问题。
在CSD访问磁盘的开始部用来写入LSM对象的元数据。举个例子，现在全闪版本每个NVME盘都有一个独立分分区100G，给CSD用，用来作为CSD的的物理存储。
这个100G的开头部分，用来做存储元数据。

## dcache 概述
1. DCache是全闪系统的一部分，属于加速系统。
1. 聚合小IO以及启用ROW来发挥后端盘的读写能力。

## 需求规格
1. 对象以及数据的增删改查，对象以及数据信息缓存在DRAM中，32G写Cache。
1. 数据以及对象的的日志写入，对象写入DRAM的同时，以日志形式写入AEP或者SSD。
1. 从DCache下刷到后端主存，刷盘成功后才可以删日志和缓存数据。
1. 基于AEP构建分布式日志资源池。
1. 基于SSD构建分布式日志资源池。

3. 快照特性支持。用ROW完成快照回滚功能。
4. 故障切换和恢复。故障发生时，新的节点快速接管业务，故障恢复之后快速切换。
5. 支持系统扩容或缩容时业务切换。
6. 支持查缓存区与日志区的对象信息。可以检测缓存区与日志区，日志区不同副本之间数据的一致性。
7. 支持刷盘水位配置以及配额配置。
8. 支持强制刷盘。

1. 根据预取策略来将数据预取到DCache中。
1. 支持DCache内部各流程的IO信息统计，支撑挂IO问题的定位以及后续性能的优化。（CPU占用率控制在1%以内）


## DCache 线程模型
1. DCacheInstance inferfaces running in the dcache-processor.
2. ctrlproc-code rnnning in the dcache-processor. (init, destroy, migrate)
3. opproc-code running in the dcache-processor.
4. lsm-code running in the dcache-processor.
5. destage-code running in the dcache-processor except the callbacks like **handle_destage_post()**

## dcache 创建 (create)
```
DSE::ms_dispatch()
DSE::handle_engine_map()
DSE::create_engine()
DSE::init_engine()  // new task
EngineService::init()
dcache = new DCacheInstance()
```

## dcache 初始化 (init)
```
DSE::ms_dispatch()
DSE::handle_engine_map()
DSE::create_engine()
DSE::init_engine()  // new task
EngineService::init()
dcache = new DCacheInstance()
EngineService::DCache_create_instance() // in dcache task
DCacheInstance::DCache_start()
DCacheInstance::DCache_module_init()
```

## dcache 关闭 (shutdown) 
```
DSE::ms_dispatch()
DSE::handle_engine_map()
DSE::shutdown_engine() // new task, processer(1)
EngineService::shutdown()
EngineService::try_shutdown()
EngineService::_shutdown()
DCacheInstance::DCache_shutdown()
DCacheInstance::DCache_shutdown_instask() //  in dcache task
```

## 调试
#### process start
1. search **luminous**
2. search **" pid "**, pay attention of the space in 

#### engine start
```
engine.4 245 start_boot set STATE_PREBOOT
```
#### locate backtrace
search **thread_name**
