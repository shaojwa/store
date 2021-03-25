## Logs
```
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
## Function offset in text section
```
[root@node1 wsh]# nm dse | grep hn_get_object | c++filt | grep T
0000000000ba1bf0 T dm_hash_node_t::hn_get_object(object_t const&, bool)
0000000000c08840 T rcache_hash_node_t::hn_get_object(object_t const&, bool)
```
0xba1bf0 + 0x229 = 0xba1f19

## Cause instructions
```
ba1e19:       48 8b b3 a0 fe ff ff    mov    -0x160(%rbx),%rsi
```

## Analyze
thread 1366740/7f50817f0700, file ceph-dse.engine.6.1.log-2021-03-25-154855
```
target obj benchmark_data_node119_508101_object490569
id benchmark_data_node119_508101_object366884
id benchmark_data_node119_508101_object401042
id benchmark_data_node119_508101_object490569
hit id benchmark_data_node119_508101_object490569
```

benchmark_data_node119_508101_object490569 is the one after benchmark_data_node119_508101_object401042
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


