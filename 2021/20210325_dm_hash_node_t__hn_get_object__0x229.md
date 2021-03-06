## bug
202103251408

## logs
```
2021-03-25 15:39:24.259258 7f50817f0700 1366740 2 WARNING Dcache_qm:allocateQM: alloc quota 8192 of quota type 1
2021-03-25 15:39:24.259741 7f5080fef700 1366742 0 WARNING Dcache_qm:allocateQM: alloc quota 8192 of quota type 1
2021-03-25 15:39:24.267914 7f5080fef700 1366742 0 WARNING Dcache_qm:allocateQM: alloc quota 8192 of quota type 0
2021-03-25 15:39:24.270093 7f50817f0700 1366740 5 ERROR *** Caught signal (Segmentation fault) **
 in thread 7f50817f0700 thread_name:Processer_5

1: (()+0x89dbe0) [0x55d3b9cf2be0]
2: (()+0xf6d0) [0x7f5215d4a6d0]
3: (dm_hash_node_t::hn_get_object(object_t const&, bool)+0x229) [0x55d3b9ff6e19]
4: (DataManager::dm_write_obj_data(hobject_t const&, ...)+0xb1) [0x55d3ba019911]
5: (DCacheOPProc::do_transaction(DCacheTransaction*, DCacheOPProc::OpContext*)+0x20aa) [0x55d3b9f89bda]
6: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, ...)+0x561) [0x55d3b9f9ff31]
7: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x314b) [0x55d3b9fa328b]
8: (()+0xb52a6d) [0x55d3b9fa7a6d]
9: (()+0x1144c9) [0x7f521838f4c9]
10: (co::Task::Run()+0xba) [0x7f521838f616]
11: (co::Task::StaticRun(long)+0x20) [0x7f521838fde4]
12: (make_fcontext()+0x21) [0x7f521842f361]
```

## engine

ceph-dse.engine.6.1.log-2021-03-25-154855

## hn_get_object
1366740， all target obj in thread 1366740


## function offset in text section
```
[root@node1 wsh]# nm dse | grep hn_get_object | c++filt | grep T
0000000000ba1bf0 T dm_hash_node_t::hn_get_object(object_t const&, bool)
0000000000c08840 T rcache_hash_node_t::hn_get_object(object_t const&, bool)
```
0xba1bf0 + 0x229 = 0xba1f19

## cause instructions
```
ba1e19:       48 8b b3 a0 fe ff ff    mov    -0x160(%rbx),%rsi
```

## analyze
thread 1366740/7f50817f0700, file ceph-dse.engine.6.1.log-2021-03-25-154855
```
target obj benchmark_data_node119_508101_object490569
id benchmark_data_node119_508101_object366884
id benchmark_data_node119_508101_object401042
id benchmark_data_node119_508101_object490569
hit id benchmark_data_node119_508101_object490569
```

benchmark_data_node119_508101_object490569  is the one after benchmark_data_node119_508101_object401042
```
target obj benchmark_data_node119_508101_object490569
id benchmark_data_node119_508101_object366884
id benchmark_data_node119_508101_object401042
```
how to guess the cause-object???? read the ceph-dse.node.log, we got the target object is:
```
benchmark_data_node119_508101_object490569
```
when created:
```
hn_get_object create obj 0x7f4b58c544c8, id benchmark_data_node119_508101_object490569
```

## core file
```
-rw------- 1 ceph ceph 34017210368 Mar 25 15:41 core-Processer_5-1363277-1616657967
Processer_5: executable filename
1363277: PID of dumped process
1616657967: time of dump, expressed as seconds since the Epoch
```
2021-03-25 14:43:56.432042 7f52219ad5c0 1363277 4 WARNING ... luminous (stable), process (unknown), pid 1363277

## core file pattern
```
cat /proc/sys/kernel/core_pattern
/corefile/core-%e-%p-%t
```

## core file
```
#0  0x00007f5215d4a59b in raise () from /lib64/libpthread.so.0
#1  0x000055d3b9cf2c7a in reraise_fatal (signum=11) at /src/global/signal_handler.cc:76
#2  handle_fatal_signal (signum=11) at /src/global/signal_handler.cc:140
#3  <signal handler called>
#4  _M_data (this=0x58c544c8) at /usr/include/c++/4.8.2/bits/basic_string.h:293
#5  _M_rep (this=0x58c544c8) at /usr/include/c++/4.8.2/bits/basic_string.h:301
#6  size (this=0x58c544c8) at /usr/include/c++/4.8.2/bits/basic_string.h:716
#7  operator<< <char, std::char_traits<char>, std::allocator<char> > (__str=..., __os=...)
    at /usr/include/c++/4.8.2/bits/basic_string.h:2758
#8  operator<< (o=..., out=...) at /src/include/object.h:76
#9  dm_hash_node_t::hn_get_object (this=0x7f4def64ed78, obj_id=..., create=create@entry=true)
    at /src/dse/dcache/dm/dm.cc:990
#10 0x000055d3ba019911 in _dm_locate_object (create=true, obj_id=..., this=0x7f4def0007d0)
    at /src/dse/dcache/dm/dm.h:597
#11 DataManager::dm_write_obj_data (this=0x7f4def0007d0, hobj=..., oper=..., data=...)
   at /src/dse/dcache/dm/dm.cc:160
```

## opertaion
do_write transaction write
