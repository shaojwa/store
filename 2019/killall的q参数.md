
#### killall 命令的一个参数是 -q 1

killall 和kill 的q参数含义不一样。killall 的q表示quiet。

kill的q参数表示，通过sigqueue()不是kill()系统调用来发送信号。和kill的区别是：sigqueue可以指定一个整数，随着信号一起发送给进程。
如果接收进程安装了该信号的处理函数，那么接收进程是可以收到这个数据的。（信号处理函数中的的第二个参数，即siginfo_t类型的参数，这个参数中的si_value字段就是调用进程传入的value值）
