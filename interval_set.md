#### 赋值运算不会影响源interval_set
```
interval_set<uint64> old_ints = interval_set<uint64>(old_map);
interval_set<uint64> new_ints = old_ints;
```

#### 无法用匿名map去构造interval

必须用已经存在的具名map去构造interval_set，下面两种方式都无法通过编译，当然原理上没有区别，
```
// 
interval_set<uint64> direct_ints = interval_set<uint64>({{100,10}});
interval_set<uint64> direct_ints = interval_set<uint64>(map<uint64, uint64>({{100,10}})); 
```
只能：
```
interval_set<uint64_t> my_interval(my_map);
interval_set<uint64_t> map_set(m);
```

#### 无法dump到一个map的同时不影响自己的数据。

#### intersection_of(s) 之后s不会发生变化
```
```

#### union_of(interval) 可以临时构造。
union_of(const interval_set &b) 是const 引用，难道对匿名对象只能用const 引用么
```
map_set.union_of(interval_set<uint64_t>(m_backend));
````
