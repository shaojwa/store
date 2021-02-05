
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
