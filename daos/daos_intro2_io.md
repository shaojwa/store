#### server 中的poll-thread
- CART来数据。
- 创建ULT（userspace-lightweight-thread） 来handle 这个RPC。
- 如果是大数据，那需要启动一个Buld transfer，通过RDMA，
- 一个盘创建1-2个线程，避免pthread带来的开销。
- 在一个PMDK的transaction里，把SSD中的存储分配和元数据一次性写入PMEM中。用这个transaction来避免space leak。

#### 多副本支持
- client 把请求（注意不是数据）发到primary-server上，这个primary-server把这个request转发给其他engine，通过RPC。
- 每个engine读取完成数据的io，从client侧通过RDMA获取数据。
- 多副本的原子性通过2-phase-commit这个协议来完成。
- perimary-server收到其他server的回应之后，马上就会恢复给client，来减小延迟，没有做server之间的commit。

#### primary-server的选举和个数
- 每个objecter都有自己的primary-server（通过hash算法来选）。
- 三副本来说，这个对象的primary-server是固定的，甚至是以对象中的key为单位来选举primary-server。

#### rdb （raft database）
- RDB是只用来存系统的元数据，不存用户的元数据，和IO没有关系。
- 一个pool选了64个节点，是哪64个节点，这些系统的元数据，是存在RDB里的。
- 用户的元数据是存在container之内的，这些数据我们不走raft，raft太慢，走2pc。
- leader的选举用的hash算法，是一致性hash。

#### 扩容支持
- 支持节点级的扩容，不支持加盘。8台服务器可以变成12台是支持的。但是没太服务器中的盘数目前不支持扩容。

#### 问题
- write的io流程图中，途中涉及9个步骤，其中涉及的ULT好像只有2个左右，是哪两个？
