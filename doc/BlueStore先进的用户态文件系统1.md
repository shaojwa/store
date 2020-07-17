https://zhuanlan.zhihu.com/p/45084771

1. 单机存储系统
1. FileStore的缺陷1：文件系统不支持很多上层的原子性操作不支持，也就是不支持事务，所以需要FileJournal，但是FileJournal导致写放大。
1. FileStore的缺陷2：文件系统本身的写放大。
1. 写分两种：覆盖写，追加写。
1. 覆盖写，对于ext4文件系统来说，数据写入1次，元数据操作2次（1次记录修改的inode，一次标记事务完成），元数据真正落盘1次，所以一共4次。
1. 追加写，因为需要修改superblock（总的空间在占用情况）以及bitmap（标记哪些空间已经占用，哪些可以释放），所以一共6次写入。
1. 对于读来说，没有缓存时（cold cache），需要读bitmap，superblock，dir，dentry，inode，数据等等。
1. 对于读来说，有缓存时（warm cache），缓存中有bitmap，superblock，dir，dentry，只需要读inode和数据。
1. 流控机制不完整导致IOPS和带宽抖动。
1. 绕过本地文件系统层，直接管理裸设备，缩短IO路径。
1. 对象的数据和元数据管理分离，加上索引，提高效率。
1. 用KV索引，解决目录下文件遍历效率低的问题。
1. 预写式日志（WAL）。
1. BlueFS是BlueStore针对RocksDB开发的轻量级文件系统。BlueFSB是BlueStore的一部分。
1. 异常掉电、进程崩溃等突发情况。
1. 虽然硬盘本身可以保证在扇区级别写入的原子性，但是针对文件的写入数据一般包含多个扇区以及元数据更新，无法做到原子写。
1. ROW只需要保证元数据更新的原子性，而不需要保证数据写入的原子性，因为磁盘性能的提高，所以以前很少用的ROW现在越来越普遍。
1. RMW，非对齐覆盖写，要先读出来，然后再次写入。
1. 最小分配单元min_alloc_size的配置项。
1. BlueStore按照写入大小是不是min_alloc_size对齐，分别采用ROW和RMW+Journal的形式来完成。
