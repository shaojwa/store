#### 现象
```
 ceph version 12.2.1-UniStorOS_V100R001B51 (65dcb248a7caf71c1b28196dbc7d1d7cf3fc399f) luminous (stable)
 1: (()+0x4e5c30) [0x56476bb89c30]
 2: (()+0xf6d0) [0x7f2ce87f66d0]
 3: (RCache::rcache_evict_object(object_t const&)+0x26b) [0x7f2ceb02c2db]
 4: (DCacheOPProc::do_all_op_through(DCacheOPProc::OpContext*)+0xd6) [0x7f2ceaf3ec26]
 5: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x243) [0x7f2ceaf7d2a3]
 6: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x2d17) [0x7f2ceaf804e7]
 7: (()+0x67a11d) [0x7f2ceaf8411d]
 8: (()+0x114159) [0x7f2cec49c159]
 9: (co::Task::Run()+0xba) [0x7f2cec49c2a6]
 10: (co::Task::StaticRun(long)+0x20) [0x7f2cec49ca4e]
 11: (make_fcontext()+0x21) [0x7f2cec533471]
```

#### 分析
```
[root@qat154 wsh]# nm libdcache.so | grep rcache_evict_object | c++filt
00000000014bf140 b __gcov0._ZN6RCache19rcache_evict_objectERK8object_t
00000000011ef540 d __gcov_._ZN6RCache19rcache_evict_objectERK8object_t
0000000000722070 T RCache::rcache_evict_object(object_t const&)
00000000011e0690 d RCache::rcache_evict_object(object_t const&)::_log_exp_length
00000000011e0688 d RCache::rcache_evict_object(object_t const&)::_log_exp_length
0000000000d05ed0 r RCache::rcache_evict_object(object_t const&)::__func__
```

#### 代码：
```
/home/dcache/rcache/rcache.cc:377
  7222d8:       48 8b 03                mov    (%rbx),%rax
  7222db:       48 8b 78 08             mov    0x8(%rax),%rdi
  7222df:       80 bf 48 06 00 00 00    cmpb   $0x0,0x648(%rdi)
  7222e6:       0f 84 f4 fd ff ff       je     7220e0 <RCache::rcache_evict_object(object_t const&)+0x70>
/home/dcache/rcache/rcache.cc:377 (discriminator 1)
  7222ec:       48 81 c7 88 01 00 00    add    $0x188,%rdi
  7222f3:       ba 03 00 00 00          mov    $0x3,%edx
  7222f8:       be 3f 00 00 00          mov    $0x3f,%esi
```
