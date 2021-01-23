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

```
0000000000ac00b0 T DataManager::dm_get_conflict_list_ref(object_t const&)
```
```
0000000000ac00b0 <DataManager::dm_get_conflict_list_ref(object_t const&)>:
DataManager::dm_get_conflict_list_ref(object_t const&)():
dm.cc:871
  ac00b0:       41 56                   push   %r14
  ac00b2:       41 55                   push   %r13
  ac00b4:       41 54                   push   %r12
  ac00b6:       55                      push   %rbp
  ac00b7:       48 89 f5                mov    %rsi,%rbp
  ac00ba:       53                      push   %rbx
  ac00bb:       48 89 fb                mov    %rdi,%rbx
  ac00be:       48 81 ec 30 01 00 00    sub    $0x130,%rsp
  ac00c5:       48 83 05 13 3b 26 01    addq   $0x1,0x1263b13(%rip)        # 1d23be0 <__gcov0._ZN11DataManager24dm_get_conflict_list_refERK8obje
ct_t>
  ac00cc:       01
  ac00cd:       64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
  ac00d4:       00 00
  ac00d6:       48 89 84 24 28 01 00    mov    %rax,0x128(%rsp)
  ac00dd:       00
  ac00de:       31 c0                   xor    %eax,%eax
dm.cc:872
  ac00e0:       48 8b 87 00 01 40 01    mov    0x1400100(%rdi),%rax
  ac00e7:       48 8b 78 08             mov    0x8(%rax),%rdi
  ac00eb:       80 bf 48 06 00 00 00    cmpb   $0x0,0x648(%rdi)
  ac00f2:       0f 85 c8 00 00 00       jne    ac01c0 <DataManager::dm_get_conflict_list_ref(object_t const&)+0x110>
  ```
```
