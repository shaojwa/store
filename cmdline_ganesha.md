#### 查看ganesha中的ceph配置
```
ceph daemon $(netstat -anp | grep ganesha.*asok | awk '{print $10}')   config show | grep debug_client 
```
默认等级是1/5，但是问题环境上是15
