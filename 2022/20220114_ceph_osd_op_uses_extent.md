#### ceph_osd_op_uses_extent
```
static inline bool ceph_osd_op_uses_extent(int op)
{
  switch(op) {
  case CEPH_OSD_OP_READ:
  case CEPH_OSD_OP_MAPEXT:
  case CEPH_OSD_OP_MASKTRUNC:
  case CEPH_OSD_OP_SPARSE_READ:
  case CEPH_OSD_OP_SYNC_READ:
  case CEPH_OSD_OP_WRITE:
  case CEPH_OSD_OP_WRITEFULL:
  case CEPH_OSD_OP_TRUNCATE:
  case CEPH_OSD_OP_ZERO:
  case CEPH_OSD_OP_APPEND:
  case CEPH_OSD_OP_TRIMTRUNC:
  case CEPH_OSD_OP_CMPEXT:
    return true;
  default:
    return false;
  }
}
```
