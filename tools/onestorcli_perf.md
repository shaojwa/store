
#### mds 性能命令

* 需要在handy节点上运行
* mds 相关数据取自 ceph daemon mds.mds0 perf dump

#### 使用步骤

先clean：

        onestor-cli perf -m mds -t clean
 
然后open：

        onestor-cli perf -m mds -t open
        
开始业务

然后关闭：
        
        onestor-cli perf -m mds -t close
        
最后显示：

        onestor-cli perf -m mds -t show

### perf dump 数据

perf 先关的leve有三个，默认情况下都是false，也就是不做统计的，目的是对不同类型的延时进行分类。

        ceph_perf_count_third_level
        ceph_perf_count_second_level
        ceph_perf_count_third_level
        
####  阶段：

* 收到请求：recv_stamp
* msg中分发：dispatch_stamp。占用时 30% 以下。

在一个目录下跑业务，一般都只会发送到一个mds上。

####  request: 总的请求数
####  reply: 总的响应数
####  reply_latency（rlat）: 

从recv请求到early_reply或者reply_client_request的延时。

也就是说，如果这个请求有early_reply，那么这个时间就算到early_reply，如果没有early reply，那么就算到正式reply给client为止。

虚拟机下平均8910微秒

        avgcount：统计到的事件数。
        sum：总的用时（秒）。
        avgtime（微秒）：平均每个请求用时。
        begincount：开始统计时的已经处理的请求数量。
        endcount：统计结束时的处理的请求数。
        maxtime：最大时延（微秒）
        
####  dispatch_latency（dlat）: 分发延时。
  
  虚拟机下平均2723微秒
  
  在请求在msg中分发的时间，设定接口是：
  
        ms_deliver_dispatch
        ms_fast_dispatch
  
  在一下两个接口中统计，但不会重复，所以count一般等于request的数量：
  
        earpy_reply
        reply_client_request
  
 字段：
 
        avgcount：统计到的事件数。
        sum：总的dispatch用时（秒）。
        avgtime（微秒）：平均每个请求dispatch用时。
        begincount：开始统计时的已经处理的事件数量。
        endcount：统计结束时的处理的事件数。
        maxtime：最大时延（微秒）
  

#### second_reply_latency（slat）：

在reply_client_request中处理，虚拟机下平均87579微秒。

计算是从early_reply结束到日志落盘后调用reply_client_request时的时间间隔，就是第一次relay和第二次relay之间的时间间隔。

也就是说，针对的就是有early_reply的情况下，进行的统计。这个比rlat要大得多，在虚拟机上测几乎是10倍的差距。

####  flush_caps_msg_num 

针对 CEPH_CAP_OP_FLUSH，不清楚具体用途。



## onestor-cli perf 字段
### mds 模块
#### reply_latency
#### dispatch_latency
#### flush_caps_reply_latency

从消息收到到处理CEPH_CAP_OP_FLUSH这个op的时间。

虚拟机下平均85934微秒，不清楚为什么这么久。

#### flush_caps_dispatch_reply_latency

从收到消息到OP被dispatch的时间。

虚拟机下平均84345微秒，占flush_caps_reply_latency的绝大部分，不知道为什么。

#### update_caps_msg_num

虚拟机下有3个。

#### update_caps_reply_latency

从收到请求到handle_client_caps处理完 CEPH_CAP_OP_UPDATE 的时间。

handle_client_caps处理的CEPH_MSG_CLIENT_CAPS类型的msg，但是要处理的op很多。

虚拟机下平均692微秒。

#### update_caps_dispatch_reply_latency

虚拟机下平均422微秒。


### mds_server 模块

#### handle_client_request_latency

在dispatch中处理完这个请求的时间，包 dispatch到具体的处理函数，然后获取锁，eary reply，提交日志，最后回到dispath流程的总时间。

虚拟机平均 6968微秒，共101个。

#### handle_client_session_latency

处理session相关请求的时间。

虚拟机平均 81微秒，共3个。

#### create_reply_latency

这个是mds_server模块下的 third_level的 perf。

这个和最开始的reply_latency 是一样的，只是这里会细分出各种操作，在只有create的情况下，这两个是一样的。

虚拟机环境下是 8910 微秒， 数量是 101。

#### create_dispatch_reply_latency

这个是mds_server模块下的third_level的指标。

这个和最开始的dispatch_latency 是一样的，只是这里会细分出各种操作，在只有create的情况下，这两个是一样的。

虚拟机环境下是 2723 微秒，数量是 101。

### mds_log 模块

#### jlat

日志下刷延时，基本是占 second_reply_latency 的大部分，因为日志下刷是异步的，所以一般都会比较久。

## objecter 模块

#### wr_reply_latency

从op发送出去，到执行 finish_op的用时， 该接口在handle_osd_op_reply中调用。 在这个接口的最后面会调用回调函数。

虚拟机环境下是 74989 微秒。

#### wr_dispatch_latency

