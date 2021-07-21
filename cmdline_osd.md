#### 维护
|命令|功能|说明|
|:-|:-|:-|
|ceph tell osd.* injectargs --debug_osd |show value||
|ceph tell osd.0 injectargs --debug_osd 0/5 |set value||
|ceph daemon osd.0 dump_mempools|||
|ceph osd lspools||
|ceph osd pool ls||
|ceph osd pool ls detail||
|ceph osd df|OSD id，weight，size，usage，PGs|


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
