#### object placement（基于伪随机算法）
- 我拿到一个对象，没有存储位置的matadata，通过算法来确定位置。
- 数据可以移到另外一个存储引擎上，这个是可以的。
- service-leader会告知其他节点，某个节点完成，这是一个全局的监控，而不是参与重建。

#### 数据保护与数据自修复 
- Health-monitoring （SWIM protocal，类似）
- Rebuild protocol

#### Self-healing process
- Failuer-detection by running SWIM
- Data recover by running rebuild protocol (Replication: reconstuct replica, EC: reconsturct data or parity cell)

#### DAOS 的数据是一个多版本(multi-version)
- 每次数据都会有索引，每一个索引也是一个write-log

#### VOS 存储的模块
versioning-object-store

#### EC aggregation

#### 读数据三个副本都可以读
- 读哪个怎么确定？

#### 问题
- 数据迁移的时候，down掉一个，是怎么保证，值需要移动一个节点？
