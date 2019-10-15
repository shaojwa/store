
        https://docs.ceph.com/docs/master/architecture/
     
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

#### 智能的DAEMON使得集群可以超大规模扩展


在很多集群架构中，集群成员关系的主要目的是有一个集中式的接口知道哪些节点可以访问。所以一个中心化的接口通过double-dsipatch来提供服务给客户端，这对PB到EB字节规模来说，是一个巨大瓶颈。

ceph消除了这种瓶颈，OSD金城河client是集群感知的。和client一样，OSD进程知道集群中的其他OSD，这就能让OSD进程可以直接和其他OSD进程以及Monitor进程交互。
另外，也让client可以直接和OSD交互。

client，Monitors，OSD进程之间相互交互的能力意味着，OSD进程可以利用节点上的CPU以及RAM，更加容易得执行任务，这些任务通常会拖慢中心化服务器。
这种能最大化利用算力的能力会有以下几个主要的获益：

* OSD直接为client提供服务

任何网络设备都有一个所能支持的最大并发连接数的限制。一个中心化的系统中，大规模场景下必然会有一个低的物理限制。能让客户端直接连接OSD，ceph就能同时提高性能以及总体容量，并消除单点故障。client可以在需要时，同某个特定的OSD之间维护一个会话，而不需要和一个中心化的节点之间维持会话，

* OSD成员关系以及状态

OSD进程加入一个集群并上报状态，在底层，OSD通过up/down来反应他们是否正在运行以及是否能处理client请求。
如果一个OSD进程已经down，并且也处于in状态，这表明OSD进程故障。如果一个OSD进程不再运行（即crush掉），OSD不能通知给moniter它已经down掉。
OSD请求发送消息给Monitor，如果monitor没有在配饰的时间间隔内收到消息，他也会把OSD标down。但是，这种机制是failsafe的。
通常来说，OSD进程能确定是否临近的OSD已经down掉并上报给Monitor，这就能保证Monitor进程是轻量级的。

* 数据 scrub （清洗）

作为维持数据一致性以及清洁度的一部分，OSD可以清洗PG内的object。即，OSD可以比较一个PG内不同osd上对象副本的元数据。scrub（通常一天一次）可以发现bug或者文件系统错误。ceph也可以进行更深的scrub，通过逐bit得比较数据。深度scrub（通常一周一次）可以发现磁盘上损坏的扇区，这在轻量 scrub中并不会发现。

* 数据复制

同client一样，OSD进程也用CRUSH算法，但是OSD进程使用CRUSH来计算副本应该存储在什么地方（也未了重平衡），在一个典型的写场景中，client使用CRUSH来计算什么地方可以存一个对象，将对象一个社到一个pool以及PG，然后查看CRUSH map来找到这个PG的主OSD。

client把对象写到主OSD中，主OSD有它自己的CRUSH map来标记的其他的从OSD。然后复制对象到从OSD中，在确认对象已经成功存储之后再返回给client。因为可以进行数据的复制，OSD可以缓解client的工作，以确保数据的高可用以及安全性。

#### 动态集群管理

在可扩展性以及高可用一节中，我们已经解释ceph怎么使用CRUSH，集群感知，以及智能进程来扩展以及维护高可用。ceph的关键设计点是：自治的，自恢复的，以及智能的OSD守护进程。让我们更深入得了解CRUSH是怎么工作，使得现代云存储基础设置可以放置数据、集群中重平衡、以及从故障中动态恢复。

#### 关于pools

ceph集群只是Pool的概念，这是一个存储对象的逻辑分区。

client从monitor那收到cluster map，应把对象写到pool中。pool的size或者副本数，CRUSH规则，以及PG的数量决定ceph怎么放置数据。

Pool至少会设置以下参数：

* Object对象所有者
* PG的数量
* 采用的CRUSH规则

#### 将PG映射到OSD

每一个池都有一定数量的PG，CRUSH动态得将PG映射到OSD，当client存储对象时，CRUSH将映射每个object到PG。对象到PG的映射会在OSD和client之间创建一个间接层。client集群必须可以增长或者缩减，并且可以重新平衡存储的对象时放置的位置。如果client知道哪个OSD中有哪个对象，那么这就会让client和OSD之间形成紧耦合。所以，CRUSH算法来把每个object映射到PG，然后将每一个PG映射到一个或者多个OSD进程。这个中间层是的cpeh可以在由新的OSD上线时，能动态得重新平衡。

通过cluster map以及CRUSH算法，客户端可以准确计算出用哪个OSD来读取或者写入对象。

#### 计算PG ID

当一个客户端绑定到一个monitor，退回收到最新的一份cluster map拷贝。通过cluster map，client知道集群中所有的 Monitors，OSDs，MDSs。但是并不知道object的位置。

对象的位置通过计算获得。

客户端需要的输入只是 object id以及 pool。通过 object name 计算出 PG，client通过以下步骤计算出PG ID：

