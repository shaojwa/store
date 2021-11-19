#### 流程
```
LSM->
CSDC(生MCSDCOp)->
Build Session->
send_op
```

#### CSDC的对外接口
```
csdc_obj_write()
ocdc_obj_read()
csdc_obj_delete()
csdc_obh_get_size() // 获取固定engine 和pool的所有数据对象的元数
csdc_get_pgs() // 获取所有的PG
```
