```
inodeno_t next_ino() const {
  if (info.prealloc_inos.empty())
    return 0;
  return info.prealloc_inos.range_start();
}
```
很简单，还有元素就返回下一个，没有可用就返回0标记没有可用元素。
