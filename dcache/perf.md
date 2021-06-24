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
