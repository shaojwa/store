## perf branch
```
2021-04-13 14:57:42.138777 7f5b3c7e8700 972511 27 ERROR *** Caught signal (Segmentation fault) **
 in thread 7f5b3c7e8700 thread_name:Processer_10

 ceph version (e4be0cf575aa8a545e6d03e8ef1856488390fc1f) luminous (stable)
 1: (()+0x878b30) [0x5633adb08b30]
 2: (()+0xf6d0) [0x7f5c125536d0]
 3: (dm_user_obj_t::_attach_snap(dm_objsnap_t&)+0x197) [0x5633ade9bc37]
 4: (dm_user_obj_t::obj_create_snap(snapid_t)+0x4f) [0x5633ade7778f]
 5: (DataManager::dm_write_obj_data(hobject_t const&, ...)+0x245) [0x5633ade90155]
 6: (DCacheOPProc::do_transaction(DCacheTransaction*, ...)+0x210b) [0x5633ade0035b]
 7: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, ...)+0x6c9) [0x5633ade14c89]
 8: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>, ...)+0x2c3c) [0x5633ade17adc]
 9: (()+0xb8b746) [0x5633ade1b746]
 10: (()+0xf9d96) [0x7f5c14b7dd96]
 11: (co::Task::Run()+0xba) [0x7f5c14b7dea8]
 12: (co::Task::StaticRun(long)+0x20) [0x7f5c14b7e2de]
 13: (make_fcontext()+0x21) [0x7f5c14c19d21]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
```

## asm
```
c13450:       48 8b bb 10 01 00 00    mov    0x110(%rbx),%rdi
c13457:       4c 8b 45 18             mov    0x18(%rbp),%r8
```
