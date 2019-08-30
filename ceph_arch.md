        
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

#### 数据存储

ceph集群从clients那收到数据，不管是通过 block device，还是object，还是 filesystem，甚至是通过librados的一个用户实现。
ceph集群以object来存储数据。每一个对象对应一个文件，存储在设备上（如果存储引擎是filestore），osd进程处理存储磁盘上的读写操作。
  
osd进程把所有的数据存储在对象中，这些对象都在一个扁平的命名空间中。每个object都用一个id，二进制的数据，以及由name/value的集合组成的元数据。
语义完全基于client，比如cephfs使用元数据来存储文件的属性，比如所有者、创建时间、修改时间等，
  
#### 可扩展性和高可用性

 在传统的结构中，client直接和中心化的组件进行交互。这个组件作为进入复杂子系统的单一入口。这个限制了性能以及可扩展性，同时引入了单点故障。
 ceph通过让client和osd直接交互来消除中心化的网关。ceph通过创建在其他节点上创建对象副本来保证数据的安全性和可用性。
 ceph也通过一个monitor集群来保证高可用。为了消除中心化，ceph使用一个叫做CRUSH的算法。
 
 #### CRUSH 介绍
 
ceph clients 和 osd进程都使用CRUSH算法拉高效得计算关于对象位置的信息。CRUSH提供一个比老方法更好的数据管理机制。
并且通过将负载分散到所有的clients和集群中的所有osd来支持海量的扩展。CRUSH使用智能数据复制来保证弹性，这更加适合超大规模存储。

#### cluster map

ceph依赖于具有集群拓扑信息的客户端以及拥有osd进程。包括5个map，这5个map被统称为cluster map。

* monitor map：集群的fsid，位置，每个monitor的名字以及端口。 同时也标记当前的epoch（map是什么时候创建的以及最后一次修改时间）。
通过运行 ceph mon dump 来查看mon map。

* osd map：包括fsid，map创建以及最后一次修改的时间，pools列表，副本数，PG数，osd列表以及状态，查看osdmap，运行 ceph osd map。

* PG map： 包括PG版本，以及时间戳，最后的OSD map epoch，使用率，以及每个PG的详细信息（PG ID， Up set， acting Set， PG状态）以及每个pool的使用率统计信息。

* CRUSH map：包括存储设备列表，故障域层次关系（即，device，host，rack，row，room等），以及存储数据时遍历层次关系的规则。查看 CRUSH map，执行：
 ceph osd getcrushmap -o {filename}; 然后通过 crushtool -d {comp-crushmap-filename} -o {decomp-crushmap-filename} 来反编译后，通过文本表机器或者cat查看。
 
* MDS map：包括当前MDS map epoch，map创建的时间，最后一次修改时间，以及元数据池，元数据服务器列表，以及每个元数据服务器的状态，通过 ceph fs dump查看看MDS map。

#### 高可用 monitors

在客户端可以读写数据之前，client必须链接monitor来获取最近的cluster map副本。一个ceph集群可以在单一monitor下运行，但是这回引入单点故障。
为增强可靠性以及容错，ceph支持monitor集群。在monitor集群中，潜在的以及其他错误会导致一个或多个节点落后于当前集群状态，因为这个原因，ceph必须在多个moniter之前对集群的状态达成一致。ceph总是使用多数monitors原则以及Paxos算法去建立一致性。

#### 高可用性认证

为了标识用户以及保护免收中间人攻击，ceph提供cephx认证系统来对用户和守护进程进行认证。

cephx并不解决数据传输过程中的数据加密问题。

cephs使用共享秘钥进行认证，即client和monitor集群都有一份client的秘钥。认证协议能让任何双方都可以在不透露秘钥的情况下，向对方证明自己持有一份秘钥的拷贝。这就提供相互认证，即cluster确信，用户拥有秘钥，而用户也确信集群持有一份秘钥的拷贝。（怎么做到的？）

ceph的一个关键的可扩展性是避免一个中心化的接口来存储对象。也就说，client必须可以和OSD直接进行交互。为了保护数据，ceph提供cephx认证系统，系统能认证作为客户端的用户，cephx协议的运行方式和kerberos有些类似。

用户通过ceph client 来连接一个monitor，不同于Kerberos，每个monitor可以认证用户以及分发keys，所以cephx没有单点故障或者瓶颈。
monitor返回一份认证数据结构，和Kerberos中的ticker类似，这份数据包括一个session key，用来获取ceph 服务。
这个session key是通过用户的永久性的secret key加密过的。所以，只有这个用户可以从monitor那请求服务。
接下去，用户使用这个session key 项monitor请求需要的服务。然后monitor提供给客户单一个ticket，用来认证client对osd的访问，osd实际处理数据。
monitor以及osd共享秘钥，所以client可以用monitor提供的ticket和集群中的任何OSD或者MDS使用。
和Kerberos类似，ticket会过期，所以攻击者不能使用一个过期的窃取的ticket或者session key。
这种方式的认证可以避免攻击者用某个用户的id伪造消息，或者篡改其他有某个用户的合法消息。
只要用户的secret 可以在过期之前不被泄露。

要使用cephx，管理员必须先创建用户，client.admin这个用户在命令行下调用
ceph auth get-or-create-key来过去用户名和秘钥，monitor中的ceph的认证子系统生成username和key，在monior中存一份拷贝，同时把secret key返回给client.admin。也就是说client和monitor共享这份秘钥。

要向monitor进行认证，client发送用户名给monitor（注意不需要用户的secret key），monitor生成一个session key。
并用这个用户名对应的secret key加密这个session key。然后monitor把这个加密过的ticket回传给client。
客户端然后用共享的secret key解密获取到session key。这个session key表示当前会话中的这个用户。
然后client请求一个ticket（用session key签名），monitor生成ticket（使用user的secret key加密）后返回给client。
client解密ticket，并用ticket来签名发往OSD以及MDS的请求。

所以，client先要请求session key，monitor生成session key，用secret key加密后成为一张ticket，发送给client。  
client得到session key之后，再次请求ticket，moniter会发送给有使用期限的ticket给client（还是用secret key加密） 
client达到这张tiacket之后，就可以和OSD和MDS交互。

该认证提供的ceph client和ceph server之间的保护，认证并不扩展到超出client的范围。也就是说，如果用户远程访问client，ceph的认证并不会应用到用户主机和client主机之间的链接。
