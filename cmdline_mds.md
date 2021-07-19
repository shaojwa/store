|命令|功能|说明|
|:-|:-|:-|
|ceph mds stat|||
|ceph mds dump|||
|ceph tell mds.* respawn |||
|ceph tell mds.* injectargs --debug_mds |show value||
|ceph tell mds.0 injectargs --mds_becon_interval 10 |set value||
|ceph tell mds.* injectargs --mds_becon_interval 10 |set value||
|ceph mds dump|||
|ceph daemon mds.mds10 status|||
|ceph daemon mds.mds10 dump cache|||
|ceph daemon mds.mds10 ops|||
|ceph daemon mds.mds10 perf dump|||
|ceph daemon mds.mds10 perf dump mds_log|||
|ceph daemon mds.mds10 perf dump objecter|||
|ceph daemonperf mds.mds0 <interval>|||
|ceph daemon mds.mds10 session ls|||
|ceph daemon mds.mds10 session evict <client-id>|||
|ceph daemon mds.mds10 dirflag ls <dir>|||
|ceph daemon mds.mds10 get subtrees|查看子树||
|ceph daemon mds.mds10 export dir <dir> <rank> |查看子树||
|ceph daemon mds.mds10 get pindirs|查看静态pin||
|ceph daemon mds.mds10 set max_mds 10 |||
