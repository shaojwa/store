## stack
```
in thread 7f90b17f7700 thread_name:Processer_6

(2e4f77a994a3b9a787722ac6f5f686bc03519417) luminous (stable)
1: (()+0x8d9720) [0x5578936e1720]
2: (()+0xf6c0) [0x7f90c3fcf6c0]
3: (gsignal()+0x37) [0x7f90bd24c247]
4: (abort()+0x148) [0x7f90bd24d938]
5: (()+0x2f066) [0x7f90bd245066]
6: (()+0x2f112) [0x7f90bd245112]
7: (rcache_hash_node_t::delete_object(rcache_object_t&)+0x338) [0x557893a5f3f8]
8: (RCache::_evict_objects(boost::intrusive::list<rcache_object_t,void, ...)+0x87) [0x557893a5fdb7]
9: (RCache::_lru_cold()+0x5f5) [0x557893a60715]
10: (RCache::_enqueue_cold(boost::intrusive::list<rcache_object_t, ...)+0x3cc) [0x557893a6108c]
11: (RCache::_lru_warm()+0x67d) [0x557893a61a5d]
12: (RCache::_enqueue_warm(rcache_object_t&)+0xb7) [0x557893a63da7]
13: (RCache::rcache_write(object_t const&, snapid_t, ...)+0x298) [0x557893a6ef78]
14: (DCacheOPProc::do_sparse_read(DCacheOPProc::OpContext*, OSDOp&)+0x8cd) [0x55789396b69d]
15: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x6f6) [0x55789398eb36]
16: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x1fe) [0x55789398f2ee]
17: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x3a1c) [0x55789399327c]
18: (()+0xb9007d) [0x55789399807d]
19: (()+0x114649) [0x7f90c6614649]
20: (co::Task::Run()+0xba) [0x7f90c6614796]
21: (co::Task::StaticRun(long)+0x20) [0x7f90c6614f64]
22: (make_fcontext()+0x21) [0x7f90c66b99b1]
```

## dmesg
no error record in dmesg

## core file
```
gdb dse core-Processer_6-2344201-1617935900     (wd: /corefile)

#0  0x00007f90c3fcf58b in raise () from /lib64/libpthread.so.0
#1  0x00005578936e17ba in reraise_fatal (signum=6) at /src/global/signal_handler.cc:76
#2  handle_fatal_signal (signum=6) at /src/global/signal_handler.cc:140
#3  <signal handler called>
#4  0x00007f90bd24c247 in raise () from /lib64/libc.so.6
#5  0x00007f90bd24d938 in abort () from /lib64/libc.so.6
#6  0x00007f90bd245066 in __assert_fail_base () from /lib64/libc.so.6
#7  0x00007f90bd245112 in __assert_fail () from /lib64/libc.so.6
#8  0x0000557893a5f3f8 in iterator_to (this=0x7f8ee6a69978, value=...)
    at /build/boost/include/boost/intrusive/list.hpp:1300
#9  rcache_hash_node_t::delete_object (this=0x7f8ee6a69958, obj=...)
    at /src/dse/dcache/rcache/rcache.cc:1205
#10 0x0000557893a5fdb7 in RCache::_evict_objects (this=this@entry=0x7f8ee5800af8, objects=...)
    at /src/dse/dcache/rcache/rcache.cc:354
#11 0x0000557893a60715 in RCache::_lru_cold (this=this@entry=0x7f8ee5800af8)
    at /src/dse/dcache/rcache/rcache.cc:1019
#12 0x0000557893a6108c in RCache::_enqueue_cold (this=this@entry=0x7f8ee5800af8, objs=..., space=space@entry=3284992)
    at /src/dse/dcache/rcache/rcache.cc:984
#13 0x0000557893a61a5d in RCache::_lru_warm (this=this@entry=0x7f8ee5800af8)
    at /src/dse/dcache/rcache/rcache.cc:951
#14 0x0000557893a63da7 in RCache::_enqueue_warm (this=this@entry=0x7f8ee5800af8, obj=...)
    at /src/dse/dcache/rcache/rcache.cc:892
#15 0x0000557893a6ef78 in RCache::rcache_write (this=0x7f8ee5800af8, obj_id=..., snap_id=..., ...)
    at /src/dse/dcache/rcache/rcache.cc:248
#16 0x000055789396b69d in DCacheOPProc::do_sparse_read (this=this@entry=0x7f8ee3c00030, ctx=ctx@entry=0x7f8dcb4b6800, dse_op=...)
    at /rc/dse/dcache/opproc/opproc.cc:2781
#17 0x000055789398eb36 in DCacheOPProc::do_dse_ops (this=this@entry=0x7f8ee3c00030, ctx=ctx@entry=0x7f8dcb4b6800, ops=...)
    at /src/dse/dcache/opproc/opproc.cc:882
#18 0x000055789398f2ee in DCacheOPProc::dcache_do_op_proc (this=this@entry=0x7f8ee3c00030, ctx=ctx@entry=0x7f8dcb4b6800, ops=...)
    at /src/dse/dcache/opproc/opproc.cc:5213
#19 0x000055789399327c in DCacheOPProc::do_op_operation (this=0x7f8ee3c00030, req=...)
    at /src/dse/dcache/opproc/opproc.cc:819
#20 0x000055789399807d in operator() (__closure=<optimized out>) at /src/dse/dcache/opproc/opproc.cc:844
#21 std::_Function_handler<void(), DCacheOPProc::do_op(DSEOpRequestRef)::__lambda33>::_M_invoke(const std::_Any_data &)
    (__functor=...) at /usr/include/c++/4.8.2/functional:2071
#22 0x00007f90c6614649 in co::Task::__lambda8::operator() (__closure=0x7f8ca1105f20)
    at /Everyday_build/workspace/Everyday_build_ceph/UniStorOS-E1151-AF-ALL/Libgo/libgo/task/task.cpp:37
#23 0x00007f90c6614796 in co::Task::Run (this=0x7f8d3e751d80)
    at /Everyday_build/workspace/Everyday_build_ceph/UniStorOS-E1151-AF-ALL/Libgo/libgo/task/task.cpp:48
#24 0x00007f90c6614f64 in co::Task::StaticRun (vp=140244614978944)
    at /Everyday_build/workspace/Everyday_build_ceph/UniStorOS-E1151-AF-ALL/Libgo/libgo/task/task.cpp:79
#25 0x00007f90c66b99b1 in make_fcontext ()
    at /Everyday_build/workspace/Everyday_build_ceph/UniStorOS-E1151-AF-ALL/Libgo/libgo/context/make_x86_64_sysv_elf_gas.S:64
```
