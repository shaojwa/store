#### get subtrees中的 auth_first 和 auth_second 是什么意思？

#### get subtrees中的 export_pin 看到的是什么

子树的单位是dir，这里的export_pin是dir对应的inode的export_pin属性。

如果子树目录路径中，任何一层dir对应的inode 的 export_pin不是MDS_RANK_NONE就返回对应的export_pin值。

所以，如果 get subtrees 里看到的是 -1，说明这个目录的任何一层dir都没有pin住。

#### export_pin是针对目录的inode而子树的单位是目录分片

export_pin的话，一个目录都pin在一个rank上，就算这个目录有多个分片，也都会固定在一个上面。

动态迁移基于目录分片，既然是动态迁移，export_pin就会是-1，所以这是俩个功能，不矛盾。

#### set export pin 之前应该先project一下：

        pi = cur->project_inode();
        cur->set_export_pin(rank);

应该要使用projected_inode(), 类似set_export_pin:

        void CInode::set_export_pin(mds_rank_t rank)
        {
          assert(is_dir());
          assert(is_projected());
          get_projected_inode()->export_pin = rank;
          maybe_export_pin(true);
        }
        
#### 链接

     https://ceph.com/community/new-luminous-cephfs-subtree-pinning/

#### 根目录所在的子树一般是在rank值为0的mds上

    尽管在rank值为0的mds上，但是export_pin字段为-1，也就是并没有pin在rank值为0的mds上。
    
#### mds.0 上都保存根目录的对应的子树

    根目录是CAPFS，inode是1（umount之后为139772829），data目录不是根（inode是0x10000000001）。

#### 每个active mds 都至少有一颗子树
  
    子树名为~mdsX，X即为该active mds 当前的rank值。
    
#### export dir会不会pin住
    
    export dir 会导致子树迁移，但是并不会pin住。所以很多时候 export dir之后，马上回迁移回来。

#### 要把一个dir pin在一个mds上

    setfattr -n ceph.dir.pin -v 1 /mnt/cephfs/tmp // 要bin住只能通过这种方式
