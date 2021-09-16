#### 创建 task
```
 scheduler->CreateTask(
  [this, shard_index, pg] { _remove_csdpg(shard_index, pg);}
  ::co::TaskOpt(
    UINT16_MAX,
    UINT16_MAX,
    processors[shard_index],
    true,
    0,
    0,
    __func__,
    __FILE__,
    __LINE__)
);
```
#### 是否支持销毁
协程目前不支持销毁，目前看只能等task全部清零

#### 设置日志
```
ceph daemon dse.<hostname> coro_setlog <n>
```
