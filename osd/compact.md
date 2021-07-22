#### 日志文件大小
固定64M

#### 日志分级
分L0-L6，其中L0的compact触发条件是文件数，当文件数大于4个时触发，也就是文件容量大于256M。
L1-L6触发compact的条件是文件大小。L1文件最多2560M，L2是25600M，两层之间10倍比例。

####
#### 日志查看
```
cat cephg-osd.0.log | grep -i compact
cat cephg-osd.0.log | grep -i compacted
cat cephg-osd.0.log | grep -i "compaction stat" -A 10
```
