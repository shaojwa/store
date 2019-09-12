#### export_pin是针对目录的inode，子树是目录分片，会有不一致


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

#### 每个active mds 都有一颗子树
  
    子树名为~mdsX，X即为该active mds 当前的rank值。
    
#### export dir会不会pin住
    
    export dir 会导致子树迁移，但是并不会pin住。所以很多时候 export dir之后，马上回迁移回来。

#### 要把一个dir pin在一个mds上

    setfattr -n ceph.dir.pin -v 1 /mnt/cephfs/tmp // 要bin住只能通过这种方式


