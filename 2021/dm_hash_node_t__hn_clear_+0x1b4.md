## time
2021-04-07 hukedong
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
