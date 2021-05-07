|模块|用例|说明|
|:-|:-|:-|
|ceph daemon |ceph daemon dse.node23 engine 12.4 config set debug_engine 5||
||ceph daemon dse.node23 engine all dcache desage get_info||
||ceph daemon dse.node23 engine 12.4 dcache desage get_info||
||ceph daemon dse.node23 engine all dcache qm get_quota||
||ceph daemon dse.node23 engine 12.4 dcache qm get_quota||
||ceph daemon dse.node23 engine 12.4 config show||
||ceph daemon dse.node23 engine 12.4 config debug_dcache 1||
||ceph daemon dse.hkd90 config show \| grep dcache_rc_total_quota_in_gb||
||ceph daemon dse.hkd90 config set dcache_rc_total_quota_in_gb 1||
|ceph osd|ceph osd lspools||
||ceph osd pool ls||
||ceph osd pool ls detail||
|ceh engine|ceph engine map||
|rados bench|rados bench -p .diskpool0.rbd 10 write -b 8192 |rados io, 10 = duration|
||rados bench -p blkpool0 10 write -b 8192 --no-cleanup |rados write|
||rados bench -p blkpool0 10 rand |rados read rand|
||rados bench -p blkpool0 10 seq |rados read seq|
|rados|rados create -p .diskpool0  obj0| create object|
||rados ls -p blkpool0 | list object|
||rados stat -p blkpool0 obj0| stat object|
||rados lspools||
||rados -p blkpool0 put object_file1 file1| add object|
