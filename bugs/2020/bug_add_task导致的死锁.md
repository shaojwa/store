```
virtual void add_task(opm_task_t *t) {
  _tasks_lock.Lock();
  if (empty();) {
    first_task_stamp = ceph_clock_now();
  }
  tasks.insert(t);
  _tasks_lock.Unlock();
}
bool empty() {
  _tasks_lock.Lock();
  bool b = tasks.empty();
  _tasks_lock.Unlock();
  return b;
}
```

gdb：
```
0x00007fa421ddf277 in raise () from /lib64/libc.so.6
0x00007fa421de0968 in abort () from /lib64/libc.so.6
0x00007fa4145cb5c5 in ceph::__ceph_assert_fail (assertion=assertion@entry=0x7fa414ad0266 "r == 0",
0x00007fa4145984ca in Mutex::Lock (this=this@entry=0x7fa3a2c9f930, no_lockdep=no_lockdep@entry=false)
0x00007fa41d165808 in empty (this=0x7fa3a2c9f8e0)
OpmBatchBase::add_task (this=0x7fa3a2c9f8e0, t=0x7fa3a2c6b020) 
```
