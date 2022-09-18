#### 同一个对象如果3副本，会放到单个不同的engine上，但是这三个不同的engine一定是不同的节点吗？
看数据的性质，如果是元数据，那么一定是高层的故障域，那么至少也是Node级别的，那样的化，数据一定是放到不同的Node上的。
而且，元数据的节点并不是集群中的每个节点，只有一部分节点提供元数据服务。

#### engine和node的关系是怎样的？
#### 同一个pool中的不同对象，可以用不同的冗余策略？
#### 三个副本策略下，读数据三个副本都可以读, 怎么确定读哪个副本？
#### write的io流程图中，途中涉及9个步骤，其中涉及的ULT好像只有2个左右，是哪两个？
#### 数据迁移的时候，down掉一个，是怎么保证只需要移动一个节点？
#### 什么是punch operations
#### 什么是out-of-band
## 存储模型 storage model


#### 算法
- bplus-tree (used for key index)
- rectangle-tree (used for value index)
- 正态哈希
- ring-based placement
- jump consistent hash
#### jump consistent hash
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

# DAOS 内部
## 组件
### 管理网络
an out-of-band TCP/IP network
### 数据网络
a high-performant fabric for data access.
### 管理 dmg
### 客户端 daos_agent
### 控制面 daos_server
### 数据面 daos_engine
## DAOS system
one daos-system = N daos-server
### DAOS server
- one daos-server = N daos-dameon-process
- 一个DAOS server 是多租户系统multi-tenant，有配置文件，YAML配置文件。
#### daemon processes.
- control plane, daos_server
- data plane, daos_engine
#### CART
#### PMDK
用于SCM的访问
#### SPDK
用于NVMe-SSD的访问
#### Rank
每个data-plane实例一个
### daos-agent
客户节点上的守护进程。

## 通信
三种通信通道dRPC，gRPC，CART
- daos_server(control-plane)和 daos_engine(data-plane)之间，用dRPC(基于UDS)
- daos_agent(client)和libdaos之间，用dRPC(基于UDS)
- daos_agent和daos_server之间，用gRPC
- libdaos和和daos_engine之间，用CART(基于RDMA，高带块，低延时) 

总结一下，同一个节点上的服务之间用dRPC通信，不同节点上，同控制面的交互用gRPC，同数据面的交互用CART。
