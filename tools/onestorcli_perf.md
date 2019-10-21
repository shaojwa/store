## onestor-cli perf 性能命令

### 代码

/opt/xxx/lib/python2.7/site-packages/onestor_cli/perf_counter

* 需要在handy节点上运行
* mds 相关数据取自 ceph daemon mds.mds0 perf dump

### 使用步骤

先clean：

        onestor-cli perf -m mds -t clean
 
然后open：

        onestor-cli perf -m mds -t open
        
开始业务

然后关闭：
        
        onestor-cli perf -m mds -t close
        
最后显示：

        onestor-cli perf -m mds -t show
## reply_latency

见perf dump

## dispatch_latency

见perf dump

###  flush_caps_msg_num 

见perf dump

### flush_caps_reply_latency

见perf dump

### flush_caps_dispatch_reply_latency

见perf dump

## update_caps_msg_num

虚拟机下有3个。

## update_caps_reply_latency

从收到请求到handle_client_caps处理完 CEPH_CAP_OP_UPDATE 的时间。

handle_client_caps处理的CEPH_MSG_CLIENT_CAPS类型的msg，但是要处理的op很多。

虚拟机下平均692微秒。

## update_caps_dispatch_reply_latency

虚拟机下平均422微秒。

## mds_server 模块

## handle_client_request_latency

在dispatch中处理完这个请求的时间，包 dispatch到具体的处理函数，然后获取锁，eary reply，提交日志，最后回到dispath流程的总时间。

虚拟机平均 6968微秒，共101个。

## handle_client_session_latency

处理session相关请求的时间。

虚拟机平均 81微秒，共3个。

## create_reply_latency

这个是mds_server模块下的 third_level的 perf。

这个和最开始的reply_latency 是一样的，只是这里会细分出各种操作，在只有create的情况下，这两个是一样的。

虚拟机环境下是 8910 微秒， 数量是 101。

## create_dispatch_reply_latency

这个是mds_server模块下的third_level的指标。

这个和最开始的dispatch_latency 是一样的，只是这里会细分出各种操作，在只有create的情况下，这两个是一样的。

虚拟机环境下是 2723 微秒，数量是 101。

## mds_log 模块

## jlat

日志下刷延时，基本是占 second_reply_latency 的大部分，因为日志下刷是异步的，所以一般都会比较久。

## objecter 模块

## wr_reply_latency

从op发送出去，到执行 finish_op的用时， 该接口在handle_osd_op_reply中调用。 在这个接口的最后面会调用回调函数。

虚拟机环境下是 74989 微秒。

## wr_dispatch_latency
 
 osd返回操作结果，osdc收到后dispatch的时间，基本很小，虚拟机中未 142 微秒。
