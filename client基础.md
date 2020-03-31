## pah_walk 流程

比如path_walk /data/wsh/file40, 一开始没有cache任何inode，所以需要从/data开始找：

```
path_walk #0x1/data/wsh/file40
may_lookup 0x1.head // 第一次找，在0x1中找data
_getattr
may_lookup 0x7f9eb8016d30 = 0 // 0x7f9eb8016d30是inode为0x1的目录对应的dir的指针地址。
_lookup not found valid dn data in dir 0x1.head // 在0x1中找data，找不到
_do_lookup on #0x1/data // 发请求找data
choose_target_mds inode dir hash is 2 on data => 1843686825
send_request client_request(unknown.0:2 op=262 op_name=lookup_wantauth #0x1/data ...) //unknown.0:2中的2就是request_id
awaiting reply|forward|kick on 0x7ffc619a0940 
// 开始等待响应
sendrecv kickback on tid 2 0x7f9ebeffc780
inode.get on 0x7f9eb8019430 0x10000000001.head now 4  // 找到data的inode号0x10000000001
make_request target is 0x10000000001.head
_do_lookup res is 0

----
may_lookup 0x10000000001.head // 再次may_lookup， 找wsh
_getattr 
may_lookup 0x7f9eb8019430 = 0 // 0x7f9eb8019430是inode为0x10000000001，也就是data目录对应的dir的指针地址。
_lookup not found valid dn wsh in dir 0x10000000001.head // 在0x10000000001中找wsh，找不到
_do_lookup on #0x10000000001/wsh // 发请求找wsh
choose_target_mds inode dir hash is 2 on wsh => 14620335 // 找到data目录对应的权威mds
send_request rebuilding request 3 for mds.0 // 发请求
send_request client_request(unknown.0:3 op=262 op_name=lookup_wantauth #0x10000000001/wsh ...) //unknown.0:3中的3就是request_id
awaiting reply|forward|kick on 0x7ffc619a0940
// 等响应
inode.get on 0x7f9eb801cce0 0x100002b8a5c.head now 4 // 拿到wsh目录的inode号 0x100002b8a5c
make_request target is 0x100002b8a5c.head
_do_lookup res is 0

----
may_lookup 0x100002b8a5c.head // 第三次may_lookup, 找file40
_getattr
may_lookup 0x7f9eb801cce0 = 0
_lookup not found valid dn file40 in dir 0x100002b8a5c.head
_do_lookup on #0x100002b8a5c/file40
choose_target_mds inode dir hash is 2 on file40 => 2657414041
send_request rebuilding request 4 for mds.0
send_request client_request(unknown.0:4 op=262 op_name=lookup_wantauth #0x100002b8a5c/file40
awaiting reply|forward|kick on 0x7ffc619a0940
// 等响应，240微秒
sendrecv kickback on tid 4 0x7f9ebeffc780
_do_lookup res is -2  // 注意，找不到
put_inode on 0x100002b8a5c.head // 释放wsh目录inode
path_walk done for relpath, r=-2 // 最终path_walk告诉我们 file40找不到

// 之后，再次查找/data/wsh/file41 的时候, 前面的/data/wsh/就可以从local-cache中找到，也是按照路径/data/wsh逐层访问
// 最后的file41需要发请求给mds，最后等到时间大约240微秒。

```
## client请求处理

|业务线程|分发线程|说明|
|:-|:-|:-|
|ceph_link()|| // 对外接口|
|Client::link()||// 业务接口|
|Client::\_link|||
|Client::get_or_create()|| // 操作dir的inode，session等需要对象内部锁|
|Client::make_request()||// 内部持有c_request_lock, client_lock锁|
|\_open_mds_session()|||
|send_request()|||
|request->dispatch_cond->Signal()|| // 唤醒handle线程|
||ms_dispatch发送消息给mds||
||ms_dispatch线程调用 handle_client_reply()|// 处理mds回复的响应|
||ms_dispatch线程调用 insert_trace()|// 处理mds回复的响应|
||ms_dispatch线程调用 insert_readdir_results|// 唤醒业务线程|
|reply->get_result()|||
|Client::insert_readdir_results|||

## insert_trace() 用处

把收到的响应，放入缓存。

## client请求中的tid是什么？
```
client.125255315:2877811973
```
|字段|字段|
|:-|:-|
|125255315|client id|
|2877811973|tid，transcation id|

#### client 缓存 mds 分配的caps
#### dirty cap 相关

dirty cap 是什么含义？

内核中把 cap 标脏的接口是__ceph_mark_dirty_caps，调用的地方有__ceph_setattr，__ceph_setxattr 等。

可以重点读一下__ceph_setattr 代码：

* 最初 dirtied = 0
* atime, dirtied |= CEPH_CAP_FILE_EXCL


#### client 写数据的大概流程

    参考这里：https://docs.ceph.com/docs/master/architecture/
        

#### client和pool的连接

    集群通信的时候，是一定和一个pool链接的。
    
#### client 调试
