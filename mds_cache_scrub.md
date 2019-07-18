#### mds scrub 的流程
关键入口函数是 void MDCache::enqueue_scrub_work(MDRequestRef& mdr) 两种触发方式:  
一种是 void MDCache::dispatch_request(MDRequestRef& mdr), 因为OP是CEPH_MDS_OP_ENQUEUE_SCRUB触发。  
一种是 void MDCache::enqueue_scrub()触发，这种方式是响应命令做void MDSRank::command_scrub_path() 和void MDSRank::command_tag_path()时调用。


#### MDCache::disptch() 和

MDCache::dispatch_request(MDRequestRef& mdr) 有各种work函数。MDCache模块中有dispatch()接口，这里还有dispatch_request(),区别是：  
MDCache::dispatch() 用来处理 port 为 MDS_PORT_CACHE 类型的消息，根据代码看，只处理MDS发过来的请求：

    ALLOW_MESSAGES_FROM(CEPH_ENTITY_TYPE_MDS);
    mdcache->dispatch(m);

其中port什么用暂时不清楚，只知道是一个分类。比如还有一个 MDS_PORT_MIGRATOR 是迁移的，都是MDS内部之间的。

MDCache::dispatch_request() 处理三类请求，client的，slave的，还有internal的。比如 CEPH_MDS_OP_ENQUEUE_SCRUB这个就是其中一个。
dispatch_reques()主要在void C_MDS_RetryRequest::finish(int r) 这个回调函数里执行，暂且认为主要是执行别人的请求。

##### message中的 port

MDS_PORT_CACHE

MDS_PORT_MIGRATOR

#### ceph中的OP

CEPH_MDS_OP_XXXX 开头，


#### 加锁地方

scrub流程在调用mdcahe->enqueue_scrub()前获取mds_lock大锁。
