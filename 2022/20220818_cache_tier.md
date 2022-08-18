https://docs.ceph.com/en/latest/rados/operations/cache-tiering/

#### tier 是什么意思
tier 就是一个层级， 和layer的概念类似，layer好像更倾向于逻辑上的层级（Logical layers）。
tier更适用于物理层次上的层级（Physical tiers）In other words, tiers are the physical deployment of layers.

- https://stackoverflow.com/questions/120438/whats-the-difference-between-layers-and-tiers


#### cache tier 作用
更好的IO性能

#### 为谁服务
ceph client

#### cache tier提供的数据范围
后端存储的一个子集， a subset of the data stored in backing storage tier

#### backing storage tier
后端存储

#### cache tier的实现方式
及时创建一个cache pool，对client来说 cache tier 和backing storage是透明的。


#### 引入的角色 agent
tiering agent determines when to flush objects from the cache to the backing storage tier.
