#### 快照特性的必要
快照是任何存储系统的一个必备功能，而且涉及到的流程比较多。

#### 快照的两种实现机制
COW和ROW，ROW就是写时重定向，写的时候写到别的地方。COW，写时复制，写的时候把原数据复制到别的地方。而RADOS所选择的实现方式是COW。

#### HEAD对象和CLONE对象
1. 一个对象存储时分HEAD对象和CLONE对象，即针对一个对象的不同版本。

#### 现在的实现
1. 一个对象有多个克隆版本，这个克隆版本由对象id，和快照id来唯一确定，即oid+snapid。
1. RADOS采用COW机制，就是拷贝原有的数据到别处，好处是，HED对象数据是覆盖写连续，缺点是，有写放大。

#### SnapContext 和 SnapSet
OSDC通过SnapContext这个结构把信息给OSD，SnapContext的信息主要包括，seq号和snaps。

#### SnapContext中seq值是不是等于SnapContext中的snaps集合中的最大值？
不一定，快照删除是seq也会递增，此时seq 就比 snaps中的最大值要大。

#### SnapSet中的seq值是不是等于SnapSet中snaps集合中的最大值？
不一定，SnapSet中的seq也会比snaps中最大值大的情况，什么时候出现？暂时我还不知道。

#### SnapSet的理解
1. seq，最新的快照序号。
1. snaps，已经打过的快照号。
1. clone，clone时的快照号，锁存一个clone对应多个快照号。
1. clones_snaps，一个clone对应的快照集合，比如 clone_snaps(<3, (3,2)>, <5, (5,4)>)

因为只有当有写操作的时候，才会把Snap信息下发到OSD，OSD就会进行clone，所以当写操作到OSD的时候，OSD会把最新的snap号作为clone中的snap号。

#### 快照的创建
1. 通过在SnapContext中构造新的的seq号，和snaps来实现，但是一直到有写操作时，才下发SnapContext到OSD侧。

#### 快照的删除
1. 删除快照时，会先通知MON，MON会通过OSDMap消息推送给OSD，OSD后台有trim线程做这个工作。
1. 删除操作通过携带删除的seq号，告诉OSD，比对SnapSet，更新snaps和clone_snaps，当一个clone的snaps集合为空的时候，这个clone就可以删掉。

#### last 为什么是HEAD(CEPH_NOSNAP)值

