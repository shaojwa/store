#### dedup和compact
1. dedup就是deduplicate，去重，删除重复的数据，在ROW下面。
1. 以8k为单位计算指纹。
1. 8k对齐的整块数据给压缩模块。
1. 在线重删除和离线重删。
1. 在线重删只用非透传模式，透传模式下，只计算指纹。为什么？
1. 重删怎么做的？
1. 普通透传，和非透传模式的数据才进行压缩。


#### enable/disable compress
```
ceph compress set_switch pool Poolname on/off
```

#### enable/disable online-dedup  
```
ceph dedup set pool Poolname online on/off
```
#### enable/disable offline-dedup  
```
ceph dedup set pool Poolname offline on/off
```
