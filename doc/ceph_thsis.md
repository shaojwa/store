## 2.1 Local File systems

接口以及行为，也就是语义，构成了POSIX标准的基础。

### 3.2.2 Client synchronization

* 跨对象边界的写要做到原子性是很复杂的。所以，还不能完全做事务的语义。（不知道最新的版本如何？）
* 读写共享在通用负载中很少出现，但是在科学计算中却很常见。
* POSIX I/O 中针对高性能计算扩展被提出，其中的一部分被ceph实现，比如 open 接口的 O_LAZY 标记(写共享文件)。

## 3.3 Communication Model

ceph在节点间通信时采用异步消息模型。记发出的消息会先排队，延后发送，而不需要阻塞。


# Appendix B：MDS Implementation Details

## B.1 
