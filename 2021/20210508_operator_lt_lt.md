#### 环境
```
20210508
qinxuan
```

#### 现象
观察corefile的输出可以看到，operator<< 运算符执行有问题
```
(gdb) bt
#0  0x00007fe5e989959b in raise () from /lib64/libpthread.so.0
#1  0x000055fd7b9ad5da in reraise_fatal (signum=11) at /src/global/signal_handler.cc:79
#2  handle_fatal_signal (signum=11) at /src/global/signal_handler.cc:143
#3  <signal handler called>
#4  0x000055fd7bcd0a54 in operator<< <char, std::char_traits<char>, std::allocator<char> > (__str=..., __os=...)
    at /usr/include/c++/4.8.2/bits/basic_string.h:2758
#5  operator<< (o=..., out=...) at /src/include/object.h:76
#6  rcache_objsnap_t::write_fragment (
    this=this@entry=0x7fe024afcf68, offset=offset@entry=0, len=len@entry=1048576, bl=..., prefetch=prefetch@entry=false)
    at /src/dse/dcache/rcache/rcache.cc:1524
#7  0x000055fd7bcd15d0 in RCache::rcache_write (
    this=0x7fe18ac00cd8, obj_id=..., snap_id=..., offset=0, len=<optimized out>, bl=..., prefetch=prefetch@entry=false)
    at /src/dse/dcache/rcache/rcache.cc:249
#8  0x000055fd7bc3add5 in DCacheOPProc::do_sparse_read (
    this=this@entry=0x7fe189000048, ctx=ctx@entry=0x7fe39616cc18, dse_op=...)
    at /src/dse/dcache/opproc/opproc.cc:2847
#9  0x000055fd7bc48efe in DCacheOPProc::do_dse_ops (
    this=this@entry=0x7fe189000048, ctx=ctx@entry=0x7fe39616cc18, ops=...)
    at /src/dse/dcache/opproc/opproc.cc:801
#10 0x000055fd7bc4936f in DCacheOPProc::do_op_write_back (
    this=this@entry=0x7fe189000048, ctx=ctx@entry=0x7fe39616cc18, ops=...)
    at /src/dse/dcache/opproc/opproc.cc:1172
#11 0x000055fd7bc496ee in DCacheOPProc::dcache_do_op_proc (
    this=this@entry=0x7fe189000048, ctx=ctx@entry=0x7fe39616cc18, ops=...)
    at /src/dse/dcache/opproc/opproc.cc:5270
#12 0x000055fd7bc4b006 in DCacheOPProc::do_op_operation (this=<optimized out>, req=...)
    at /src/dse/dcache/opproc/opproc.cc:749
#13 0x000055fd7bc4cdc5 in operator() (__closure=<optimized out>)
    at /src/dse/dcache/opproc/opproc.cc:763
#14 std::_Function_handler<void(), DCacheOPProc::do_op(DSEOpRequestRef)::__lambda33>::_M_invoke(
    const std::_Any_data &) (__functor=...) at /usr/include/c++/4.8.2/functional:2071
#15 0x00007fe5ec4f7994 in co::Task::__lambda8::operator() (__closure=0x7fe214400ef0)
    at /Libgo/libgo/task/task.cpp:37
#16 0x00007fe5ec4f7b05 in co::Task::Run (this=0x7fdef45c7ed0)
    at /Libgo/libgo/task/task.cpp:48
#17 0x00007fe5ec4f8313 in co::Task::StaticRun (vp=140595559169744)
    at /Libgo/libgo/task/task.cpp:79
#18 0x00007fe5ec5c9b61 in make_fcontext ()
    at /libgo/context/make_x86_64_sysv_elf_gas.S:64
#19 0x000000000000004d in ?? ()
#20 0x0000000000000000 in ?? () 
```

#### 查看具体的值
```
(gdb) f 6
#6  rcache_objsnap_t::write_fragment (
    this=this@entry=0x7fe024afcf68, offset=offset@entry=0, len=len@entry=1048576, bl=..., prefetch=prefetch@entry=false)
    at /src/dse/dcache/rcache/rcache.cc:1524
    1524    /src/dse/dcache/rcache/rcache.cc: No such file or directory.
(gdb) p *(rcache_objsnap_t*）this
Invalid character '' in expression.
(gdb) p *(rcache_objsnap_t*)this
$1 = {void (rcache_objsnap_t * const, snapid_t, RCache *, rcache_object_t *)} 0x7fe024afcf68
(gdb) p this->user_obj
$2 = (rcache_object_t *) 0x7fe39041eda8
(gdb) p this->user_obj->obj_id
$3 = {name = {static npos = <optimized out>, _M_dataplus = {<std::allocator<char>>
      = {<__gnu_cxx::new_allocator<char>> = {<No data fields>}, <No data fields>},
      _M_p = 0x72616d68636e6562 <Address 0x72616d68636e6562 out of bounds>}}}
(gdb) f 5
#5  operator<< (o=..., out=...) at /src/include/object.h:76
      76   /src/include/object.h: No such file or directory.
(gdb) p
$4 = {name = {static npos = <optimized out>, _M_dataplus = {<std::allocator<char>> =
      {<__gnu_cxx::new_allocator<char>> = {<No data fields>}, <No data fields>},
      _M_p = 0x72616d68636e6562 <Address 0x72616d68636e6562 out of bounds>}}}
(gdb) p o
$5 = (const object_t &) @0x7fe39041edc0: {name = {static npos = <optimized out>,
    _M_dataplus = {<std::allocator<char>> = {<__gnu_cxx::new_allocator<char>> =
    {<No data fields>}, <No data fields>}, _M_p = 0x72616d68636e6562 <Address 0x72616d68636e6562 out of bounds>}}}
(gdb) p out
$6 = (std::ostream &) @0x7fe2143ffec0: <incomplete type>
(gdb) 
```

#### 初步结论
内存管理有错，string中存的数据不对。
