* ceph mds 开头的常用命令不多，这在ceph -h中称为 monitor命令，估计是因为这些命令都是通过和mon交互进行的。

#### 查看帮助都是用 -h
    ceph -h
    ceph mds -h
  
#### 将整形转为caps
    ceph mds caps <caps_int>
 
#### 启动多mds
    ceph mds set max_mds <val>

#### 查看当前那几个mds是active

    ceph mds stat #当然也可以用 ceph fs status

#### 通过rank值找到节点的mds的元信息（最常用的是找到主机名）

    ceph mds metadata 0 # 找到rank值为0的mds节点信息

* mds的很多功能都是通过ceph dameon 进行查询，ceph daemon 命令属于 local命令，估计h和这些命令都是查询某个特定mds/osd/mon有关。
ceph daemon mds.mdsX 的帮助和 ceph 以及 ceph mds不同，不是用的-h，而是 ceph daemon mds.mdsX help，原因是这已经需要通过守护进程自己处理。

#### 查询mds的id

    ceph daemon mds.mdsX status
    
mds的id一般在mds的日志中很少体现，主要用在mon中处理mds的心跳时，标记是哪个mds。这个是用来标记mds唯一性的，不容时间的rank值相同的两个mds，id也是不一样的。所以，这是一个mds的实例id，用来唯一标记某个mds实例。


#### 怎么看文件系统角度的性能
      
    ceph daemonperf mds.mds* 
