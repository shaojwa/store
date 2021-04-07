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

## shutdown thread
7f0b45ff8700 2469499 

## search log file by 2469499
ceph-dse.engine.3.1.log-2021-03-30-154125

## works of thread  2469499
```
2021-03-30 13:37:30.523691 7f0b45ff8700 2469499 11 WARNING Dcache_qm:allocateQM: alloc quota 12288 of quota type 0
2021-03-30 13:37:30.535724 7f0b45ff8700 2469499 7 WARNING Dcache_qm:allocateQM: alloc quota 16384 of quota type 1
2021-03-30 13:37:30.535774 7f0b45ff8700 2469499 7 WARNING Dcache_qm:releaseQM: release quota 8192 of quota type 1
2021-03-30 13:37:30.538247 7f0b45ff8700 2469499 9 WARNING Dcache_qm:allocateQM: alloc quota 4096 of quota type 0
2021-03-30 13:37:30.538580 7f0b45ff8700 2469499 9 WARNING Dcache_qm:releaseQM: release quota 131072 of quota type 1
2021-03-30 13:37:30.538644 7f0b45ff8700 2469499 9 WARNING Dcache_qm:releaseQM: release quota 131072 of quota type 1
2021-03-30 13:37:30.705427 7f0b45ff8700 2469499 0 WARNING Dcache_qm:allocateQM: alloc quota 16384 of quota type 1
2021-03-30 13:37:30.705508 7f0b45ff8700 2469499 0 WARNING Dcache_qm:releaseQM: release quota 8192 of quota type 1
2021-03-30 13:37:30.707496 7f0b45ff8700 2469499 1 WARNING Dcache_qm:allocateQM: alloc quota 8192 of quota type 0
2021-03-30 13:37:30.733710 7f0b45ff8700 2469499 2 WARNING Dcache_qm:releaseQM: release quota 131072 of quota type 1
```
 
## shutdown
```
2021-03-30 13:37:30.713944 7f0b37fdc700 2469533 7 WARNING rocksdb: submit_transaction_sync engine is stopping, dropping task
```
in ceph-dse.engine.3.1.log-2021-03-30-154125 shutdown
```
2021-03-30 13:37:30.661702 7f0b42ff2700 2469507 9  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
2021-03-30 13:37:30.667536 7f0b42ff2700 2469507 9  INFO DCACHE_CTRL:DCache_shutdown:waite to finish shutdown.
```

## ctrl thread
thread 2469507 in ceph-dse.engine.3.1.log-2021-03-30-154125
```
2021-03-30 13:37:30.661702 7f0b42ff2700 2469507 9  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
2021-03-30 13:37:30.667536 7f0b42ff2700 2469507 9  INFO DCACHE_CTRL:DCache_shutdown:waite to finish shutdown.
```

## tow handle thread
```
2469499
2710428
```
before crash, thread 2469499 handle the hn_get_object

## nm
```
[root wsh]# nm dse | grep dm_hash_node_t| c++filt | grep clear
0000000000bc4e00 T dm_hash_node_t::clear()
```
 ## asm code
 ```
 bc4fb4:       49 8d bf a8 fe ff ff    lea    -0x158(%r15),%rdi
 ```

## core file 
no corefile, destage_obj_t has not earsed.
