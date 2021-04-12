## DCache threads
1. DCacheInstance inferfaces running in the dcache-processor.
2. ctrlproc-code rnnning in the dcache-processor. (init, destroy, migrate)
3. opproc-code running in the dcache-processor.
4. lsm-code running in the dcache-processor.
5. destage-code running in the dcache-processor except the callbacks like **handle_destage_post()**

## DM 如何处理补齐读task的销毁
DM中的task创建之后，发送请求给ROW，同步等响应，得到响应之后写入DM之后就返回，没有task的销毁。

## DM多processors实现参考
DM用到dcache中多个processors，通过hash将不同的对象处理映射到不同的task。

参考get_data_obj_info() (cstore_template.h) 代码

## dm如何处理truncate的数据一致性问题
truncate操作如何让ROW清除原有的数据。truncate之后，DM中有对元数据的维护，访问DM就知道最新元数据信息，下刷之后，在回调函数中删除DM的对象。

## 补齐读如何避免多次触发
对slab进行filling标记，每个slab在filling时加上标记，避免对同一个slab的多次filling操作。
