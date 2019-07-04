#### pg 各种状态的含义

http://docs.ceph.com/docs/master/rados/operations/monitoring-osd-pg/

pg 的外部状态：

* active： 活跃状态，此时可以正常处理客户端的读写请求。

* clean：干净状态，不存在待修复对象，存在指定的副本数，acting-set 和 up-set 内容一致（蓝书）。

* perring：peer一个PG，就是ceph让这个pg中的osd，对这个pg中所有object的状态和元数据达成一致。状态的一致，不代表所有object的副本都为最新的数据。要注意的是，一个三副本的pg，因为一个osd down掉，此时只有两个osd up，那peering的过程就是保证这两个osd数据一致的过程，而不是等到另外选取一个osd后让这三个osd数据一致的过程。

* peered：peering已经完成, 但是acting-set规模小于最小副本数（注意是最小副本数，不是副本数）

* degraded：如果这个pg中的osd有一个down掉，或者找不到对应的osd，此时osd数目小于副本数，那么这个pg就会标记为degraded状态。同时，当写一个对象时，主osd写入之后，备osd返回完成写入之前的这段时间，这个PG也处于degraded状态，直到主osd收到osd的写入完成ack。


* recovering：一个osd因为某种原因down掉一段时间后重新up，此时的内容可能已经落后于最新的版本，所以这个osd就需要和最新的副本同步，此时反应到pg层的状态就是recovering，正在恢复。

* backfilling：回填，和恢复类似，只是这个osd是新加入的，一般回填在后台进行。（蓝书上说，backfillin总数在recovery完成之后进行？为什么？）

* incomplete：recovering或者backfilling失败，比如容量不够等。

* remapped：一般是pg对应的acting set发生变化，数据需要迁移。因为迁移需要时间，所以需要原有的set先服务一段时间，等下新的set数据迁移完成可以提供服务之后，就会启用新的acting set。在这段时间内，这个pg处于remapped状态？？？？

* stale：pg中的主osd没有上报pg统计信息给monitor时，就会被mon标记为stale状态，或者pg中的其他osd上报主osd已经down掉时。这个pg会被标记为stale。

其他不太常见的外部状态：

* Deep：总是和Scrubbing成对出现，表明将对PG中的对象执行深度扫描（即同时扫描对象的元数据和用户数据）。

其他问题：

* degraded 这个和undersized的区别是什么？undersized存储是acting-set小于存储池的副本数，而degraded可能是发现某个PG实例存在不一致（需要被同步或者修复），acting-size小于副本数只是导致degraded的一种原因。


#### 如何查看一个对象的stat信息
 
    rados -p <pool_name> stat 10000003f2.00000000

#### mds_max_purge_ops_per_pg

平均每个pg进行purge操作的上限？

#### 查看一个pg scrub 的时间

  ceph pg <pg_id> query
  
