#### 现象
```
1: (()+0x4e7930) [0x558d8dc18930]
2: (()+0xf6d0) [0x7f5e625a26d0]
3: (gsignal()+0x37) [0x7f5e60d1d277]
4: (abort()+0x148) [0x7f5e60d1e968]
5: (()+0x2f096) [0x7f5e60d16096]
6: (()+0x2f142) [0x7f5e60d16142]
7: (RCache::_enqueue_warm(rcache_object_t&)+0x2f4) [0x7f5e64dd2554]
8: (RCache::rcache_write(object_t const&, )+0x192) [0x7f5e64ddb652]
9: (DCacheOPProc::do_read(OSDOp&, DCacheOPProc::OpContext*)+0xe8f) [0x7f5e64d22c0f]
10: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x949) [0x7f5e64d28ef9]
11: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x1fe) [0x7f5e64d2945e]
12: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x2d17) [0x7f5e64d2c6e7]
```
