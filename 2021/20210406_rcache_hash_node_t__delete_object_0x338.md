## bug
```
2021-04-06 16:42:03.108614 7f3e817f9700 1354956 9 WARNING Dcache_qm:releaseQM: release quota 0 of quota type 2
2021-04-06 16:42:03.113566 7f3e817f9700 1354956 9 ERROR *** Caught signal (Aborted) **
 in thread 7f3e817f9700 thread_name:Processer_4

(dfc9c6c65b927724fe8f88f33129308995d3cfca) luminous (stable)
 1: (()+0x8d6240) [0x55c84fc7a240]
 2: (()+0xf6c0) [0x7f3e92e9f6c0]
 3: (gsignal()+0x37) [0x7f3e8c11d247]
 4: (abort()+0x148) [0x7f3e8c11e938]
 5: (()+0x2f066) [0x7f3e8c116066]
 6: (()+0x2f112) [0x7f3e8c116112]
 7: (rcache_hash_node_t::delete_object(rcache_object_t&)+0x338) [0x55c84fff2688]
 8: (RCache::_evict_objects()+0x87) [0x55c84fff3047]
 9: (RCache::_lru_cold()+0x5f5) [0x55c84fff39a5]
 10: (RCache::_enqueue_cold(+0x3cc) [0x55c84fff431c]
 11: (RCache::_lru_warm()+0x67d) [0x55c84fff4ced]
 12: (RCache::_enqueue_warm(rcache_object_t&)+0xb7) [0x55c84fff7037]
 13: (RCache::rcache_write(object_t const&, snapid_t, unsigned long long, ...)+0x298) [0x55c850002258]
 14: (DCacheOPProc::do_prefetch_read(OSDOp&, DCacheOPProc::OpContext*)+0x629) [0x55c84fefc2a9]
 15: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x560) [0x55c84ff27a30]
 16: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, ...)+0x1fe) [0x55c84ff2837e]
 17: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x3a1c) [0x55c84ff2c30c]
 18: (()+0xb8d10d) [0x55c84ff3110d]
 19: (()+0x114649) [0x7f3e954e4649]
 20: (co::Task::Run()+0xba) [0x7f3e954e4796]
 21: (co::Task::StaticRun(long)+0x20) [0x7f3e954e4f64]
 22: (make_fcontext()+0x21) [0x7f3e955899b1]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
```

## conclusion
deference iterator after erase
