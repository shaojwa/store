## SPANNING TREE

* 如果/usr/bin/vi 在缓存里，那么/usr/bin/, /usr/, /也在内存里，包括inode，directory对象，以及dentry。

## 权威

* 维护关于什么节点缓存什么inode的列表。
* 每一个副本会有一个nonce用来消除多个副本之间的歧义，即一个缓存项可能在多个mds上缓存，nonce用在这里。
    map<int, int> replicas; 
* cached_by 集合存储所有缓存某个对象的所有mds节点，有时候也包括之前缓存而现在不缓存的某个MDS。
    * 权威节点包括所有的缓存该对象的MDS
    * 缓存过期了之后，过期通知一定会发送到权威MDS。（非常重要，有其他节点在用会导致权威MDS节点pin主这个元数据，以避免被trim掉）
* 每一个元数据对象都有一个权威标记位，用来标记这个元数据对象是权威的，还只是一个副本。

## 副本 NONCE

* 每一个副本对象都维护一个nonce值，这个值时这个副本被创建时，权威节点分配的。
* nonce用来区别是哪个副本过期，有时候同一个对象的多个副本同时被创建。

## 子树分区

* 如果/分配给mds0，/usr分配给mds1，那么/usr的inode由mds0管理，因为这个inode信息是/目录的一部分。
* 每一个CDir对象都有一个dir_auth元数，如果这个字段的值时AUTH_PARENT表示，CDir的权威节点和这个目录的inode的权威节点相同。
* 如果dir_auth指向其他MDS，那么表示一棵新的子树。CDir是一棵子树根，当且仅当dir_auth指向一个MDS，且不是AUTH_PARENT。

