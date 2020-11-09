make_request是一个通用的接口，原有的设计中，都是针对单一op，那么四个参数已经足够处理几乎是有的posix接口，包括：
```
mount
upward_nested_xattr
check_stray_snapdir_nums
_do_filelock
_interrupt_filelock

// 增
_mknod
_create
_mkdir
_link
_symlink
_open

// 删
_unlink
_rmdir
_removexattr

// 改
_rename
_do_setattr
_do_setxattr
_renew_caps

// 查
_getattr
_getcwd
_readdir_get_frag
_do_lookup
lookup_hash
lookup_ino
lookup_parent
lookup_name
```
如果要扩展到opm批量方式，不同的请求由不同的出参需要填充，这个接口应该如何设计？
