#### 不用new且要有括号：
```
len_ratio.insert(pair<uint64, req_hit_t>(region, req_hit_t()));
```
用new报错, new 之后返回的可就是指针，不是对象本身：
```
len_ratio.insert(pair<uint64, req_hit_t>(region, new req_hit_t()));
```
没有括号也不行，那只是一个类型，操作不明：
```
len_ratio.insert(pair<uint64, req_hit_t>(region, new req_hit_t));
```
