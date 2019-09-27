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

看dirty数据， 从/proc/meminfo 中有dirty字段

#### meminfo中buffer 和cache 的区别？

https://jin-yang.github.io/post/linux-memory-buffer-vs-cache-details.html

buffer = buffer cache，cache = page cache。 

原先 buffer 用来指写缓存，cache 用来指读缓存。

现在，buffer cache 用来指 块管理缓存（内存以块 block 进行管理，所以叫block cache更合适），page 用来指页管理缓存（内存以页进行分配管理）。

所以现在文件的IO 缓存都用 page cache，而buffer cache 用来优化块设备IO。

Short answer: Cachedis the size of the page cache. Buffers is the size of in-memory block I/O buffers.Cached matters; Buffers is largely irrelevant.

Long answer: Cached is the size of the Linux page cache, minus the memory in the swap cache, which is represented by SwapCached(thus the total page cache size is Cached+ SwapCached). Linux performs all file I/O throughthe page cache. Writes are implemented as simply marking as dirty the corresponding pages in the page cache; the flusher threads then periodically write back to disk any dirty pages. Reads are implemented by returning thedata from the page cache; if the data is not yet in the cache, it is firstpopulated. On a modern Linux system, Cached can easily be several gigabytes. It will shrink only in response to memory pressure. The system will purge the page cache along with swapping data out to disk to make available more memory as needed.

Buffers are in-memory block I/O buffers. They are relatively short-lived. Prior to Linux kernel version 2.4, Linux had separate page and buffer caches. Since 2.4, the page and buffer cache are unified and Buffersis raw disk blocksnot represented in the page cache—i.e., not file data. The Buffers metric isthus of minimal importance. On most systems, Buffers is often only tens ofmegabytes.
