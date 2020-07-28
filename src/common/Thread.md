#### Thread就是一个框架
Thread就是一个框架，需要派生类来实现entry接口，所以有一个纯虚函数：
```
 protected:
  virtual void *entry() = 0;
```
比如：SafeTimerThread继承Thread的时候需要实现entry()
```
void *entry() override {
    parent->timer_thread();
    return NULL;
  }
```
#### 为什么是protected
c++ primer中有说过，protected可以想象为private和public的混合，它是类的使用者不可见的。
