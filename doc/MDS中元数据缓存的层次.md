#### MDS中的CInode层次
CInode是最终呈现出来的结构，根据不同的业务逻辑，CInode的存储也是分层的。

最上层的CInode继承自三个类，MDSCacheObject，InodeStoreBase，和Counter。这三个类分别做什么？

MDSCacheObject这个类，主要是用来标记缓存状态，比如Inode是否已经标脏，引用计数有多少等等，
具体可以参看MDSCacheObject.h查看。

第二个基类，InodeStoreBase，按照注释，这里面存的是后端存储的数据以及序列化的方法。
为什么需要这么一个中间类，按照注释说明，这样可以处理后端存储的Inode数据而不会触及CInode的业务逻辑。
那具体什么意思？CInode中存的是CInode的inode信息，xattr信息等等。

Counter是什么？只是一个计数器？暂时还不清楚准确的含义。


最后，有了InodeStoreBase，为什么还有InodeStore？不知道，看引用来说，都是tool工具在使用，可能专门封装给工具用的。
看InodeStore中的接口来说，主要是编解码用的。

下面我们就继续往下看InodeStoreBase存的是什么？

#### InodeStoreBase类中的数据

这个类中的字段非常多。
