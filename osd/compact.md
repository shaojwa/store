#### 1. 日志文件大小
固定64M

#### 1. 日志分级
分L0-L6，L0最多4个文件，也就是文件容量大于256M。
L1-L6触发compact的条件是文件大小。L1文件最多2560M，L2是25600M，两层之间10倍比例。

#### 1. compact触发的条件
1. L0 其中L0的compact触发条件是文件数，当文件数大于4个时触发
2. L1-L6 是文件容量和达到上限（`256*10^n`）
3. Entry数目达到10W条。

#### 1. 日志查看
```
cat cephg-osd.0.log | grep -i compact
cat cephg-osd.0.log | grep -i compacted
cat cephg-osd.0.log | grep -i "compaction stat" -A 10
```
