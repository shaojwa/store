#### dir dentry 和 inode

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
