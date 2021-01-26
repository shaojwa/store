 youzhengyun
 ```
 1: (()+0x7cb650) [0x56382487b650]
 2: (()+0xf6c0) [0x7fbb747936c0]
 3: (()+0xd5cd) [0x7fbb73cea5cd]
 4: (()+0x266ff) [0x7fbb73d036ff]
 5: (malloc()+0x22f) [0x7fbb73ce314f]
 6: (operator new(unsigned long)+0x1d) [0x7fbb731f31bd]
 7: (std::_Rb_tree_iterator<std::pair<unsigned long long const, unsigned long long>>, ...)+0x6a) [0x7fbb76aa423a]
 8: (std::map<unsigned long long, unsigned long long, std::less<unsigned long long>, ...)+0x56) [0x7fbb76b01d56]
 9: (dm_objsnap_t::snap_write_fragment(hobject_t const&, unsigned short, unsigned long long, unsigned long long, ceph::buffer::list const&)+0x6aa) [0x7fbb76af425a]
 10: (DataManager::dm_write_obj_data(hobject_t const&, dm_data_oper_t const&, ceph::buffer::list const&)+0x11e) [0x7fbb76af7a5e]
 11: (DCacheOPProc::do_transaction(DCacheTransaction*, DCacheOPProc::OpContext*)+0x2022) [0x7fbb76a7a552]
 12: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> >&)+0x561) [0x7fbb76a8e7f1]
 13: (()+0xa7561d) [0x7fbb76a9161d]
 14: (()+0xa791c4) [0x7fbb76a951c4]
 15: (std::function<void ()>::operator()() const+0x19) [0x5638245bf2e9]
 16: (()+0x113f59) [0x7fbb7845ff59]
```
