```
inodeno_t take_ino(inodeno_t ino = 0) {
    assert(!info.prealloc_inos.empty());

    if (ino) {
      if (info.prealloc_inos.contains(ino))
        info.prealloc_inos.erase(ino);
      else
        ino = 0;
    }
    if (!ino) {
      ino = info.prealloc_inos.range_start();
      info.prealloc_inos.erase(ino);
    }
    info.used_inos.insert(ino, 1);
    return ino;
 }
 ```
 1. 如果ino为0很好理解，就是拿一个新的ino，也就是第一个可用的就可以。
 2. 如果ino不等于0，其实就是优先选ino，如果这个值有就拿，没有就拿第一个元素。
