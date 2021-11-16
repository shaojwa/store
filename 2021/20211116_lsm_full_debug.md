写入LSM的日志序号查询：
```
cat ceph-dse.engine | grp "begin, obj_id: \[CSDObjId"
```
释放LSM的日志
```
cat ceph-dse.engine | release_destaged_log_map | grep log_seq
```
查询LSM的引用计数：
```
cat ceph-dse.engine | grep -a "log_map\["
```
