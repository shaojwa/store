

#### ceph-mds收到Hangup信号时无法访问proc下某个进程的cmdline

因为发送信号的进程已经退出

#### killall 命令的一个参数是 -q 1

q参数表示不是通过kill()系统调用来发送信号，而是通过sigqueu()来发送，和kill的区别是：
