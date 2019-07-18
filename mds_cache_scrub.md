#### mds scrub 的流程

关键入口函数是 void MDCache::enqueue_scrub_work(MDRequestRef& mdr) 两种触发方式:  
一种是 void MDCache::dispatch_request(MDRequestRef& mdr), 因为OP是CEPH_MDS_OP_ENQUEUE_SCRUB触发，应该是命令执行时因为异常操作需要重试。
一种是 void MDCache::enqueue_scrub()触发，这种方式是响应命令做void MDSRank::command_scrub_path() 和void MDSRank::command_tag_path()时调用。


#### MDCache::disptch() 和 MDCache::disptch_request()

有一个要注意，disptch的是message，不是request，是比较底层的消息。

MDCache::dispatch() 用来处理 port 为 MDS_PORT_CACHE 类型的message，根据代码看，只处理MDS发过来的message：
    case MDS_PORT_CACHE:
        ALLOW_MESSAGES_FROM(CEPH_ENTITY_TYPE_MDS);
        mdcache->dispatch(m);
其中port什么用暂时不清楚，只知道是一个分类。比如还有一个 MDS_PORT_MIGRATOR 是迁移的，都是MDS内部之间的。


MDCache::dispatch_request(MDRequestRef& mdr) 有各种work函数。MDCache模块中有dispatch()接口：  
MDCache::dispatch_request() 处理的是request，即MDRequestRef，和dispatch是不在一个层次的东西。

请求分三类，client的，slave的，还有internal的。比如 CEPH_MDS_OP_ENQUEUE_SCRUB这个就是其中一个。
dispatch_request()主要在void C_MDS_RetryRequest::finish(int r) 这个回调函数里执行。

C_MDS_RetryRequest类中的回调都会执行dispatch_request(),这是一个比较上层的接口。

#### 加锁地方

scrub流程在调用mdcahe->enqueue_scrub()前获取mds_lock大锁。

#### 调用流程
    
    MDCache::dispatch_request(MDRequestRef& mdr)      
        enqueue_scrub_work(mdr); // internal op
            scrubstack->enqueue_inode_top()
            scrubstack->enqueue_inode_bottom()
                enqueue_inode()
                    _enqueue_inode()
                    kick_off_scrubs()
                        while {
                            scrub_file_inode()
                            scrub_dir_inode()
                        }
