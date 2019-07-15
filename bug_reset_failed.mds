#### 为什么ceph-mds.target的状态是active而ceph-mds没有不来？

    因为ceph-mds异常被终止次数半小时内超过3次
    
#### 半小时内三次的配置文件在哪里？

    ceph-mds@.service
   
#### reset-failed ceph-mds.target为什么无效
    
因为状态异常的服务时ceph-mds@mds0.service，而不是ceph-mds.target这个单元，可以通过 systemctl list-units看到单元的状态。

#### target 和service文件什么区别

    service文件也是单元（unit）中的一种，在ceph-mds中，ceph-mds@mds0.service 是 ceph-mds.target的一部分。

#### 如何查看所有ceph-mds相关的单元

    systemctl list-units | grep ceph-mds

可以看到有两个单元，一个是ceph-mds.target,另外一个是ceph-mds@mds0.serice

