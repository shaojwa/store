#### 新创建的目录总是pin到一个固定的mds上

参见《kR》中的第173页的算数类型转换： 

* 如果一个uint32_t 和 int32_t比较，那么会把int32_t转为uint32_t  
* 如果一个uint32_t 和 int64_t比较，那么会把uint32_t 转为 int64_t  

问题代码：

  int64_t auth_subtree_num = mds->mdcache->num_subtrees_fullauth();
  if (auth_subtree_num - load.second.auth_subtree_num > g_conf->mds_smart_pin_subtree_threshold)
  // load.second.auth_subtree_num 是 uint32_t, mds_smart_pin_subtree_threshold 是 uint64_t
  // int64_t - uint32_t  > uint64_t 相减之后的负数 int64_t 转为 uint64_t时变为大数

一般写法，要注意几个地方：

* 算数运算要保证相同的数据类型，一定要避免隐式转换。
* 可以用加法来替换减法。

  (cur_xattrs_size + inc) > g_conf->mds_max_xattr_pairs_size

