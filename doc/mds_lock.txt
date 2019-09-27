
* read locks 可以放在任何节点上
* xlocks 必须在权威节点上应用
* lock request 比如分配一个reqid

### remote lock

* link unlik rename 是多锁操作（multi-lock operations），必须在 remote node上获取到xlock。
* 权威节点必须跟踪它持有的remote lock，如果转发或者重启，它可以丢弃 remote lock。

### path pin

语义：　某个路径上的读锁

性质：　阻断 dentry 上的 xlock

### dnxlock 

语义： 独立占有　某个路径的锁

性质：
* locking时，阻止 后续额 的path pins
* locked时，阻止 dn read
×　必须在权威节点上。

夺取规则：

* 一次 pin 所有的路径，等待时不持有任何锁。
* 按顺序夺取锁。

### auth pin

语义： pin 到权威节点上，作用在 dir 和 in

性质：

* 阻止 freezing 变成 frozen
* freezing 状态会阻止新的 auth pin，英尺会阻断其他的 lock auth_pin (挂起本地 export)
* 不会阻止remote 节点的 auth_pins，因为远端的子树并不是权威，直到本地子树 frozen。

注意：

*　在auth_pin 上阻塞是危险的，永远不要在持有其他 auth_pin的时候 block（怎么算block？）

夺取规则：

* 一次性的获取所有的 auth_pin，等待时不持有任何锁。

### file_wrlock

语义：exlusive lock on inode content

性质：

* revents inode read
* on auth

夺取规则：

* 按顺序获取 lock


## ordering

* namespace(dentries) < inode #  inode优先级高
* 对dentry排序：(inode, dname)
* 对inode排序：(inode)
* read和write 锁都需要进行排序

举例：

需要对/usr/bin/foo上锁，user，bin需要read， foo需要xwrite，我们需要按顺序获取所有的这些锁。

* 在同一节点上，我们可以友好一点，查看所有项是否可以上锁，然后锁住所有，而在等待时丢弃所有的锁。
* 在多个节点上，我们需要使用全序，（后面的没看明白？？）


**auth pin 怎么配合以上规则**
* auth pin 只使用xlock锁，不需要read locks
* 在锁获取时，第一次遍历的时候就预取(pre-grab) 所有的 auth pins
* 如果发现我们不能auth pin，那么我们丢弃所有的 locks 然后等待。
