#### 版本
```
6fb8e4e28eb803264994aa34f4af692d90672150
ip 182.200.64.44
time 10:45:43
yinhuiyu
```

#### 现象
```
1: (()+0x85a190) [0x5560269cc190]
2: (()+0xf6c0) [0x7f42f2b866c0]
3: (gsignal()+0x37) [0x7f42f10d1247]
4: (abort()+0x148) [0x7f42f10d2938]
5: (ceph::__ceph_assert_fail(char const*, char const*, int, char const*)+0x185) [0x7f42f5858b85]
6: (DataManager::do_filling_read(hobject_t, snapid_t, unsigned short, ...)+0x33fd) [0x556026d334fd]
7: (()+0xbc1e97) [0x556026d33e97]
8: (()+0x114159) [0x7f42f51cb159]
9: (co::Task::Run()+0xba) [0x7f42f51cb2a6]
10: (co::Task::StaticRun(long)+0x20) [0x7f42f51cba4e]
```
在日志恢复是报错
#### 原因
日志模块调用dm接口时，没有初始化hobject对象：
```
```
