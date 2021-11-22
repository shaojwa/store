```
killall -q -23 ceph-mon ceph-mds ceph-osd ceph-hbm dse 
```
23 is SIGURG in `kill -l`
