        
     arch 参考https://docs.ceph.com/docs/master/architecture/
     rados 参考：https://ceph.com/wp-content/uploads/2016/08/weil-rados-pdsw07.pdf
     
## 架构

ceph 独特地将对象，快，文件存储在一个统一的系统中进行交付。ceph是高可靠的、易管理的、并且是免费的。
ceph的力量在于可以改变公司的IT基础设施以及管理海量数据的能力。ceph能提供超强的可扩展性，上千个客户端访问PB甚至EB级别的数据。
ceph节点可以充分利用商用硬件以及智能的守护进程。而一个ceph存储集群可以容纳大量的ceph节点，这些节点之间相互通信来进行的复制以及动态的重新分布。

* APP 使用 LIBRADOS，或者 RADOSGW
* HOST/VM  使用 RBD  （基于LIBRADOS）
* CLIENT 使用 CEPHFS （基于LIBRADOS）
  
### ceph 存储集群

ceph 基于RADOS提供一个无限可扩展的存储集群。

一个存储集群由两类守护进程组成 monitor 和 osd。

一个monitor维护一个cluster map的主副本，一个monitor集群可以保证子一个monitor节点失效情况下的高可用。
客户端从monitor处获取到 cluster map的一个从副本。

osd会检查自己的状态以及其他osd的状态并上报给monitor。

存储集群的client是以及每一个osd都使用CRUSH算法来高效得计算关于数据位置的信息，以避免依赖一个中心化的查找表。ceph的上层特性包括：
（1）通过librados 提供一个native 的接口给ceph存储集群。
（2）基于librados的一些列服务接口。

####　数据存储

ceph集群从clients那收到数据，不管是通过 block device，还是object，还是 filesystem，甚至是通过librados的一个用户实现。
ceph集群以object来存储数据。每一个对象对应一个文件，存储在设备上（如果存储引擎是filestore），osd进程处理存储磁盘上的读写操作。
  
osd进程把所有的数据存储在对象中，这些对象都在一个扁平的命名空间中。每个object都用一个id，二进制的数据，以及由name/value的集合组成的元数据。
语义完全基于client，比如cephfs使用元数据来存储文件的属性，比如所有者、创建时间、修改时间等，
  
#### 可扩展性和高可用性

 在传统的结构中，client直接和中心化的组件进行交互。这个组件作为进入复杂子系统的单一入口。这个限制了性能以及可扩展性，同时引入了单点故障。
 ceph通过让client和osd直接交互来消除中心化的网关。ceph通过创建在其他节点上创建对象副本来保证数据的安全性和可用性。
 ceph也通过一个monitor集群来保证高可用。为了消除中心化，ceph使用一个叫做CRUSH的算法。
 
 #### CRUSH 介绍
 
 
  
  


    
  
  
  
