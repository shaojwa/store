https://zhuanlan.zhihu.com/p/46362124

1. BlueStore使用RocksDB来管理元数据。RocksDB需要文件系统，但是BlueStore没有文件系统。
1. 尽管RocksDB用满足POSIX协议的文件系统即可，但是POSIX文件系统中很多功能对RocksDB来说不是必须的，效率因此不高。

#### BlueFS功能特点
1. RocksDB需要的文件系统层次比较简单，数量少，文件层次单一。
1. 而BlueFS将存储空间划分为三层：慢速（Slow）空间、高速（DB）空间、超高速（WAL）空间。
1. BlueFS中不同空间可使用不同设备类型.log和BlueFS本身的journal优先用WAL空间，.sst优先用DB空间。
1. 随着固态盘 (SSD) 等全新存储设备以及3D Xpoint 存储等下一代存储技术的推出，使存储速度远高于磁盘。
1. 并将瓶颈从硬件（比如磁盘）移回至了软件（比如中断 + 内核）。

#### 
1. SPDK是什么？ 存储性能开发工具包。SPDK可以提供运行在用户态的NVMe 驱动程序。
1. 读写数据时， SPDK提供的用户态驱动程序可以轮询存储设备，所以不再需要中断。
1. SPDK 用户空间 NVMe 驱动程序可将总体延迟降低 10 倍。SPDK 可以运行在用户态？直接和存储设备交互，怎么实现的？
