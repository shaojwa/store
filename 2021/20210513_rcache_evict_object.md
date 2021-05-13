## rcach_evict_object  segment fault
liyuehong

core-Processer_4-39301-1620861817

## analyze

```
2021-05-13 07:23:37.291550 7f4b367fa700 39394 7 ERROR *** Caught signal (Segmentation fault) **
 in thread 7f4b367fa700 thread_name:Processer_4

 ceph version 12.2.1-UniStorOS_V100R001B51 (aabc2ebd290e429360ec4d617061d7f11b1015ac) luminous (stable)
 1: (()+0x676ad0) [0x560c6ee35ad0]
 2: (()+0xf6d0) [0x7f4bce3bd6d0]
 3: (RCache::rcache_evict_object(object_t const&, std::string const&)+0x2f1) [0x560c6f158611]
 4: (Destage::release_dcache_objs()+0x7e) [0x560c6f0dd06e]
 5: (Destage::destroy_destage()+0x99) [0x560c6f105b89]
 6: (DCacheInstance::DCache_shutdown_intask(co::CoSem&, bool&, int)+0x176) [0x560c6f14ac96]
 7: (()+0x116b96) [0x7f4bd1527b96]
 8: (co::Task::Run()+0xc9) [0x7f4bd1527d07]
 9: (co::Task::StaticRun(long)+0x2f) [0x7f4bd1528515]
 10: (make_fcontext()+0x21) [0x7f4bd15f9d61]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
```


## result
error nspace access by iter:
```
obj_iter = destage_views[i]->objs.erase(obj_iter);
rcache->rcache_evict_object(temp_destage_obj->dm_user_obj->obj_id, obj_iter->dm_user_obj->nspace);
```
