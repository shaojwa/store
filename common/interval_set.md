#### insert() 注意点
```
set_a.insert(offset, len); // 要保证len > 0
set_a.insert(set_b);  // set_a 和 set_b 不能有交集，不然会有断言，有交集场合可以考虑用union_insert()代替
```

#### union_insert() 注意点
```
union_insert(offset, len); // 要保证 len > 0
```

#### subtruct() 注意点
```
b.subtruct(a) // a必须是b的集合，不能直接减去任何集合，所以先要用a.intersection_of(b) 算出交集
```

#### interval_set的遍历
```
for (auto it = filling_ints.begin(); it != filling_ints.end(); ++it)
{
  uint64 off = it.get_start(), len = it.get_len();
  bufferptr ptr(data_ptr, off, len);
  slabs[index].slab_data.copy_in(off, len, ptr.c_str());
}
```

#### 赋值运算不会影响源interval_set
```
interval_set<uint64> old_ints = interval_set<uint64>(old_map);
interval_set<uint64> new_ints = old_ints;
```

#### 无法用匿名map去构造interval
必须用已经存在的具名map去构造interval_set，下面两种方式都无法通过编译，当然原理上没有区别。
```
// 
interval_set<uint64> direct_ints = interval_set<uint64>({{100,10}});
interval_set<uint64> direct_ints = interval_set<uint64>(map<uint64, uint64>({{100,10}})); 
```
只能
```
interval_set<uint64_t> my_interval(my_map);
```

####  dump到map影响interval_set原有数据
先赋值给别的interval_set之后再dump，不然原有的interval数据会清掉。

#### intrvl_a.union_of(intrvl_b) 中，intrvl_b可以临时构造
union_of(const interval_set &b) 是const引用
```
map_set.union_of(interval_set<uint64_t>(m_backend));
````
难道对匿名对象只能用const引用么，是的为了安全。
