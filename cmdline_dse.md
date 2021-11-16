#### dse
```
ceph daemon dse.node73 status
```

#### engine
```
ceph engine map
ceph engine ls
ceph engine dump [epoch_id]
ceph engine dump 390
ceph engine dump [epoch_id] | grep modify  # 查看 modify 信息
```

#### opproc
```
ceph daemon dse.node95 engine all dcache ctrl show_state
ceph daemon dse.node95 engine all dcache ctrl set_back
```

#### dm
```
ceph daemon dse.node95 engine all dcache dm help
```

#### rcache
```
ceph tell dse.* config set dcache_rc_enable true // 只能设置dse的上下文而不能设置某个engine的上下文
ceph daemon dse.node95 engine all dcache dm help
ceph daemon dse.node73 engine 65539.0 perf dump rcache
```

#### csd
```
ceph tell osd.5 purge_data
```
