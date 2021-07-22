#### 日志文件大小
固定64M

#### 日志分级
分L0-L6，L0最多4个文件，也就是文件容量最多256M。
。L1文件最多2560M，L2是25600M，两层之间10倍比例。

#### compact触发的条件
1. L0 其中L0的compact触发条件是文件数，当文件数大于4个时触发
2. L1-L6触发compact的条件是文件总容量，文件容量和达到上限时触发（`256*10^n`，比如L1层为2560M）

后来，增加两条触发条件，针对整个Level的总的deletion项数目和比例。
配置项为`rocksdb_deletion_entries`达到`100000`条或者`deletion_entries_key_score`达到`0.5`。

#### 日志查看
```
cat cephg-osd.0.log | grep -i compact
cat cephg-osd.0.log | grep -i compacted
cat cephg-osd.0.log | grep -i "compaction stat" -A 10
```
