* 优化下一代OSD中消息处理，利用批处理提高性能(https://github.com/ceph/ceph/pull/27430)
* 改进下一代OSD消息分发机制的优化手段(https://github.com/ceph/ceph/pull/27690)
* Ceph在Recovery时，如何最大程度保证业务访问的性能问题。目前在Recovery时，会造成集群性能下降比较严重，导致正常的业务I/O收到影响。
* Ceph中Qos的机制问题。
* 如何降低Ceph运维成本？目前Ceph开源版本在运维成本上对于传统运维人员还是有很高的门槛。
* ScatterLock.h代码学习
* ceph hash函数实现学习：
```
while (length--) {
  unsigned char c = *str++;
  hash = (hash + (c << 4) + (c >> 4)) * 11;
}
```
* hash函数看看是否可以优化，hash值带下来。
* user_obj->pre_conflict_ops.push_back(op_node) 为什么需要引用。
* 如何在构造map是初始化元素(done)
* int返回值是否为0怎么写(done)
* Mutex中的Lock/Unlock是void类型，而ptherad_mutex_lock是有返回值的，怎么做这个一层屏蔽转换？
* decode接口有没有针对char指针的输出进行处理？
* 想用一套框架来处理不同的batch和task，那么自然，接口中都是用的基类指针。
但是派生类的构造是不是只能独立于框架接口，不同的batch用batcher的工厂模式创建么？
batch中的不同task又怎么在框架内构造？不同的派生task，派生batch必然需要有自己的特定接口吧

* libc里已经有strtol()，但是ceph中又实现 strict_strtol() 系列函数将string转为整数，为什么要新实现一个？
``` 
int level = (int) strict_strtol(levelstr.c_str(), 10, &err);
```
* 边界怎么说？ bound，比如复杂度的上界，下界一般用lower bound， upper bound。
* 构造函数参数名和成员同名怎么区分？参数以下划线结束，比如param_，参见 MDSRank::MDSRank。
* 非公共成员函数怎么区别public成员函数？ 以下划线开始，比如_stop_local()，参见 class AsyncConnection。
* 等号比较常量一定要放左面么？ ceph代码没有这个要求，按照语义顺序来，一般常量放在等号右边。
* 关于post和pre接口的命名怎么写？一般post和pre 在动词前，比如postfix， prefix。
* 类中成员是引用类型是否支持？当然支持，而且需要在构造函数中完成初始化。
* 枚举型的必要性到底有多少？ ceph 中似乎很少用，用的比较多的是定义宏，参数中用int来指定。
* 试试用指针的引用。
* iterator的命名，是it_map还是map_it。
* 比较时常量宏写等号左边还是右边。
* ceph中如果嵌套比较深，会不会倾向用if把特例先continue掉，这样减少嵌套深度。
* string到int的hash算法。
* 接口函数和工作函数什么时候分离？工作函数被调用较多，或者接口函数需要处理锁操作的时候。
* 模块处于STOPPED状态，无法处理请求，接口该如何返回错误码？
* new 之后要不要校验返回值是否为null？
* 一个指针数组空间的释放怎么实现最好？
* 保护状态的小锁是否有必要？比如rcache_state
* 模块对外接口中，状态判断没有必要么？
* release 掉析构，还是析构中掉release？ 应该是析构中掉release，析构掉再执行release中this就不可用。
* 一个外部接口调用另外一个外部接口，两个接口都有需要加锁的场景，怎么设计？ `if(mutex.is_locked_by_me()) { mutex.unlock(); } `
* 模块状态机需要分NONE，INIT，ACTIVE等多个状态么？是否尽可能简单比较好？
* 先设置状态还是，等所有操作之后再设置状态，比如STOP模块的时候？？
* 把枚举移动到类内部
```
enum {
  DM_STAT_HASH    = 0x01,
  DM_STAT_OBJECT  = 0x02,
  DM_STAT_DESTAGE = 0x04,
  DM_STAT_FILLING = 0x08,
};
```

* 这种写法专业么?
```
return (--_snap_to_objs[snap_id]);
```
