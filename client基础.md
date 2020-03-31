#### client 中的基础函数
|函数名|基本功能|
|:-|:-|
|may_create|检查是否有权限create|
|may_open|检查时候有权限open|
|_create| 实际发送请求给mds去create文件|
|_open|实际发送请求给mds去open文件|

## client侧open流程

1. 得到要打开的文件，比如/data/test/file
1. 执行path_walk，查看这个文件能不能找到，本地缓存没有的，向mds发请求找。
1. 如果文件已经存在，而且flag中有O_CREAT和O_EXCL，那么oepn返回-EEXIST错误。
1. 如果文件不存在，而且有flag有0_CREAT标记，那么就去创建。如果其他错误，比如文件不存在，又没有o_CREAT，那么就返回出错。
1. 如果要创建文件，那么就先path_walk到父目录的inode。
   1. 如果父目录不存在那就报错退出。
   1. 如果存在就检查目录是否允许在其中创建文件，其中会通过_getattr(dir_inode)得到目录inode中的信息。
   1. 拿到之后通过inode_permission()判断权限是否足够。
   1. 通过_create()完成创建，这里面做主要的工作。
1. 如果不需要created，即文件已经存在，那么我们就会尝试调用may_open去检查是否有权限打开。
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
#### client请求处理

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

#### insert_trace() 用处

把收到的响应，放入缓存。

#### client请求中的tid是什么？
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
#### 配额相关问题
```
// size 也通过cap 进行交互
ceph_write_iter()
    ceph_get_caps()
        check_max_size()
             ceph_check_caps()
        try_get_cap_refs()
        add_wait_queue()
        wait_woken()
         
```
几个接口
```
// 等待mds回复caps (包括max_size)
ceph_get_caps

//
// 判断是否需要申请更大的max_size
static void check_max_size(struct inode *inode, loff_t endoff)
// endoff // 将要写到的偏移
// ceph_inode_info.i_max_size        mds授权的 max_size
// ceph_inode_info.i_wanted_max_size 客户端希望可以写入的大小

// 如果写入的偏移大于MDS授权给的最大大小，也大于之前想写入的大小
// 那么需要修改i_wanted_max_size, 此时 i_wanted_max_size >= i_max_size。
// 如果 i_wanted_max_size 大于不包括等于 i_max_size 那么需要重新发请求获取更大的i_max_size
ceph_check_caps()
```
#### 内核客户端中cap的超时时间

s_cap_ttl: cap 的超时时间，正常等于最后一次发送renew请求的时间加上1分钟。
s_renew_requested： 
 
正常流程：
发送renew cap：设置 s_renew_requested，设置为发送的当前时间。
收到renew cap：设置 并设置 s_cap_ttl

#### client 调试
#### 客户端重连问题
#### 判断底层socket状态
```
[546255.865385] libceph: mds0 172.87.60.52:6800 socket closed (con state CONNECTING)
// 显示 connection的状态是, 接口是 con_sock_closed()
// 链接关闭
```
dmesg中可以查看日志

#### 内核客户端需要收集的日志

* dmesg
* /sys/kernel/debug/ceph/ caps debug_command mdsc osdc

#### 查看内核客户端中inode相关信息

```
echo inode=1099511627781 > debug_command

inode 1099511627781 caps(summary): used - issued pAsLsXsFscr implemented pAsLsXsFscr revoking - mds_wanted - file_wanted - retain p
// used         -
// issued       pAsLsXsFscr // mds分发给的
// implemented  pAsLsXsFscr // client中实际的
// revoking     -           // implemented - issued
// mds_wanted   -           // client 向 MDS申请的（不确定）
// file_wanted  -           // 根据文件mode需要申请的（不确定）
```
接口：
```
// fs/ceph/debugfs.c
inode_info_show()
```

#### 内核打桩模拟不回复mds的revoking-caps消息
内核回复调用流程:

```
ceph_handle_caps ->
handle_cap_grant (CEPH_CAP_OP_REVOKE or CEPH_CAP_OP_GRANT) ->
ceph_check_caps
```
