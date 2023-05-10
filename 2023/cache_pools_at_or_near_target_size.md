```
1 cache pools at or near target size

[SDS_Admin@z-141 ~]$ ceph osd pool get cache..capfs.data.nfs target_max_bytes
target_max_bytes: 322122547200
[SDS_Admin@z-141 ~]$ ceph osd pool set cache..capfs.data.nfs target_max_bytes $((512*1024*1024*1024))
set pool 3 target_max_bytes to 549755813888
```
