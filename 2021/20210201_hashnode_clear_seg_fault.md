## 现象
messages 日志
```
Jan 29 17:55:59 node104 ceph-dse: *** Caught signal (Segmentation fault) **
Jan 29 17:55:59 node104 ceph-dse: in thread 7fd22d2b9700 thread_name:Processer_6 
```

log 日志
```
2021-01-29 17:55:59.593087 7fd22d2b9700 2905611 13  INFO
  Dcache_destage: destroy_destage destage all success before destroy destage
2021-01-29 17:55:59.593100 7fd22d2b9700 2905611 13  INFO Dcache_destage: destroy_destage destroy_destage OK!
2021-01-29 17:55:59.593127 7fd22d2b9700 2905611 13  INFO Dcache_lsm:lsm_destroy start to destroy lsm.
2021-01-29 17:55:59.593138 7fd22d2b9700 2905611 13 DEBUG Dcache_csdc:csdc_get_dcachepool_id dcache_pool_id: [63]
2021-01-29 17:55:59.593141 7fd22d2b9700 2905611 13  INFO Dcache_lsm:lsm_release_all_csdobj start to release all csd obj.
2021-01-29 17:55:59.593144 7fd22d2b9700 2905611 13  INFO Dcache_lsm:lsm_release_all_csdobj release all csd obj success.
2021-01-29 17:55:59.593145 7fd22d2b9700 2905611 13
  DEBUG Dcache_csdc:csdc_destroycsdc_destroy start, storage_pool_id[64], engine_id[5]
2021-01-29 17:55:59.593950 7fd22d2b9700 2905611 13  INFO Dcache_lsm:operator() finish the lsm release task.
2021-01-29 17:55:59.593958 7fd22d2b9700 2905611 13  INFO Dcache_lsm:lsm_destroy finished to destroy lsm. 
```

dmsg 日志现象:
```
[Fri Jan 29 17:56:02 2021] Processer_5[2905610]:
segfault at 0 ip 00007fd23b6e020f sp 00007fc79d505b60 error 4 in libdcache.so[7fd23ac16000+13d4000] 
```
## 分支
AF_ALL分支

## 分析
0x7fd23b6e020f - 0x7fd23ac16000 = 0xaca20f

```
objdump -lS --start-address=0xaca10f --stop-address=0xaca30f ./libdcache.so | c++filt > libdcache_segfault.asm
```

```
/dse/dcache/dm/dm.cc:958
  aca1ee:       4d 39 ef                cmp    %r13,%r15
  aca1f1:       0f 84 ee 01 00 00       je     aca3e5 <dm_hash_node_t::clear()+0x225>
  aca1f7:       66 0f 1f 84 00 00 00    nopw   0x0(%rax,%rax,1)
  aca1fe:       00 00
  aca200:       48 83 05 50 90 28 01    addq   $0x1,0x1289050(%rip) 
  aca207:       01
erase_and_dispose<dm_hash_node_t::delete_dm_obj_t>(): /boost/include/boost/intrusive/list.hpp:667
  aca208:       49 8d 9f d0 fe ff ff    lea    -0x130(%r15),%rbx
boost::intrusive::list_node_traits<void*>::get_next(boost::intrusive::list_node<void*>* const&)():
  aca20f:       49 8b 2f                mov    (%r15),%rbp
  aca212:       48 83 05 06 98 2a 01    addq   $0x1,0x12a9806(%rip)        # 1d73a20 
  aca219:       01
  aca21a:       49 8b 07                mov    (%r15),%rax
boost::intrusive::list_node_traits<void*>::get_previous(boost::intrusive::list_node<void*>* const&)():
/boost/include/boost/intrusive/detail/list_node.hpp:54
  aca21d:       49 8b 57 08             mov    0x8(%r15),%rdx
```
2905610 这个task是ceph-dse进程。 ceph-dse.node104.log-2021-01-29-214110中有日志显示，这段时间在掉析构。


#### 场景还原
1. 2021-01-29 17:55:59 engine.5 shutdown
```
2021-01-29 17:55:59.592906 7fd22aab4700 2905616 8 DEBUG engine.5 40161 shutdown
2021-01-29 17:55:59.592920 7fd22aab4700 2905616 8  INFO DCACHE_CTRL:DCache_shutdown:start to shutdown.
2021-01-29 17:55:59.593043 7fd22aab4700 2905616 8  INFO DCACHE_CTRL:DCache_shutdown:waite to finish shutdown.
2021-01-29 17:55:59.593055 7fd22d2b9700 2905611 13  INFO Dcache_opproc:  begin to destroy opproc, flying_op_cnt = 0
```


#### 进一步分析
engine64.4和 64.d 中的两个线程在destory lsm，几乎同时。
```
ceph-dse.engine.64.4.log-2021-01-29-214110:2021-01-29 17:55:59.593085 7fd22daba700 2905610 3  INFO Dcache_lsm:lsm_destroy start to destroy lsm.
ceph-dse.engine.64.5.log-2021-01-29-214110:2021-01-29 17:55:59.593127 7fd22d2b9700 2905611 13  INFO Dcache_lsm:lsm_destroy start to destroy lsm.
```
从日志看，触发segment fault的的是 7fd22d2b9700，也就是 7fd22d2b9700。而触发message中的是 2905610。

还是怀疑重复释放的问题，走读代码：
```
 if (!destroy_eng.empty()) {
    increase_task_tid();
    ::co::TaskOpt opt = {MY_MID, 0, processer_alloc.get_processer(1), true, 0, 0, __func__, __FILE__, __LINE__};
    coroutine_sched->CreateTask(
      [destroy_eng, this]() {
        this->shutdown_engine(destroy_eng, false);
        this->delete_engine(destroy_eng);
        this->decrease_task_tid();
      },
      opt
    );
  }
```
