## rados bench 基本参数

|参数|值|说明|
|:-|:-|:-|
|并发IO数目|16|这个并发的数目，网上说是线程数，但是我并没有看到那么多线程|
|块大小|4M||
|Bandwidth||主要性能指标|
|Bandwidth(Min)||主要性能指标|
|Bandwidth(Max)||主要性能指标|
|IOPS||主要性能指标|
|IOPS(Min)||主要性能指标|
|IOPS(Max)||主要性能指标|

https://tracker.ceph.com/projects/ceph/wiki/Benchmark_Ceph_Cluster_Performance

## 全闪集群测试结果


## Benchmark a ceph storage cluster
```
> rados bench -p test_pool 10 write --no-cleanup
```
default 16 threads:
```
[root@node0 ~]# rados bench -p blkpool0 10 write --no-cleanup
hints = 1
Maintaining 16 concurrent writes of 4194304 bytes to objects of size 4194304 for up to 10 seconds or 0 objects
Object prefix: benchmark_data_node0_233372
  sec Cur ops   started  finished  avg MB/s  cur MB/s last lat(s)  avg lat(s)
    0       0         0         0         0         0           -           0
    1      16        22         6   23.9996        24    0.923882    0.874877
    2      16        33        17   33.9978        44      1.0873     1.23972
    3      16        49        33   43.9967        64    0.856734     1.19597
    4      16        65        49   48.9966        64    0.912776     1.12494
    5      16        79        63   50.3963        56    0.744533     1.11291
    6      16        90        74   49.3296        44     1.35364     1.13007
    7      16       111        95   54.2815        84    0.813422     1.11334
    8      16       129       113   56.4955        72     1.01948     1.07034
    9      16       148       132    58.662        76    0.556231     1.04373
   10      16       167       151   60.3952        76    0.680786     1.01076
   11      16       168       152   55.2683         4     1.24019     1.01227
Total time run:         11.419165
Total writes made:      168
Write size:             4194304
Object size:            4194304
Bandwidth (MB/sec):     58.8484
Stddev Bandwidth:       24.4503
Max bandwidth (MB/sec): 84
Min bandwidth (MB/sec): 4
Average IOPS:           14
Stddev IOPS:            6
Max IOPS:               21
Min IOPS:               1
Average Latency(s):     1.0819
Stddev Latency(s):      0.33822
Max latency(s):         2.36782
Min latency(s):         0.494124
```
32 thread:
```
[root@node0 ~]# rados bench -p blkpool0 10 write -t 32 --no-cleanup --run-name benchmark_write_t32
hints = 1
Maintaining 32 concurrent writes of 4194304 bytes to objects of size 4194304 for up to 10 seconds or 0 objects
Object prefix: benchmark_data_node0_328028
  sec Cur ops   started  finished  avg MB/s  cur MB/s last lat(s)  avg lat(s)
    0       0         0         0         0         0           -           0
    1      31        45        14    55.997        56     0.95286    0.902561
    2      31        84        53   105.992       156    0.687498    0.934576
    3      31       126        95   126.657       168     1.00559    0.830658
    4      31       157       126    125.99       124    0.907393    0.848185
    5      31       200       169    135.19       172    0.519313    0.859725
    6      31       240       209   139.323       160    0.677908    0.835005
    7      31       283       252   143.989       172    0.802674    0.822872
    8      31       319       288   143.989       144    0.701135    0.827169
    9      31       357       326   144.877       152    0.686082    0.833104
   10      31       402       371   148.388       180    0.675451    0.819857
   11      17       403       386   140.352        60     1.06291     0.83598
Total time run:         11.429895
Total writes made:      403
Write size:             4194304
Object size:            4194304
Bandwidth (MB/sec):     141.034
Stddev Bandwidth:       43.5414
Max bandwidth (MB/sec): 180
Min bandwidth (MB/sec): 56
Average IOPS:           35
Stddev IOPS:            10
Max IOPS:               45
Min IOPS:               14
Average Latency(s):     0.873288
Stddev Latency(s):      0.275154
Max latency(s):         2.087
Min latency(s):         0.438047
```
