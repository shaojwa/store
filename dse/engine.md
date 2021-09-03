# 概要
 1. engine id 全集群唯一。
 1. engineClient类似osdc，在engine模块上层的service模块找。
 1. 一个engine实例目前规划四个线程。

## Engine 的多线程模型
一个engine instance 会运行在多个线程上(processor)。

## Engine 的启动
```
DSE::ms_dispatch()
DSE::handle_engine_map()
DSE::create_engine() 
DSE::init_engine() // in new task, processer(0)
EngineService::init()
// create row, dcache, dedup, compress, gc
EngineService::start_boot() 
```

log
```
grep handle_engine_map | grep "create engine" 
```

## Engine shutdown
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
