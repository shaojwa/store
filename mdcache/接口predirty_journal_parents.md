predirty_journal_parents

```
1. flag 如果有 PREDIRTY_PRIMARY 就表示，dentry是primary，primay的判断看linkage中的ino和remote_ino中谁不为0。
如果是primary，那么是需要调整nested的计数的。
 
1. flag 如果有 PREDIRTY_DIR，parent的概念是只 inode对应的dentry，这个需要记住。dentry的增加自然要影响所在目录的mtime和size。
所以如果有这个标记，说明说明需要吗，更新父目录的相关信息。

1. flag 如果有 PREDIRTY_SHALLOW，表示是浅标脏，估计只是对直接父目录更新，对更上层的父目录不更新。

1. stray_snapdir_processed 什么用处，暂时不知道。

1. 断言mdlog处于open状态。

1. 设置mds时间，这个mds_stamp是mds本地的时间，op_stamp是client提供的op时间。

1. 保证inode的mutex被已经被当前线程持有。

1. 如果当前inode是目录是base目录的inode，那么就返回，不用处理，base的范围是rootdir和mdsdir。

1. 如果parent cdir传入为空，那么flag一定有 PREDIRTY_PRIMARY 标记。
因为parent没传，说明还没有dentry出来，此时这个inode应该是刚创建。
所以通过get_projected_parent_dn()来获取到dentry。

1. parent这个dir的互斥锁也被当前线程获取到。

1. 如果flags 和 linkunlink都为空，那么只需要将parent放到，mdlog中，不清楚什么情况下会出现这种场景。

1. 将cur设置为当前的inode，first为true，开始循环。只要parent非空，就一直循环。最初parent为存放当前inode的目录分片。

    1. 断言当前mds是parent这个dir的权威。is_auth接口就是判断MDSCacheObject中的state字段是否有STATE_AUTH标记。
    1. 通过parent dir，拿到父目录对应的inode为pin（注意是父目录的inode）。
    1. 循环中的pinode和parent的mutex都应该被当前线程持有。
    1. 只要标记flag中没有PREDIRTY_FORCE_UNPUSH标记（这个标记是为rename的准备阶段用的），那么就需要将pinode和parent放到mut的锁集合中。

    1. 将parent和mdr相互添auth_pin，把parnet加入到mdr的project_fnodes集合中。

    1. 把parent这个dir新projec出一个fnode_t（fnode_t的用途和意义参见MDCache部分）
    1. parent调用pre_dirty()接口，这个接口只是把CDir的projected_version加一，并把版本返回给fnode_t fp;

    1. 如果 stray_snapdir_processed 为false，也就是没有处理stray和snapdir，但是处理的时候似乎只是对num_stray_snapdirs进行加减。
    只是在rename和unlink的时候用，别的op没有该处理流程。

    1. 如果需要处理parent的mtime，或者有增删（linkunlink），那么就需要进行处理。
    此时文件inode的filelock和nestlock的写权限都要被当前请求获取。
    然后父目录分片就要把fragstat和rstat更行到accounted_fragstat和accounted_rstat中。
    其实主要更新的就是rstat中的rctime，以及fragstat中的mtime，nfiles，nsubdirs几个字段。


    1. 如果dentry不是primary的，就什么都不做。
    1. 如果没有linkunlink，并且父目录inode的nestlock和versionlock中可以不能都拿到写权限，就调用mark_dirty_rstat(), 这个接口暂时还不知道具体操作。
    1. 如果linkunlink非空，那就是能断言，要么nestlock这个分散锁的的wrlock数量已经大于0，要么这个请求是slave的。
    如果mut的写锁集合中，没有pin->nestlock锁，那么去强制获得写锁???
    如果既不是RNAME相关的请求（flag中有PREDIRTY_FORCE_UNPUSH），并且pin也不是base目录，那么就将父目录的父目录放到reqlockset集合中。（为什么要这么做???）
    然后处理快照。
    调用父目录dir的resync_accounted_rstat接口（为什么这么做???）。
    project_rstat_inode_to_frag()
   ```
