逻辑PG, 整个集群概念中的唯一的集合，是设计上的概念。
而针对不同的副本策略，这同一个PG需要参与这个PG的节点共同维护，代码层面的这个PG概念的实现，就是PG实例，PG中的每个osd都会维护这个PG。

所以，创建存储池中指定的PG数目是逻辑PG数目，为了数据的可靠性，Ceph会将每个逻辑PG转换为多个实例PG，由它们负责将对象的不同备份或者部分写入不同的OSD。
如果使用多副本，那么每个逻辑PG被转换为与副本数相等的PG实例。

对副本来说，每个PG实例区别不大，但是也都有一个主要的PG，一般是CRUSH返回的第一个OSD充当。
但是对于纠删码来说，每个PG，osd都只存储一个shard。所以每个PG之间都需要明确区别身份。
