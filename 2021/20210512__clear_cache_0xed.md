## time
```
20210512 14:25:03
yangwenwen
```

## corefile
```
-rw------- 1 ceph ceph 23367061504 May 12 14:26 core-Processer_4-3465938-1620800722
[root corefile]# date --date @1620800722
Wed May 12 14:25:22 CST 2021
```

## operation
```
21-05-12 14:26:05 ## root pts/3 (196.16.102.8) ## /corefile ## ceph daemon dse.yww37 engine all dcache rcache clear
```

## log stack
```
2021-05-12 14:25:03.375631 7f7d177f8700 3467757 8 ERROR *** Caught signal (Segmentation fault) **
 in thread 7f7d177f8700 thread_name:Processer_4

 ceph version 12.2.1-V100R001B51 (4e999402cd1a3f998619b907b3c616a72d67e525) luminous (stable)
 1: (()+0x66d4e0) [0x55b1f0e774e0]
 2: (()+0xf6c0) [0x7f7d2ce1c6c0]
 3: (RCache::_clear_cache()+0xed) [0x55b1f1195add]
 4: (RCache::_cmd_clear(ceph::Formatter*)+0x9) [0x55b1f11962a9]
 5: (RCache::rcache_cmd_handler(
    ceph::Formatter*, std::vector<std::string, std::allocator<std::string> >&)+0x140) [0x55b1f119c320]
 6: (DCacheInstance::DCache_cmd_handle_intask(
    ceph::Formatter*, std::vector<std::string, std::allocator<std::string> >&, sem_t&, std::string&)+0x2ff) [0x55b1f118996f]
 7: (()+0x116994) [0x7f7d2fa7a994]
 8: (co::Task::Run()+0xc9) [0x7f7d2fa7ab05]
 9: (co::Task::StaticRun(long)+0x2f) [0x7f7d2fa7b313]
 10: (make_fcontext()+0x21) [0x7f7d2fb4cb61]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
 ```
 
 ## corefile stack
