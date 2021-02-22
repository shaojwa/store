```
2021-02-22 16:41:34.966281 7fca0396f700 1727559 21 ERROR *** Caught signal (Segmentation fault) **
 in thread 7fca0396f700 thread_name:Processer_5
 ceph version 12.2.1-UniStorOS_V100R001B51 (c7a0b8475247fb362e58e4e9fdd5248306ae1988) luminous (stable)
 1: (()+0x4e7930) [0x55b147d12930]
 2: (()+0xf6d0) [0x7fca104506d0]
 3: (QM::qm_cmd_handler(ceph::Formatter*, std::vector<std::string, std::allocator<std::string> >)+0x33) [0x7fca12c6a023]
 4: (DCacheInstance::DCache_cmd_handle_intask(...)+0x142) [0x7fc
a12c70242]
 5: (()+0x70c552) [0x7fca12c70552]
 6: (()+0x114159) [0x7fca140ef159]
 7: (co::Task::Run()+0xba) [0x7fca140ef2a6]
 8: (co::Task::StaticRun(long)+0x20) [0x7fca140efa4e]
 9: (make_fcontext()+0x21) [0x7fca14186471]
 ```
