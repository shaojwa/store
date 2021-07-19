#### 维护命令
|命令|功能|说明|
|:-|:-|:-|
|ceph daemon osd.0 dump_mempools|||
||||

#### dump_mempools

#### 管理 osd daemon
```
systemctl start ceph-osd@2
systemctl stop  ceph-osd@2
systemctl restart ceph-osd@2
```

#### 设置池的副本数为1
```
ceph osd pool set .capfs.metadata.Metadata size 1
ceph osd pool set .capfs.data.datapool0 size 1
```

#### 显示所有的命令用
```
ceph osd --help
```
用 ceph osd help 只显示一部分。

#### bluestore的对象的元数据存储在什么地方
rocksdb
```
$ ceph daemon mds.mds0 config show | grep kvbackend
"bluestore_kvbackend": "rocksdb"
```
rocksdb 基于BlueFS写入裸设备。


#### 停止osd之后避免拉起
```
touch /var/lib/ceph/shell/watch_maintaining
```

##### 怎么查看某个版本的osd map
```
ceph osd dump <epoch>
```

#### down 和 out 什么区别

osd中down只是临时性故障，不会触发PG迁移。而out是mon检测到某个osd处于down超过一段时间，mon将其设置为out，即为永久性故障。  

#### mon把osd标记为out的日志
```
Marking osd.* out
```
  
#### OSD 和 MON 之间的心跳延时 
```
osd_heartbeat_grace = 20s
```

#### down 掉一部分osd 之后 inactive 的 PG 在一段时间后会减少

OSD reweight之后，部分pg的map会进行修改。

#### 三副本 down 掉数据池 3个 osd 之后，文件系统中的 inactive pg

对于三副本来说，stale的 pg 就是包含那三个 osd 的 pg

#### 一个4M的对象，纠删码2+1时怎么存？

```
一共三片，为2M + 2M + 2M，三个对象
```

#### 停止某个osd

```
systemctl stop ceph-osd@2
```

#### 停止osd之后避免拉起

```
touch /var/lib/ceph/shell/watch_maintaining
```

##### 怎么查看某个版本的osd map
```
ceph osd dump <epoch>
```

#### 怎么找到一个文件对应的对象

先找出文件的inode号：

```
$ ll -i
1099511628786 -rw-r--r-- 1 root root 6291456 test_file
```
在数据池中找到所有对应的对象：
  
```
$ rados -p <data_pool> ls
100000003f2.00000000
100000003f2.00000001
```
100000003f2 就是文件 file0 的inode号的16进制表示

#### 查看一个pool中的所有object

```
rados -p <pool_name> ls
```

#### 查看一个对象的stat信息
 
```
rados -p <pool_name> stat 10000003f2.00000000
```
 
#### osd向mon报告其他osd挂掉时的最少上报次数

```
mon_osd_min_down_reporters: "2"
```
 
#### 查看stale的pg

```
ceph pg dump_stuck stale
```

#### 查看某个pool的 io
 
```
ceph osd pool stats
```
 
#### 创建pool

```
ceph osd pool create mypool 16 16
```
 
#### 设置pool副本数

```
ceph osd pool set mypool size 4
```
   
一般setsize 之后，pool的PG对应的osd会马上发生变化。

#### 往池内写入一个文件

```
rados -p mypool put thekey pri_key
```

#### 查看池内所有文件

```
rados –p mypool ls
```
 
####  把池添加到文件系统中

```
ceph mds add_data_pool <pool> 
ceph fs add_data_pool <fs_name> <pool>
```

#### 指定目录的layout，属性叫ceph.dir.layout.pool

```
setfattr -n ceph.dir.layout.pool -v 5 ecpool
```

####  查看pool相关信息

ceph没有提供ceph pool的命令集，pool的相关操作在osd 下。

```
ceph osd pool ls
```
    
但是rados 提供直接针对pool的相关操作：

```
rados lspools
```

####  查看集群内所有pool状态

```
ceph df 
ceph df deatil
```

#### 查看一个pg开始scrub的时间

```
ceph pg <pg_id> query
```

#### pool的几个属性

* pool type：池的类型定义了数据持久化方式。
* Placement Groups：
* CRUSH Ruleset：
* Durability：可靠性

### 集群要做的事

```
数据持久化
数据完整性
数据备份
数据平衡
数据恢复
```
 
#### crash做的事

```
* 把一个对象所在的pg算出来
* 把一个pg对应的acting set 算出来。
```

#### pg 各种状态的含义

http://docs.ceph.com/docs/master/rados/operations/monitoring-osd-pg/

pg 的外部状态（蓝书146页）：

* active： 活跃状态，此时可以正常处理客户端的读写请求。

* clean：干净状态，不存在待修复对象，存在指定的副本数，acting-set 和 up-set 内容一致（蓝书）。

