#### 现象
```
2021-03-04 10:01:09.367969 7f7bfaffe700 1633131 3 ERROR *** Caught signal (Segmentation fault) 
 in thread 7f7bfaffe700 thread_name:Processer_0
 
 version  (a53774ebc5d878587b76a9a90a1a48a583e304eb) luminous 
 1: (()+0x4f7220) [0x55c873843220]
 2: (()+0xf6d0) [0x7f7c1aa556d0]
 3: (rcache_hash_table_t::~rcache_hash_table_t()+0x2f) [0x7f7c1d2a659f]
 4: (EngineService::~EngineService()+0x14f) [0x55c8735f6b4f]
 5: (EngineService::~EngineService()+0x9) [0x55c8735f6e09]
 6: (DSE::delete_engine(std::map<engine_t, EngineService*, std::less<engine_t>, ..)+0x27) [0x55c873569827]
827]
 7: (()+0x22f0be) [0x55c87357b0be]
 8: (()+0x113f19) [0x7f7c1e8c3f19]
 9: (co::Task::Run()+0xba) [0x7f7c1e8c4066]
 10: (co::Task::StaticRun(long)+0x20) [0x7f7c1e8c480e]
 11: (make_fcontext()+0x21) [0x7f7c1e95b231]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
 ```
