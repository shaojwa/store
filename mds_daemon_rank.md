#### 消息的分发

daemon 和 rank中，所有的dispatch接口都是针对Message，有以下接口：

    bool MDSDaemon::ms_dispatch(Message *m)
        bool MDSDaemon::handle_core_message(Message *m) 
        bool MDSRankDispatcher::ms_dispatch(Message *m)
            bool MDSRank::_dispatch(Message *m, bool new_msg)
                bool MDSRank::handle_deferrable_message(Message *m)
                
bool MDSRank::handle_deferrable_message(Message *m) 字面意思，就是可以延期的消息，到这一步，后续的都是各个子系统的dispatch()

还是刚才说的，各个dispatch都是以Message为参数的，包括：

    mdcache->dispatch(m);
    mdcache->migrator->dispatch(m);
    server->dispatch(m);
    balancer->proc_message(m);
    locker->dispatch(m);

#### mds_lock的获取

  现在我们只要记得一点，mds_lock在最底层的 bool MDSDaemon::ms_dispatch(Message *m)中就已经获取到，所以说，这是一把大锁。
