

#### ceph-mds收到Hangup信号时无法访问proc下某个进程的cmdline

因为发送信号的进程已经退出

#### killall 命令的一个参数是 -q 1

q参数表示不是通过kill()系统调用来发送信号，而是通过sigqueue()来发送，和kill的区别是：sigqueue多一个参数用来指定同信号一起发送的数据。
如果接收进程安装了该信号的处理函数（通过SA_SIGINFO标记调用sigaction()来安装），那么，接收进程是可以收到这个数据的。
（信号处理函数中的的第二个参数，即siginfo_t类型的参数，这个参数中的si_value字段就是调用进程传入的value值）
