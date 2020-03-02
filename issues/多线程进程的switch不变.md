多线程进程的`/proc/<pid>/switch` 不代表这个进程下所有的线程switch之和，而是主线程的switch。  
也就是说，是pid这个task的switch，和这个进程下的其他线程无关。比如ceph-mds的进程是1234。  
那么  `cat /proc/1234/sched | grep switch` 并没有什么变化，应该取查看ms_dispatch线程的数据。  
