## desc

```
-1> 2021-04-19 10:18:59.295735 7f9e08ff1700 155093 26 DEBUG mid_dse_control 245
    is_oid_belong_local_host rbd_data.3.a76a3da9ad55.000000000000b7b4 6 belong to engine:6.7 bucket:6.f6d
0> 2021-04-19 10:18:59.298558 7f9e08ff1700 155093 26 ERROR /src/dse/dcache/dm/dm.cc:
In function 'void DataManager::dm_write_obj_data(const hobject_t&, const dm_data_oper_t&, const bufferlist&)'
thread 7f9e08ff1700 time 2021-04-19 10:18:59.295960
/src/dse/dcache/dm/dm.cc: 170: FAILED assert(oper.snap_seq >= obj->get_first_snapid())

2021-04-19 10:18:59.687959 7f9e08ff1700 155093 35 ERROR *** Caught signal (Aborted) **
 in thread 7f9e08ff1700 thread_name:Processer_5

12.2.1-UniStorOS_V100R001B51 (cca98c01ed371be93f0c26b488492a292d079bcf) luminous (stable)
 1: (()+0x632d90) [0x563531efcd90]
 2: (()+0xf6d0) [0x7f9f1a9146d0]
 3: (gsignal()+0x37) [0x7f9f13b90277]
 4: (abort()+0x148) [0x7f9f13b91968]
 5: (ceph::__ceph_assert_fail(char const*, char const*, int, char const*)+0x185) [0x7f9f1d8055b5]
 6: (DataManager::dm_write_obj_data(hobject_t const&, dm_data_oper_t const&, ...)+0x6be) [0x5635321e1efe]
 7: (DCacheLineSpaceManager::lsm_recovery_write_log(char*, unsigned short, ...)+0x31f) [0x5635321f261f]
 8: (DCacheLineSpaceManager::lsm_do_recovery(char*, ...)+0x7a5) [0x5635321f8ff5]
 9: (DCacheLineSpaceManager::lsm_recovery_by_csdobj(CSDObjId, ...)+0x14b) [0x5635321f936b]
 10: (DCacheLineSpaceManager::lsm_recovery_log()+0x2e2) [0x5635321f9d22]
 11: (DCacheInstance::DCache_start(unsigned char)+0x7e9) [0x5635322087d9]
 12: (EngineService::DCache_create_instance(unsigned char, init_step)+0x5cc) [0x563531c557ac]
 13: (()+0x11401d) [0x7f9f1d15e01d]
 14: (co::Task::Run()+0xba) [0x7f9f1d15e16a]
 15: (co::Task::StaticRun(long)+0x20) [0x7f9f1d15e938]
 16: (make_fcontext()+0x21) [0x7f9f1d203331]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
 ```
