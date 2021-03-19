```
2021-01-20 15:50:14.325723 7ff3cc154700 4140256 74 ERROR *** Caught signal (Segmentation fault) **
 in thread 7ff3cc154700 thread_name:ms_dispatch

 version 12.2.1-UniStorOS_V100R001B51 (82e3bcf0d0aa0ca4b978ac7d4e8bbd41a2c0812d) luminous (stable)
 1: (()+0x2b64c0) [0x565461e024c0]
 2: (()+0xf6d0) [0x7ff3ed1636d0]
 3: (DataManager::dm_del_snaps(interval_set<snapid_t>&)+0x31) [0x7ff3ef0a6a21]
 4: (DCacheInstance::DCache_rm_snaps_incache(interval_set<snapid_t>&)+0x18) [0x7ff3ef0cf0f8]
 5: (DSE::delete_snap(std::shared_ptr<EngineMap>)+0xe6) [0x565461c48166]
 6: (DSE::handle_engine_map(Message*)+0x187e) [0x565461c557ee]
 7: (DSE::ms_dispatch(Message*)+0x926) [0x565461c57786]
 8: (DispatchQueue::entry()+0x41a) [0x7ff3f074004a]
 9: (DispatchQueue::DispatchThread::entry()+0xe) [0x7ff3f0742dde]
 10: (()+0x7e25) [0x7ff3ed15be25]
 11: (clone()+0x6d) [0x7ff3eb7a2bad]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this. 
```
