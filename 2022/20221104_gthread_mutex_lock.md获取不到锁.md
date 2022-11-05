```
(gdb) bt
#0  0x00007f8fdb4f254d in __lll_lock_wait () from /lib64/libpthread.so.0
#1  0x00007f8fdb4ede9b in _L_lock_883 () from /lib64/libpthread.so.0
#2  0x00007f8fdb4edd68 in pthread_mutex_lock () from /lib64/libpthread.so.0
#3  0x000055d83ab68ab3 in __gthread_mutex_lock (__mutex=0x7f88e4f852a8) at /usr/include/c++/4.8.2/x86_64-redhat-linux/bits/gthr-default.h:748
#4  lock (this=0x7f88e4f852a8) at /usr/include/c++/4.8.2/mutex:134
#5  lock_guard (__m=..., this=<synthetic pointer>) at /usr/include/c++/4.8.2/mutex:414
#6  DseFS::open_for_read (this=0x7f88e4f85000, dirname=..., filename=..., h=h@entry=0x7f81734bec10, random=random@entry=true)
```
