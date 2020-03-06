
## 日志中的字段

|thread ID |task id|运行的cpu号| 日志等级|
|:-|:-|:-|:-|
|7fa20d3fe700 |2094980 |2|DEBUG|
|pthread_t|syscall(SYS_gettid)|sched_getcpu()| -1:ERROR 0:WARNING 1:INFO >1: DEBUG|

----
mds 启动流程

|线程|事务|状态|说明|
|:-|:-|:-|:-|
|ms_dispatch |handle_mds_map epoch 77 from mon.0|||
|ms_dispatch |mds.mds0 handle_mds_map standby|||
|ms_dispatch |mds.mds0 handle_mds_map epoch 85 from mon.0|||
|ms_dispatch |mds.0.0 handle_osd_map epoch 0, 0 new blacklist entries|||
|ms_dispatch |mds.0.85 handle_mds_map i am now mds.0.85|||
|ms_dispatch |mds.0.85 handle_mds_map state change up:boot --> up:replay|replay||
|ms_dispatch |mds.0.85  recovery set is 1|||
|fn_anonymous |mds.0.85 boot_start 0: opening inotable|||
|fn_anonymous |mds.0.85 boot_start 0: opening sessionmap|||
|fn_anonymous |mds.0.85 boot_start 0: opening mds log|||
|fn_anonymous |mds.0.log open discovering log bounds|||
|fn_anonymous |mds.0.85 boot_start 0: opening purge queue (async)|||
|fn_anonymous |mds.0.purge_queue open: opening|||
|fn_anonymous |mds.0.85 boot_start 0: opening snap table|||
|fn_anonymous |mds.0.85 boot_start 1: loading/discovering base inodes|||
|fn_anonymous |mds.0.85 boot_start 2: replaying mds log|||
|fn_anonymous |mds.0.85 boot_start 2: waiting for purge queue recovered|||
|fn_anonymous |mds.0.85 replay_done|||
|fn_anonymous |mds.0.85 making mds journal writeable|||
|fn_anonymous |mds.0.85 i am not alone, moving to state resolve|||
|fn_anonymous |request_state up:resolve||request_stat|
|ms_dispatch |handle_mds_map state change up:replay --> up:resolve|resolve||
|ms_dispatch |mds.0.85 reopen_log|||
|ms_dispatch |mds.0.85 now recovery set is 1|||
|fn_anonymous |WARNING auth: secret_end_id = 712|||
|ms_dispatch |mds.0.85 resolve_done|||
|ms_dispatch | request_state up:reconnect||request_state|
|ms_dispatch |mds.0.85 handle_mds_map state change up:resolve --> up:reconnect|reconnect||
|ms_dispatch  |reconnect_start: killed 0 blacklisted sessions (2 blacklist entries, 5)|||
|ms_dispatch  |mds.0.server reconnect_clients -- 5 sessions|||  
|ms_dispatch |mds.0.server reconnect_tick_finish|||
|ms_dispatch |mds.0.85 request_state up:rejoin||request_state|
|ms_dispatch |handle_mds_map state change up:reconnect --> up:rejoin|rejoin||
|ms_dispatch |mds.0.cache rejoin_send_rejoins,  rejoin message sent to mds:1|||
|ms_dispatch |mds.0.cache handle_cache_rejoin_strong begin, receive rejoin_strong from: 1|||
|md_submit |mds.0.log _submit_thread 252162901~300 : ESessions 5 opens cmapv 149197|||
|ms_dispatch |mds.0.cache handle_cache_rejoin_ack form mds.1|||
|ms_dispatch |mds.0.cache handle_cache_rejoin_ack done, still need to gather rejoin or rejoin ack|||
|fn_anonymous |mds.0.cache rejoin_send_acks,  recovery_set: 1, rejoin_ack_sent: , need_resend_rejoin_ack|||
|fn_anonymous |mds.0.cache rejoin_send_acks,  rejoin ack message sent to mds:1|||
|fn_anonymous |mds.0.cache rejoin_gather_finish done, after rejoin_send_acks, rejoin_gather: (), rejoin_ack_gather: ()|||
|fn_anonymous |mds.0.cache rejoin_gather_finish done, after rejoin_send_acks, rejoin_sent: (1), rejoin_ack_sent: (1)|||
|fn_anonymous |request_state up:active||request_state|
|ms_dispatch |handle_mds_map state change up:rejoin --> up:active|||
|ms_dispatch |recovery_done|||
|ms_dispatch |active_start|||

