## CRUSH 所对应的技术点
从分布式系统的基本技术点角度来说，CRUSH属于数据分区策略。即将一个对象放置在什么位置。最理想的情况，我们可以只用一层分区策略，来决定一个数据分片放置到什么节点。
在设计这种完美的数据分区策略时，我们必须要意识到一点？数据分区，同时也意味着数据重分布。这是和数据分区相伴随的一个问题。

我们知道，数据分布策略常常有以下几种：

- 基于关键字区间分区。

这种分布和字典差不多，一个或者多个关键字分为一个区间，这个区间对应到特定的存储区域。这种分区方式的一个最直接问题是，容易产生局部热点。
关键字不加处理地进行分区，是导致这个问题的直接原因。访问本身是存在局部性的，我们需要将这种局部性消除，那么直接使用和访问信息强相关的关键字就不可避免存在这种问题。

- 基于关键字哈希值

既然关键字区间存在局部热点问题，要消除这种局部性，首先想到的就是随机化，即通过hash进行打散。hash之后，数据的分部几乎是均匀的，而且访问也几乎是均匀的。看起来很好。
但是，我们必须知道，没有绝对的更好，hash这种方式带来的明显问题是，连续范围查找（或者说区间查询）速度变慢，连续的几个关键字查找，经过hash之后，完全打散。
那么意味着连续关键字的访问是全集群范围内的查询。其实在我看来，关键字区间分区所带有的有序相邻特性并不重要，关键字连续区间的查找并不是分布式系统的性能关键点。
关键字的hash方式拥有的均衡和无序也许是一个很大的优点。无序化之后，数据分区的边界就可以均匀分布。

## CRUSH 需要解决的问题
我们明确知道，我们需要hash来打散，但是打散函数有很多，比如MD5就是一个很好的打散函数，是不是打散了就解决了分布问题？不是的。
我们有hash值，只是第一步，只是明确，我们希望避免负载倾斜。我们需要将hash值进一步和存放的位置对应起来。
如果我们有100个节点，那么怎么将打散后的值和具体的位置对应就是下一步要解决的问题。最简单的，我们可以取模，`hash % node_num = node_index`。
看起来很完美，但是存取只是一个需求，我们前面说过，任何分区分布策略，都需要考虑两点，一是数据访问，二是数据再平衡。
如果集群不会出任何故障，节点数量也不变，取模当然已经足够。但是集群是肯能发生扩容缩容，也有不可避免的故障。当节点发生变化时，数据需要重新均衡。
如果只是取模，那么大部分的hash值是会重新分布的。一旦出现故障，数据的重分布产生的带宽需求会严重影响系统的可用性。

现在，数据的再平衡遇到问题，因为节点变化，导致分区数量变化，这会导致再平衡成本的增加。要解决这个问题，有两个基本思路：
1. 有没有更好的hash值到节点的映射算法，导致节点发生变化时，重平衡成本不会那么高。
2. 分区的数量可否固定，即，底层节点数量的变化，不会导致分区的变化。

对于思路2，其实并不是解决问题，而只是避开问题，即使添加一层固定的分区数量，那么分区数量和底层的节点之间依然需要解决数据再分布问题。
所以，这是一个绕不过去的问题，我们需要找到一种更好分区策略，让重分布的成本不会那么高。

## 分区到节点的分布策略

现在来到了最关键的点，分区到节点的分布策略设计，如何将分区均匀分布到节点，同时又尽可能降低重平衡的成本？
很直观的一种方式是，如何将分区的一部分数据进行移动，或者节点上部分分区进行迁移。很显然，这意味着集群内分区数量要大于节点数。
一个节点上存取多个分区。那么现在的问题还是数据分分布策略问题？

其实，这种问题也叫做服务发现问题，这并不仅限于分布式系统。根据DDIA中的介绍，这种问题通常有三种处理方式，而我个人最认可的自然是第三种方式：
客户端感知分区和节点的分配关系，此时客户端就可以直接连接到目标节点，而不需要任何中介。这是一个很有挑战性的问题！

## CRUSH的创新
