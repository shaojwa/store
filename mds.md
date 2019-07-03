#### ms_dispath 线程的工作

* handle client 的request，一系列 handle_client_xxxx 接口操作。

#### md_submit 线程的工作

* 提交日志

#### fn_anonymous 线程的工作

* client 的请求处理commit日志之后的回调处理。



#### safe_timer线程的工作

* MDBalancer::tick()

#### ms_local 线程做什么？

### service 线程

* 干什么呢？

#### admin_socket 线程的工作

* 处理admin_asok 的请求

#### pq_finisher线程
  
* PurgeQueue的finisher 线程， PurgeQueue队列是干什么的？

#### mds中的subsystem

*　在 subsys.h中定义各个子系统以及日志等级

#### signal_handler 线程

#### recovery_thread 线程

#### lease相关的时间配置有哪些？
#### Mutex::Locker l(mds->mds_lock) 是如何获取锁的？
#### cond.Wait(mds->mds_lock) 是如何释放锁的？
#### systemctl中的ceph-mds.service 和ceph-mds.target有什么区别？
#### 对象的omap和xattr有什么区别？
#### dir_auth_pin和auth_pin的区别是什么？

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

#### 文件的layout信息怎么看

文件一旦创建就会有一个layout信息，可以通过以下命令查看：

    getfattr -n ceph.file.layout test_file

其中一般信息是：
    
     ceph.file.layout="stripe_unit=4194304 stripe_count=1 object_size=4194304 pool=.data.pool0

文件的layout和parent信息是放在数据池的第一个对象中的，而目录的这两个信息是在元数据池中的。

#### 文件的layout信息是存放在什么地方？

存在放文件的第一个数据对象的xattr中，可以通过以下命令看到：

    $ rados -p <data_pool> listxattr 100000003f2.00000000
    layout
    parent
     
#### 怎么找到一个文件对应的对象？

  先找出文件的inode号：
  
    $ ll -i
    1099511628786 -rw-r--r-- 1 root root 6291456 test_file
  
  在数据池中找到所有对应的对象：
  
    $ rados -p <data_pool> ls
    100000003f2.00000000
    100000003f2.00000001
   
   100000003f2 就是文件 file0 的inode号的16进制表示
   
  #### 如何查看一个对象的stat信息
 
      rados -p <pool_name> stat 10000003f2.00000000
