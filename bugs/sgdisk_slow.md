#### 现象

（1）执行sgdisk慢，卡主一分多钟才执行完。
（2）NAS节点上执行sync也很慢。

#### 系统配置

nproc = 32，负载达到 69

#### stack信息

    [root@host33 2267355]# cat /proc/2279183/stack
    [<ffffffffc08adc3c>] ceph_osdc_sync+0xec/0x150 [libceph]
    [<ffffffffc09a44d2>] ceph_sync_fs+0x42/0xc0 [ceph]
    [<ffffffff8928a860>] sync_fs_one_sb+0x20/0x30
    [<ffffffff89257009>] iterate_supers+0xb9/0x110
    [<ffffffff8928a964>] sys_sync+0x64/0xb0
    [<ffffffff897d6001>] entry_SYSCALL_64_fastpath+0x1f/0xb9 
    [root@host33 2267355]# cat /proc/2279183/stack
    [<ffffffff890b9d56>] io_schedule+0x16/0x40
    [<ffffffff891ae2de>] wait_on_page_bit_common+0x10e/0x1c0
    [<ffffffff891ae4c6>] __filemap_fdatawait_range+0x136/0x1b0
    [<ffffffff891ae5ae>] filemap_fdatawait_keep_errors+0x1e/0x40
    [<ffffffff89284628>] sync_inodes_sb+0x268/0x2b0
    [<ffffffff8928a5f5>] sync_inodes_one_sb+0x15/0x20
    [<ffffffff89257009>] iterate_supers+0xb9/0x110
    [<ffffffff8928a944>] sys_sync+0x44/0xb0 

#### sync 刷的是文件系统缓存，怎么查看需要下刷的大小？
