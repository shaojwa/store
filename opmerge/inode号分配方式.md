# Inode allocate

## 分配的顺序

MDS在通过接口Server::alloc_inode_id()分配inode时，会按照session为单位预先分配一部分inode号。

1. 先从session.info.prealloc_inos拿。
1. session中没有可用的就从inotable中take_ino()拿。

#### session中关键的inode集合：
1. session.info.prealloc_inos    ：分配给这个session的，可以使用的inode，已经记入日志。
1. session.info.used_inos        ：这个session的，已经使用的inode，注意是已经使用。
1. session.pending_prealloc_inos ：多个请求都可能触发预分配申请，还没记入日式日志。

#### InoTable中关键的inode集合：
1. projected_free： inotable中获取的话，优先从这里拿。
1. free

```
首先根据不同的命名空间，分三种：
（a）全局的InoTable下有两个，一个是projected_free和free
（b）session中的info中的，pending_prealloc_inos，prealloc_inos 和used_inos。
（c）mdr中的prealloc_inos，
```

（1）如果当前session的状态不是正在打开（opening），那么就认为是允许预分配的，在这个情况下会去看预分配的集合中还有没有可用的inode。此时take_ino() 的入参useino比较重要，take_inode就是从预分配的inode集合中获取inode。
注意这里的预先分配就是从session.info.prealloc_inos中获取，这部分ino是已经记日志分配给这个session的。


（a）此时如果useino不为0，那么就会看看这个ino在不在prealloc_inos里，如果有，那直接删掉，就当做已经分配出去。
如果prealloc_ino中没有，那么就标记ino，目的是触发第二步再次分配一个。

这里的问题是，为什么会出现这个情况? 以及为什么不认为这个是之前分配出去的ino，而要重新分配？看下面分析


（b）如果这个useino为0，表示client没有收到unsafe回应中分配inode值，这个应该是大部分情况，那么就会从prealloc_inode中拿出一个ino，并把这个ino放到used_inos中。

把当前请求的会话进行projected，其实就是把全局的一个session-map的version 放到当前的会话中。

（2）如果说预分配中已经没有ino可用，那么就通过mds->inotable->project_alloc_id();接口再次分配。

（3）这里即解决上面的问题，如果客户端认为已经分配的ino，而mds认为不再预分配里，由分配了一个new_ino，这时候 useino 和 new_ino就不一样。
这种情况应该是不应该出现的，所以有会有级别为0 的日志，并有mds->clog->error() 打印，好像应该要ceph_abort()，但是不知道为什么注释掉。

（4）如果当前projected的prealloc_ino数目连配置值的一半都没有，那么就会再次出发预分配，分配的目标是达到配置值（默认是1000个）这个时候就把新申请的ino放到pending_prealloc_inos集合里，对当前的会话来说这个是pending_prealloc_inos。记录日志之后，这个pending_prealloc_inos中的元素会变成prealloc_inos，参见apply_allocated_inos()接口。

现在再说下几个问题：

（1）为什么已经已经有session.info.prealloc_inos，还要有pending_prealloc_inos。 计划projected_prealloc_inos? 
session.info.prealloc_ino是之前的请求触发的已经完成的预分配ino，如果非空，都是从这个里面取走的。
而pending_prealloc_inos是当前请求时，可能触发的预分配，这个操作完成之后，pending_prealloc_inos中的，ino就会放到session.info.prealloc_inos中。

（2）projected_free这个是干什么用的？
预分配的ino需要申请，就是从这里拿出来，这个里面放的是原先的会话释放掉的ino，这ino也是之前的会话申请的预分配ino，后来会话关闭就回收到这里。申请inode的时候，project_alloc_id() 优先会从projected_free集合中分配，如果是project_alloc_ids()操作。是从projected_free中获取，获取之后把得到的ids放到会话的pending_prealloc_inos中，之所以是pending，是因为当时还没记日志。

所以流程上就是：

inotable.projected_free 拿出来放到放到new_ino 和 pending_prealloc_inos中，其中new_ino是马上要用的，pending_prealloc_inos是申请成为prealloc_ino的ino集合。
从session.info.prealloc_inos的来源我们就知道，代码是`session->info.prealloc_inos.insert(mdr->prealloc_inos);`，接口是 apply_allocated_inos()。
这个接口是在reply_client_request()中调用的，也就是一个请求处理完成之后，预分配的申请正式完成之后。

（3） 计算get_num_projected_prealloc_inos的时候，为什么要算 prealloc_inos 加上 pending_prealloc_inos 的呢？ 有了上面的分析就很好理解。
这是已经给这个会话的预分配ino集合，以及正在申请的将要预分配给这个会话的ino集合。
