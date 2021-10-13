这个标记在destage_obj_t,destage_view_t, destage_context_t中都有包含。

#### 什么时候需要刷bucket
在节点进行扩容的时候。

不engine的部分bucket就需要迁移到其他的engine上。
迁出bucket的engine就需要下刷数据，以便新的承载engine可以读到最新的数据。
所以engine 告诉dcache，调用接口dcache_bucket_migrate()，然后dcache告诉destage去下刷。

#### 迁移哪些bucket
engine会告诉dcache，以参数的范式传入`dcache_bucket_migrate()`.
此时，dcache的状态会变成全透模式。同时destage需要下刷这些buckets。

#### destage干了什么
先把需要下刷的bucket放到destage_view中的buckets_to_destage集合中。

然后调用do_destage_bucket()去把涉及到的processer对应的destage_view的destage_sem唤醒，触发启动下刷。

#### bucket没有刷下的一个问题

原因分析：
因为多个destage_view同时下刷对应bucket，但是只有在destage_bucket_sum为0时，才会把对应的view中的need_destage_bucket为false。
这导致，多个view中，只有一个view结束指定对象刷盘，其他的view 都因为need_destage_bucket标记依然为true而导致无法启动正常的对象下刷。
