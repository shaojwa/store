1. 模块处于STOPPED状态，无法处理请求，接口该如何返回错误码？
2. string 到 int 的hash算法。
3. new 之后要不要校验返回值是否为null？
4. 枚举型的必要性到底有多少？
5. 一个指针数组空间的释放怎么实现最好？
7. 保护状态的小锁是否有必要？比如rcache_state
8. 模块对外接口中，状态判断没有必要么？
9. release 掉析构，还是析构中掉release？ 应该是析构中掉release，析构掉再执行release中this就不可用。
10. 一个外部接口调用另外一个外部接口，都需要加锁，怎么处理，会有if(mutex.is_locked_by_me()) {mutex.unlock();} 这种操作么？
