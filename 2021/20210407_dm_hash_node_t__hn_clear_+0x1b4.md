## time
2021-04-07 hukedong, delete the node from the handy at 04-07 15:21-19/15:23:20

## stack
```
2021-04-07 15:23:05.235508 7fbe873f9700 1945207 6 ERROR *** Caught signal (Aborted) **
 in thread 7fbe873f9700 thread_name:Processer_4

(680169bf53081fcd66baf022f22d7fd3f54ce07a) luminous (stable)
 1: (()+0x8d03d0) [0x5632f48d93d0]
 2: (()+0xf6d0) [0x7fbe9888e6d0]
 3: (gsignal()+0x37) [0x7fbe91b0c277]
 4: (abort()+0x148) [0x7fbe91b0d968]
 5: (()+0x2f096) [0x7fbe91b05096]
 6: (()+0x2f142) [0x7fbe91b05142]
 7: (()+0xbd52a8) [0x5632f4bde2a8]
 8: (dm_hash_node_t::hn_clear()+0x1b4) [0x5632f4be3f64]
 9: (dm_hash_table_t::ht_clear()+0x56) [0x5632f4be4066]
 10: (DataManager::dm_shutdown()+0xa0) [0x5632f4be4310]
 11: (DCacheInstance::DCache_shutdown_intask(co::CoSem&, bool&)+0xdf) [0x5632f4c4115f]
 12: (()+0xc392df) [0x5632f4c422df]
 13: (()+0x114649) [0x7fbe9aed3649]
 14: (co::Task::Run()+0xba) [0x7fbe9aed3796]
 15: (co::Task::StaticRun(long)+0x20) [0x7fbe9aed3f64]
 16: (make_fcontext()+0x21) [0x7fbe9af78981]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
```

## tid
1945207

## thread_id
7fbe873f9700

## engine shutdown DCache
```
ceph-dse.engine.3.c.log-2021-04-07-154121:2021-04-07 15:23:04.305245 7fbe843f3700
    1945213 17  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
ceph-dse.engine.3.d.log-2021-04-07-154121:2021-04-07 15:23:04.305254 7fbe83bf2700
    1945214 1  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
ceph-dse.engine.3.e.log-2021-04-07-154121:2021-04-07 15:23:04.305272 7fbe833f1700
    1945215 23  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
ceph-dse.engine.3.f.log-2021-04-07-154121:2021-04-07 15:23:04.305289 7fbe82bf0700
    1945216 5  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
ceph-dse.engine.6.c.log-2021-04-07-154121:2021-04-07 15:23:04.305310 7fbe823ef700
    1945217 2  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
ceph-dse.engine.6.d.log-2021-04-07-154121:2021-04-07 15:23:04.305374 7fbe81bee700
    1945218 18  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
ceph-dse.engine.6.f.log-2021-04-07-154121:2021-04-07 15:23:04.305486 7fbe80bec700
    1945220 1  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
```
## dcache to shutdown
```
ceph-dse.engine.3.c.log-2021-04-07-154121:2021-04-07 15:23:04.305344 7fbe873f9700
    1945207 6  INFO Dcache_opproc:  begin to destroy opproc
ceph-dse.engine.3.f.log-2021-04-07-154121:2021-04-07 15:23:04.306785 7fbe873f9700
    1945207 7  INFO Dcache_opproc:  begin to destroy opproc
ceph-dse.engine.6.c.log-2021-04-07-154121:2021-04-07 15:23:04.306777 7fbe873f9700
    1945207 7  INFO Dcache_opproc:  begin to destroy opproc
ceph-dse.engine.6.f.log-2021-04-07-154121:2021-04-07 15:23:04.307817 7fbe873f9700
    1945207 7  INFO Dcache_opproc:  begin to destroy opproc
```

## which engine cause the fault
ceph-dse.engine.6.f.log in which there is no "dm shutdown OK"

