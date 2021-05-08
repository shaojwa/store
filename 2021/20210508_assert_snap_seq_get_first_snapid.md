## 集群
```
hukedong上报
196.16.16.125/125/127
20210428的版本
```

## 现象
```
(gdb) bt
#0  0x00007efec977559b in raise () from /lib64/libpthread.so.0
#1  0x0000558a8b8f28da in reraise_fatal (signum=6) at /src/global/signal_handler.cc:79
#2  handle_fatal_signal (signum=6) at /src/global/signal_handler.cc:143
#3  <signal handler called>
#4  0x00007efec19dc277 in raise () from /lib64/libc.so.6
#5  0x00007efec19dd968 in abort () from /lib64/libc.so.6
#6  0x00007efecca7d055 in ceph::__ceph_assert_fail (
    assertion=assertion@entry=0x558a8be9cf50 "oper.snap_seq >= obj->get_first_snapid()",
    file=file@entry=0x558a8be9cc00 "//src/dse/dcache/dm/dm.cc", line=line@entry=179,
    func=func@entry=0x558a8be9eac0 <DataManager::dm_write_obj_data(
    hobject_t const&, dm_data_oper_t const&, ceph::buffer::list const&)::__PRETTY_FUNCTION__>
    "void DataManager::dm_write_obj_data(const hobject_t&, const dm_data_oper_t& const bufferlist&)")
    at /src/common/assert.cc:66
#7  0x0000558a8bbdae1e in DataManager::dm_write_obj_data (this=0x7efb530009a0, hobj=..., oper=..., data=...)
    at /src/dse/dcache/dm/dm.cc:179
#8  0x0000558a8bbec4eb in DCacheLineSpaceManager::lsm_recovery_write_log (
    this=0x7efb528005c0, log=<optimized out>, bucket_id=<optimized out>, log_seq=2)
    at /src/dse/dcache/lsm/lsm.cc:1383
#9  0x0000558a8bbf3005 in DCacheLineSpaceManager::lsm_do_recovery (
    this=this@entry=0x7efb528005c0, log=log@entry=0x7efb4c800010 "",
    read_size=read_size@entry=2543616, recovey_size=@0x7efdf27006c8: 0, log_seq=2)
    at /src/dse/dcache/lsm/lsm.cc:1456
#10 0x0000558a8bbf337b in DCacheLineSpaceManager::lsm_recovery_by_csdobj (
    this=this@entry=0x7efb528005c0, csd_obj_id=..., data_len=2543616, readLog=readLog@entry=0x7efb4c800010 "")
    at /src/dse/dcache/lsm/lsm.cc:1544
#11 0x0000558a8bbf3d32 in DCacheLineSpaceManager::lsm_recovery_log (this=this@entry=0x7efb528005c0)
    at /src/dse/dcache/lsm/lsm.cc:1604
#12 0x0000558a8bc027d9 in DCacheInstance::DCache_start (this=0x7efb52800010, type=type@entry=3 '\003')
    at /src/dse/dcache/dcache_init.cc:123
#13 0x0000558a8b62084c in EngineService::DCache_create_instance (
    this=0x7efdd0abcc10, create_t=<optimized out>, step=INIT_STEP_FIRST)
    at /src/dse/engine/Engine.cc:371
#14 0x00007efecc3d101d in co::Task::__lambda8::operator() (__closure=0x7efdf2700f20)
    at /Libgo/libgo/task/task.cpp:37
#15 0x00007efecc3d116a in co::Task::Run (this=0x7efdcafd36c8) at /Libgo/libgo/task/task.cpp:48
#16 0x00007efecc3d1938 in co::Task::StaticRun (vp=139628497417928) at /Libgo/libgo/task/task.cpp:79
#17 0x00007efecc476331 in make_fcontext () at //Libgo/libgo/context/make_x86_64_sysv_elf_gas.S:64
```

## 定位
```
gdb /opt/bin/dse core-Processer_5-762356-1620372143
```
assert时oper中的值：
```
(gdb) p obj
$16 = (dm_user_obj_t *) 0x7efb8e6c40c8
```
user_obj是0x7efb8e6c40c8
查看snaps：
```
(gdb) p obj->dm_snaps
...
oot_plus_size_ = {
<boost::intrusive::detail::size_holder<true, unsigned long, void>> =
{static constant_time_size = <optimized out>, size_ = 1},

m_header = {<boost::intrusive::list_node<void*>> =
{next_ = 0x7efb992748c0, prev_ = 0x7efb992748c0}, <No data fields>}}}}, <No data fields>}
```
发现其中只有一个snap，也确实 next_等于prev_，值是0x7efb992748c0。但是这个值是dm_objsnap_t中snap_item的偏移。
我们计算侵入式链表hook的地址偏移，发现snap_item的便宜事0xa0，所以我们计算出dm_objsnap_t的内存地址是：
0x7efb99274820 （= 0x7efb992748c0 - 0xa0），然后我们再次print一下：
```
(gdb) p *(dm_objsnap_t*)0x7efb99274820
$25 = {_cct = 0x7efdccc49450, dm = 0x7efb530009a0, user_obj = 0x7efb8e6c40c8, snap_seq = {val = 18446744073709551614},
truncate_size = 0, truncate_seq = 0, size = 0, mtime = {tv = {tv_sec = 0, tv_nsec = 0}}, snap_deleted = true
```
发现user_obj是0x7efb8e6c40c8，和我们之前确认的地址0x7efb8e6c40c8是一样的，所以，这个计算应该是正确的。
可以在user_obj中找dm来核对：
```
(gdb) p obj->dm
$6 (DataManager *) 0x7efb530009a0
```
可以确认dm也是对的，所以user_obj中的数据应该是对的，进一步确认得到的snap地址0x7efb99274820应该也是对的。
从snap结构，我们可以看到。这个snap是被delete，snap_seq是-2（18446744073709551614）

