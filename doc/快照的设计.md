#### 快照的设计
快照是任何存储系统的一个必备功能，而且涉及到的流程比较多。

#### 几个概念
1. 一个对象存储时分HEAD对象和CLONE对象，即针对一个对象的不同版本。

#### 快照的两种实现机制
COW和ROW，ROW就是写时重定向，写的时候写到别的地方。COW，写时复制，写的时候把原数据复制到别的地方。

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


#### 为什么有一个snapid叫CEPH_SNAPDIR

因为head对象被删掉，但是clone对象还在，snapset这个元数据需要存放，这个元数据本来存放在head对象的xattr中，现在head对象被删掉，需要有一个对象来存放原snapset数据。
所以需要有这么个对象，OSD中的SNAPDIR和文件里的.snapdir没有关系。

#### 文件快照
1. 对一个文件来说，打快照是基于文件的，但是一个文件可能由多个快照组成，那么只有对某个对象的写操作才会触发对象快照的创建。
1. 所以，OSDC中的SnapContext是维护整个的，一次快照，seq就增加。这个SnapContext会下发到具体的某个对象，和对象内部的SnapSet进行比对。
1. 文件系统中，一个文件打过快照（假设seq为5）之后，再次写入导致COW时，文件的head就会变成\[6, HEAD\]，快照为\[2, 5\]

#### 目录快照
1. 一个目录，假如原先这个目录的CInode中的信息是\[2, head\]，打快照，比如seq=5，之后，目录属性改变，比如chmod。
那么，目录的dentry对应的inode结构中，就会把 `{5, (2,inodedata)}` 放到old_inodes中。
其中5表示打快照时的seq，2表示原先的first。这样file的CInode，CInode最新的first就会变成6。
1. 目录改名才会触发CDentry中first和last的变化。

#### MDS中的CInode/CDentry/CDir
CInode/CDentry都是有实体对应的CDir没有，但是为什么CInode/CDentry有first和last，CDir只有first。

#### 文件系统的COW为什么要设计成两套机制
文件系统中，文件也好目录也好，都关联两个东西，一个是dentry，一个是inode。但是在ceph中，快照的实现在文件和目录上并不相同。

文件打了快照，然后写数据，写数据带来元数据的改变，文件inode中的size会发生变化。
会生成新的inode和dentry。新的dentry中的last就是快照号，老的inode中的first变成snap_id + 1, last变成head。
新的inode中的last是快照号。老的inode中的first是snap_id+1，last还是head。这是文件COW之后write操作带来的变化。

但是目录不一样，对于目录来说，目录的写入可以是目录中多创建一个子文件或者目录。
或者目录本身被chmod，因为chmod改变的是目录inode中的uid和gid。
反正就是目录的inode被改变。此时目录的dentry并没有和文件一样，创建一个新的。
目录的inode也同样没有创建一个新的。而只是把原来的数据放到inode结构中的old_inodes中。

为什么要这样? 现在我还不清楚

#### 文件系统中的inode的first为什么需要等于最新快照号+1

#### last 为什么是HEAD(CEPH_NOSNAP)值