* client 输入pool name和 object id. (e.g. pool = 'liverpool', and object-id = 'john')
* ceph 获取 object id，并计算 hash值
* ceph 对hash值对PG 数量取模得到 PG ID
* ceph 通过pool name 得到 pool id （比如 'liverpool' = 4）
* ceph 规划 pool ID 到 PG ID（比如 4.58）

计算对象的位置远远快于执行一次对象位置查询。CRUSH 算法允许一个client计算出对象应该存储的位置，使得client可以连接到主OSD去存取对象。


#### PEERING AND SETS

在之前的章节，我们注意到OSD进程会校验相互之间的心跳，并上报给Monitor。另外一件OSD做的时叫做Peering，
这是一个将PG中的所有OSD对所有对象以及元数据的状态达成一致的过程。事实上，OSD会上报Peering 失败给Mon，Peering的问题通常会自动解决。
但是，如果问题持续存在，你也许就需要参考Troubleshooting Peering Failure章节。

对object的状态达成一致并不是说PG有最新的数据。

ceph计算设计的最小副本数时2（也就是size = 2），这是对数据安全的最低要求，对高可用性来说，集群应该保存2个以上的对象副本。
（size = 3， min size = 2），这样，集群才可以在degraded的状态下继续运行，并维持数据的安全。

回过头参考 智能守护进程支持高扩展中的图，我没并没有专名命名OSD进程，而是将他们称为 Primary, Secondary。按照惯例，Primary 是 Acting Set中的第一个OSD，主管负责PG中的peering过程，并且primary OSD是唯一可以接受由client发起的写对象操作的OSD。

当一系列的OSD对一个PG负责时，那一些列的OSD我们称为Acting Set，一个Acting Set可能是当前对这个PG负责的OSD，或者是在某个epoch时对某个特定的PG负责的OSD。

Acting Set 中的OSD并不总是up，当一个Acting Set 中的OSD up时，他是Up Set中的一部分，这个Up set是一个重要的区别，因为当一个OSD故障时，ceph会把PG重新映射为其他OSD。如果住主OSD挂掉，Acting Set中的第二个OSD会变成主OSD。

#### 重平衡

当天津爱一个osd 到ce平衡集群中时，cluster map会进行更新，参见 【计算PGID】部分，这改变了cluster map。所以，这改变了对象的放置，因为这修改了计算的输入。下面的图从某种程度上描述了重平衡的过程（尽管比较初略，但是基本生对大型集群的影响比较小）。并不是所有的PG会从已经存在的OSD迁移到别的OSD。计算是正在进行重平衡，CRUSH是稳定的。很多PG会保持原有原有的配置。每一个OSD都会获得一些容量的增长，所以子完成重平衡后，新的OSD并没有负载的峰值。

#### 数据一致性

作为维护数据一致性和清洁度的一部分，OSD可以在PG的范围内进行对象的清洗。也就是说，OSD会比较在一个PG中所有副本的对象的元数据。清洗过程会发现OSD的bug或者文件系统的错误。OSD也可以执行更深层的清洗，通过逐字节得比较对象的数据。深度scrub因此会发现扇区损坏等在轻量scrub中不会发现的问题。

#### 纠删码

一个纠删码池会把一个对象存储为 K+M 块。它把对象分为K个数据块，以及M个编码块。pool被配置成大小为K+M，以便每一块都存到Acting Set中的一个OSD上。
每一块的rank值作为对象的属性被存储起来。

创建一个使用5个OSD的纠删码池作为示例（K+M = 5），允许其中的2块丢失（M = 2）

#### 纠删码块的读和写

当一个数据位ABCDEFGHI的，名为NYAN的对象写进一个池中时，纠删码功能会把内容拆分为3个数据块：第一块包含ABC，第二块包含DEF，最后一块为GHI。
如果内容的出昂度不是K的整数倍，那内容会被追加补全。就删码模块同样会创建爱你两个编码块。第4块包含YXY以及第5块包含QGC。每一块都会存储到acting set中的一个OSD中。所有的块都会用相同的名字NYAN以对象的形式存储在OSD上，除了对象的名字外，块创建的顺序必须以对象属性的形式被保留下来（shard_t）。
块1（chunk）包括ABC，并且存在OSD5上，而块4包含YXY存在OSD3上。

当对象NYAN 从纠删码池中读取的时候，解码函数会读到3个块，chunk1（包含ACB），chunk3（包含GHI）和块4（包含YXY）。然后重建原先的数据ABCDEFGHI。
解码模块会通知chunk2和chunk5丢失（其实被称作擦除（erasures）），chunk5不能被毒气，因为OSD4已经out。
只要有三个chunk被读取，解码函数马上回被调用，OSD2因为最后才读取到，所以OSD2上的chunk就不会算在内。

#### 被中断的全写操作

