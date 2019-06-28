#### 如何查看samba缓存时间相关配置

    testparm -sv | grep cache

#### 如何查看samba和AD服务器交互是否正常

    net ads testjoin    // 查如果不正常，得考虑是网络问题还是winbind进程出问题。
    
#### samba 改异步

samba/smb.conf在[global]中添加  

    strict sync = no
    sync always = no 
    
重启smbd进程
testparm –sv 可以检查配置

#### 查看samba状态

    smbstatus

#### ctdb 问题定位命令
    
   * ctdb ip 查看动态ip所在的节点号 （显示在0上）
   
    # ctdb ip
    # 192.168.0.90 0 
    
   * 查看序号0所在的主机
   
    # ctdb status 
    pnn：0 192.168.0.11
    pnn：1 192.168.0.12

   * 查看日志 /var/log/ctdb/ctdb.log  //ctdb日志多查看 
