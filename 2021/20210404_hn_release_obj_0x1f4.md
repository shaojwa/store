```
2021-04-04 20:28:06.391790 7efdcc7fa700 710744 46  INFO mid_dse_control 18 ms_handle_reset
2021-04-04 20:28:06.392195 7efdca7f6700 710748 16  INFO mid_dse_control 18 ms_handle_reset
2021-04-04 20:28:06.392711 7efdcd7fc700 710742 39  INFO mid_dse_control 18 ms_handle_reset
2021-04-04 20:28:06.394192 7efdefff7700 710648 15 ERROR *** Caught signal (Aborted) **
 in thread 7efdefff7700 thread_name:Processer_6

 luminous (stable)
 1: (()+0x8d73f0) [0x5566288c83f0]
 2: (()+0xf6d0) [0x7efe025576d0]
 3: (gsignal()+0x37) [0x7efdfb7d4277]
 4: (abort()+0x148) [0x7efdfb7d5968]
 5: (()+0x2f096) [0x7efdfb7cd096]
 6: (()+0x2f142) [0x7efdfb7cd142]
 7: (()+0xbe2558) [0x556628bd3558]
 8: (dm_hash_node_t::hn_release_obj(dm_user_obj_t&)+0x1f4) [0x556628bd9bb4]
 9: (Destage::release_dcache_objs()+0x92) [0x556628b8ae92]
 10: (Destage::destroy_destage()+0xa1) [0x556628bb0751]
 11: (DCacheInstance::DCache_shutdown_intask(co::CoSem&, bool&)+0x77) [0x556628c38e57]
 12: (()+0xc4903f) [0x556628c3a03f]
 13: (()+0x114649) [0x7efe04b9c649]
 14: (co::Task::Run()+0xba) [0x7efe04b9c796]
 15: (co::Task::StaticRun(long)+0x20) [0x7efe04b9cf64]
 16: (make_fcontext()+0x21) [0x7efe04c41981]
```

## conclusion
destage call **erase_and_dispose()** without erase the destage_obj from another list
