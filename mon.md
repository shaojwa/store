#### 怎么看哪个mon是主mon  
      ceph mon stat
输出中有leader相关信息

#### mon把osd标记为out的日志
Marking osd.* out

#### 怎么看某个池的io
      
      ceph osd pool stats # statistics

#### 怎么看文件系统角度的性能
      
      ceph daemonperf mds.mds* 

