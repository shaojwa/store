#### SafeTimer 关于构造

禁用拷贝构造函数和赋值运算符重载：
```
// This class isn't supposed to be copied
SafeTimer(const SafeTimer&) = delete;
SafeTimer& operator=(const SafeTimer&) = delete;
```

学习下构造函数：
```
SafeTimer::SafeTimer(CephContext *cct_, Mutex &l, bool safe_callbacks)
  : cct(cct_), lock(l), safe_callbacks(safe_callbacks), thread(NULL), stopping(false) {}
```

####  为什么需要Mutex
SafeTimer提供一些接口，用来添加event，取消event，这些操作和schedule这个map相关系。
另外SafeTimer有一个工作线程叫timer_thread，这个线程也会操作schedule这个map，这样就可能有多个线程操作schedule。
