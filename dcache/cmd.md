```
rados bench -p 1 1200 write -b 8192 
```

```
ceph daemon dse.node23 engine 12.4 congit set debug_engine 5
```

```
ceph daemon dse.node23 engine all dcache desage get_info
ceph daemon dse.node23 engine 12.4 dcache desage get_info

ceph daemon dse.node23 engine all dcache qm get_quota
ceph daemon dse.node23 engine 12.4 dcache qm get_quota
```
