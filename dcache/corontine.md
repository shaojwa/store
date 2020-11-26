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
