```
#! /bin/bash

cephfs-journal-tool journal reset
ceph mds repaired 0
systemctl reset-failed ceph-mds@mds1.service
systemctl restart ceph-mds.target
```