----
mds recovery 过程

#### replay

* 回放日志，是相对简单的过程。
* 读取元数据信息到缓存中，用以恢复失败MDS中还没有来得及提交的元数据，元数据没提交，日志已经提交。

#### resolve

* 用于确定权威元数据在MDS的位置，解决跨多个MDS出现权威元数据分歧的场景，只是确定权威元数据所属的MDS。
* 恢复中的MDS会向所有的其他MDS广播Resolve消息，消息内容包括权威子树信息，在失败时导入的未知位置的子树信息，向目标节点发送的的更新请求。
* 恢复中的MDS更新自己的缓存来反应其他节点上已经明确声明的权威子树。
* 恢复中的MDS对不明确的更新请求信息进行交叉检查，由不同的MDS进行，正常MDS也会回复replay给恢复中的MDS。
* 恢复中的MDS会裁剪掉非权威元数据，保留权威元数据以及相关约束祖先元数据。
* 正常MDS也会发送类似的Resolve消息到每一个恢复中的MDS。

#### reconnect

* 文件状态并不和其他MDS共享，也就是说，一个客户端和一个MDS交互，交互信息并不共享到其他MDS。
* 恢复中的MDS会和原有的客户端建立连接，为了查询之前客户端发布的句柄，重新在缓存中创建一致性功能和锁状态。
* MDS不会在client打开文件时同步记录这些信息，为了减少打开的延时，但是MDS会将最近打开的inode写入日志, 为了再恢复时加快速度。
* 如果客户端打开的文件并不在恢复中的MDS缓存中，MDS会根据文件名和inode到目录树中索引得到。

#### rejoin

* 恢复中的MDS发送Weak Rejoin消息给正常的MDS，送的是自己恢复了哪些元数据。
* 正常的MDS会发送Strong Rejoin给恢复中的MDS，回复的是它拥有的元数据副本信息以及锁状态。
* 最终完成分部署缓存以及锁状态。


|字段|说明|
|:-|:-|
|rejoin_sent| 我发送rejoin给这些rank||
|rejoin_ack_sent| 我需要发送rejoin ack给这些rank|
|rejoin_gather|我从这些rank收集rejoin（也就是这些rank会向当前rank 发送 rejpoin） |
|rejoin_ack_gather| 我从这些rank收集rejoin ack（也就是这些rank会向当前rank 发送 rejoin ack） |

|接口|接口|接口||
|:-|:-|:-|:-|
|rejoin_start||||
||rejoin_joint_start|||

## 一个请求的生命周期是怎样的？

|操作|接口|说明|
|:-|:-|:-|
|产生Message|AsyncConnection::process||
||Messenger::ms_deliver_dispatch||
||MDSDaemon::ms_dispatch(Message *m)|获取mds_lock，handle_core_message() or ds_rank->ms_dispatch(m)|
||MDSRankDispatcher::ms_dispatch(Message *m)|mds_rank->ms_dispatch(m)|
||MDSRank::_dispatch(Message *m, bool new_msg)||
||MDSRank::handle_deferrable_message(Message *m)||
|将Message转为MClientRequest|Server::dispatch()||
|将MClientRequest转为mdr|MDCache::request_start(MClientRequest *req)||mdr存放在active_requests中
|清理mdr|MDCache::request_finish(MDRequestRef& mdr)||
||MDCache::request_cleanup(MDRequestRef& mdr)||

只有到 Server::dispatch() 才把 Message转为 MClientRequest。

## mds laggy 时会 dispatch 么？

不会，MDSRank::_dispatch() 中会判断，如果是 laggy，那么就把 message放到 waiting_for_nolaggy 队列。

```
if (beacon.is_laggy()) {
    dout(10) << " laggy, deferring " << *m << dendl;
    waiting_for_nolaggy.push_back(m);
}
```



## 如果获取锁失败，怎么触发再次尝试

```
Locker::rdlock_start 中有 SimpleLock::WAIT_STABLE
lock->add_waiter(wait_on, new C_MDS_RetryRequest(mdcache, mut));
```


## 检查 slow request的接口

```
check_ops_in_flight()
```

## 请求中的tid是什么？

```
client.125255315:2877811973
```

|字段|字段|
|:-|:-|
|125255315|client id|
|2877811973|tid，transcation id|
