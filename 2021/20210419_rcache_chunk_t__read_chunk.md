## desc
```
2021-04-19 16:34:55.675732 7f46e1ff7700 782058 4 ERROR *** Caught signal (Aborted) **
 in thread 7f46e1ff7700 thread_name:Processer_6
(ebe208064aec50c96ef471870dea9dd3915da50c) luminous (stable)
 1: (()+0x8e1330) [0x56027b8d4330]
 2: (()+0xf6d0) [0x7f46f3d2f6d0]
 3: (gsignal()+0x37) [0x7f46ecfac277]
 4: (abort()+0x148) [0x7f46ecfad968]
 5: (ceph::__ceph_assert_fail(char const*, char const*, int, char const*)+0x185) [0x7f46f6a1b565]
 6: (rcache_chunk_t::read_chunk(unsigned long long, ...)+0xf7f) [0x56027bc5839f]
 7: (rcache_objsnap_t::read_fragment(unsigned long long, ...)+0xae) [0x56027bc58c7e]
 8: (RCache::rcache_read(object_t const&, snapid_t, ...)+0x6cd) [0x56027bc666bd]
 9: (DCacheOPProc::rcache_read_sp(std::list<dcache_data_frag_t, ...)+0x1e6) [0x56027bb5beb6]
 10: (DCacheOPProc::do_sparse_read(DCacheOPProc::OpContext*, OSDOp&)+0x941) [0x56027bb63991]
 11: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, ...)+0x7a6) [0x56027bb87086]
 12: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, ...)+0x1fe) [0x56027bb878de]
 13: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x32f0) [0x56027bb8b140]
 14: (()+0xb9c30d) [0x56027bb8f30d]
 15: (()+0x11401d) [0x7f46f637401d]
 16: (co::Task::Run()+0xba) [0x7f46f637416a]
 17: (co::Task::StaticRun(long)+0x20) [0x7f46f6374938]
 18: (make_fcontext()+0x21) [0x7f46f6419331]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
 ```
