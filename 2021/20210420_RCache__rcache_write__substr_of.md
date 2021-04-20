## desc
```
2021-04-20 10:48:46.153398 7f469c7f8700 2355051 0 ERROR *** Caught signal (Aborted) **
 in thread 7f469c7f8700 thread_name:Processer_5

 ceph version 12.2.1-UniStorOS_V100R001B51 (ebe208064aec50c96ef471870dea9dd3915da50c) luminous (stable)
 1: (()+0x8e1330) [0x56431b4ee330]
 2: (()+0xf6d0) [0x7f46adeb36d0]
 3: (gsignal()+0x37) [0x7f46a7130277]
 4: (abort()+0x148) [0x7f46a7131968]
 5: (__gnu_cxx::__verbose_terminate_handler()+0x165) [0x7f46a7a3fac5]
 6: (()+0x5ea36) [0x7f46a7a3da36]
 7: (()+0x5ea63) [0x7f46a7a3da63]
 8: (()+0x5ec83) [0x7f46a7a3dc83]
 9: (ceph::buffer::list::substr_of(ceph::buffer::list const&, unsigned int, unsigned int)+0x26d) [0x7f46b0b489fd]
 10: (RCache::rcache_write(object_t const&, snapid_t, ...)+0x223) [0x56431b884123]
 11: (DCacheOPProc::do_prefetch_read(OSDOp&, DCacheOPProc::OpContext*)+0x209) [0x56431b7756d9]
 12: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, ...)+0x5d8) [0x56431b7a0eb8]
 13: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, ...)+0x1fe) [0x56431b7a18de]
 14: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x32f0) [0x56431b7a5140]
 15: (()+0xb9c30d) [0x56431b7a930d]
 16: (()+0x11401d) [0x7f46b04f801d]
 17: (co::Task::Run()+0xba) [0x7f46b04f816a]
 18: (co::Task::StaticRun(long)+0x20) [0x7f46b04f8938]
 19: (make_fcontext()+0x21) [0x7f46b059d331]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
```

##  offset and len
frame 10
```
(gdb)
#10 0x00007f46b0b489fd in ceph::buffer::list::substr_of(
    this=this@entry=0x7f446a2df2d0, other=..., off=off@entry=0, len=len@entry=4194304)
```

## bl.\_len 
frame 11
```
_M_node = {_M_next = 0x7f43dd3702e0, _M_prev = 0x7f4367b2a500}}}, <No data fields>}, _len = 1495040
```

##  check  DCacheOPProc::do_prefetch_read
frame 12
```
(gdb) print dse_op
$3 = (OSDOp &) @0x7f43640e5800: {op = {op = {v = 4644}, flags = {v = 0}, {extent = {offset = {v = 0}, length = {v = 4194304}
```
