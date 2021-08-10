#### opproc
```
ceph daemon dse.node95 engine all dcache ctrl show_state
```

#### dm
```
ceph daemon dse.node95 engine all dcache dm help
```

#### rcache
```
ceph tell dse.* config set dcache_rc_enable true
ceph daemon dse.node95 engine all dcache dm help
ceph daemon dse.node73 engine 65539.0 perf dump rcache
```
