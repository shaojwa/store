## jobs


## ioengine
### rados
using librados, direct access to Ceph Reliable Autonomic Distributed Object Store.

### rbd
using librbd, direct access to Ceph Rados Block Devices whitout the need to use the kernel rbd driver. the kernel rbd driver is placed at
```
/lib/modules/<kernel-version>/kernel/drives/block/rbd.so
```
like kernel-cephfs at
```
/lib/modules/<kernel-version>/kernel/fs/ceph/ceph.ko
```
comparing with the user-space lib at
```
/opt/xxx/lib/librdb.so
/opt/xxx/lib/libcephfs.so
```
and the rados lib at
```
/opt/xxx/lib/librados.so
```




