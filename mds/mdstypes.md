#### fnode_t

目录分片的元数据，fnode_t就和inode一样，只是这个里的信息是目录分片的元数据信息，参见mdstypes.h中的struct fnode_t结构。

目录分片的元数据主要包括包括fragstat， 和rstat。fragstat 是frag_info_t 类型，rstat是 nest_info_t类型。

#### frag_info_t

分片的信息，和cdir一一对应，在cdir的fnode_t结构中，主要是四个字段：

1. 当前目录下非嵌套的的文件数（nfiles）
1. 当前目录下非嵌套子目录数（nsubdirs）
1. mtime
1. change_attr，是属性的修改次数么？不确定，类型是整型，看代码应该是这个意思。

#### struct nest_info_t
也是派生自scatter_info_t，字段有5个：
```
utime_t rctime;
int64_t rbytes;   // 某个目录下
int64_t rfiles;   // 某个目录下直接子目录包含的所有文件数
int64_t rsubdirs; // 某个目录下直接子目录包含的所有子目录数
```
