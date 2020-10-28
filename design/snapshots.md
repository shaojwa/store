#### 快照的设计
快照是任何存储系统的一个必备功能，而且相关的流程比较多。

#### 几个概念
1. 一个对象存储时分HEAD对象和CLONE对象，即针对一个对象的不同版本。

#### 快照的两种实现机制
COW和ROW，ROW就是写时重定向，写的时候写到别的地方。COW，写时复制，写的时候把原数据复制到别的地方。

#### 现在的实现
1. 一个对象有多个克隆版本，这个克隆版本由对象id，和快照id来唯一确定，即oid+snapid。
1. RADOS采用COW机制，就是拷贝原有的数据到别处，好处是，HED对象数据是覆盖写连续，缺点是，有写放大。

#### 对象的克隆
OSDC通过SnapContext这个结构把信息给OSD，SnapContext的信息主要包括，seq号和snaps。

#### SnapSet的理解
1. seq，最新的快照序号。
1. snaps，已经打过的快照号。
1. clone，clone时的快照号，锁存一个clone对应多个快照号。
1. clones_snaps，一个clone对应的快照集合，比如 clone_snaps(<3, (3,2)>, <5, (5,4)>)

因为只有当有写操作的时候，才会把Snap信息下发到OSD，OSD就会进行clone，所以当写操作到OSD的时候，OSD会把最新的snap号作为clone中的snap号。

