#### 现象
```
2021-02-20 14:52:07.217925 7f5e56570700 2197109 6 ERROR *** Caught signal (Aborted) **
 in thread 7f5e56570700 thread_name:Processer_4

1: (()+0x4e7930) [0x558d8dc18930]
2: (()+0xf6d0) [0x7f5e625a26d0]
3: (gsignal()+0x37) [0x7f5e60d1d277]
4: (abort()+0x148) [0x7f5e60d1e968]
5: (()+0x2f096) [0x7f5e60d16096]
6: (()+0x2f142) [0x7f5e60d16142]
7: (RCache::_enqueue_warm(rcache_object_t&)+0x2f4) [0x7f5e64dd2554]
8: (RCache::rcache_write(object_t const&, ...)+0x192) [0x7f5e64ddb652]
9: (DCacheOPProc::do_read(OSDOp&, DCacheOPProc::OpContext*)+0xe8f) [0x7f5e64d22c0f]
10: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x949) [0x7f5e64d28ef9]
11: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x1fe) [0x7f5e64d2945e]
12: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x2d17) [0x7f5e64d2c6e7]
```
#### 定位
```
[root@node2 ceph]# nm /opt/h3c/lib/libdcache.so | c++filt | grep RCache::_enqueue_warm
000000000071c260 T RCache::_enqueue_warm(rcache_object_t&)

[root@node2 ceph]# objdump -lS --start-address=0x71c260 --stop-address=0x71d260 /path/to/libdcache.so | c++filt > _enqueue_warm.s
```
其中 `_enqueue_warm.s` 中 71c554的代码是：
```
/src/dse/dcache/rcache/rcache.cc:832
  71c554:       e8 d7 05 db ff          callq  4ccb30 <__stack_chk_fail@plt>
```
看到这个，stack check似乎意味着，这个函数有循环调用？通过 `_enqueue_warm()` 内部的函数再次调用`_enqueue_warm()`。

```
dse.engine.6.6.log:2021-02-20 14:52:07.209245 7f5e56570700 2197109 6 DEBUG dcache_rcache:rcache_writercache_write 
    obj obj_file4m1, snap_idhead, prefetch 0, off 0, len 4194304, align_from 0, algin_to 4194304, align_len 4194304
```
但是很明显，_enqueue_warm中并没有调用`__stack_chk_fail()`，那么是谁调用的？
看起来，这个是gcc添加的，在函数_enqueue_warm()的开头，添加：
```
mov    %fs:0x28,%rax
mov    %rax,0x128(%rsp)
```
在函数结束时添加：
```
71c54c: mov    0x128(%rsp),%rax
71c554: xor    %fs:0x28,%rax
71c55d: jne    71c794 <RCache::_enqueue_warm(rcache_object_t&)+0x2f4>
...
71c794: callq  4ccb30 <__stack_chk_fail@plt> 
```
这代码的意思是，`0x128(%rsp)`的值和`%fs:0x28`比较进行比较，如果不不相等，则跳转到`__stack_chk_fail`。

但是为什么这个值会改变呢？
