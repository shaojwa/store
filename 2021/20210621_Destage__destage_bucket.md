#### 现象
```
(gdb) bt
#0  0x00007f370741159b in raise () from /lib64/libpthread.so.0
#1  0x000055fef25934da in reraise_fatal (signum=11) at /src/global/signal_handler.cc:79
#2  handle_fatal_signal (signum=11) at /src/global/signal_handler.cc:143
#3  <signal handler called>
#4  0x000055fef2859fd9 in operator() (this=<optimized out>, __den=<optimized out>, __num=<optimized out>)
  at /usr/include/c++/4.8.2/bits/hashtable_policy.h:345
#5  _M_bucket_index (this=<optimized out>, __n=<optimized out>, __c=<optimized out>)
  at /usr/include/c++/4.8.2/bits/hashtable_policy.h:1023
#6  _M_bucket_index (this=<optimized out>, __k=<optimized out>, __c=<optimized out>)
  at /usr/include/c++/4.8.2/bits/hashtable.h:593
#7  _M_insert<unsigned short const&> (__v=<optimized out>, this=<optimized out>)
  at /usr/include/c++/4.8.2/bits/hashtable.h:1419
#8  insert (__v=<optimized out>, this=<optimized out>)
  at /usr/include/c++/4.8.2/bits/hashtable_policy.h:604
#9  insert (__x=@0x7f32c1db4c2a: 8103, this=0x70)
  at /usr/include/c++/4.8.2/bits/unordered_set.h:345
#10 Destage::destage_bucket (this=this@entry=0x7f36a7047180, bucket_ids=...)
  at /src/dse/dcache/destage/destage.cc:1236
#11 0x000055fef28b36e7 in DCacheInstance::DCache_bucket_migrate (this=0x7f36a7047000, bucket_ids=...)
  at /src/dse/dcache/dcache_init.cc:191
#12 0x000055fef22456c1 in EngineService::_flush_dcache_bucket (this=0x7f368728f000, bucket_set=...)
  at /src/dse/engine/Engine.cc:1709
#13 0x000055fef2245ae4 in operator() (__closure=0x7f32d0c02640)
  at /src/dse/engine/Engine.cc:1756
#14 std::_Function_handler<void(), EngineService::_flush_bucket(
  std::unordered_set<bucket_t>)::__lambda47>::_M_invoke(const std::_Any_data &) (__functor=...)
  at /usr/include/c++/4.8.2/functional:2071
#15 0x00007f370a562d6c in co::Task::__lambda8::operator() (__closure=0x7f36d7c16ef0)
  at /Libgo/libgo/task/task.cpp:37
#16 0x00007f370a562edd in co::Task::Run (this=0x7f36b8fc2800)
  at /Libgo/libgo/task/task.cpp:48
#17 0x00007f370a56371f in co::Task::StaticRun (vp=139873008494592)
  at /Libgo/libgo/task/task.cpp:79
#18 0x00007f370a6540c1 in make_fcontext ()
  at /Libgo/libgo/context/make_x86_64_sysv_elf_gas.S:64
#19 0x000000000000004d in ?? ()
#20 0x0000000000000000 in ?? ()
(gdb)
```
