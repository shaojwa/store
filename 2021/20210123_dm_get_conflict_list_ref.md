18848
```
021-01-23 12:58:20.688072 7f691b96e700 239744 4 ERROR *** Caught signal (Segmentation fault) **
 in thread 7f691b96e700 thread_name:Processer_6

 ceph version 12.2.1-UniStorOS_V100R001B51 (d7c0135ae7913b4c7559c313f20ce666d349fd9f) luminous (stable)
 1: (()+0x7c7940) [0x5648e2a37940]
 2: (()+0xf6d0) [0x7f6927a476d0]
 3: (DataManager::dm_get_conflict_list_ref(object_t const&)+0x37) [0x7f6929d90af7]
 4: (()+0xa73b58) [0x7f6929d43b58]
 5: (()+0xa7a024) [0x7f6929d4a024]
 6: (std::function<void ()>::operator()() const+0x19) [0x5648e277f719]
 7: (()+0x113de9) [0x7f692b6dcde9]
 8: (co::Task::Run()+0xba) [0x7f692b6dcf36]
 9: (co::Task::StaticRun(long)+0x20) [0x7f692b6dd6de]
 10: (make_fcontext()+0x21) [0x7f692b773fc1]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.  
```
