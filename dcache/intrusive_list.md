## Check if the node in list
```
[root@node32 build]# fg
Program received signal SIGABRT, Aborted
0x00007fffe52e1387 in raise () from /lib64/libc.so.6
gdb /home/wsh/build/bin/dcache-dm-test
#0  0x00007fffe52e1387 in raise () from /lib64/libc.so.6
#1  0x00007fffe52e2a78 in abort () from /lib64/libc.so.6
#2  0x00007fffe52da1a6 in __assert_fail_base () from /lib64/libc.so.6
#3  0x00007fffe52da252 in __assert_fail () from /lib64/libc.so.6
#4  0x0000555555b056d0 in boost::intrusive::detail::destructor_impl<boost::intrusive::generic_hook
    <(boost::intrusive::algo_types)0, boost::intrusive::list_node_traits<void*>,
    boost::intrusive::member_tag, (boost::intrusive::link_mode_type)1, (boost::intrusive::base_hook_type)0> > (hook=...)
    at /home/wsh/build/boost/include/boost/intrusive/detail/generic_hook.hpp:48
#5  0x0000555555b1698e in ~generic_hook (this=0x7fffe323d600, __in_chrg=<optimized out>) at
    /home/wsh/build/boost/include/boost/intrusive/detail/generic_hook.hpp:192
#6  ~list_member_hook (this=0x7fffe323d600, __in_chrg=<optimized out>) at
    /home/wsh/build/boost/include/boost/intrusive/list_hook.hpp:207
#7  ~dog_t (this=0x7fffe323d5e0, __in_chrg=<optimized out>) at
    /home/wsh/src/test/dse/dcache/dm/dcache_dm_test.cc:366
#8  operator() (this=<optimized out>, delete_this=0x7fffe323d5e0) at
    /home/wsh/src/test/dse/dcache/dm/dcache_dm_test.cc:390
#9  erase_and_dispose<DMTest::DelDog> (i=..., this=0x7fffffffe110, disposer=...) at
    /home/wsh/build/boost/include/boost/intrusive/list.hpp:667
#10 erase_and_dispose<DMTest::DelDog> (i=..., this=0x7fffffffe110, disposer=...) at
    /home/wsh/build/boost/include/boost/intrusive/list.hpp:674
#11 DMTest::test_blist_erase (this=this@entry=0x7fffe323b580) at
   /home/wsh/src/test/dse/dcache/dm/dcache_dm_test.cc:407
```
