## stack
```
(gdb) bt
#0  0x00007fea342e259b in raise () from /lib64/libpthread.so.0
#1  0x0000564b0721951a in reraise_fatal (signum=6) at /src/global/signal_handler.cc:79
#2  handle_fatal_signal (signum=6) at /src/global/signal_handler.cc:143
#3  <signal handler called>
#4  0x00007fea2b525277 in raise () from /lib64/libc.so.6
#5  0x00007fea2b526968 in abort () from /lib64/libc.so.6
#6  0x00007fea2b51e096 in __assert_fail_base () from /lib64/libc.so.6
#7  0x00007fea2b51e142 in __assert_fail () from /lib64/libc.so.6
#8  0x0000564b074ed1c0 in boost::intrusive::detail::destructor_impl<boost::intrusive::generic_hook<(
    boost::intrusive::algo_types)0, boost::intrusive::list_node_traits<void*>, boost::intrusive::member_tag,
    (boost::intrusive::link_mode_type)1, (boost::intrusive::base_hook_type)0> > (hook=...)
    at /build/boost/include/boost/intrusive/detail/generic_hook.hpp:48
#9  0x0000564b074f1df4 in ~generic_hook (this=0x7fdd8e7e7820, __in_chrg=<optimized out>)
    at /build/boost/include/boost/intrusive/detail/generic_hook.hpp:192
#10 ~list_member_hook (this=0x7fdd8e7e7820, __in_chrg=<optimized out>)
    at /build/boost/include/boost/intrusive/list_hook.hpp:207
#11 ~destage_obj_t (this=0x7fdd8e7e7820, __in_chrg=<optimized out>)
    at /src/dse/dcache/destage/destage.h:86
#12 ~dm_user_obj_t (this=0x7fdd8e7e7800, __in_chrg=<optimized out>)
    at /src/dse/dcache/dm/dm.h:395
#13 operator() (this=<optimized out>, obj=0x7fdd8e7e7800)
  at /src/dse/dcache/dm/dm.h:486
#14 erase_and_dispose<dm_hash_node_t::delete_dm_obj_t> (i=..., this=0x7fdd9f8f8ca0, disposer=...)
    at /build/boost/include/boost/intrusive/list.hpp:667
#15 erase_and_dispose<dm_hash_node_t::delete_dm_obj_t> (i=..., this=0x7fdd9f8f8ca0, disposer=...)
    at /build/boost/include/boost/intrusive/list.hpp:674
#16 dm_hash_node_t::hn_clear (this=this@entry=0x7fdd9f8f8ca0)
    at /src/dse/dcache/dm/dm.cc:1512
#17 0x0000564b074f525c in ~dm_hash_node_t (this=0x7fdd9f8f8ca0, __in_chrg=<optimized out>)
    at /src/dse/dcache/dm/dm.h:492
#18 ~dm_hash_table_t (this=0x7fdd9f816000, __in_chrg=<optimized out>)
    at /src/dse/dcache/dm/dm.h:501
#19 _Destroy<dm_hash_table_t> (__pointer=0x7fdd9f816000)
    at /usr/include/c++/4.8.2/bits/stl_construct.h:93
#20 __destroy<dm_hash_table_t*> (__last=<optimized out>, __first=0x7fdd9f816000)
    at /usr/include/c++/4.8.2/bits/stl_construct.h:103
#21 _Destroy<dm_hash_table_t*> (__last=<optimized out>, __first=<optimized out>)
    at /usr/include/c++/4.8.2/bits/stl_construct.h:126
#22 _Destroy<dm_hash_table_t*, dm_hash_table_t> (__last=0x7fdd9f956080, __first=<optimized out>)
    at /usr/include/c++/4.8.2/bits/stl_construct.h:151
#23 ~vector (this=0x7fe9d3fd6998, __in_chrg=<optimized out>) at /usr/include/c++/4.8.2/bits/stl_vector.h:415
#24 DataManager::~DataManager (this=0x7fe9d3fd6970, __in_chrg=<optimized out>) 
```

## PN
202106210677

## 原因
在调用release_dcache_objs接口中，本来需要判断当前destage_obj->user_obj->is_filling()，如果当前user_obj正在filling就跳过。
但是实际实现的时候，判断的是写一个对象是不是filling，导致，如果当前对象 obj_a 没有filling，而 obj_a 的下一个在filling时，就会跳过当前对象 obj_a 的淘汰。
