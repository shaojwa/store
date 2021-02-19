|模块|用例|说明|
|:-|:-|:-|
|rados bench|rados bench -p .diskpool0.rbd 10 write -b 8192 |rados io, 10 = duration|
||rados bench -p blkpool0 10 write -b 8192 --no-cleanup ||
||rados bench -p .diskpool0.rbd 10 write -b 8192 --no-cleanup ||
||rados bench -p blkpool1 10 write -b 8192 --no-cleanup ||
||rados bench -p .diskpool0.rbd 10 seq ||
|rados|rados create -p .diskpool0  obj0| create object|
||rados ls -p .diskpool0 | list object|
||rados stat -p .diskpool0 obj0| stat object|
||rados lspools||
|ceph daemon |ceph daemon dse.node23 engine 12.4 config set debug_engine 5||
||ceph daemon dse.node23 engine all dcache desage get_info||
||ceph daemon dse.node23 engine 12.4 dcache desage get_info||
||ceph daemon dse.node23 engine all dcache qm get_quota||
||ceph daemon dse.node23 engine 12.4 dcache qm get_quota||
|ceph osd|ceph osd lspools||
||ceph osd pool ls||
||ceph osd pool ls detail||
|ceh engine|ceph engine map||
