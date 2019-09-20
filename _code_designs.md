#### 工作函数中不获取锁，接口函数中获取锁

  Journaler::wait_for_flush() -> _wait_for_flush()
  Journaler::flush() -> _flush()
