#### 现象

mds的日志显示的是pthread的线程好，但是不是task号

#### 分析

显示task号这个在日志中是支持的，但是值29开始支持，28并不支持。
sched_getcpu() 获取线程执行的线程。 ceph_gettid() 获取线程的tid 号。
