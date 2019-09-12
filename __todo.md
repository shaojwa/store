 
    ceph架构：https://docs.ceph.com/docs/master/architecture/
    rados论文：https://ceph.com/wp-content/uploads/2016/08/weil-rados-pdsw07.pdf
    crush论文：https://ceph.com/wp-content/uploads/2016/08/weil-crush-sc06.pdf
    osds-report-peering-failure：https://docs.ceph.com/docs/master/rados/configuration/mon-osd-interaction/
    https://yq.aliyun.com/articles/221507

#### 时钟跳变

    commit: a5fc29...b4b3
    http://tracker.ceph.com/issues/26962
    
#### MDS respawn的实现

respawn

#### ms_dispath线程的工作

* handle mds map 
* handle client 的request，一系列 handle_client_xxxx 接口操作。

#### beacon ms_dispath线程

#### md_submit 线程的工作

* 提交日志

#### fn_anonymous 线程的工作

* client 的请求处理commit日志之后的回调处理。


#### safe_timer 线程的工作

* MDBalancer::tick()

#### safe_timer 线程的工作

*　给mon发心跳

#### ms_local 线程做什么？

### service 线程

* 干什么呢？

#### admin_socket 线程的工作

* 处理admin_asok 的请求

#### pq_finisher线程
  
* PurgeQueue的finisher 线程， PurgeQueue队列是干什么的？

#### log 线程


#### mds中的subsystem

*　在 subsys.h中定义各个子系统以及日志等级

#### signal_handler 线程

#### recovery_thread 线程

#### mds_rank_progr 线程的作用
  
好像嗯哼一些内部的消息处（比如MDSInternalContextBase），laggy，shutdown等处理有关。
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
