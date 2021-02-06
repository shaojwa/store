|模块|用例|说明|
|:-|:-|:-|
|rados|rados -p 1 bench 1200 write -b 8192  |rados io|
||rados -p .diskpool0 create obj0| create object|
||rados -p .diskpool0 ls| list object|
||rados -p .diskpool0 stat obj0| lis object|
|ceph daemon |ceph daemon dse.node23 engine 12.4 config set debug_engine 5||
||ceph daemon dse.node23 engine all dcache desage get_info||
||ceph daemon dse.node23 engine 12.4 dcache desage get_info||
||ceph daemon dse.node23 engine all dcache qm get_quota||
||ceph daemon dse.node23 engine 12.4 dcache qm get_quota||
|ceph osd|ceph osd lspools||
||ceph osd pool ls||
||ceph osd pool ls detail||
|ceh engine|ceph engine map||
