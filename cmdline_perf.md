#### perf dump
```
ceph daemon mds.mds10 perf dump
ceph daemon mds.mds10 perf dump mds_log
ceph daemon mds.mds10 perf dump objecter
ceph daemon dse.node73 engine 1.0 perf dump rcache
ceph daemon dse.node73 engine all perf dump rcache
```

#### daemonperf
目前这个命令只能在mds，osd等组件上使用，dcache 等不支持，这个命令会动态输出实时的性能数据。
```
ceph daemonperf osd.2
ceph daemonperf mon.node73
ceph daemonperf mgr.node73
ceph daemonperf dse.node73 // 暂时不支持
```
