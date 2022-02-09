## root概念
一个root就是一个硬盘池，或者更准确说是一个分区池。

## 元数据的概念
落盘时才会有元数据的需求

## OSD中的层次
```
OSD-pg
OSD-rep/EC
----
OSD:scache
OSD:nlueStore-rocksdb-bluefs
block-dev
```

## 元数据分离部署
就是对象的元数据(rocksdb中)和对象的数据(bluestore)管理分开，不在同一个磁盘上。

## 全闪和元数据分离部署的关系
没有关系，3.0或者5.0版本，与元数据是否分离没有必然关系。全闪下，也可以有元数据分离部署。

## ROW池的作用
ROW池给分布式rocksdb用。

## SCache的作用
SCache是bluestore之上的一层，存储的是pg角度看到的对象的数据和元数据，此时，没有bluestore参与（应该没有涉及rockdb）。

## osd下的block连接
block链接的是数据盘。

## block分区和scache的关系
block分区会和scache进行绑定。


## 元数据分离部署时中osd目录下多出的2个链接
元数据分离部署情况下多出来的block.db, block.wal
```
block.db    存放rocksdb中的数据。
block.wal   存放rockdb的日志。
```

## 对象存储在block-dev上的位置等信息也是放在rocksdb中么
是的


## 其他参考
参考1：[混闪缓存盘为什么压力比较大](store/2021/202110混闪缓存盘为什么压力比较大.md)
