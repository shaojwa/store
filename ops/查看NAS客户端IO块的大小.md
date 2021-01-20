
#### 如何查看NAS客户端IO块的大小

用strace跟踪看下：

##  跟踪vdbench的xfersize, 2097152 是IO大小，12582912是偏移量
```
$ strace -tt -T -f -e trace=pwrite64 -p 1500232
[pid 1500856] 15:45:22.077391 pwrite64(19, "\0\f\...\236I\17~"..., 2097152, 12582912 <unfinished ...>
[pid 1500879] 15:45:22.094193 <... pwrite64 resumed> ) = 2097152 <1.576809>
```
如果vdbench的openflags是directio，那么所有的请求是串行的。
