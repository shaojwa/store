#### 新创建的目录总是pin到一个固定的mds上

参见《kR》中的第173页的算数类型转换： 

* 如果一个uint32_t 和 int32_t比较，那么会把int32_t转为uint32_t  
* 如果一个uint32_t 和 int64_t比较，那么会把uint32_t 转为 int64_t  
