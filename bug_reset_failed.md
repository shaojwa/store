#### 为什么ceph-mds.target的状态是active而ceph-mds没有运行来？

    因为ceph-mds异常被终止次数半小时内超过3次
    
#### 半小时内三次的配置文件在哪里？

    ceph-mds@.service
    
#### 怎么知道是以为内达到次数起不来？

    systemctl status ceph-mds@mds0.service
 
输出可以看到，Active：failed (Result: start-limit)

#### 怎么看解决办法

用以下命令可以看到提示

    systemctl start ceph-mds@mds0.service
    
但是用这个是不行的：

    systemctl start ceph-mds.target

原因上面说明过，这是两个不同的单元。

#### reset-failed ceph-mds.target为什么无效
    
因为状态异常的单元是ceph-mds@mds0.service，而不是ceph-mds.target这个单元，可以通过 systemctl list-units看到单元的状态。

#### target和service文件什么区别

    service也是单元（unit）中的一种，在ceph-mds中，ceph-mds@mds0.service 是 ceph-mds.target的一部分。

#### 如何查看所有ceph-mds相关的单元

    systemctl list-units | grep ceph-mds

可以看到有两个单元，一个是ceph-mds.target,另外一个是ceph-mds@mds0.serice，单元好像 有high-level unit 和 low-level unit。


#### 如何查看失败的单元

    sysctmctl --failed
