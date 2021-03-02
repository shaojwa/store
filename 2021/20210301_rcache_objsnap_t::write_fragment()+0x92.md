####  现象
```
(rcache_objsnap_t::write_fragment(unsigned long long, unsigned long long, ceph::buffer::list&, bool)+0x92) 
```
stack
```
 (249e2bde69e3743815c19299888ab70bf7c155a4) luminous (stable)
 1: (()+0x5008f0) [0x559aab6d78f0]
 2: (()+0xf6d0) [0x7fabec0076d0]
 3: (gsignal()+0x37) [0x7fabea782277]
 4: (abort()+0x148) [0x7fabea783968]
 5: (__gnu_cxx::__verbose_terminate_handler()+0x165) [0x7fabeb091ac5]
 6: (()+0x5ea36) [0x7fabeb08fa36]
 7: (()+0x5ea63) [0x7fabeb08fa63]
 8: (()+0x5ec83) [0x7fabeb08fc83]
 9: (()+0x330c63) [0x7fabf04b1c63]
 10: (rcache_objsnap_t::write_fragment(unsigned long long, unsigned long long, ceph::buffer::list&, bool)+0x92) [0x7fabee860f72]
 11: (RCache::rcache_write(object_t const&, snapid_t, unsigned long long, unsigned long long, ...)+0x17f) [0x7fabee86301f]
 12: (DCacheOPProc::do_read(OSDOp&, DCacheOPProc::OpContext*)+0xe8f) [0x7fabee79fa1f]
 13: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x949) [0x7fabee7a5d09]
 14: (DSEClassOperation::cls_read2_op(void*, int, int, ceph::buffer::list*, unsigned int)+0x88) [0x559aab469598]
 15: (get_id(void*, ceph::buffer::list*, ceph::buffer::list*)+0xa5) [0x7fabca2fdf45]
 16: (ClassHandler::ClassMethod::exec(void*, ceph::buffer::list&, ceph::buffer::list&)+0x34) [0x559aab461da4]
 17: (DCacheOPProc::do_call(OSDOp&, DCacheOPProc::OpContext*)+0x27d) [0x7fabee76e51d]
 18: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x336) [0x7fabee7a56f6]
 19: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x1fe) [0x7fabee7a626e]
 20: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x2d0d) [0x7fabee7a94ed]
 21: (()+0x69212d) [0x7fabee7ad12d]
 22: (()+0x114159) [0x7fabefe7e159]
 23: (co::Task::Run()+0xba) [0x7fabefe7e2a6]
 24: (co::Task::StaticRun(long)+0x20) [0x7fabefe7ea4e]
 25: (make_fcontext()+0x21) [0x7fabeff15471]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this. 
```

#### 分析
log
```
ceph-dse.engine.9.7.log:2021-03-01 17:02:51.970529 7f001516f700 12269 49 DEBUG dcache_rcache:ercache_write
obj 0x7efecf59e080, obj_id rbd_id.rbd0, snap_id head, prefetch 0, off 0, len 18, align_from 0, algin_to 0, align_len 0
```


