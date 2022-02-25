#### 5.0版本中rocksdb存储的数据
1. 用户对象的元数据
2. 用户对象在聚合对象中的位置信息
3. 聚合对象的元数据

#### 现在有几个rocksdb
```
两大类：分布式rocksdb和本地rocksdb
分布式给ROW和Dedup用
本地rocksdb给OSD用
```

#### 分布式rocksdb实现的文件系统
```
DseFS
```

#### 本地rocksdb需要的文件系统
```
bluefs
```
