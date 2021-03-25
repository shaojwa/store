## bug description

```
0> 2021-03-15 15:54:49.668305 7f3456bf6700 2960016 52 ERROR *** Caught signal (Segmentation fault) **
in thread 7f3456bf6700 thread_name:Processer_7

1: (()+0x852b80) [0x55645c012b80]
2: (()+0xf6d0) [0x7f34640df6d0]
3: (dm_hash_node_t::hn_get_object(object_t const&, unsigned short, bool)+0x454) [0x55645c35e1c4]
4: (DataManager::dm_get_conflict_list_ref(object_t const&, unsigned short)+0xcf) [0x55645c35e89f]
5: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>, ...)+0x2eb) [0x55645c309a5b]
6: (()+0xb50131) [0x55645c310131]
7: (()+0x114159) [0x7f3466724159]
8: (co::Task::Run()+0xba) [0x7f34667242a6]
9: (co::Task::StaticRun(long)+0x20) [0x7f3466724a4e]
10: (make_fcontext()+0x21) [0x7f34667bb471]
```

## analysis
address = 0xb9dd70+0x454 = 0xb9e1c4, the beginning of the function:
```
0000000000b9dd70 <dm_hash_node_t::hn_get_object(object_t const&, unsigned short, bool)>:
dm_hash_node_t::hn_get_object(object_t const&, unsigned short, bool)():
/src/dse/dcache/dm/dm.cc:974
  b9dd70:       41 57                   push   %r15
  b9dd72:       41 56                   push   %r14
  b9dd74:       41 55                   push   %r13
  b9dd76:       41 54                   push   %r12
  b9dd78:       49 89 f4                mov    %rsi,%r12
  b9dd7b:       55                      push   %rbp
  b9dd7c:       48 89 fd                mov    %rdi,%rbp
  b9dd7f:       53                      push   %rbx
  b9dd80:       48 81 ec 48 01 00 00    sub    $0x148,%rsp
  b9dd87:       64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
```
```
/src/dse/dcache/dm/dm.cc:989
  b9e1bb:       bf e8 01 00 00          mov    $0x1e8,%edi
  b9e1c0:       48 8b 45 08             mov    0x8(%rbp),%rax
  b9e1c4:       4c 8b 70 10             mov    0x10(%rax),%r14
  b9e1c8:       e8 f3 c0 98 ff          callq  52a2c0 <operator new(unsigned long)@plt>
  b9e1cd:       48 83 05 03 8d ae 00    addq   $0x1,0xae8d03(%rip)        # 1686ed8 <__gcov0...>
  b9e1d4:       01
  b9e1d5:       0f b7 54 24 1c          movzwl 0x1c(%rsp),%edx
  b9e1da:       48 89 e9                mov    %rbp,%rcx
  b9e1dd:       4c 8b 45 08             mov    0x8(%rbp),%r8
  b9e1e1:       4d 89 f1                mov    %r14,%r9
  b9e1e4:       4c 89 e6                mov    %r12,%rsi
  b9e1e7:       48 89 c7                mov    %rax,%rdi
  b9e1ea:       48 89 c3                mov    %rax,%rbx
  b9e1ed:       e8 0e f9 ff ff          callq  b9db00 <dm_user_obj_t::dm_user_obj_t(object_t const&, ...)>
  b9e1f2:       48 83 05 ee 8c ae 00    addq   $0x1,0xae8cee(%rip)        # 1686ee8 <__gcov0...>
```
take a look, before call the new operator, we should setup 3 parameter
```
move $0x1e8, %edi // the size of dm_user_obj_t is 0x1e8
move 0x8(%rbp),%rax // refer to 0xb9dd7c, rbp is this, so rax is 0x8 bytes offset this, the dm
move 0x10(%rax),%r14 // 0x10 is the offset of _destage in dm, try to access _destage, so something wrong with dm?
```
after calling new, goto, 6 mov before callq dm_user_obj_t:;dm_user_obj_t, thay are:
```
mov  %rbp,%rcx // ref to 
mov  0x8(%rbp),%r8//
mov  %r14,%r9 // %r14 is shard_index
mov  %r12,%rsi // obj_t 
mov  $rax,%rdi // this of dm_user_obj_t
mov  $rax,%rbx // 
```
we got:
```
  r15 = create(bool)
  r14 = shard_index
  r13 = obj_id
  r12 = this
```