## core file
```

Program terminated with signal 6, Aborted.
#0  0x00007fbe9888e59b in raise () from /lib64/libpthread.so.0
Missing separate debuginfos, use: 
debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 elfutils-libelf-0.170-4.el7.x86_64
glibc-2.17-222.el7.x86_64 nspr-4.17.0-1.el7.x86_64 nss-3.34.0-4.el7.x86_64
nss-softokn-3.34.0-2.el7.x86_64 nss-softokn-freebl-3.34.0-2.el7.x86_64
nss-util-3.34.0-2.el7.x86_64 openssl-libs-1.0.2k-12.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64
(gdb) bt
#0  0x00007fbe9888e59b in raise () from /lib64/libpthread.so.0
#1  0x00005632f48d946a in reraise_fatal (signum=6) at /src/global/signal_handler.cc:76
#2  handle_fatal_signal (signum=6) at /src/global/signal_handler.cc:140
#3  <signal handler called>
#4  0x00007fbe91b0c277 in raise () from /lib64/libc.so.6
#5  0x00007fbe91b0d968 in abort () from /lib64/libc.so.6
#6  0x00007fbe91b05096 in __assert_fail_base () from /lib64/libc.so.6
#7  0x00007fbe91b05142 in __assert_fail () from /lib64/libc.so.6
#8  0x00005632f4bde2a8 in boost::intrusive::detail::destructor_impl<boost::intrusive::generic_hook<(boost::intrusive::algo_types)0, boost::intrusive::list_node_traits<void*>, bo                          ost::intrusive::member_tag, (boost::intrusive::link_mode_type)1, (boost::intrusive::base_hook_type)0> > (hook=...)
    at /build/boost/include/boost/intrusive/detail/generic_hook.hpp:48
#9  0x00005632f4be3f64 in ~generic_hook (this=0x7fbe8b7e1a18, __in_chrg=<optimized out>)
    at /build/boost/include/boost/intrusive/detail/generic_hook.hpp:192
#10 ~list_member_hook (this=0x7fbe8b7e1a18, __in_chrg=<optimized out>)
    at /build/boost/include/boost/intrusive/list_hook.hpp:207
#11 ~destage_obj_t (this=0x7fbe8b7e1a08, __in_chrg=<optimized out>)
    at /src/dse/dcache/destage/destage.h:82
#12 ~dm_user_obj_t (this=0x7fbe8b7e1a00, __in_chrg=<optimized out>) at /src/dse/dcache/dm/dm.h:295
#13 operator() (this=<optimized out>, obj=0x7fbe8b7e1a00) at /src/dse/dcache/dm/dm.h:369
#14 erase_and_dispose<dm_hash_node_t::delete_dm_obj_t> (i=..., this=0x7fbe11e93018, disposer=...)
    at /build/boost/include/boost/intrusive/list.hpp:667
#15 erase_and_dispose<dm_hash_node_t::delete_dm_obj_t> (i=..., this=0x7fbe11e93018, disposer=...)
    at /build/boost/include/boost/intrusive/list.hpp:674
#16 dm_hash_node_t::hn_clear (this=this@entry=0x7fbe11e93018) at /src/dse/dcache/dm/dm.cc:1042
#17 0x00005632f4be4066 in dm_hash_table_t::ht_clear (this=this@entry=0x7fbe114007e0)
    at /src/dse/dcache/dm/dm.cc:993
#18 0x00005632f4be4310 in DataManager::dm_shutdown (this=this@entry=0x7fbe114007c0)
    at /src/dse/dcache/dm/dm.cc:134
#19 0x00005632f4c4115f in DCacheInstance::DCache_shutdown_intask (this=0x7fbe10c00000, _sem=..., exist_pool=@0x7fb5e87052ec: true)
    at /src/dse/dcache/dcache_init.cc:217
#20 0x00005632f4c422df in operator() (__closure=<optimized out>)
    at /src/dse/dcache/dcache_init.cc:244
#21 std::_Function_handler<void(), DCacheInstance::DCache_shutdown(bool)::__lambda30>::_M_invoke(const std::_Any_data &) (__functor=...)
    at /usr/include/c++/4.8.2/functional:2071
#22 0x00007fbe9aed3649 in co::Task::__lambda8::operator() (__closure=0x7fb6bc105f20)
    at /Libgo/libgo/task/task.cpp:37
#23 0x00007fbe9aed3796 in co::Task::Run (this=0x7fbe09fc0c00) at /Libgo/libgo/task/task.cpp:48
#24 0x00007fbe9aed3f64 in co::Task::StaticRun (vp=140454188026880) at /Libgo/libgo/task/task.cpp:79
#25 0x00007fbe9af78981 in make_fcontext () at /Libgo/libgo/context/make_x86_64_sysv_elf_gas.S:64
```
