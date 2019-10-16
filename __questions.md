### 权威 元数据 cache 更新后，是怎么通知副本 更新的，但是 version相同？ 

发现副本常常没有及时更新。

### dump inode 中的 accounted_rstat 是什么意思？

### flush cap 是做什么的

内核代码上看，flush cap是在fsync的流程中调用。fsync 会把所有的in-core data of file 落盘，也会把所有的元数据下刷。

而ydatasync不一样，fdatasync只会下刷部分元数据，比如 atime 和 mtime的改变不会在fdatasync中下刷。
因为这些信息对后续的read操作来说并不是必须的。而size就不一样，它就会要求一次元数据的flush，在fdatasync中也会刷下去。


#### dump inode  字段

    "auth_state": {
       "replicas": {
           "1": 3
       }
    }
    
 1 为rank， 3 为 replica_nonce。
 
 
