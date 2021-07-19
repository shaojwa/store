https://ceph.io/en/news/blog/2017/new-luminous-bluestore/
## OSD 的内存使用

#### FileStore 的好处
在用FileStore时，其中的一个好处是，内核会管理数据和元数据的内存缓存，内核甚至可以用所有的RAM来缓存数据和元数据，直到需要释放空间。

#### BluseStore的问题
因为BlueStore实在OSD的用户态内存空间实现的，是OSD的一部分，需要我们自己管理cache，所以我们只有很少的管理工具。

#### BlueStore 中的 bluestore_cache_size 配置
用来配置BlueStore中的cache大小，可以根据需要调整，在HDD盘中，这个只默认是1G，SSD中是3G。

#### ceph 中OSD进程内存统计问题
默认的tcmalloc 会导致OSD进程的RSS空间，比OSD自己认为的要大1.5倍左右，这可以通过以下命令查看：
```
ceph daemon osd.0 dump_mempools
```
