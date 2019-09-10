#### MDS 状态 replay

#### MDS 状态 resolve

resolve阶段是多活mds才有的阶段，这个阶段主要是处理分布式事务未提交成功的事件。
代码里分析来看，先是处理rollback_uncommitted_fragments，即回滚未提交的日志段，然后处理adjust_subtree_auth，即调整mds的子树权威，最后向其他mds做同步mdcache->send_resolves()

#### MDS 状态 reconnect

这里主要处理cephfs客户端重连任务，mds向monitor申请更新为reconnect状态后，monitor会向cephfs客户端发送当前active的mds信息，cephfs客户端在ceph_mdsc_handle_mdsmap中更新当前mdsmap，并向当前提升的mds发送reconnect请求。mds收到客户端重连请求后会将该客户端加入客户端列表中，并赋予相关caps。若客户端在mds_reconnect_timeout时间内未重新连接，mds会丢弃该客户端，若该客户端重连会被mds拒绝。

#### MDS 状态 rejoin

主要是实现mds之间缓存的同步，caps还有锁状态的同步。

#### ceph 的 mon 命令

ceph mds 开头的常用命令不多，这在ceph -h中称为 monitor命令，因为这些命令都是通过和mon交互进行的。

#### 查看帮助都是用 -h

    ceph -h
    ceph mds -h
  
#### 将整形转为 caps

    ceph mds caps <caps_int>
 
#### 启动多mds

    ceph mds set max_mds <val>

#### 查看当前那几个mds是active

    ceph mds stat 
    ceph fs status
    
#### 找到某个epoch的 mds map

    ceph fs dump <epoch>
    // 目前不清楚为什么 ceph mds dump <epoch> 返回的都是最新的版本

#### 通过rank值找到节点的mds的元信息（最常用的是找到主机名）

找到rank值为0的mds节点信息

    ceph mds metadata 0 

* mds的很多功能都是通过ceph dameon 进行查询，ceph daemon 命令属于 local命令，估计h和这些命令都是查询某个特定mds/osd/mon有关。
ceph daemon mds.mdsX 的帮助和 ceph 以及 ceph mds不同，不是用的-h，而是 ceph daemon mds.mdsX help，原因是这已经需要通过守护进程自己处理。

#### 查询 mds 的 id

    ceph daemon mds.mdsX status
    
mds的id一般在mds的日志中很少体现，主要用在mon中处理mds的心跳时，标记是哪个mds。这个是用来标记mds唯一性的，不容时间的rank值相同的两个mds，id也是不一样的。所以，这是一个mds的实例id，用来唯一标记某个mds实例。

#### 怎么看文件系统角度的性能
      
    ceph daemonperf mds.mds* 

#### MDS给mon的心跳异常超时时间

    10秒，mds_beacon_grace = 10s

#### ceph中默认的单个文件最大大小

    Option("mds_max_file_size", Option::TYPE_UINT, Option::LEVEL_ADVANCED)
    .set_default(70368744177664)
    .set_description("")
    
    70368744177664 = 64T
