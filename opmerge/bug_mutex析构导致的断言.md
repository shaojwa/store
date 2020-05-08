```
0x00007fa6b85cb5c5 in ceph::__ceph_assert_fail (assertion=assertion@entry=0x7fa6b8ac5206 "nlock == 0"
func=func@entry=0x7fa6b8ac55d0 <Mutex::~Mutex()::__PRETTY_FUNCTION__> "Mutex::~Mutex()") 
0x00007fa6b8598336 in Mutex::~Mutex (this=0x7fa6a28382a8, __in_chrg=<optimized out>)
0x00007fa6c113b915 in ~opm_task_t (this=0x7fa6a28382a0, __in_chrg=<optimized out>)
Client::_create (this=this@entry=0x7fa6b6173000, dir=dir@entry=0x7fa6a847c000
```

wait之后没有释放lock就delete：
```
void wait() {
      assert(cond);
      lock.Lock();
      cond->Wait(lock);
    }
```
修改方案：添加release接口。
```
void release() {
  if (lock.is_locked()) {
    lock.Unlock();
  }
}
```
