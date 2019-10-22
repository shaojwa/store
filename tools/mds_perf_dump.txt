### perf dump 数据

perf 先关的leve有三个，默认情况下都是false，也就是不做统计的，目的是对不同类型的延时进行分类。

        ceph_perf_count_third_level
        ceph_perf_count_second_level
        ceph_perf_count_third_level
        
###  阶段：

收到请求，recv_stamp
msg层中分发，dispatch_stamp

mds层early_reply
mds层journal
Journaler::C_Flush::finish()

finish回调
Server::respond_to_request
Server::reply_client_request

### 字段

        avgcount：统计到的事件数。
        sum：总的用时（秒）。
        avgtime（微秒）：平均每个请求用时。
        begincount：开始统计时的已经处理的请求数量。
        endcount：统计结束时的处理的请求数。
        maxtime：最大时延（微秒）

###  request

总的请求数 1001

###  reply

总的响应数 1001

###  reply_latency (rlat): 

从recv请求到early_reply或者reply_client_request的延时。

也就是说，如果这个请求有early_reply，那么这个时间就算到early_reply，如果没有early reply，那么就算到正式reply给client为止。
        
虚拟机下平均8910微秒，物理机下为797微秒
        
###  dispatch_latency (dlat): 分发延时。
  
请求在msg中分发的时间，设定接口是：
  
        ms_deliver_dispatch
        ms_fast_dispatch
  
  在以下下两个接口中统计，但不会重复，所以count一般等于request的数量：
  
        earpy_reply
        reply_client_request
 
虚拟机下平均2723微秒，物理机下 31微秒

## second_reply_latency (slat)：

在reply_client_request中处理。

计算是从early_reply结束到日志落盘后调用reply_client_request时的时间间隔，就是第一次relay和第二次relay之间的时间间隔。

也就是说，针对的就是有early_reply的情况下，进行的统计。这个比rlat要大得多，在虚拟机上测几乎是10倍的差距。

虚拟机下平均87579微秒。物理机下为1952微秒。

### flush_caps_msg_num 

针对 CEPH_CAP_OP_FLUSH，不清楚具体用途。

1000个

### flush_caps_reply_latency

从消息收到到处理CEPH_CAP_OP_FLUSH这个op的时间。

虚拟机下平均85934微秒，物理机下111824微秒，不清楚为什么这么久。

### flush_caps_dispatch_reply_latency

从收到消息到OP被dispatch的时间。

虚拟机下平均84345微秒，物理机下为111581微秒，占flush_caps_reply_latency的绝大部分，不知道为什么。

### update_caps_msg_num

虚拟机下有549个。

### update_caps_reply_latency

从收到请求到handle_client_caps处理完 CEPH_CAP_OP_UPDATE 的时间。

handle_client_caps处理的CEPH_MSG_CLIENT_CAPS类型的msg，但是要处理的op很多。

虚拟机下平均692微秒，物理机为57013微秒，不知道为什么。

### update_caps_dispatch_reply_latency

虚拟机下平均422微秒，物理机为56799微秒，不知道为什么。

## mds_cache

## mds_log

### jlat

对应枚举值l_mdl_jlat，在Journaler中是logger_key_lat。
开始：Journaler::_do_flush中构造C_Flush开始。
结束：Journaler::C_Flush::finish() 执行回调结束。

### mds_mem

### mds_server

### handle_client_request_latency

893

### create_reply_latency

797

### create_dispatch_reply_latency

31

### readdir_reply_latency

457

### readdir_dispatch_reply_latency

98

## objecter

### wr_reply_latency

1549
和 wr_reply_latency 一个量级。

### wr_dispatch_latency

33us， 和 wr_dispatch_latency一个量级。

## mds-worker 统计数据

* 入队列
* 出队列

### msgr_running_total_time_lat 

线程总的执行时间

### msgr_running_send_time_lat

线程总的发送报文时间

### msgr_running_recv_time_lat

线程总的接收报文时间

### msgr_running_fast_dispatch_time_lat

快速分发时间

### msgr_send_enqueue_time_lat

报文入队列时间

### msgr_send_dequeue_time_lat

报文发送过程中的出对队列时间

### msgr_send_write_time_lat

发文发送过程中的

### msgr_receive_real_time_lat

### msgr_receive_all_time_lat

### msgr_fast_dispatch_time_lat

### msgr_keep2_time_lat

### msgr_keep2_ack_time_lat

### msgr_msgack_time_lat

### msgr_open_header_time_lat

### msgr_recv_osd_op_complete_lat

### msgr_recv_osd_reply_complete_lat

### msgr_recv_repop_complete_lat

### msgr_recv_repop_reply_complete_lat

### msgr_delay_state_time_lat

### msgr_running_process_time_lat

### msgr_send_osd_op_time_lat

### msgr_send_osd_op_reply_time_lat

### msgr_send_repop_op_time_lat

### msgr_send_repop_reply_time_lat

### msgr_send_osd_op_dequeue_lat

### msgr_send_osd_op_reply_dequeue_lat

### msgr_send_repop_dequeue_lat

### msgr_send_repop_reply_dequeue_lat

### msgr_osd_op_time_lat

### msgr_osd_opreply_time_lat

### msgr_osd_repop_time_lat

### msgr_osd_repopreply_time_lat

### msgr_op_inqueue_lat

### msgr_opreply_inqueue_lat

### msgr_repop_inqueue_lat

### msgr_repopreply_inqueue_lat

### msgr_hand_write_lock_time_1_lat

### msgr_hand_write_lock_time_2_lat

### msgr_hand_write_lock_time_3_lat

### msgr_hand_write_lock_time_4_lat

### msgr_ack_time_lat

### msgr_other_send_time_lat

### msgr_receive_header_time_lat

### msgr_throttle_message_time_lat

### msgr_throttle_bytes_time_lat

### msgr_dispatch_queue_time_lat

### msgr_read_real_time_lat

### msgr_decode_time_lat

### msgr_prepare_send_time_1_lat

### msgr_prepare_send_time_2_lat

### msgr_try_send_time_lat

### msgr_calc_crc_time_lat

### msgr_buffer_time_lat
