# 功能规格

## Engine 的多线程模型
一个engine instance 会运行在多个线程上(processor)。

## Engine的创建
DSE 进程在处理enginemap的时候，创建engine。
```
DSE::ms_dispatch()
DSE::handle_engine_map()
DSE::handle_each_enginemap()
DSE::create_engine() 
DSE::init_engine() // in new task, processer(0)
EngineService::init()
// create row, dcache, dedup, compress, gc
EngineService::start_boot() 
```
日志查找：
```
grep handle_engine_map | grep "create engine" 
```

## Engine 关闭
```
DSE::ms_dispatch()
DSE::handle_engine_map()
DSE::shutdown_engine() // new task, processer(1)
DSE::delete_engine() // new task, processer(1)
```

log
```
grep handle_engine_map | grep "destroy engine" 
```

## engine_create_state: migrate_new

## engine_create_state: broken_new

## 一个引擎中的 one engine
16

## engine id 构成
pool_id + seq_num，整个集群唯一。

## engine client
engine_lient类似osdc，在engine模块上层的service模块找。
