## frag_info_t

分片的信息，和cdir一一对应，在cdir的fnode_t结构中，主要是四个字段：

1. 当前目录下非嵌套的的文件数（nfiles）
1. 当前目录下非嵌套子目录数（nsubdirs）
1. mtime
1. change_attr，是属性的修改次数么？不确定，类型是整型。
