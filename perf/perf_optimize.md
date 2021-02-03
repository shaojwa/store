
#### 评判标准
多快好省

#### 测试工具
文件和块一般通用，可以fio，vdbench，dd。对象一般用cosbench。

#### 简单测试性能工具
默认自带的dd

#### 性能测试最主要的两个方面参数
1. 并发 2. 模型（同步异步，随机顺序，IO大小）

#### 性能的测试的一般原则
1. 原则合适的鬓发和模型
1. 记录完整的性能数据（硬件，软件版本，配置）
1. 组件微基准测试
1. 硬件的checklist以及硬件的基准测试
1. 避免业务影响，比如保证无重构，scrub等功能参与。

#### 典型性能数据
|项目|说明||
|:-|:-|:-|
||0||

#### 网络延时
|项目|时延|说明|
|:-|:-|-:|
|上下文切换|1us||
|集群内部RTT|0.1ms||
|RAID卡写入缓存|10-100us||
|1M数据的内存拷贝|300us||
|1M文件写(HDD)|20ms||

#### CPU基准测试
|工具|示例|说明|
|:-|:-|:-|
|dd|dd if=/dev/zero  of=/dev/null bs=1M count=100000 |不太准，但是比较讨巧，做内存拷贝|
|sysbench| sysbench --test=cpu --cpu-max-prime=20000 run||

#### CPU观测工具
|工具|示例|说明|
|:-|:-|:-|
|top/atop|看空闲cpu = idle + wait，注意wait字段，这个状态也可以工作|
|trace-noschedule|https://github.comn/bytedance/trace-noschedule|因为优先级原因没有被调度走|

#### CPU优化和排查
|工具|说明|
|:-|:-|
|绑核|网卡中断基本都可以，但是进程绑核需要慎重|
|CPU降频率排查|是否配置成节能模式，正常需要性能模式，电源功率限制|

#### 内存基准测试
|工具|实例|说明|
|:-|:-|:-|
|dd|dd if=/dev/zero  of=/dev/null bs=1M count=100000|cpu和内存都可用用dd|
|stream|需要自己编译https://github.com/jeffhammond/STREAM||

#### 内存观测工具
|工具|说明|
|:-|:-|
|free|空余应该看available，不是free|
|vmstat||
|/proc/meminfo|内存中的active页面，inative页面，dirty页面|
|numasstat|对不同NUMA node上内存分配统计，注意留意miss值|
|slabtop|内核文件系统中inode和dentry分配信息|

#### 内存优化
|工具|说明|
|:-|:-|
|关闭swap|swap如果出现，对性能影响非常大|
|将进程版订到NUMA节点||
|page cache优化|比如性能波动大可以调整 dirty_ratio和background dirty ratio|

#### 内存问题排查
|工具|说明|
|:-|:-|
|内存槽位会对性能有非常明显影响|内存插法一定要按照厂商推荐的配置|

#### 磁盘基准测试
磁盘既然是块设备，就可以用fio完全搞定
|工具|说明|
|:-|:-|
|fio|块设备通用|

#### 磁盘观测工具
常用的就这一种：
|字段|说明||
|:-|:-|:-|
|iostat|r_await，w_await，包括队列等待和实际处理时间，单位为ms||
|iostat|svctm，处理IO请求的平均时间，不包括等待时间，为推断数据||
|iostat|%util工作时间占总时间百分比，对于SSD等可能存在并行IO的介质，100%并不代表饱和||

#### 磁盘优化和排查
磁盘硬件本身的优化很少，对它之上的RAID卡有几个需要注意：
|项目|说明|
|:-|:-|
|主要排查RAID缓存是否打开以及读写比例是否配置正确||

#### 网络基准测试
|工具|||
|:-|:-|:-|
|ping|比如集群内ping包超过0.1ms就明显有问题||
|iperf|client: iperf -c 1.1.1.1 -P 5 -t 10  server: iperf -s|侧重带宽|
|qperf|client: qperf 192.168.25.18 tcp_lat server: qperf |侧重时延|
qperf，因为有时候协议栈的配置不对会影响性能，用来测试TCP/UDP协议，这个是ping做不到的，特别是在跑上业务的时候，用qperf打一下时延。

#### 网络观测工具
|工具|说明||
|:-|:-|:-|
|sar|sar -n DEV 1|查看各个网卡的实时吞吐量，用来检查排查类似bound网卡配置问题|
|tcpdump/wireshark|更细致的网络调优|有专家信息，丢包，错报，重传等网络问题|

#### 网络优化和排查
|手段|||
|:-|:-|:-|
|网卡中断绑核|||
|增大TCP缓冲区|net.ipv4.tcp_wmem|有min，default，max，一般增大max足够，推荐大小=带宽×时延|
|增大网卡ring buffer|硬件上的环形缓冲区，溢出就会丢包||

#### 案例 kworder:H 导致网卡丢包问题

kworker的优先级80，高于网卡软中断ksoftirq线程的60。
