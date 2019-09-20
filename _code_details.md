  
#### Option.set_default("").set_description（""）写法
 
    Option类有set_default()和set_description（）接口，返回的是对象自己的应用，即*this

#### ceph中有get_str_vec接口来处理将string分割为vector

    vector<string> kvs;
    get_str_vec(config, ",",  kvs);
    
 #### ceph中有 strict_strtol系列函数将string转为做整型
 
    int level = (int) strict_strtol(levelstr.c_str(), 10, &err);
    
 #### CDir中的两个get_inode()函数
 
    CInode *get_inode()    { return inode; }
    const CInode *get_inode() const { return inode; }
  
  diri = dir->get_inode() 调用时会更具dir是不是const指针进行选择，如果dir是const指正，那么编译时只会调用第二个接口。
  所以，而如果CInode中获取字段的接口如果没有const属性，就不能调用，所以代码中很多时候以diri->inode的方式直接访问字段。
  
  #### 根据字段类型返回字段名接口参考
  
    static inline const char *get_lock_action_name(int a)
