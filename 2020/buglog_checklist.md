|收集项|满足以下条件时，请帮助收集对应日志|描述|
|:-|:-|:-|:-|
|主要现象描述  | 必填 ||
|测试类型  | 必填 |鉴定测试 or 回归测试（包括预鉴定） or 功能测试（比如热补丁测试） or 拷机测试 or 其他|
|问题性质  | 必填 |是测试点本身不过 还是 测试过程中新发现的问题|
|问题出现时间  | 必填 |描述出问题的大概时间|
|问题出现时跑什么业务| 必填 |请尽量详细描述下业务模型以及工具|
|问题出现前后操作描述| 必填 |描述出问题前后进行的操作，结合 /var/log/operation/下日志|
|出问题前后handy上的相关告警和日志| 必填 | 和问题关系紧密的日志|
|internel 版本| 必填 |执行 cat /etc/onestor_internal_version|
|externel 版本| 必填 |执行 cat /etc/onestor_external_version|
|相关节点内核版本| 必填 |执行 uname -a|
|ceph.log|必填| 路径 /var/log/ceph|
|出问题前的active mds是什么| 必填 ||
|出问题后的active mds是什么| 必填 ||
|active MDS日志| 必填|mds damaged，filesystem read only，session异常等，只需要收集出问题时间前一小时|
|osd 池信息| 必填 |执行 ceph osd pool ls detail|
|是否稳定复现  | 选填 | |
|operation log| 选填 | 操作节点每个节点 /var/log/operation/下日志|
|mds侧inode信息| 涉及文件读写异常，业务掉0 |ceph daemon mds.mds1 dump inode 1099511627777 > dump_inode.log|
|mds侧revoke cap 信息| 问题涉及文件读写异常，业务掉0|ceph daemon mds.mds1 dump revoking caps > revoking_caps.log|
|mds发给osd的op| 出现slow request，业务掉0，ls卡住等| ceph daemon mds.mds1 objecter_requests|
|mds自身处理的op| 出现slow request，业务掉0，ls卡住等 |ceph daemon mds.mds1 dump_historic_ops （最近600秒的op）|
|mds自身处理的op| 出现slow request，业务掉0，ls卡住等 |ceph daemon mds.mds1 dump_blocked_ops （延时30秒以上的op）|
|NAS 机头ops信息| 出现nfsd异常，业务掉0||
|nfsd 进程号| 出现nfsd异常，业务掉0||
|nfsd 进程状态| 出现nfsd异常，业务掉0||
|nfsd 进程堆栈| 出现进程卡住，业务掉0||
