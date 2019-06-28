#### 如何查看samba缓存时间相关配置

    testparm -sv | grep cache

#### 如何查看samba和AD服务器交互是否正常
查看以下命令否正常，如果不正常，得考虑是网络问题还是winbind进程出问题。

    net ads testjoin


#### ctdb 问题定位命令
 
 看状态 release 释放ip，takeover获取ip 
 
    ctdb status
    
看ip分配 

    ctdb ip
    
ctdb日志多查看 

    /var/log/ctdb/ctdb.log
