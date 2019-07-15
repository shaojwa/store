
#### tick 的工作线程是哪个？

    通过scatter_tick的日志可以看到，mds tick的线程是safe_timer线程
    
#### tick 的周期是多少
  
    默认情况下是5秒，可以通过日志看到。
    
#### tick 的调用流程

     MDSDaemon::tick()-> mds_rank->tick()
