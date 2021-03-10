#### 部署顺序流识别

/etc/ceph.conf文件
```
rbd_readahead2 = true
```
在改存储节点执行
```
kill -9 tgtd
```

#### 测试集群网络配置
```
管理网: 182.200.65.111/16
前段网: 172.17.65.111/24
存储网: 192.169.65.112/24
```

#### 新池的数据
```
[root@node0]# rados -p blkpool0 df
POOL_NAME USED OBJECTS CLONES COPIES MISSING_ON_PRIMARY UNFOUND DEGRADED RD_OPS RD WR_OPS WR SIZE_ACCURACY
blkpool0     0       0      0      0                  0       0        0      0  0      0  0             0

total_objects    269
total_used       27053M
total_avail      16730G
total_space      16756G
```

#### rcache中对象的evcit
destage下刷完成之后，或者透写模式写入row之后，都会调用rcche的对象evict操作，粒度是对象，无法只evict部分数据。

#### 存储前端网段不能与RDMA卡上IP同网段
```
vim /opt/h3c/lib/python2.7/site-packages/onestor/plat/cm/cluster/cluster_util.py +426
```

#### 日志等级
```
debug_engine = 4
debug_dse = 4
```
#### 日志一致性检测
各位后面测试日志恢复相关用例的时候，在下IO之前，将日志一致性检测功能打开：
```
ceph daemon dse.node64 engine all dcache lsm plus_on
```

#### engine-id 中的 pool-id
是系统中原生池的id，一个原生池对应一个dse池和一个dcache池。
dcache池用来存储原生池的日志。
dse池用来存储ROW对象的元数据。

#### op_cancel_dse engine_timeout

在engine的日志中会出现`failed to open db` 说明底层数据混乱，多个dse操作同一个engine 的 rocksdb，需要重新创建pool。
```
3159819 60 ERROR row init failed to open db, r = -5
3159819 51 ERROR row init failed to open db, r = -5
```
要发现这个问题，可以先看dse中有没有如下的日志`try_boot wait for`


#### 全闪版本数据读取
1. 块的数据读取，都会先从DCache读，DCache如果没有，就从ROW读。
1. 块如果需要预取，直接给opproc下发预取op，opproc读取数据后写入ROW。

#### 预取的触发
```
blk开启顺序流识别特性之后，会主动去预取，然后干两件事（1）写入Rcache（2）写入ROW
```

#### 每一种硬盘池都有一种属性
块，还是文件，还是对象。

#### 块存储的硬盘池
每个块存储硬盘池下最多只能创建一个pool。

#### 块池的副本策略
用3副本

### 免高可用方式
install完product在部署前，修改:
```
# /etc/onestor/onestor.conf
handy_ha_needed = no
```
就可以不用配置`handyha`，完了执行`supervisorctl restart all`

#### 跑 FIO
```
fio -direct=1 -ioengine=rbd -group_reporting -name=mytest -bs=8K -iodepth 10 -numjobs 1 \
  -size=10G -rw=randread -pool=.111.rbd -rbdname=test10g5
```

#### dse/dcache pools
```
data: pool_a -> dcache.pool_a(dcache_log_pool for pool_a) + .pool_a.dse (pool for ROW)
meta: .diskpool8.rbd-> dcache..diskpool8.rbd + ..diskpool8.rbd.dse
```

#### instance_id
```
instance_id = poolid << 16 + engineid
```

#### ENV
```
[root@node231 etc]# cat onestor_external_version
UniStorOS-E1151
Release date 2020.10.22
[root@node231 etc]# cat onestor_internal_version
NAS V200R001B01D001
ONEStor V300R001B05D001
UniStorOS V100R001B51D001
NAS V100R003B02D008
```
