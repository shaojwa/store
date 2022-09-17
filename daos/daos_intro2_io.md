#### server 中的poll-thread
- CART来数据。
- 创建ULT（userspace-lightweight-thread） 来handle 这个RPC。
- 如果是大数据，那需要启动一个Buld transfer，通过RDMA，
- 一个盘创建1-2个线程，避免pthread带来的开销。
- 在一个PMDK的transaction里，把SSD中的存储分配和元数据一次性写入PMEM中。用这个transaction来避免space leak。


#### 多副本支持

#### 问题
- write的io流程图中，途中涉及9个步骤，其中涉及的ULT好像只有2个左右，是哪两个？
