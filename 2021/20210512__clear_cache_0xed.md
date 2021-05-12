## time
```
20210512 14:25:03
yangwenwen
```

## corefile
```
-rw------- 1 ceph ceph 23367061504 May 12 14:26 core-Processer_4-3465938-1620800722
[root corefile]# date --date @1620800722
Wed May 12 14:25:22 CST 2021
```

## operation
```
21-05-12 14:26:05 ## root pts/3 (196.16.102.8) ## /corefile ## ceph daemon dse.yww37 engine all dcache rcache clear
```

## log stack
```
2021-05-12 14:25:03.375631 7f7d177f8700 3467757 8 ERROR *** Caught signal (Segmentation fault) **
 in thread 7f7d177f8700 thread_name:Processer_4

 ceph version 12.2.1-V100R001B51 (4e999402cd1a3f998619b907b3c616a72d67e525) luminous (stable)
 1: (()+0x66d4e0) [0x55b1f0e774e0]
 2: (()+0xf6c0) [0x7f7d2ce1c6c0]
 3: (RCache::_clear_cache()+0xed) [0x55b1f1195add]
 4: (RCache::_cmd_clear(ceph::Formatter*)+0x9) [0x55b1f11962a9]
 5: (RCache::rcache_cmd_handler(
    ceph::Formatter*, std::vector<std::string, std::allocator<std::string> >&)+0x140) [0x55b1f119c320]
 6: (DCacheInstance::DCache_cmd_handle_intask(
    ceph::Formatter*, std::vector<std::string, std::allocator<std::string> >&, sem_t&, std::string&)+0x2ff) [0x55b1f118996f]
 7: (()+0x116994) [0x7f7d2fa7a994]
 8: (co::Task::Run()+0xc9) [0x7f7d2fa7ab05]
 9: (co::Task::StaticRun(long)+0x2f) [0x7f7d2fa7b313]
 10: (make_fcontext()+0x21) [0x7f7d2fb4cb61]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
 ```
 
 ## corefile stack
 ```
Program terminated with signal 11, Segmentation fault.
#0  0x00007f7d2ce1c58b in raise () from /lib64/libpthread.so.0
Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64
elfutils-libelf-0.170-4.el7.x86_64 glibc-2.17-222.1.el7.x86_64 nspr-4.17.0-1.el7.x86_64
nss-3.34.0-4.el7.x86_64 nss-softokn-3.34.0-2.el7.x86_64 nss-softokn-freebl-3.34.0-2.el7.x86_64
nss-util-3.34.0-2.el7.x86_64 openssl-libs-1.0.2k-12.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64
(gdb) bt
#0  0x00007f7d2ce1c58b in raise () from /lib64/libpthread.so.0
#1  0x000055b1f0e7757a in reraise_fatal (signum=11) at /src/global/signal_handler.cc:79
#2  handle_fatal_signal (signum=11) at /src/global/signal_handler.cc:143
#3  <signal handler called>
#4  set_next (n=<synthetic pointer>, next=<synthetic pointer>) 
    at /build/boost/include/boost/intrusive/detail/list_node.hpp:66
#5  unlink (this_node=<synthetic pointer>)
    at /build/boost/include/boost/intrusive/circular_list_algorithms.hpp:145
#6  erase_and_dispose<boost::intrusive::detail::null_disposer> (i=..., this=0x7f7c7a000da8, disposer=...)
    at /build/boost/include/boost/intrusive/list.hpp:663
#7  erase (i=..., this=0x7f7c7a000da8) at /build/boost/include/boost/intrusive/list.hpp:585
#8  RCache::_clear_cache (this=this@entry=0x7f7c78400cc0) at /src/dse/dcache/rcache/rcache.cc:588
#9  0x000055b1f11962a9 in RCache::_cmd_clear (this=this@entry=0x7f7c78400cc0, f=f@entry=0x7f7c924f0280)\
    at /src/dse/dcache/rcache/rcache.cc:2117
#10 0x000055b1f119c320 in RCache::rcache_cmd_handler (this=this@entry=0x7f7c78400cc0, f=f@entry=0x7f7c924f0280, cmd=...)
    at /src/dse/dcache/rcache/rcache.cc:1873
#11 0x000055b1f118996f in DCacheInstance::DCache_cmd_handle_intask (
    this=0x7f7c76800000, f=0x7f7c924f0280, vec_command=..., dcache_cmd_sem=..., name=...)
    at /src/dse/dcache/dcache_init.cc:327
#12 0x00007f7d2fa7a994 in co::Task::__lambda8::operator() (__closure=0x7f7c92603ef0)
    at /Libgo/libgo/task/task.cpp:37
#13 0x00007f7d2fa7ab05 in co::Task::Run (this=0x7f7c92500400)
    at /Libgo/libgo/task/task.cpp:48
#14 0x00007f7d2fa7b313 in co::Task::StaticRun (vp=140173007389696)
    at /Libgo/libgo/task/task.cpp:79
#15 0x00007f7d2fb4cb61 in make_fcontext ()
    at /Libgo/libgo/context/make_x86_64_sysv_elf_gas.S:64
#16 0x00007f7d232d65b8 in ?? ()
#17 0x0000001200000033 in ?? ()
#18 0x000000000021ffff in ?? ()
#19 0x0000000000000000 in ?? ()
(gdb)
```

## analyze
boost/include/boost/intrusive/list.hpp:585
```
iterator erase(const_iterator i)
{ return this->erase_and_dispose(i, detail::null_disposer()); }
```
boost/include/boost/intrusive/list.hpp:663
```
node_algorithms::unlink(to_erase)
```
iterator is 
```
(gdb) p i
{static stateful_value_traits = false, members_ = {nodeptr_ = 0x7f7c3efeb3b0}}
(gdb) info locals
to_erase = 0x7f7c3efeb3b0
(gdb) p (node_ptr*)0x7f7c3efeb3b0
$4 = (boost::intrusive::list_impl<
 boost::intrusive::mhtraits<rcache_object_t, boost::intrusive::list_member_hook<void, void, void>,
 &rcache_object_t::lru_item>, unsigned long, true, void>::node_ptr *) 0x7f7c3efeb3b0
```
