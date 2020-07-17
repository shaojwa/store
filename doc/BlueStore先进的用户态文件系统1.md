https://zhuanlan.zhihu.com/p/45084771

1. 单机存储系统
1. FileStore的缺陷1：文件系统不支持很多上层的原子性操作不支持，也就是不支持事务，所以需要FileJournal，但是FileJournal导致写放大。
1. FileStore的缺陷2：文件系统本身的写放大。
1. 写分两种：覆盖写，追加写。
1. 覆盖写，对于ext4文件系统来说，数据写入1次，元数据操作2次（1次记录修改的inode，一次标记事务完成），元数据真正落盘1次，所以一共4次。
1. 追加写，因为需要修改superblock（总的空间在占用情况）以及bitmap（标记哪些空间已经占用，哪些可以释放），所以一共6次写入。
1. 对于读来说，没有缓存时（cold cache），需要读bitmap，superblock，dir，dentry，inode，数据等等。
1. 对于读来说，有缓存时（warm cache），缓存中有bitmap，superblock，dir，dentry，只需要读inode和数据。
