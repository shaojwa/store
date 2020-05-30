## fnode_t

目录分片的元数据，fnode_t就和inode一样，只是这个里的信息是目录分片的元数据信息，参见mdstypes.h中的struct fnode_t结构。

目录分片的元数据主要包括包括fragstat， 和rstat。fragstat 是frag_info_t 类型，rstat是 nest_info_t类型。
