用 strace跟中vdbench时，一定要加上-f参数，这样才能捕捉到数据，因为vdbench正常工作的线程都是fork出来的线程，所以需要追踪。
```
strace -tt -f -e pread64,pwrite64 -p 31945
```
