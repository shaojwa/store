#### 现象
版本
```
6fb8e4e28eb803264994aa34f4af692d90672150
ip 182.200.64.44
time 10:45:43
yinhuiyu
```
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

#### 现象2
版本
```
220a56e364df82a768647091ad645c10c7bb7dbb
182.200.76.109
wangzhaorong
2021-03-09 12:50:43.794921
```
```
 1: (()+0x85e8d0) [0x55b6e5a108d0]
 2: (()+0xf6d0) [0x7fc932a5f6d0]
 3: (gsignal()+0x37) [0x7fc92bce3277]
 4: (abort()+0x148) [0x7fc92bce4968]
 5: (ceph::__ceph_assert_fail(char const*, char const*, int, char const*)+0x185) [0x7fc935732ce5]
 6: (DataManager::do_filling_read(hobject_t const&, snapid_t, unsigned short, unsigned long long, unsigned long long)+0x340d) [0x55b6e5d7a2ad]
 7: (()+0xbc8ba9) [0x55b6e5d7aba9]
 8: (()+0x113f19) [0x7fc9350a3f19]
 9: (co::Task::Run()+0xba) [0x7fc9350a4066]
 10: (co::Task::StaticRun(long)+0x20) [0x7fc9350a480e]
 11: (make_fcontext()+0x21) [0x7fc93513b231]
 ```

#### 原因
日志模块调用dm接口时，没有初始化hobject对象：
```
```
