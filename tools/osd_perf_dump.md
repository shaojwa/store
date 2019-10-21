### 处理阶段

* 收到请求
* 入队：OSD::enqueue_op
* 出队：OSD::dequeue_op
* 完成op后的：log_op_stats


### op_w_process_latency

写操作延时，不包括排队时间。

开始点：PrimaryLogPG::do_op
结束点：PrimaryLogPG::log_op_stats
