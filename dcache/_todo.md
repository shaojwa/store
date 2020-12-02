1. 把枚举移动到类内部
```
enum {
  DM_STAT_HASH    = 0x01,
  DM_STAT_OBJECT  = 0x02,
  DM_STAT_DESTAGE = 0x04,
  DM_STAT_FILLING = 0x08,
};
```

1. 这种写法专业么?
```
return (--_snap_to_objs[snap_id]);
```
