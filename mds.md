#### 查看帮助都是用 -h
    ceph -h
    ceph mds -h
  
#### 将整形转为caps
    ceph  mds caps <caps_int>
 
#### 启动多mds
    ceph mds set max_mds  <val>

#### 查看当前那几个mds是active

    ceph mds stat # 当然也可以用 ceph fs status

#### 通过rank值找到节点的mds的元信息（最常用的是找到主机名）

    ceph mds metadata 0 # 找到rank值为0的mds节点信息

ceph mds 开头的常用命令就以上这么多，大部分功能都是通过ceph dameon 进行查询，通过ceph tell 进行设置。

