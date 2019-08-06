#### 局点一个集群mds受到terminated消息

通过last命令查看，以及message消息，确认主机有重启。crond进程也在同一时刻被重启。
Terminate信号的发起进程是systemd，所以除非认为执行systemctl命令，否则很大可能性是系统触发的。
执行systemctl stop ceph-mds.target命令时，mds有日志：

    WARNING received signal: Terminated from PID: 1 task name: /usr/lib/systemd/systemd --switch-root --system --deserialize11 UID: 0 
    ERROR mds.mds0 **** got signal Terminated ****
