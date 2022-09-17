#### 存储模型(storage model)

#### 1 node has N target (in Hard-ware)
#### 1 pool spans N nodes (1 shard/target)
pool中target的数量和pool创建时指定的node数量，以及每个node中的target数量有关系，是一个加权和。

#### pool
- pool是提供存储服务和隔离单元。一个集群含有的pool的量级是100。
- pool有UUID，维护着target的信息，放在poolmap里。
- 创建成功后，返回的是连接上下文（connection context）

#### container
- container有自己的独立的空间，是快照个数据管理单元。一个pool中含有的target的量级也是100。
- container也有UUID，创建成功后，返回的是container handle。

#### Objecter
- 一个pool中存放的objecter的设计量级是10亿。
- 对象还可以动态分片，Dynamic or static striping
- 唯一的 128-bit object address

#### shard 

## 硬件规格
#### Node/Server
一个集群系统，一般还有几千上万个node/server
#### Target
一个server上一般含有的Target量级为10

## 安全实现
#### dkey
distribution key

#### akey
attribute key 
