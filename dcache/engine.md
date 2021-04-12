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
