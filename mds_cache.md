## Dir Dentry 和 Inode 层次关系

回想下inode 和 对应的dentry 以及 cdir的关系。inode 是通过 parent找到它的 dentry，因为link的存在，parent可能会很多，所以有一个parent代表primary link，以及一个集合，叫remote_parent。而dentry怎么找到自己的CDir，就是dentry中的dir指针。而CDir中也有map叫items来存储dentry。所以CDir和CDentry关系比较密切。

考虑到dentry和dir都是逻辑上的概念，实际存储的时候都是inode，以inode为中心就可以理解清楚整个层次，也许也就比较好的理解inode中的parent的意思。

#### project系列方法的作用

见Cinode.h中的说明，projection 方法用来保存inode的变化，直到它们被记到日志中。记录日志之后，会被pop掉。

#### pop projected的接口

    pop_and_dirty_projected_inode()
    
#### 调用pop_and_dirty_projected_inode的地方

      Locker::file_update_finish()
      Locker::scatter_writebehind_finish()
      MDCache::subtree_merge_writebehind_finish()
      MDCache::_queued_file_recover_cow()
      MDCache::_snaprealm_create_finish()
      MDCache::_fragment_logged()
      MDCache::rollback_uncommitted_fragments()

      // 回调系列函数
      C_MDS_inode_update_finish::finish()
      C_MDS_inode_xattr_update_finish::finish()
      Server::_link_local_finish()  // C_MDS_link_local_finish::finish() 调用
      Server::_logged_slave_link()  // C_MDS_SlaveLinkPrep::finish() 调用
      Server::_logged_slave_link()  // C_MDS_SlaveLinkPrep::finish() 调用
      Server::_rename_apply()       // C_MDS_rename_finish::finish() 调用
      Server::_mksnap_finish()      // C_MDS_mksnap_finish::finish() 调用
      Server::_rmsnap_finish()      // C_MDS_renamesnap_finish::finish() 调用
      Server::_renamesnap_finish()    // C_MDS_renamesnap_finish::finish() 调用
      StrayManager::_truncate_stray_logged () // C_TruncateStrayLogged::finish() 调用


#### cache对osd相关的头文件引用

#### MDCache::disptch() 和 MDCache::disptch_request()

有一个要注意，disptch的是message，不是request，是比较底层的消息。

MDCache::dispatch() 用来处理 port 为 MDS_PORT_CACHE 类型的message，根据代码看，只处理MDS发过来的message：
    case MDS_PORT_CACHE:
        ALLOW_MESSAGES_FROM(CEPH_ENTITY_TYPE_MDS);
        mdcache->dispatch(m);
其中port什么用暂时不清楚，只知道是一个分类。比如还有一个 MDS_PORT_MIGRATOR 是迁移的，都是MDS内部之间的。


MDCache::dispatch_request(MDRequestRef& mdr) 有各种work函数。MDCache模块中有dispatch()接口：  
MDCache::dispatch_request() 处理的是request，即MDRequestRef，和dispatch是不在一个层次的东西。

请求分三类，client的，slave的，还有internal的。比如 CEPH_MDS_OP_ENQUEUE_SCRUB这个就是其中一个。
dispatch_request()主要在void C_MDS_RetryRequest::finish(int r) 这个回调函数里执行。

C_MDS_RetryRequest类中的回调都会执行dispatch_request(),这是一个比较上层的接口。

#### mds scrub 的流程

关键入口函数是 void MDCache::enqueue_scrub_work(MDRequestRef& mdr) 两种触发方式:  
一种是 void MDCache::dispatch_request(MDRequestRef& mdr), 因为OP是CEPH_MDS_OP_ENQUEUE_SCRUB触发，应该是命令执行时因为异常操作需要重试。
一种是 void MDCache::enqueue_scrub()触发，这种方式是响应命令做void MDSRank::command_scrub_path() 和void MDSRank::command_tag_path()时调用。

#### 加锁地方

scrub流程在调用mdcahe->enqueue_scrub()前获取mds_lock大锁。

#### 调用流程
    
    MDCache::dispatch_request(MDRequestRef& mdr)      
      enqueue_scrub_work(mdr); // internal op
        scrubstack->enqueue_inode_top()
          scrubstack->enqueue_inode_bottom()
            enqueue_inode()
              _enqueue_inode()
              kick_off_scrubs()
