####  环境
```
chenhongzhou
2021-03-09 16:38:56.729582
182.200.70.112
```
#### 版本
7a78ea276207c4ab7d4bea08a59304e1c01f1232

#### 现象
```
 0> 2021-03-09 16:44:56.499865 7f62637f0700 2334332 18 ERROR *** Caught signal (Aborted) **
 in thread 7f62637f0700 thread_name:Processer_6

 version (7a78ea276207c4ab7d4bea08a59304e1c01f1232) luminous (stable)
 1: (()+0x85d670) [0x558ef1dc5670]
 2: (()+0xf6d0) [0x7f6558bc96d0]
 3: (gsignal()+0x37) [0x7f6551e4d277]
 4: (abort()+0x148) [0x7f6551e4e968]
 5: (ceph::__ceph_assert_fail(char const*, char const*, int, char const*)+0x185) [0x7f655b89cce5]
 6: (dm_objsnap_t::snap_write_fragment(hobject_t const&, ...)+0x36a7) [0x558ef212a407]
 7: (DataManager::dm_write_obj_data(hobject_t const&, dm_data_oper_t const&, ceph::buffer::list const&)+0x125) [0x558ef212abd5]
 8: (DCacheLineSpaceManager::lsm_recovery_write_log(char*, unsigned short, unsigned long long)+0x3ae) [0x558ef213dbce]
 9: (DCacheLineSpaceManager::lsm_do_recovery(char*, unsigned long long, unsigned long long&, unsigned long long)+0x92b) [0x558ef214871b]
 10: (DCacheLineSpaceManager::lsm_recovery_by_csdobj(CSDObjId, unsigned long long)+0x15d) [0x558ef2148efd]
 11: (DCacheLineSpaceManager::lsm_recovery_log()+0x330) [0x558ef2149c20]
 12: (DCacheInstance::DCache_start(unsigned char)+0x7e7) [0x558ef215f5e7]
 13: (EngineService::DCache_create_instance(unsigned char, init_step)+0x604) [0x558ef1b6e5e4]
 14: (()+0x113f19) [0x7f655b20df19]
 15: (co::Task::Run()+0xba) [0x7f655b20e066]
 16: (co::Task::StaticRun(long)+0x20) [0x7f655b20e80e]
 17: (make_fcontext()+0x21) [0x7f655b2a5231]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
```

#### 分析
查看日志：
```
/src/dse/dcache/dm/dm.cc: 1991: FAILED assert(data.length() >= length)
```
日志：
```
snap_write_fragment offset 0, length 90112, bl.length() 90112, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 90112, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 90112, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 90112, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 90112, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 90112, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 90112, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
snap_write_fragment offset 0, length 90112, bl.length() 24576, num of buffers in data 1
```
对比时间：
```
16:35:34.917467 7f58f2ff0700 length 90112, bl.length() 90112
16:35:41.048591 7f58f2ff0700 length 90112, bl.length() 90112
16:35:44.641932 7f58f2ff0700 length 90112, bl.length() 90112
16:35:53.034101 7f58f2ff0700 length 90112, bl.length() 90112
16:35:59.398164 7f58f2ff0700 length 90112, bl.length() 90112
16:36:06.284333 7f58f2ff0700 length 90112, bl.length() 90112
16:36:50.558904 7f58f2ff0700 length 90112, bl.length() 90112
16:37:48.660755 7fef2bff0700 length 90112, bl.length() 24576
16:38:05.769090 7faa06ff0700 length 90112, bl.length() 24576
16:38:22.256181 7f54907f0700 length 90112, bl.length() 24576
16:38:39.334633 7f7d78ff0700 length 90112, bl.length() 24576
16:38:56.495587 7f6eb97f0700 length 90112, bl.length() 24576
16:42:20.276705 7f16587f0700 length 90112, bl.length() 24576
16:42:37.389125 7f4af3ff0700 length 90112, bl.length() 24576
16:42:53.853544 7f6c94ff0700 length 90112, bl.length() 24576
16:43:11.357948 7f7587ff0700 length 90112, bl.length() 24576
16:43:29.444888 7fafa1ff0700 length 90112, bl.length() 24576
16:43:46.692692 7fadfa7f0700 length 90112, bl.length() 24576
16:44:04.261318 7fa3bd7f0700 length 90112, bl.length() 24576
16:44:21.029099 7f6706ff0700 length 90112, bl.length() 24576
16:44:38.583470 7f0dc0ff0700 length 90112, bl.length() 24576
16:44:56.242793 7f62637f0700 length 90112, bl.length() 24576
```
找出所有的因为length比较不过导致的assert，然后对比时间
```
2021-03-09 16:37:48.664273 7fef2bff0700 2270532 2 ERROR 
2021-03-09 16:38:05.772648 7faa06ff0700 2273326 21 ERROR
2021-03-09 16:38:22.260555 7f54907f0700 2276104 10 ERROR
2021-03-09 16:38:39.338521 7f7d78ff0700 2278349 11 ERROR
2021-03-09 16:38:56.499194 7f6eb97f0700 2280865 18 ERROR
2021-03-09 16:42:20.281253 7f16587f0700 2310186 26 ERROR
2021-03-09 16:42:37.392753 7f4af3ff0700 2312454 2 ERROR 
2021-03-09 16:42:53.857110 7f6c94ff0700 2315243 16 ERROR
2021-03-09 16:43:11.361955 7f7587ff0700 2317985 29 ERROR
2021-03-09 16:43:29.448497 7fafa1ff0700 2320616 2 ERROR 
2021-03-09 16:43:46.696556 7fadfa7f0700 2323427 16 ERROR
2021-03-09 16:44:04.264848 7fa3bd7f0700 2326233 29 ERROR
2021-03-09 16:44:21.032811 7f6706ff0700 2329294 23 ERROR
2021-03-09 16:44:38.587565 7f0dc0ff0700 2331614 22 ERROR
2021-03-09 16:44:56.246340 7f62637f0700 2334332 16 ERROR
```
完全一致
