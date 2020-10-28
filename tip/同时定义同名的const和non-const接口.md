#### CDir中的为什么两个get_inode()函数，一个const，一个非const
```
CInode *get_inode()   { return inode; }
const CInode *get_inode() const { return inode; }
``` 

1. 因为要修改，所以需要对开放开，但同时提供const函数可以尽可能减少被误修改的风险。
2. diri = dir->get_inode() 调用时会根据dir是不是const指针进行选择。如果dir是const指针，那么编译时就会选择用第二个接口。
而如果CInode中获取字段的接口如果没有const属性，就不能调用，所以代码中很多时候以diri->inode的方式直接访问字段。
