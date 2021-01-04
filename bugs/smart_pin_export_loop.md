 直接设置有问题:
 
        dirinode->get_inode().export_pin = MDS_RANK_NONE;
        dirinode->maybe_export_pin(true);
        
应该要使用projected_inode(), 类似set_export_pin:

        void CInode::set_export_pin(mds_rank_t rank)
        {
          assert(is_dir());
          assert(is_projected());
          get_projected_inode()->export_pin = rank;
          maybe_export_pin(true);
        }
        
 而且在set之前应该先project一下：
 
        pi = cur->project_inode();
        cur->set_export_pin(rank); 
