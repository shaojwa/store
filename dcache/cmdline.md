#### 全闪版本数据读取
块的数据读取，都会先从Dcache读，DCache如果没有，就从ROW读。

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
就可以不用配置handyha，完了执行supervisorctl restart all

#### rdb 命令
Command-line interface for managing Ceph RBD images.
```
rbd ls -p .111.rbd 
rbd debug_ls -p .111.rbd
```

#### 跑 FIO
fio -direct=1 -ioengine=rbd -group_reporting -name=mytest -bs=8K -iodepth 10 -numjobs 1 -size=10G -rw=randread -pool=.111.rbd -rbdname=test10g5

#### dse/dcache pools
```
data: pool_a -> dcache.pool_a(dcache_log_pool for pool_a) + .pool_a.dse (pool for ROW)
meta: .diskpool8.rbd-> dcache..diskpool8.rbd + ..diskpool8.rbd.dse
```

#### instance_id
```
instance_id = poolid << 16 + engineid
```

#### engine dump
```
ceph engine dump
```

#### env
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

#### IO
```
rados -p 1 bench 1200 write -b 8192 
// -p 1: pool
// 1200, seconds
```

```
ceph daemon dse.node23 engine 12.4 config set debug_engine 5
ceph daemon dse.node23 engine all dcache desage get_info
ceph daemon dse.node23 engine 12.4 dcache desage get_info

ceph daemon dse.node23 engine all dcache qm get_quota
ceph daemon dse.node23 engine 12.4 dcache qm get_quota
```

#### osd
```
ceph osd lspools
ceph osd pool ls
ceph osd pool ls detail
```
