#### 停掉一个节点上的所有ceph服务

```
systemctl stop ceph.target 
```

#### 刚写入的文件没有layout和parent属性是为什么

元数据没有下刷，flush journal 一下就可以：
```
ceph daemon mds.mdsX flush journal
```
#### 为什么在dir目录下的touch操作不需要dir目录inode的 Fx 权限
问题： 因为在dir下创建dentry，相当于写dir的inode，似乎需要Fx权限。

client的wanted权限是AsLsXsFsx，但是issued的是pAsLsXsFs。handle_client_openc中的接口rdlock_path_xlock_dentry()中说明：
/path/to/dir里的所有dentry都是rdlock，新创建的dentry需要xlock。应该是对dentry获取独占锁就可以，以保证不会被其他客户端占用。


#### 重新加载 mds 进程
```
ceph tell mds.0 respawn 
```

#### 对某个mds标fail
```
$ceph mds fail <rank>
failed mds gid 3589
```

#### 怎么修复damage mds
```
ceph mds repaired 0 
```
告诉mon，mds已经修好

#### mds 查询命令选择
```
总结来说，ceph fs 命令比 ceph mds 命令多一个standy信息，子命令 dump 比 stat/status 多一个IP信息。
如果要查询所有active, 那么用 ceph mds stat
如果要查询所有active以及standby, 那么用 ceph fs status
如果要查询那些mds的ip信息，那么就用 ceph mds dump
如果要查询所有active以及standby的ip, 那么用 ceph fs dump
```

#### ceph 的 mon 命令

ceph mds 开头的常用命令不多，这在ceph -h中称为 monitor命令，因为这些命令都是通过和mon交互进行的。

#### 查看帮助都是用 -h
```
ceph -h
ceph mds -h
``` 
#### 将整形转为 caps
```
ceph mds caps <caps_int>
```
#### 启动多mds
```
ceph mds set max_mds <val>
```
#### 查看当前那几个mds是active
```
ceph mds stat  // stat = status
ceph fs status
```

#### 找到某个epoch的 mds map
```
ceph fs dump <epoch>
```
目前不清楚为什么 ceph mds dump <epoch> 返回的都是最新的版本

#### 通过rank值找到节点的mds的元信息（最常用的是找到主机名）
```
// 找到rank值为0的mds节点信息
ceph mds metadata 0
```

mds的很多功能都是通过ceph dameon 进行查询，ceph daemon 命令属于 local命令，估计h和这些命令都是查询某个特定mds/osd/mon有关。
ceph daemon mds.mdsX 的帮助和 ceph 以及 ceph mds不同，不是用的-h，而是 ceph daemon mds.mdsX help，原因是这已经需要通过守护进程自己处理。

#### 查询 mds 的 id，也就是 gid
```
ceph daemon mds.mdsX status
```
    
mds的id一般在mds的日志中很少体现，主要用在mon中处理mds的心跳时，标记是哪个mds。这个是用来标记mds唯一性的，不同时间的rank值相同的两个mds，id也是不一样的。所以，这是一个mds的实例id，用来唯一标记某个mds实例。

#### 修复mds日志
```
MDS 修复
cephfs-journal-tool journal inspect 
cephfs-journal-tool journal reset --force 
```

#### 避免因为子目录频繁操作而导致父目录频繁更新的参数
```
mds dirstat min interval
```

#### 查看删除文件后purge的速度阀门

删除文件后台的对象删除时异步，删除的限制可以参见：
```
ceph daemon mds.mds0 config show | grep mds_max_purge_ops_per_pg
```

#### mds 和 mon之间的心跳

mds主动发送给mon，mds收到回应，并计算rtt (round-trip time)时间，从mds发出报文开始，到收到mon回复为止。  
seq_stamp中记录每一次的发送时间，当收到一条ack时，就会拿这条信息的发送时间去更新last_acked_stamp。
last_acked_stamp 记录的是最近一条得到ack回复的心跳的mds的发送时间。
然后计算rrt，发送的时间和当前收到消息时间之差。
如果mds的时钟出现回退，mds会把自己标记为laggy，mds日志里也会有显示。

