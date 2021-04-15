## baseline performance statistics of two main components of cluster
### Benchmark Your Disk
```
> dd if=/dev/zeo of=here bs=1G count=1 oflag=direct
```
remembering to add the oflag parameter to bypass the disk page cache.


// HDD speed
```
$ dd if=/dev/zero of=outfile bs=1G count=1 oflag=direct
1+0 records in
1+0 records out
1073741824 bytes (1.1 GB, 1.0 GiB) copied, 7.1199 s, 151 MB/s
```
// SSD speed
```
[root@node0 ~]# dd if=/dev/zero of=outfile bs=1G count=1 oflag=direct
1+0 records in
1+0 records out
1073741824 bytes (1.1 GB) copied, 3.23191 s, 332 MB/s
```
//NVMe
```
[wsh@node32 cache]# dd if=/dev/zero of=outfile bs=1G count=1 oflag=direct
1+0 records in
1+0 records out
1073741824 bytes (1.1 GB) copied, 2.15634 s, 498 MB/s
```
// 
### Benchmark Your Network
on one of the nodes, start the iperf server:
```
root@node0 ~]# iperf -s
// on client
[root@node1 ~]# iperf3 -c 182.200.65.111
Connecting to host 182.200.65.111, port 5201
[  4] local 182.200.65.112 port 53928 connected to 182.200.65.111 port 5201
[ ID] Interval           Transfer     Bandwidth       Retr  Cwnd
[  4]   0.00-1.00   sec   113 MBytes   951 Mbits/sec   79    170 KBytes
[  4]   1.00-2.00   sec   113 MBytes   945 Mbits/sec  106   94.1 KBytes
[  4]   2.00-3.00   sec   113 MBytes   947 Mbits/sec   77    150 KBytes
[  4]   3.00-4.00   sec   112 MBytes   938 Mbits/sec  171    107 KBytes
[  4]   4.00-5.00   sec   113 MBytes   946 Mbits/sec   52   71.3 KBytes
[  4]   5.00-6.00   sec  79.6 MBytes   668 Mbits/sec  218    115 KBytes
[  4]   6.00-7.00   sec   114 MBytes   954 Mbits/sec  102    165 KBytes
[  4]   7.00-8.00   sec   113 MBytes   946 Mbits/sec   56    135 KBytes
[  4]   8.00-9.00   sec   112 MBytes   943 Mbits/sec   70    154 KBytes
[  4]   9.00-10.00  sec   112 MBytes   941 Mbits/sec   22    127 KBytes
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Retr
[  4]   0.00-10.00  sec  1.07 GBytes   918 Mbits/sec  953             sender
[  4]   0.00-10.00  sec  1.07 GBytes   916 Mbits/sec                  receiver

// another interface
[root@node1 ~]# iperf3 -c 172.17.65.111
Connecting to host 172.17.65.111, port 5201
[  4] local 172.17.65.112 port 44624 connected to 172.17.65.111 port 5201
[ ID] Interval           Transfer     Bandwidth       Retr  Cwnd
[  4]   0.00-1.00   sec  2.76 GBytes  23.7 Gbits/sec    0   1.36 MBytes
[  4]   1.00-2.00   sec  2.76 GBytes  23.7 Gbits/sec    0   1.43 MBytes
[  4]   2.00-3.00   sec  2.76 GBytes  23.7 Gbits/sec    0   1.83 MBytes
[  4]   3.00-4.00   sec  2.76 GBytes  23.7 Gbits/sec    0   2.01 MBytes
[  4]   4.00-5.00   sec  2.76 GBytes  23.7 Gbits/sec    0   2.12 MBytes
[  4]   5.00-6.00   sec  2.76 GBytes  23.7 Gbits/sec    0   2.22 MBytes
[  4]   6.00-7.00   sec  2.74 GBytes  23.6 Gbits/sec    0   2.22 MBytes
[  4]   7.00-8.00   sec  2.76 GBytes  23.7 Gbits/sec    0   2.22 MBytes
[  4]   8.00-9.00   sec  2.76 GBytes  23.7 Gbits/sec    0   2.22 MBytes
[  4]   9.00-10.00  sec  2.76 GBytes  23.7 Gbits/sec    0   2.22 MBytes
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Retr
[  4]   0.00-10.00  sec  27.6 GBytes  23.7 Gbits/sec    0             sender
[  4]   0.00-10.00  sec  27.6 GBytes  23.7 Gbits/sec                  receiver
```

### NOTES
Benchmarking can be performed at different levels:
1. you can perform low-level benchmarking of the storage cluster itself,
2. or you can perform higher-level benchmarking of the key interfaces, such as block devices and object gateways.


Before running any of the benchmarks in subsequent sections, drop all caches using a command like this:
```
shell> sudo echo 3 | sudo tee /proc/sys/vm/drop_caches && sudo sync
```

### Benchmark a ceph storage cluster
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

