## DSE threads
1. handle_engine_map  // log contains "handle_engine_map engine_map(24..24 src has 1..24) v1"
2. mid_dse_control    // log contains "shutdown engine wait / flush_engine wait / flush_engine finish
3. engine-threads
4. dcache-threads
5. row-threads
6. dedup-threads
 
## DCache threads
1. DCacheInstance inferfaces running in the dcache-processor.
2. ctrlproc-code rnnning in the dcache-processor. (init, destroy, migrate)
3. opproc-code running in the dcache-processor.
4. lsm-code running in the dcache-processor.
5. destage-code running in the dcache-processor except the callbacks like **handle_destage_post()**

## engine start
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

## engine shutdown
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

## dcache create
```
DSE::ms_dispatch()
DSE::handle_engine_map()
DSE::create_engine()
DSE::init_engine()  // new task
EngineService::init()
dcache = new DCacheInstance()
```

## dcache init
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

## dcache shutdown 
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

## destage threads
1. destage_object() // destage the specified object, running on the opproc-context
2. do_destage()     // do the destage work, on the one of specified the dcache-processor
3. delete_operation() // delete the object when the destage is done, running on the specified dcache-processor


## destage 
```
DCache_ROW_ready()
Destage::destage_start()
Destage::destate_operation() // new task
Destage::destate_objs() // new task
Destage::do_destage()
ROWInstance::ROW_dcache_flush() // callback is Destage::destage_obj_cb
```
destage_obj_cb() called in row-processor
