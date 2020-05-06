```
int Signal() { 
    // make sure signaler is holding the waiter's lock.
    assert(waiter_mutex == NULL ||
	   waiter_mutex->is_locked());
    int r = pthread_cond_broadcast(&_c);
    return r;
 }
 ```
 
 条件变量时一种同步设备（man pthread_cond_signal： qsynchronization device）。
 那么信号为什么需要关联一个互斥锁（A condition variable must always be associated with a mutex）。
 man中说的很清楚，为了避免竞争条件标量，什么意思，就是一个线程在准备wait之前，另外一个线程sinal，这样前面准备wait的线程就收不到这个信号，所以，为了让这个等待和发送信号的过程串行化，就需要引入锁。


如果有多个线程在等待一个条件变量，另外一个线程sinal之后，到底谁会唤醒是不确定的，但是如果用的是pthread_cond_signal
那么肯定只有一个能唤醒（If several threads are waiting on cond, exactly one is restarted, but it is not specified which.）。如果用的是pthread_cond_broadcast，那么所有等在这个cond的线程都会唤醒。


条件变量释放锁和等待条件是原子的，也就是说，不会在释放锁之后，等待之前，其他线程会获取锁并sinal信号。

更多的消息可以参考
https://stackoverflow.com/questions/4544234/calling-pthread-cond-signal-without-locking-mutex
