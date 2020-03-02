### 现象

update_caps_reply_latency 达到 2760 微秒，对应reply_latency 只有1357微秒，两倍多。
update_caps_dispatch_reply_latency 达到838微秒，而对应的dispatch_latency只有29微秒。


### 思路1：确认是不是报文优先级问题

op是：CEPH_CAP_OP_UPDATE, 从msg层判断是否是优先级问题。
