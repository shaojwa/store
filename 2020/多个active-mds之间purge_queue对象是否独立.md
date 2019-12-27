#### 独立

验证过程可以参见《多个active-mds之间日志对象是否独立.md》

#### 验证命令

```
[root@node12 rank1]# rados -p .capfs.metadata.Metadata ls | grep ^50
500.00000001
501.00000000
500.00000000
```
