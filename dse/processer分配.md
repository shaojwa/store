
#### 查看processer的分配
```
ceph daemon dse.server1 config get processer_allocation #查看每个引擎中各个模块的负载由几个processer承载。
```
```
ceph daemon dse.server1 config get libgo_conf  #查看dse中，每个模块所分配到的processer列表，这些processer按顺序被不同的engine使用。
```
