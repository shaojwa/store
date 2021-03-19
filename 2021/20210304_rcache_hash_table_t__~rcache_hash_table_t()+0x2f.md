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
 7: (()+0x22f0be) [0x55c87357b0be]
 8: (()+0x113f19) [0x7f7c1e8c3f19]
 9: (co::Task::Run()+0xba) [0x7f7c1e8c4066]
 10: (co::Task::StaticRun(long)+0x20) [0x7f7c1e8c480e]
 11: (make_fcontext()+0x21) [0x7f7c1e95b231]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
 ```


#### 分析
```
2021-03-04 10:01:09.353459 7f7bfaffe700 1633131 3  INFO mid_dse_control 19 shutdown_engine wait
2021-03-04 10:01:09.366524 7f7bfaffe700 1633131 3  INFO mid_dse_control 19 shutdown_engine finish
2021-03-04 10:01:09.367969 7f7bfaffe700 1633131 3 ERROR *** Caught signal (Segmentation fault) **
```
objdump看：
```
000000000073d570 <rcache_hash_table_t::~rcache_hash_table_t()>:
rcache_hash_table_t::~rcache_hash_table_t()():
/src/dse/dcache/rcache/rcache.cc:1079
  73d570:       41 55                   push   %r13
  73d572:       41 54                   push   %r12
  73d574:       55                      push   %rbp
  73d575:       53                      push   %rbx
  73d576:       48 89 fb                mov    %rdi,%rbx
  73d579:       48 81 ec 28 01 00 00    sub    $0x128,%rsp
  73d580:       48 83 05 b8 ff f3 00    addq   $0x1,0xf3ffb8(%rip)        # 167d540 <__gcov0._ZN19rcache_hash_table_tD2Ev>
  73d587:       01
  73d588:       64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
  73d58f:       00 00
  73d591:       48 89 84 24 18 01 00    mov    %rax,0x118(%rsp)
  73d598:       00
  73d599:       31 c0                   xor    %eax,%eax
/src/dse/dcache/rcache/rcache.cc:1084
  73d59b:       48 8b 47 08             mov    0x8(%rdi),%rax
  73d59f:       48 8b 40 08             mov    0x8(%rax),%rax
  73d5a3:       80 b8 48 06 00 00 00    cmpb   $0x0,0x648(%rax)
 ```
 73d59f 是通过 `_cct`找`_conf`出现问题
