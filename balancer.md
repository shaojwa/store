####　几个链接

     https://ceph.com/community/new-luminous-cephfs-subtree-pinning/

#### 根目录所在的子树一般是在rank值为0的mds上

    尽管在rank值为0的mds上，但是export_pin字段为-1，也就是并没有pin在rank值为0的mds上。

#### 每个active mds 都有一颗子树
  
    子树名为~mdsX，X即为该active mds 当前的rank值。
    
#### export dir会不会pin住
    
    export dir 会导致子树迁移，但是并不会pin住。所以很多时候 export dir之后，马上回迁移回来。

#### 要把一个dir pin在一个mds上

    setfattr -n ceph.dir.pin -v 1 /mnt/cephfs/tmp // 要bin住只能通过这种方式


