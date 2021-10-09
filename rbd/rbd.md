## rbd 是什么
rbd是ceph中的块，基于对象存储，一个块存储池中可以有多个块设备，就是客户划分出多块磁盘（每一个块设备就像一个硬盘）
所有的虚拟硬盘的数据，放在一个池里。所有的虚拟硬盘的元数据也放在一个单独的池里。


## 查看一个池中的所有块image
```
rdb -p <pool_name> ls
```

## tgt 是什么
tgt 是一个独立的进程：


#### TGT日志
/var/log/storeage/TGT/TGT.log  # 相关块层面相关的日志，iSCSA。
/var/log/storeage/TGT/ceph-client.tgt.log ##  可以看到  retcode， tid，engine_id， base_oid

####

