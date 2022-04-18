#### osd中的关键水位
```
ceph osd dump | grep ratio
```

#### osd 使用率查看
下面这个很常用：
```
ceph osd df
```
但是居然还有这个命令
```
ceph osd df tree
```
不过`ceph osd -h`里是有的。

### 维护
|命令|功能|说明|
|:-|:-|:-|
|ceph tell osd.* injectargs --debug_osd |show value||
|ceph tell osd.0 injectargs --debug_osd 0/5 |set value||
|ceph tell osd.* config set rocksdb_deletion_entries 100000||
|ceph tell osd.* config set rocksdb_deletion_key_score 0.999||
|ceph osd lspools||
|ceph osd pool ls||
|ceph osd pool ls detail||
|ceph osd pool set .capfs.metadata.Metadata size 1|设置池的副本数为1|
|ceph osd pool set .capfs.data.datapool0 size 1|设置池的副本数为1|
|ceph osd df|OSD id，weight，size，usage，PGs|
|ceph osd dump <epoch>|某个版本的osd map|
|ceph osd perf||
|ceph osd pool stats|查看某个pool的 io|
|ceph pg dump_stuck stale|查看stale的pg|
|ceph pg <pg_id> query|查看一个pg开始scrub的时间|
|ceph daemon osd.0 dump_mempools||
|ceph tell osd.5 purge_data||
