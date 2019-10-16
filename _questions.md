
### 权威 元数据 cache 更新后，是怎么通知副本 更新的，但是 version相同？ 

发现副本常常没有及时更新。

### 客户端发送请求，怎么选择MDS？

### dump inode 中的 accounted_rstat 是什么意思？

### flush cap 是做什么的

内核代码上看，flush cap是在fsync的流程中调用。fsync 会把所有的in-core data of file 落盘，也会把所有的元数据下刷。

而ydatasync不一样，fdatasync只会下刷部分元数据，比如 atime 和 mtime的改变不会在fdatasync中下刷。
因为这些信息对后续的read操作来说并不是必须的。而size就不一样，它就会要求一次元数据的flush，在fdatasync中也会刷下去。


### mds 的 replica_nonce 是什么作用？

## clients
### 客户端发送请求，怎么选择MDS？

用户态发送请求调用make_request()接口, 有默认参数 mds_rank_t use_mds=-1，当然也可以自己指定。

对stat调用发出的_getattr来说用的是-1，make_request()自己会选择mds，具体怎么选得继续看。

### stat 和 statx 什么区别

libcephfs提供ceph_lstat, lstat 和stat一样，除非path参数是symbolic link，lstat 返回时的 symbolic link 本身的数据。

cephfs.pyx提供的是lstat，和stat。

libcephfs 提供的是 ceph_lstat，和 ceph_statx, ceph_lstat 没有在libcephfs.h 中导出，只在libcephfs.cc中导出。

client提供了，lstat，stat 和 statx。

fill_stat() 有配置影响size显示的是什么。

    cct->_conf->client_dirsize_rbytes。 
    
     int Client::stat(const char *relpath, struct stat *stbuf, 
            const UserPerm& perms, frag_info_t *dirstat, int mask)
            
       int Client::statx(const char *relpath, struct ceph_statx *stx,
            const UserPerm& perms, unsigned int want, unsigned int flags)
            
 从形式上看，statx通过want 和 flags 算出mask，stat直接给mask。 statx是可以在want中指定要获取什么字段，比如默认的 CEPH_STATX_BASIC_STATS。cephfs.pyx 用的是ceph_statx，而不是ceph_stat。
 
### stat 用的是什么OP

CEPH_MDS_OP_GETATTR

## mds
#### dump inode  字段

    "auth_state": {
       "replicas": {
           "1": 3
       }
    }
    
 1 为rank， 3 为 replica_nonce。
 
 
