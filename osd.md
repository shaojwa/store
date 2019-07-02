#### pg 各种状态的含义

http://docs.ceph.com/docs/master/rados/operations/monitoring-osd-pg/

pg 的外部状态：

* active： 活跃状态，能在正常处理客户端的读写请求。

* clean：干净状态，不存在待修复对象，存在指定的副本数。

* perring：peer一个PG，就是ceph让这个pg中的osd，对这个pg中所有object的状态和元数据达成一致。状态的一致，不代表所有object的副本都为最新的数据。要注意的是，一个三副本的pg，因为一个osd down掉，此时只有两个osd up，那peering的过程就是保证这两个osd数据一致的过程，而不是等到另外选取一个osd后让这三个osd数据一致的过程。


#### mds_max_purge_ops_per_pg

平均每个pg进行purge操作的上限？


