#### plat-leader 调用rcache stat的频率
15分钟一次


#### engine 启动标记
```
set_module_processer
```

#### Engine init标记
```
EngineServier::init
```
engine起来的在engine中的日志第一行是
```
create objecter
```

#### engine_id 
有的地方是16进制，有的是10进制，需要注意，用engine_t的是16进制。

#### 一个dse中的所有engine
handle_engine_map中的
```
dout(1) << __func__ << “ ip:” << host_ip << “ engines:” << enginemap->get_host_engines(host_ip) << endl;
```

#### engine 开始shutdown
```
shutdown_engine wait
DCache_shutdown
```

#### lsm timeout 
失败后重试，如果一直失败就说明CSD那边有问题

#### nspace
只有对象存储的时候需要用，文件和块不需要。
同样shard_id的对象，执行删除对象的线程也是通过shard_index进行hash
