#### samba 查看缓存相关配置

    testparm -sv | grep cache

#### samba 套件中的net命令查看和AD服务器交互是否正常
查看以下命令否正常，如果不正常，得考虑是网络问题还是winbind进程出问题。

    net ads testjoin


#### ctdb 问题定位命令
  
    ctdb status // 看状态 release 释放ip，takeover获取ip
    ctdb ip // 看ip分配
    /var/log/ctdb/ctdb.log ctdb日志多查看。   
