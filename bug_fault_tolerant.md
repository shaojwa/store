#### 第一个对象中有文件的layout和parent属性。
#### 获取文件的layout信息时往osd发送的请求。

先查看对象所在的主osd

    ceph osd map .capfs.data.datapool0 100000003ea.00000000
  
找到 acting set 为(4, 7, 5), pg 为 2.7b93bfe5  

然后发送查询请求：

    getfattr -n ceph.file.layout ddfile

发现osd4没有收到对应的请求，怀疑点是msd缓存中有对应的数据导致的，清掉缓存后再次尝试，发现并没有发往数据池，只能猜测是否从数据池。
先确定对象，因为数据池的对象都是目录对象，所以先找到ddfile所在目录的对象，以inode号命名，为1099511628777,16进制1000000039。
用ceph osd map查到10000003e9.00000000对应的osd集合为（2，1，0），所以找osd2所在的日志，时间区间在16:44:04.829624618和16:44:04:841199778 之间。
发现，请求确实发送给数据池，op是，CEPH_OSD_OPGETXATTR
