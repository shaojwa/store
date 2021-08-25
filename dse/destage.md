## destage的启动流程
```
EngineService::DCache_create_instance()
DCacheInstance::DCache_ROW_ready()
Destage::destage_start()
CreateTask()
destage_operation()
delete_operation()
```

## 调动destage的其他模块task
插入刷盘视图的opproc线程：
```
insert_obj2_view()
```

## 两个内置task
在destage_start接口会为每个processor启动两个task，接口函数分别是：
```
destage_operation()
```
destage_operation() 等待可以下刷的对象，有对象可以刷之后，执行destage_objs()后，view_destage_sem.down()。
和
```
delete_operation()
```

## destage-operation 相关
调用栈
```
Destage::destate_operation()
Destage::destate_objs()
Destage::do_destage()
ROWInstance::ROW_dcache_flush() // callback is Destage::destage_obj_cb
```
destage_obj_cb() called in row-processor

等待sem：
```
view_destage_sem
```

sem唤醒接口：
```
wakeup_destage_task()
```

唤醒方式1：
```
insert_obj2_view()
```
唤醒方式2：
```
operate_filling_obj() 
```
唤醒方式3：
```
destage_ctx_cb()
```
唤醒方式4：
```
set_destage_stat()
```
唤醒方式5：
```
up_all_destage_view()
```


## delete_operation task
当对象已经完成刷盘后，从刷盘试图上移除用。


## 其他流程
指定对象刷盘：
```
destage_object() // destage the specified object, running on the opproc-context
```

## 培训
20210812
```
destage_init()
destage_operation()
destage_start()
destage_objs()
do_destage()
destage_obj_cb()
```

##  问题
1. destage在prepare_destage的时候，不能从刷盘视图中删除，因为，删除够如果刷盘失败，那么就无法再次插入。
1. 刷盘视图中的某个对象如果刷盘失败，下一次刷盘时，还会从这个对象开始刷。
1. destage触发的时间点有两个（1）有新的对象插入（2）刷盘完成之后的回调。
1. destage的列表中，某个对象没有下刷，但是已经换过了prepare阶段，此时需要将对象再次放到队列尾部。
1. destage刷盘完成之后，设置对象的min值，此时把min值告诉LSM去删除日志对象。
