#### mdsmap osdmap 这些map存放在什么地方

rocksdb
```
ceph daemon mon.node11 config show | grep kstore_backend
```

#### 查看mon状态
```
ceph mon dump
ceph mon_status
ceph quorum_status
```

#### 主mon
```
ceph mon stat # 输出中有leader相关信息
```