#### mds 发送给 mon 心跳间隔是几秒
```
mds_beacon_interval = 4
```

#### mds 发送给 mon 心跳宽限期是几秒
```
mds_beacon_grace = 15s
```

#### 怎么看文件系统角度的性能
```
ceph daemonperf mds.mds* 
```

#### MDS给mon的心跳异常超时时间
```
mds_beacon_grace = 10s
```

#### ceph中默认的单个文件最大大小

```
Option("mds_max_file_size", Option::TYPE_UINT, Option::LEVEL_ADVANCED)
.set_default(70368744177664)
.set_description("")
```

70368744177664 = 64T

#### 文件的layout信息是存放在什么地方？

存在放文件的第一个数据对象的xattr中，可以通过以下命令看到：
```
$ rados -p <data_pool> listxattr 100000003f2.00000000
layout
parent
```

#### 文件的layout信息怎么看

文件一旦创建就会有一个layout信息，可以通过以下命令查看：

    getfattr -n ceph.file.layout test_file

其中一般信息是：
    
     ceph.file.layout="stripe_unit=4194304 stripe_count=1 object_size=4194304 pool=.data.pool0

文件的layout和parent信息是放在数据池的第一个对象中的，而目录的这两个信息是在元数据池中的。

#### 目录分片

目录分片合并大小： 
```
mds_bal_merge_size = 50
```

触发目录分片

```
dirfrag split <path> <frag> <bits> 
dirfrag split /data/dir1 0x200000/3 2 
```

倒数第二个参数 0x200000/3 是分片标记，固定24bit，0x20000是16进制的value, 3表示这个分片的现有bit。
最后一个参数 2 是bits，对目录分片（可能已经分片的）进行再次分片的bit。
所以执行以上命令之后，一共的分片是11 =（2^3-1+2^2）

查看mds是否允许分片：
```
#define CEPH_MDSMAP_ALLOW_DIRFRAGS (1<<3)
$ ceph dms dump
flags e
```
e = 1110 允许分片 

#### mds 性能
```
ceph daemon mds.0 perf dump [mds|mds_cache|mds_log|mds_server|mds_sessions|objecter]
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
"mon_osd_min_down_reporters": "2"
```
 
#### 查看stale 的pg

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
  
#### mds_max_purge_ops_per_pg

平均每个pg进行purge操作的上限？

## rados

查看某个目录的所有对象：
```
[root@node11 dirfrag]# rados -p .capfs.metadata.Metadata ls | grep 10000000003
```

目录对象的omap是空：
```
[root@node11 data]# rados -p .capfs.metadata.Metadata listomapkeys 10000000003.00000000
[root@node11 data]#
```

目录对象的xattr是：
```
[root@node11 data]# rados -p .capfs.metadata.Metadata listxattr 10000000003.00000000
layout
parent
```

分片对象的omap是：
```
[root@node11 data]# rados -p .capfs.metadata.Metadata listomapkeys 10000000003.03200000  | head -2
file10020_head
file10023_head
```

分片对象的xattr是：
```
[root@node11 data]# rados -p .capfs.metadata.Metadata listxattr 10000000003.03200000
[root@node11 data]#
```

查看目录分片系数和大小：
```
[root@node12 ~]# ceph daemon mds.mds1 config show | grep split_bits
    "mds_bal_split_bits": "3",
[root@node12 ~]# ceph daemon mds.mds1 config show | grep split_size
    "mds_bal_split_size": "10000",
[root@node12 ~]#
```

#### 日志中的字段
```
7fa20d3fe700 2094980 2 DEBUG
pthread_t, syscall(SYS_gettid), sched_getcpu(), -1:ERROR 0:WARNING 1:INFO >1: DEBUG
```
这个是后续版本添加的。
