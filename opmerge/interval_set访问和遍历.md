## interval_set区间集合
区间集合的访问
```
for (interval_set<inodeno_t>::const_iterator p = prealloc_inos.begin();
    p != prealloc_inos.end(); ++p) {
  f->open_object_section("ino_range");
  f->dump_unsigned("start", p.get_start());
  f->dump_unsigned("length", p.get_len());
  f->close_section();
}
```
这是一个区间集合，元数是一个区间，比如```{[1,10], [15,19]}```

## interval_set 的区间遍历：
```
for (interval_set<inodeno_t>::const_iterator p = prealloc_inos.begin();
  p != prealloc_inos.end(); ++p) {
  // do something
}
```
## interval_set 的元素遍历：
```
用next，需要删除元素。
```
