## description
```
2021-04-17 15:48:17.618525 7fe18c3fe700 3072691 6 ERROR *** Caught signal (Segmentation fault) **
 in thread 7fe18c3fe700 thread_name:admin_socket

12.2.1-UniStorOS_V100R001B51 (cca98c01ed371be93f0c26b488492a292d079bcf) luminous (stable)
 1: (()+0x632d90) [0x556ef0b0ed90]
 2: (()+0xf6d0) [0x7fe19aa8c6d0]
 3: (DCacheInstance::DCache_cmd_handle((ceph::Formatter*, ...)+0x12c) [0x556ef0e1ba4c]
 4: (EngineService::asok_command((ceph::Formatter*, ..., std::ostream&)+0x184e) [0x556ef087834e]
 5: (DSE::asok_command(std::string, ...)+0x568) [0x556ef07e2ec8]
 6: (DSESocketHook::call(std::string, ...)+0x25b) [0x556ef082016b]
 7: (AdminSocket::do_accept()+0x116a) [0x7fe19d9567aa]
 8: (AdminSocket::entry()+0x290) [0x7fe19d957c20]
 9: (()+0x7e25) [0x7fe19aa84e25]
 10: (clone()+0x6d) [0x7fe193dd1bad]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.

```

## version
12.2.1-UniStorOS_V100R001B51 (cca98c01ed371be93f0c26b488492a292d079bcf) luminous (stable)

##  asm code
```
/src/dse/dcache/dcache_init.cc:374
  93fa4c:       41 0f b7 47 0c          movzwl 0xc(%r15),%eax
CephContext::get_instance_id() const():
/src/common/ceph_context.h:187
  93fa51:       49 8b 57 20             mov    0x20(%r15),%rdx
  93fa55:       0f b6 92 40 01 00 00    movzbl 0x140(%rdx),%edx
TaskOpt():
/opt/h3c/include/libgo/task/task.h:36
  93fa5c:       66 89 4c 24 70          mov    %cx,0x70(%rsp)
  93fa61:       89 44 24 74             mov    %eax,0x74(%rsp)
  93fa65:       48 8d 05 94 ca 2b 00    lea    0x2bca94(%rip),%rax
```
movzbl, Move Zero-Extended Byte to Long, the low 8 bits of the destination are replaced by the source operand. the top 24 bits are set to 0. The source operand is unaffected.

movzwl, Move Zero-Extended Word to Long, the low 16 bits of the destination are replaced by the source operand. the top 16 bits are set to 0. The source operand is unaffected.

## source code
```
classs DCacheInstance {
private: 
  uint8 _init_schedule;
  int32 shutdown_result;
public:
  uint16 storage_pool_id;
  uint16 engine_id;
  uint16 thread_id;
  uint32 instance_id;
  EngineService * EngineS;
  CephContext* cct;
  scheduler * sched
  ...
  }

sched->CreateTask() (
...,
::co::TaskOpt{UINT16_MAX, INSTANCE_ID, thread_id, true, 0, 0, __func__, __FILE__, __LINE__});
```

## asm  code
```
movzwl 0xc(%r15),%eax
```
**zwl** means move word to long.
thread_id is word, and offset if 4(aligned `_init_schdule`) + 4 + 2 + 2 = 12, so mov thread_id to eax

```
mov    0x20(%r15),%rdx
```
0x20 is 12 + 4 + 8 + 8, so mov sched to rdx.

so, before call TaskOpt(), we got thread_id and instance_id, instance_id is cct->get_instance_id(), so we need cct.

```
uint8_t cct->get_instance_id() const {
  return instance_id;
  }
```
match the movzbl, so the 0x20 is the offset of cct, check,
