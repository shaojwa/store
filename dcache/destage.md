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