* perring：peer一个PG，就是ceph让这个pg中的osd，对这个pg中所有object的状态和元数据达成一致。状态的一致，不代表所有object的副本都为最新的数据。要注意的是，一个三副本的pg，因为一个osd down掉，此时只有两个osd up，那peering的过程就是保证这两个osd数据一致的过程，而不是等到另外选取一个osd后让这三个osd数据一致的过程。

* peered：peering已经完成, 但是acting-set规模小于最小副本数（注意是最小副本数，不是副本数）

* degraded：如果这个pg中的osd有一个down掉，或者找不到对应的osd，此时osd数目小于副本数，那么这个pg就会标记为degraded状态。同时，当写一个对象时，主osd写入之后，备osd返回完成写入之前的这段时间，这个PG也处于degraded状态，直到主osd收到osd的写入完成ack。


* recovering：一个osd因为某种原因down掉一段时间后重新up，此时的内容可能已经落后于最新的版本，所以这个osd就需要和最新的副本同步，此时反应到pg层的状态就是recovering，正在恢复。

* backfilling：回填，和恢复类似，只是这个osd是新加入的，一般回填在后台进行。（蓝书上说，backfillin总数在recovery完成之后进行？为什么？）

* incomplete：recovering或者backfilling失败，比如容量不够等。

* remapped：一般是pg对应的acting set发生变化，数据需要迁移。因为迁移需要时间，所以需要原有的set先服务一段时间，等下新的set数据迁移完成可以提供服务之后，就会启用新的acting set。在这段时间内，这个pg处于remapped状态？？？？

* stale：pg中的主osd没有上报pg统计信息给monitor时，就会被mon标记为stale状态，或者pg中的其他osd上报主osd已经down掉时。这个pg会被标记为stale。

其他不太常见的外部状态：

* Deep：总是和Scrubbing成对出现，表明将对PG中的对象执行深度扫描（即同时扫描对象的元数据和用户数据）。

* PG的down状态

PG的down：当前在线的osd不足以完成数据恢复，就会把一个pg表为down。和osd的down不一样。

其他问题：

* degraded 这个和undersized的区别是什么？undersized存储是acting-set小于存储池的副本数，而degraded可能是发现某个PG实例存在不一致（需要被同步或者修复），acting-size小于副本数只是导致degraded的一种原因。


#### pg 各种状态的含义

http://docs.ceph.com/docs/master/rados/operations/monitoring-osd-pg/

pg 的外部状态（蓝书146页）：

* active： 活跃状态，此时可以正常处理客户端的读写请求。

* clean：干净状态，不存在待修复对象，存在指定的副本数，acting-set 和 up-set 内容一致（蓝书）。

* perring：peer一个PG，就是ceph让这个pg中的osd，对这个pg中所有object的状态和元数据达成一致。状态的一致，不代表所有object的副本都为最新的数据。要注意的是，一个三副本的pg，因为一个osd down掉，此时只有两个osd up，那peering的过程就是保证这两个osd数据一致的过程，而不是等到另外选取一个osd后让这三个osd数据一致的过程。

* peered：peering已经完成, 但是acting-set规模小于最小副本数（注意是最小副本数，不是副本数）

* degraded：如果这个pg中的osd有一个down掉，或者找不到对应的osd，此时osd数目小于副本数，那么这个pg就会标记为degraded状态。同时，当写一个对象时，主osd写入之后，备osd返回完成写入之前的这段时间，这个PG也处于degraded状态，直到主osd收到osd的写入完成ack。


* recovering：一个osd因为某种原因down掉一段时间后重新up，此时的内容可能已经落后于最新的版本，所以这个osd就需要和最新的副本同步，此时反应到pg层的状态就是recovering，正在恢复。

* backfilling：回填，和恢复类似，只是这个osd是新加入的，一般回填在后台进行。（蓝书上说，backfillin总数在recovery完成之后进行？为什么？）

* incomplete：recovering或者backfilling失败，比如容量不够等。

* remapped：一般是pg对应的acting set发生变化，数据需要迁移。因为迁移需要时间，所以需要原有的set先服务一段时间，等下新的set数据迁移完成可以提供服务之后，就会启用新的acting set。在这段时间内，这个pg处于remapped状态？？？？

* stale：pg中的主osd没有上报pg统计信息给monitor时，就会被mon标记为stale状态，或者pg中的其他osd上报主osd已经down掉时。这个pg会被标记为stale。

其他不太常见的外部状态：

* Deep：总是和Scrubbing成对出现，表明将对PG中的对象执行深度扫描（即同时扫描对象的元数据和用户数据）。

* PG的down状态

PG的down：当前在线的osd不足以完成数据恢复，就会把一个pg表为down。和osd的down不一样。

其他问题：

* degraded 这个和undersized的区别是什么？undersized存储是acting-set小于存储池的副本数，而degraded可能是发现某个PG实例存在不一致（需要被同步或者修复），acting-size小于副本数只是导致degraded的一种原因。


