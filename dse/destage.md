## 主要流程
1. destage启动流程
2. 正常刷盘流程：destage_objs()
3. DM补齐读完成之后唤醒刷盘流程：operate_filling_obj()
4. 指定bucket刷盘流程：destage_bucket()，依赖 destage_bubcket_sem。
5. 刷盘完成之后的回调流程: destage_obj_cb()


## destage的启动流程
```
EngineService::DCache_create_instance()
DCacheInstance::DCache_ROW_ready()
Destage::destage_start()
CreateTask()
destage_operation()
delete_operation()
```


## 正常刷盘流程
```
Destage::insert_obj2_view()
Destage::start_destage_task()
```


## 指定对象刷盘流程
```
destage_object() // destage the specified object, running on the opproc-context
```

## 指定bucket刷盘流程
bucket迁移的时候，调用dcache_bucket_migrate()时，调用 destage_bucket() 进行bucket刷盘。
bucket会比engine多，所以给定一个bucket集合，就主要找到所有bucket对应的刷盘试图进行刷盘。
```
EngineService::_flush_dcache_bucket()
DCacheInstance::dcache_backet_migrate()
destage_bucket()
do_destage_bucket()
view_destage_sem.up()
```
do_destage_bucket() 流程中会down掉destage_bucket_sem，而唤醒的地方有三个：
- operator_obj_in_destage_object（）指定对象刷盘流程。
- destage_obj_cb() 在刷盘完成之后的回调函数中。
- destage_objs() 在刷盘时发现是刷bucket，而且这个view中有没有所属的刷盘对象，那么就会唤醒sem。

但是，如果唤醒时，这个destage的当前状态不是DESTAGING_NORMAL，也不是DESTAGING_FORCE。


## 刷盘完成之后的回调流程
在ROW的task中：
```
ROWInstance::dcache_flush_action()
ROWOnCommit::finish()
Destage::destage_obj_cb()
```


## \[task\] 非destage模块task
插入刷盘视图的opproc线程：
```
EngineService::ms_fast_dispatch()
DCacheOPProc::do_op()
create task: DCacheOPProc::do_op_operation()
DCacheOPProc::dcache_do_op_proc()
DCacheOPProc::do_op_write_back()
DCacheOPProc::do_transaction()
insert_obj2_view()
```
刷盘完成之后的回调task：
```
ROWInstance::dcache_flush_action()
Destage::destage_obj_cb()
```

## \[task\] 两个内置task
在destage_start接口会为每个processor启动两个task，接口函数分别是：
```
destage_operation()
```
destage_operation() 等待可以下刷的对象，有对象可以刷之后，执行destage_objs()后，view_destage_sem.down()。
和
```
delete_operation()
```


## destage-operation task
调用栈
```
Destage::destate_operation()
Destage::destate_objs()
Destage::do_destage()
ROWInstance::ROW_dcache_flush() // callback is Destage::destage_obj_cb
```
destage_obj_cb() called in row-processor

依赖的sem：
```
view_destage_sem
```

唤醒方式1：正常的刷盘流程中可能唤醒刷盘task
```
insert_obj2_view() -> start_destage_task()
```

唤醒方式2： DM补齐读完成之后也可能唤醒刷盘task
```
operate_filling_obj() -> start_destage_task()
```
唤醒方式3：一次刷盘完成之后，也可能唤醒刷盘task
```
destage_ctx_cb()-> start_destage_task()
```
唤醒方式4：设置强制刷盘时去唤醒刷盘task
```
set_destage_stat() -> start_destage_task()
```
唤醒方式5：如果不是强制刷盘，而是普通刷盘，那么也可能唤醒刷盘task
```
up_all_destage_view() -> start_destage_task()
```
以上的所有方式，都是通过start_destage_task来尝试唤醒，这种方式并不每次都满足唤醒的条件，一般来说条件有三个：
- destage功能开启
- 有需要下刷的对象
- 需要下刷的数据大于启动下刷的阈值 或者 LSM占用的配额大于需要下刷的阈值

那么，还有一种情况是一定会不需要满足这些条件，就一定会马上唤醒下刷task的，那就是最后一种情况：下刷bucket
```
Destage::do_destage_bucket()
```


## delete_operation task
当对象已经完成刷盘后，从刷盘试图上移除。destage模块没设计好，deletge_operation流程应该封装为destage_view_t的接口。

流程依赖的sem
```
view_delete_sem。
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
