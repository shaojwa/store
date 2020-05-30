## MDS一个请求的生命周期

## 一个请求的生命周期

```
AsyncConnection::process // 产生Message
Messenger::ms_deliver_dispatch 
MDSDaemon::ms_dispatch(Message *m) //获取mds_lock，handle_core_message() or ds_rank->ms_dispatch(m)
MDSRankDispatcher::ms_dispatch(Message *m) // mds_rank->ms_dispatch(m)
MDSRank::_dispatch(Message *m, bool new_msg) // 只有到 Server::dispatch() 才把 Message转为 MClientRequest。
MDSRank::handle_deferrable_message(Message *m)
Server::dispatch() // 将Message转为MClientRequest
MDCache::request_start(MClientRequest *req) // 将MClientRequest转为mdr，mdr存放在active_requests中
回调类的finish接口 // 比如C_MDS_mknod_finish::finish，cinode，dentry，cdir开始各种pop_projected
MDCache::request_finish(MDRequestRef& mdr) // 清理mdr
MDCache::request_cleanup(MDRequestRef& mdr)
```

## MDS模块划分
|模块|模块|模块|模块|
|:-|:-|:-|:-|
|ceph-mds||||
||messager|||
||mc(MonClient)|||
||mds(MDSDaemon)|||
|||mds_lock||
|||beacon||
|||mgrc||
|||mdsmap||
|||log_client||
|||mds_rank||
||||objecter|
||||server|
||||mdcache|
||||locker|
||||mdlog|
||||balancer|
||||inotable|
||||snapserver|
||||snapclient|
||||scrubstack|
||||purge_queue|