在纠删码池中，acting set中的主OSD会收到所有的OSD写操作。他负责将负载编码为K+M个块，并把这些块发送到其他的OSD上。主OSD也负责维护权威的 PG-log版本。
在下图中，一个（K=2，M=1）的就删码PG被创建，显然需要3个OSD支持。acting set 由OSD1，OSD2 和 OSD3 组成。一个object已经被编码并存储在OSD上：
chunk D1v1（即，chunk number1，verion 1） 在OSD1上，D2v1在OSD2上，C1v1（即Coding chunk 1， verion 1）在OSD 3上。PG log在每一个OSD上都是一样的（比如：1,1 表示epoch1， version1）。


OSD1 是主OSD，并且从client那收到一个 WRITE FULL操作，意味着用负载替换掉整个object，而不是覆盖一部分。 对象的version2被创建出来用来覆盖version1。
OSD1 对负载进行编码为三个chunk2 ：D1v2会写到OSD1上，D2v2会写到OSD2上，C1v2会写到OSD3上。每个chunk都会发动到目标OSD上。
主OSD除了要处理write操作外，还要负责存储chunks，以及维护一个权威版本的PG log。 当一个OSD收到消息告诉它写chunk时，它也会在PG log中创建一个新的条目来反应这次修改。比如，一旦OSD3存储了C1v2，他就会添加（1，2）（即 epoch1，version2）条目到log中。因为OSD是异步处理的，其他的chunk有可能还在处理中（比如D2v2），而有的chunk已经得到确认并存储到磁盘上，比如C1v1和D1v1。等所有的chunk都写入成功并得到确认，日志的last_complete指正会从(1,1)指向（1,2），最后用来存储原先chunk的文件就可以被删除，比如OSD1上的D1v1，OSD2上的D2v1，以及OSD3上的C1v1。（假设存储引擎是filestore）

但是意外发生了，如果在D2v2还在处理中的时候，OSD1故障，此时object的version2 只是部分被写入： OSD3上有一个chunk，但并不足以恢复。
它会没有两个chunk，D1v2，D2v2,而纠删码的参数K=2要求至少要有两个chunk才能重建第三个chunk。OSD4 称为性的primary OSD，并且发现last_complete指向的log条目是（1,1），那将成为权威log的头。

OSD3上的（1,2）这个log条目和新的权威log（OSD4提供）有分歧，它将被丢弃，C1v2这个chunk也将会被删除。D1v1chunk将会通过解码函数重建，这个重建过程在scrub的时候发生，并且D1v1会被存储在新的主OSD中，即OSD4中。

#### CACHE TIERING

tier的意思是，一层、一排。针对对后端存储的部分数据，cache tier可以提供给客户端更好的I/O性能。通过使用相对更快/更昂贵的数据设备来创建一个池。把这个池配置成一个缓存层，二后端池通常纠删码池或者相对较慢设备配置成的存储层。ceph objecter层处理将object放置到哪里，tiering agent决定什么时候把对象从缓存池下刷到后端存储层，所以 cache tier和 后端存储 tier对客户端来说是完全透明的。

#### EXTENDING CEPH

你可以通过创建叫做 Ceph Classes的共享对象类。ceph会动态得加载 osd class dir目录下的.so类。当你实现一个类，你可以创建可以访问本地方法的新的对象方法，通过库或者自己创建的类方法也可以。

在写操作中，ceph classes 可以调用native或者class 的方法，执行一些列操作后生成ceph可以原子性操作的写事务。

早读操作中，ceph classes可以调用用native或者class 方法，执行一系列操作后返回数据给client。


#### SUMMARY

ceph存储集群是动态得，就像是一个或者得生物体。很多存储设备并不能充分利用商用设备的CPU和RAM，但是ceph可以。从心跳，peering，重平衡，或者故障恢复。ceph处理client的负载，利用OSD的算力去处理负载。可以参见前面提到的概念去了解ceph是怎么充分利用计算资源的。


### ceph 协议

ceph 客户端使用自有协议去和ceph存储集群交互。ceph将这部分功能打包进librados库，那样你就可以创建自己的ceph客户端，下图描述这种基本架构。

#### 自有协议以及LIBRADOS

现代应用需要一个简单的拥有异步通信功能的对象存储接口，ceph就提供了这样的接口。接口支持对集群中对象的直接的并发访问。

* 池操作
* 快照以及写时拷贝
* 读写对象，创建或者删除，整个或者一定字节范围，追加或者截断
* 创建、设置、获取、删除 XATTR
* 创建、设置、获取、删除 Key/Value 对
* 复合操作，双重确认语义
* 对象 classes

#### 对象 WATCH/NOTIFY

client可以对一个对象注册一个持久关注冰保持和主osd之间的会话。client可以向所有的观察者（watcher）发送一个通知消息以及一个负载，并在观察者收到通知后也收到一个消息。这就使得一个client可以把任何object当做一个同步/通信的渠道。

#### 数据分条
