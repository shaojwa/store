
#### 查看processer的分配
```
# 查看不同的模块用哪些processer
ceph daemon dse.server1 config get processer_allocation

# 查看这些processer都绑定在哪些CPU上
ceph daemon dse.server1 config get libgo_conf
```

## dse中的processor和os中thread的对应
一个processor创建之后就和一个thread绑定，所以一个processor对应的thread是固定的。

## CreateTask()接口的参数名字
```
TaskF const& fn
```

## coroutine Task类成员命名
以下划线结尾
```
TaskState state_ = TaskState::runnable;
uint64_t id_;
Processer* proc_ = nullptr;
Context ctx_;
TaskF fn_;
std::exception_ptr eptr_; 
TaskAnys anys_;
```

## task.Sched()
```
tk.Sched(); 
```

## 从没见过支持多线程调度的，我觉得这个特性很有竞争力，就是不知道调度性能如何？
多线程调度使用的是worksteal算法，性能上的损耗很小，远远快于golang。
