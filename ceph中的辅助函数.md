# ceph 中的辅助函数

## 根据字段类型返回字段名接口参考
```
static inline const char *get_lock_action_name(int a)
```

## ceph中有strict_strtol系列函数将string转为整数
``` 
int level = (int) strict_strtol(levelstr.c_str(), 10, &err);
```

## ceph中有get_str_vec接口来处理将string分割为vector
```
vector<string> kvs;
get_str_vec(config, ",",  kvs);
```
