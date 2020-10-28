libc里已经有strtol()，但是ceph中又实现 strict_strtol() 系列函数将string转为整数，为什么要新实现一个？

``` 
int level = (int) strict_strtol(levelstr.c_str(), 10, &err);
```
