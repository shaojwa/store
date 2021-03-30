## bug
```
2021-03-30 13:37:30.738502 7f0b45ff8700 2469499 0 ERROR *** Caught signal (Aborted) **
 in thread 7f0b45ff8700 thread_name:Processer_5

 (7ce41199a9f93a5cecc08324cfa434375d23c5db) luminous 
 1: (()+0x8bb6d0) [0x55db4759a6d0]
 2: (()+0xf6d0) [0x7f0b57f556d0]
 3: (gsignal()+0x37) [0x7f0b511d4277]
 4: (abort()+0x148) [0x7f0b511d5968]
 5: (()+0x2f096) [0x7f0b511cd096]
 6: (()+0x2f142) [0x7f0b511cd142]
 7: (()+0xbbf5a8) [0x55db4789e5a8]
 8: (dm_hash_node_t::clear()+0x1b4) [0x55db478a3fb4]
 9: (dm_hash_table_t::clear()+0x26) [0x55db478a4086]
 10: (DataManager::shutdown()+0x2c) [0x55db478a40dc]
 11: (DCacheInstance::DCache_shutdown_intask(co::CoSem&, bool&)+0xdf) [0x55db478feacf]
 12: (()+0xc20c4f) [0x55db478ffc4f]
 13: (()+0x1144c9) [0x7f0b5a59a4c9]
 14: (co::Task::Run()+0xba) [0x7f0b5a59a616]
 15: (co::Task::StaticRun(long)+0x20) [0x7f0b5a59ade4]
 16: (make_fcontext()+0x21) [0x7f0b5a63a361]
 ```
 ## nm
 ```
[root wsh]# nm dse | grep dm_hash_node_t| c++filt | grep clear
0000000000bc4e00 T dm_hash_node_t::clear()
```
 ## asm code
 ```
 bc4fb4:       49 8d bf a8 fe ff ff    lea    -0x158(%r15),%rdi
 ```
 
