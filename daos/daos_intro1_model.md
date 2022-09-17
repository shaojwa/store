## DAOS的存储模型和访问接口
#### pool
- 整个存储集群的一部分空间，包括了每台节点上，一部分的SSD，和一部分的PMem

#### Container
- 会分布在分配给Container所在的pool对应的每一个节点之上。

#### Objecter
- Container中的一个对象，可以看成是一个key-array-store
- 每个对象都有自己的数据保护策略。
- 包含metadata和Dkey-tree
- Dkey, distribution-key
- Akey, accurate-key
- key的缩影是b-plus tree
- arry的索引是
- 每个Object下可以挂很多Dkey，如果这个对象是大对象的话，这些Dkey可以分配到不同的节点上。
- 对key做正态哈希，分配套不通的存储引擎中。
- AKey， key->single value or Array extent。
- Objecter有固定大小吗？没有。
- 三副本，分配到三个存储他引擎上，不同副本会分配到不同引擎上，所以这个engine有点类似osd。
- 如果对象很大，在创建时是可以指定节点个数的。需要给一个hint。

#### Record

#### engine和节点的对应关系

#### 问题
- 同一个对象如果3副本，会放到单个不同的engine上，但是这三个不同的engine一定是不同的节点吗？
- 同一个pool中的不同对象，可以用不同的冗余策略？
