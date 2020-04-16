#### done
```
gather.new_sub() 什么设计模式？
#include <boost/thread/shared_mutex.hpp> 其中shared_mutex是一种读写锁
```

#### todo

```
要实现根据校验有无来决定是否创建对象的接口，如何命名？
ceph::unordered_map<string, Dentry*> dentries;
unordered_multimap
compact_map
lsm-tree (rocksdb, leveldb)
https://www.cnblogs.com/hukey/p/11910741.html
```

#### 打快照需要持有哪些锁？

#### io超时为什么需要respawn

#### mds 中的信号处理？？

#### mds是怎么发送信号实现respawn的
    
#### migrator

智能pin的mds停用会怎么样？

如果设置了智能pin, 在第一期从mds.0迁出去的时候，如果超时cancel 会怎么样？

#### stary

stray对象好像是共用的， stray对象怎么清理呢？

本mds的stray目录会有副本在其他mds吗？

#### journaler

* mds中flush的延时为什么这么长？

#### ms_async_affinity_cores 配置项功能？

#### beacon
    
*　MDS respawn的实现

*  时钟跳变是什么问题？

    commit: a5fc29...b4b3
    http://tracker.ceph.com/issues/26962

#### ms_local 线程什么作用？

### service 线程什么作用？

#### pq_finisher线程什么作用？
  
* PurgeQueue的finisher 线程， PurgeQueue队列是干什么的？

#### log 线程什么作用？

#### signal_handler 线程什么作用？

#### recovery_thread 线程什么作用？

#### mds_rank_progr 线程什么作用？
  
一些内部的消息处（比如MDSInternalContextBase），laggy，shutdown等处理有关。
查看ProgressThread::entry()发现，它主要是处理finished_queue里的消息。

#### ProgressThread::entry()为什么一开始就需要获取到锁mds_lock？
ProgressThread::entry() 会在一开始获取到锁，然后cond.Wait(mds->mds_lock);释放锁后会尝试再次获取锁。
 
#### 为什么需要 auth_pin？

auth_pin的目的是两部分：
一是数据的auth不会改变，就是数据不会被迁移。
二是pin，就是数据已在在内存中，不会trim掉。ceph中，inode，dentry，dir都有auth_pin。

#### freeing和frozen是做什么用的？

如果子数要迁移，就先原先变成frozen状态，就是冻住的状态才能迁移。而子树要变成froezen必须要把所有的auth_pin置零。
所以，正常情况下用get subtrees中某棵子树 dir下的is_freeing 和is_frozen 都是false的。


#### 根子树以及~mds0子数的auth mds都是都是在rank=0 的mds上，原因是什么？

是因为总得有个默认的么？root能迁移么？

#### lease的作用是什么？

lease是处理dentry相关的，lease机制，客户端缓存部分cap，减少客户端发往mds的请求。
   
#### lease相关的时间配置有哪些？
#### Mutex::Locker l(mds->mds_lock) 是如何获取锁的？
#### cond.Wait(mds->mds_lock) 是如何释放锁的？
#### systemctl中的ceph-mds.service 和ceph-mds.target有什么区别？
#### 对象的omap和xattr有什么区别？
#### dir_auth_pin和auth_pin的区别是什么？
#### mds中的_rename_prepare_witness是做什么的？

### 权威 元数据 cache 更新后，是怎么通知副本 更新的，但是 version相同？ 

发现副本常常没有及时更新。

### 客户端发送请求，怎么选择MDS？

### dump inode 中的 accounted_rstat 是什么意思？

### flush cap 是做什么的 ？

内核代码上看，flush cap是在fsync的流程中调用。fsync 会把所有的in-core data of file 落盘，也会把所有的元数据下刷。

而ydatasync不一样，fdatasync只会下刷部分元数据，比如 atime 和 mtime的改变不会在fdatasync中下刷。
因为这些信息对后续的read操作来说并不是必须的。而size就不一样，它就会要求一次元数据的flush，在fdatasync中也会刷下去。

flush 好像是在dirtry上用？

### 为什么 flush cap的 dispatch时间这么久？

通过perf工具看到，一般请求的 dispatch_latency只有5k多微秒，而update_caps分别达到50k微秒，flush_caps甚至达到80k多。分析下原因。

在MDS测看到，CEPH_CAP_OP_UPDATE，CEPH_CAP_OP_FLUSH 这两种OP都属于 CEPH_MSG_CLIENT_CAPS。

正常处理的创建，删除等操作对应的OP是 CEPH_MSG_CLIENT_REQUEST。

这两类OP都是在handle_deferrable_message接口中处理的，为什么CEPH_MSG_CLIENT_CAPS慢这么多？

调用栈：

    mds_rank->ms_dispatch(m)
    MDSDaemon::ms_dispatch()


### mds 的 replica_nonce 是什么作用？

## clients
### 客户端发送请求，怎么选择MDS？

用户态发送请求调用make_request()接口, 有默认参数 mds_rank_t use_mds=-1，当然也可以自己指定。

对stat调用发出的_getattr来说用的是-1，make_request()自己会选择mds，具体怎么选得继续看。

### stat 和 statx 什么区别

libcephfs提供ceph_lstat, lstat 和stat一样，除非path参数是symbolic link，lstat 返回时的 symbolic link 本身的数据。

cephfs.pyx提供的是lstat，和stat。

libcephfs 提供的是 ceph_lstat，和 ceph_statx, ceph_lstat 没有在libcephfs.h 中导出，只在libcephfs.cc中导出。

client提供了，lstat，stat 和 statx。

fill_stat() 有配置影响size显示的是什么。

    cct->_conf->client_dirsize_rbytes。 
    
     int Client::stat(const char *relpath, struct stat *stbuf, 
            const UserPerm& perms, frag_info_t *dirstat, int mask)
            
       int Client::statx(const char *relpath, struct ceph_statx *stx,
            const UserPerm& perms, unsigned int want, unsigned int flags)
            
 从形式上看，statx通过want 和 flags 算出mask，stat直接给mask。 statx是可以在want中指定要获取什么字段，比如默认的 CEPH_STATX_BASIC_STATS。cephfs.pyx 用的是ceph_statx，而不是ceph_stat。

```
https://docs.ceph.com/docs/master/cephfs/
论文：https://ceph.com/wp-content/uploads/2016/08/
mds论文：https://ceph.com/wp-content/uploads/2016/08/weil-mds-sc04.pdf
rados论文：https://ceph.com/wp-content/uploads/2016/08/weil-rados-pdsw07.pdf
crush论文：https://ceph.com/wp-content/uploads/2016/08/weil-crush-sc06.pdf
ceph架构：https://docs.ceph.com/docs/master/architecture/
osds-report-peering-failure：https://docs.ceph.com/docs/master/rados/configuration/mon-osd-interaction/
https://yq.aliyun.com/articles/221507
https://docs.oracle.com/cd/E37670_01/E37355/html/ol_repair_xfs.html
```
