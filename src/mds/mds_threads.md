
## ceph-mds

    主线程，global_init()

## ms_dispatch

handle mds map，handle client request，对应 一系列 handle_client_xxxx 接口操作。

线程的启动：

    main()
      mds->init()
        messenger->add_dispatcher_tail(this)
         messager->ready()
            dispatch_queue.start()
               dispatch_thread.create("ms_dispatch")；
               local_delivery_thread.create("ms_local");

具体工作

    MDSDaemon::ms_dispatch()        
        MDSDaemon::handle_core_message() //以下是handle_core_message流程
            MDSDaemon::handle_mds_map()
                _handle_mds_map() // if whoami == MDS_RANK_NONE
                MDSRank::handle_mds_map() // if whoami != MDS_RANK_NONE
                    MDSRank::boot_create()
                    MDSRank::boot_start()                    
        MDSRank::ms_dispatch() // Not core, try it as a rank message
            MDSRank::_dispatch()
                MDSRank::handle_deferrable_message()
                    // some dispatches of subsystems 
                    mdcache->dispatch(m); // mdcache subsystem
                    mdcache->migrator->dispatch(m); // migrator
                    server->dispatch();   
                    balancer->proc_message(m);
                    locker->dispatch(m);

## admin_socket

admin 命令处理线程，启动顺序：

    main()
    common_init_finish(g_ceph_context)
    cct->start_service_thread()
    _admin_socket->init(_conf->admin_socket)
    make_named_thread ()


## service

上下文服务线程，和admin_socket一样是从common_init_finish接口中创建的线程。

    main()
    common_init_finish(g_ceph_context);
    cct->start_service_thread
    CephContext::start_service_thread()
    _service_thread->create("service")

## signal_handler

## ms_diapatch (beacon)

心跳线程dispatch线程

## safe_timer

MDBalancer::tick()
给mon发心跳

## recovery_thread

## pg_finisher

PurgeQueue的finisher 线程。MDSRank中有purge_queue。在PurgeQueue::init()接口中启动。

## ms_local

不知道什么用


    
## mds_rank_progr

## md_submit

日志提交线程

## log

日志线程

    main()
    global_init
    global_pre_init()
    common_preinit
    CephContext::CephContext()
    _log->start()
    create("log");
    
## fn_anonymous

回调处理线程，client 的请求处理commit日志之后的回调处理。

有两个，不知道什么原因？

一个是MDSRank的finisher，处理和osd，client之间的网络交互。

一个是MonClient的finisher，处理和mon之间的网络交互。

    // MDSRank中的finisher
    MDSDaemon::handle_mds_map
    mds_rank->init()
    MDSDispatcher::init()
    finisher->start();

    // MonClient中的Finisher
    main()
    mds->init();
    MDSDaemon::init()
    monc->init();
    MonClient::init()
    finisher.start();
    
 处理流程：
 
    取出finisher_queue，finisher_queue_rval中的上下文（为了减少锁竞争，让其他线程可以继续提交上下文）。
    然后循环调用上下文中的complete接口。
    如果finisher_queue中的元素是NULL，就会停下来先处理一个finisher_queue_rval中的上下文。
    
## msgr-worker-0/1/2/3

底层报文接收线程？？？
