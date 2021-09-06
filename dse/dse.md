
# 设计问题
## 为什么需要 DSE ？
（1）从总体架构上，使用全闪模式，总体提高性能。
（2）对数据做串行化、聚合、以及数据存储效率方面做加速，串行化就是dcache+LSM，聚合加速就是ROW，存储效率就是重删压缩。
所以，需要在用户数据和OSD之间加入一层控制，来解决上述问题。

## DSE 有哪些组件？
dse, engine, dcache, row, dedup, gc, csd

## dcache 需要解决什么问题
解决小IO的性能问题，将小IO先写入日志进行加速，随机写变成顺序写。


## 需要ROW 的主要目的是什么？
ROW 就是将多个小IO合并成一个顺序大IO，提高写性能。


# 实现问题
## DSE中的op分发怎么实现
dse进程中存在op分发模块，对象op路由到指定的engine上进行处理。

## DSE需要做的故障处理
dse进程故障处理（节点故障，或者进程重启，触发engine实例切换），其中的engine实例需要重新分配，dse进程故障导致业务归零时间在15秒以内。

## 节点扩容缩容和故障恢复
1. 在新节点上创建engine，触发部分bucket迁移到新的engine上。
2. 存储池的增减对应engine非变化。
3. 节点故障导致的 engine的故障切换，是指框架部分的业务处理，不包括dcache，ROW，dedup等子模块的处理。

## dse进程各个engine实例中，各个流程的IO信息统计，调试命令。

## DSE的IO路径是怎样的？
（DSE）：dse_client可以是kcephfs, libcephfs, rbd, rgw等等。以rbd为例，rbd拿到engine_map之后，和对应节点上的DSE发消息，DSE转发消息到engine上。
在dse_client角度来说，看到的是user_obj，user_obj找到对应的engine。

（ENGINE）：engine进行判断处理之后，传给dcache，dcache有两个选择，一个是回写缓存，那么走LSM 和 DM。 另外一个选择是透写走ROW。

（LSM+DM+destage）：如果走LSM和DM，那么需要后端csd的支持，csdc和csd交互，存储日志，日志一般存在nvme设备中。destage异步把数据下刷到ROW中。
日志LSM对象，写入dcache池，用户对象数据和元数据都在一起。现在常见的部署环境下，每个NVME盘都有一个100G的分区，用来给csd用。这些csd存储日志对象的数据。
但是日志对象的元数据存在哪里呢？每个节点，本地都有一块共享的空间，用来存放LSM对象的元数据。csd在收到日志对象的数据和元数据之后，接下来就是本地存储的事情。


（ROW）：如果是走透写，那么IO是同步的，会等待ROW的返回。ROW会把user_obj进行聚合。ROW主要干的事情就是对小的user_obj进行聚合存储，变成row_obj。
row_obj就是这些用户对象的的聚合对象。ROW然后写OSD，数据一旦到了OSD，是本地存储的事情。row_obj聚合对象分两部分，一部分是元数据，一部分是数据。
元数据写入rocksdb，需要bluefs支持。数据直接写入bluestore。


## user_obj 映射到 engine的方法
user_obj 中，计算出bucket_id，bucket_id 可以算出在哪个engine上。

## DSE进程的作用
通过dse达到集群拓扑管理（节点增删，存储池增删）

## DSE 中processor的分配
DSE有内置的processer的数量，参见接口`parse_module_processer()`，另外也会读取配置文件中的`processer_allocation`配置。
比如dcache默认配置4个processor，csd有4个，dse有1个。

## dse进程中，每个存储池4个engine实例（engine拓扑管理）
```
ceph engine ls
```
可以看到所有的引擎数量，除以节点数，就是每个节点上的引擎数量，然后除以每个节点上的池数量，就可以看到，目前一个节点上，单个池对应4个引擎。

## bucket的作用
UserObject Hash 到 bucket(类似于PG)， bucket 再通过类似CRUSh映射到engine（类似于OSD），节点增加后，部分bucket就会映射到新的engine。
DSE中的bucket，类似于RADOS中的PG概念，用来存放对象。hobject_t是CEPH原生的结构。 bucket_t是DSE新添加的结构。
bucket_t是MEngineOp中的一个属性，MEngineOp定义在messages/MEngineOp.h中, 和 hobject_t hobj, engine_t engineid并列。
bucket_t的实际作用是将hobject路由到正确的engine_id上。实例上的bucket数量和平均值偏差应该控制在在1/10以内。

## DSE 中的 op分发模块
dse进程中存在op分发模块，对象op路由到指定的engine上进行处理。

## DSE需要做的故障处理
dse进程故障处理（节点故障，或者进程重启，触发engine实例切换），其中的engine实例需要重新分配，dse进程故障导致业务归零时间在15秒以内。
