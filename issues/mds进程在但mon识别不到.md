### 现象

ceph mds stat 或者 ceph fs status 卡主。
在其他节点上执行 ceph osd tree 发现本节点 osd全down。
ceph mds 命令超时之后报错是：

A2019-10-22 10:54:24.596933 7f262099d700 WARNING monclient(hunting): authenticate timed out after 75
2019-10-22 10:54:24.596968 7f262099d700 WARNING librados: client.admin authentication error (110) Connection timed out
[errno 110] error connecting to the cluster

### 定位
 
重启ceph-mds，发现，mds能起来，但是日志很少。pstack发现用户态栈都很少。ceph-mds下的线程数只有14个。
最后一条日志是：2019-10-22 10:52:55.430077 7f1e6f325340 WARNING pidfile_write: ignore empty --pid-file
正常情况下是handle_mds_map，所以看起来可能是消息没收到。

### ping 节点
ping一下发现，public_addr下的其他节点不通。但是网络配置没问题，想起之前网线连到ilo上。

### 总结

看日志是超时，所以应该先看网络，都不是盲目重启ceph-mds。
