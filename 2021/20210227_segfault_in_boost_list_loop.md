```
2021-02-27 19:27:07.548632 7f33957f7700 249309 37 ERROR *** Caught signal (Segmentation fault) **
 in thread 7f33957f7700 thread_name:Processer_5

 ceph version 12.2.1-UniStorOS_V100R001B51 (58e09e716a977f1334f980ab2aa26fd3f70fb183) luminous
 1: (()+0x4f4940) [0x555c5beeb940]
 2: (()+0xf6d0) [0x7f33a22d26d0]
 3: (RCache::_evict_objects(boost::intrusive::list<rcache_object_t, ..., void, void, void>&)+0x8a) [0x7f33a4b088aa]
 4: (RCache::_lru_cold()+0x355) [0x7f33a4b08f65]
 5: (RCache::_enqueue_cold(boost::intrusive::list<rcache_object_t, ..., )+0x319) [0x7f33a4b096c9]
 6: (RCache::_lru_warm()+0x370) [0x7f33a4b09b20]
 7: (RCache::_enqueue_warm(rcache_object_t&)+0xa4) [0x7f33a4b0ae34]
 8: (RCache::rcache_write(object_t const&, snapid_t, unsigned long long, unsigned long long, ceph:
 9: (DCacheOPProc::do_read(OSDOp&, DCacheOPProc::OpContext*)+0xe8f) [0x7f33a4a5dbef]
 10: (DCacheOPProc::do_dse_ops(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<OSDOp> 
 11: (DCacheOPProc::dcache_do_op_proc(DCacheOPProc::OpContext*, std::vector<OSDOp, std::allocator<
 12: (DCacheOPProc::do_op_operation(boost::intrusive_ptr<DSEOpRequest>)+0x2d0d) [0x7f33a4a676bd]
 13: (()+0x6852fd) [0x7f33a4a6b2fd]
 14: (()+0x114159) [0x7f33a5f94159]
 15: (co::Task::Run()+0xba) [0x7f33a5f942a6]
 16: (co::Task::StaticRun(long)+0x20) [0x7f33a5f94a4e]
 17: (make_fcontext()+0x21) [0x7f33a602b471]
 ```
 这种segment fault 在dmesg中并没有记录。查看出现错误的0x8a偏移量，我们发现：
 ```
 /rcache.cc:343
  7228a7:       4c 89 f6                mov    %r14,%rsi
boost::intrusive::list_node_traits<void*>::set_next(boost::intrusive::list_node<void*>* const&, ...)():
/boost/include/boost/intrusive/detail/list_node.hpp:66
  7228aa:       48 89 02                mov    %rax,(%rdx)
 ```
 知道这是boost中intrusive list的set_next(), 其实原因是两次循环iter没有变化，第一次release掉之后，再次erase就会有问题。
