https://docs.ceph.com/en/latest/man/8/ceph/

#### ceph 服务管理
```
ceph restart ceph.target
```

#### ceph 维护命令

|用例|说明|
|:-|:-|
|ceph tell dse.* injectargs --dcache_rc_enable||
|ceph tell osd.* config set rocksdb_deletion_entries 10000000||
|ceph daemon|submit admin-socket commands.||
|ceph daemon dse.node0 engine 12.4 config set debug_engine 5||
|ceph daemon dse.node0 engine all dcache desage get_info||
|ceph daemon dse.node0 engine 12.4 dcache desage get_info||
|ceph daemon dse.node0 engine all dcache qm get_quota||
|ceph daemon dse.node0 engine 12.4 dcache qm get_quota||
|ceph daemon dse.node0 engine 12.4 config show||
|ceph daemon dse.node0 engine 12.4 config set debug_dcache 1||
|ceph daemon dse.node0 config show \| grep dcache_rc_total_quota_in_gb||
|ceph daemon dse.node0 config set dcache_rc_total_quota_in_gb 1||
|ceph daemon dse.node73 status|get status|
|ceph daemonperf dse.node73 |Watch performance counters from a Ceph daemon.|
|ceph health \[detail\] ||
|ceph df \[deatil\]||
|rados create -p .diskpool0  obj0| create object|
|rados ls -p blkpool0 | list object|
|rados stat -p blkpool0 obj0| stat object|
|rados lspools||
|rados -p blkpool0 put object_file1 file1| add object|
|rados bench -p .diskpool0.rbd 10 write -b 8192 |rados io, 10 = duration|
|rados bench -p blkpool0 10 write -b 8192 --no-cleanup |rados write|
|rados bench -p blkpool0 10 rand |rados read rand|
|rados bench -p blkpool0 10 seq |rados read seq|
|rbd \[detail\] ls -p blkpool0 |查看这个块池中的所有块设备|
|rbd du -p blkpool0 |查看这个块池中的所有块设备使用情况|


#### 注意
tell 命令可以直接用 config set 来设置config参数
```
ceph tell <name (type.id)> <command> [options…]
```
比如
```
ceph tell osd.* config set rocksdb_deletion_entries 10000000
```
