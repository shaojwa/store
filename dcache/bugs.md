1. engine, `eph engine dump` show engines donot evenly distributed , but all stay in the last node.
1. rcache, used_space uint64 overflow
1. rcache, one object with queue-id 'none'
1. rcache, the object still in cold-queue after reading by `rados get`


DCache 项目bug分类
## 组件使用类错误
1. boost intrusive list 中 erase_and_dispose接口获取下一个迭代器用法错误。

## 逻辑错误
1. dm中snap 的cache_intervals没有在chunk的filling_write之后同步更新。


