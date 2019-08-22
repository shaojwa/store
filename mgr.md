#### mgr 的作用

  从L版本开始(12.x),这是一个要求的组件。
  
  mon维护各种map信息，而mgr维护除此之外的监控和管理，包括pool的数目，object的数目等。

#### 缺少mgr

  ceph -s 会有告警。data部分也会缺少部分信息，ceph health 会无法输出。
