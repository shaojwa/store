#### target 非空
request中的target这个InodeRef在发送请求的时候是null的，但是verify_reply_trace中的会存在非空的情况。
原因是，在handle_client_reply的时候，接口insert_trace()中会把request->target进行设置。
这个是ms_dispatch处理线程干的事。所以，你不能简单断言 request->target为空，除非你在insert_trace做处理。

#### 这个handle_client_reply的ms_dispatch线程

这个线程和用户线程线程不是同一个，显然的。
