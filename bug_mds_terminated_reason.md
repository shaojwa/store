#### 局点一个集群mds受到terminated消息

通过last命令查看，以及message消息，确认主机有重启。crond进程也在同一时刻被重启。
Terminate信号的发起进程是systemd，所以除非认为执行systemctl命令，否则很大可能性是系统触发的。
执行systemctl stop ceph-mds.target命令时，mds有日志：

    WARNING received signal: Terminated from PID: 1 task name: /usr/lib/systemd/systemd
        --switch-root --system --deserialize 22 UID: 0 
    ERROR mds.mds0 **** got signal Terminated ****
    
#### 主机reboot时/var/log/message中的日志
    
 关机时：
 
    * kernel 会有umount操作（如果需要umount）
    * systemd会有一些列的stoppiing操作
    
 启动时：
 
    * BOOT_IMAGE一般就会在前两行中打印
    
#### 主机shutdown时/var/log/message中的日志

关机时：

    * kernel  没有umount操作
    * systemd 也没有一些列的stoppiing操作 
但是 ceph-mds也会收到 SIGTERM 信号，收到后ceph-mds 自杀，最后shutdown。
    
#### 主机shutdown 0 时/var/log/message中的日志
    
 关机时：
 
    * kernel  没有umount操作
    * systemd  也没有一些列的stoppiing操作 
    
但是 ceph-mds也会收到 SIGTERM 信号，收到后ceph-mds 自杀，最后shutdown。
