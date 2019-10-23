
#### 子系统

    // sub systems
    Server       *server;
    MDCache      *mdcache;
    Locker       *locker;
    MDLog        *mdlog;
    MDBalancer   *balancer;
    ScrubStack   *scrubstack;
    DamageTable  damage_table;

Server子系统：session管理， recovery管理，辅助例程，request处理（主要工作）


