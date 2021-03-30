##  write (pre-store data)
```
[root@node74 ~]# fio --name=vol_base_test --numjobs=1 --ioengine=rbd --rw=write --direct=1 --iodepth=1 --bs=256K --size=1G 
                     --pool=.disk01.rbd --rbdname=vol0 --group_reporting 
vol_base_test: (g=0): rw=write, bs=256K-256K/256K-256K/256K-256K, ioengine=rbd, iodepth=1
fio-2.2.10
Starting 1 process
rbd engine: RBD version: 1.12.0
Jobs: 1 (f=1): [W(1)] [100.0% done] [0KB/25318KB/0KB /s] [0/98/0 iops] [eta 00m:00s]
vol_base_test: (groupid=0, jobs=1): err= 0: pid=4070481: Mon Mar 29 20:30:07 2021
  write: io=1024.0MB, bw=26099KB/s, iops=101, runt= 40177msec
    slat (usec): min=22, max=215, avg=50.68, stdev=16.20
    clat (msec): min=7, max=31, avg= 9.76, stdev= 2.02
     lat (msec): min=7, max=31, avg= 9.81, stdev= 2.03
    clat percentiles (usec):
     |  1.00th=[ 7712],  5.00th=[ 7968], 10.00th=[ 8160], 20.00th=[ 8384],
     | 30.00th=[ 8640], 40.00th=[ 8768], 50.00th=[ 9152], 60.00th=[ 9408],
     | 70.00th=[ 9920], 80.00th=[10688], 90.00th=[12096], 95.00th=[14656],
     | 99.00th=[17280], 99.50th=[18304], 99.90th=[20352], 99.95th=[23424],
     | 99.99th=[31360]
    bw (KB  /s): min=22483, max=28388, per=100.00%, avg=26140.63, stdev=1317.61
    lat (msec) : 10=70.65%, 20=29.22%, 50=0.12%
  cpu          : usr=0.60%, sys=0.07%, ctx=4257, majf=0, minf=65
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=0/w=4096/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
  WRITE: io=1024.0MB, aggrb=26098KB/s, minb=26098KB/s, maxb=26098KB/s, mint=40177msec, maxt=40177msec

Disk stats (read/write):
    dm-0: ios=0/464, merge=0/0, ticks=0/213, in_queue=213, util=0.38%, aggrios=0/1091,
    aggrmerge=0/18, aggrticks=0/12747, aggrin_queue=12746, aggrutil=1.11%
  sda: ios=0/1091, merge=0/18, ticks=0/12747, in_queue=12746, util=1.11%
```

## read

```
[root@node74 ~]# fio --name=vol_base_test --numjobs=1 --ioengine=rbd --rw=read --direct=1 --bs=256K --iodepth=1 --size=1G
                      --pool=.disk01.rbd --rbdname=vol0 --group_reporting=1
vol_base_test: (g=0): rw=read, bs=256K-256K/256K-256K/256K-256K, ioengine=rbd, iodepth=1
fio-2.2.10
Starting 1 process
rbd engine: RBD version: 1.12.0
Jobs: 1 (f=1): [R(1)] [100.0% done] [101.2MB/0KB/0KB /s] [404/0/0 iops] [eta 00m:00s]
vol_base_test: (groupid=0, jobs=1): err= 0: pid=1663431: Tue Mar 30 09:20:23 2021
  read : io=1024.0MB, bw=99278KB/s, iops=387, runt= 10562msec
    slat (usec): min=1, max=41, avg= 8.46, stdev= 7.21
    clat (usec): min=1799, max=9337, avg=2568.43, stdev=485.34
     lat (usec): min=1809, max=9356, avg=2576.89, stdev=486.38
    clat percentiles (usec):
     |  1.00th=[ 1992],  5.00th=[ 2096], 10.00th=[ 2160], 20.00th=[ 2256],
     | 30.00th=[ 2320], 40.00th=[ 2384], 50.00th=[ 2448], 60.00th=[ 2544],
     | 70.00th=[ 2640], 80.00th=[ 2800], 90.00th=[ 3088], 95.00th=[ 3376],
     | 99.00th=[ 4320], 99.50th=[ 5088], 99.90th=[ 6624], 99.95th=[ 7712],
     | 99.99th=[ 9280]
    bw (KB  /s): min=83123, max=106581, per=100.00%, avg=99388.48, stdev=5116.96
    lat (msec) : 2=1.10%, 4=97.46%, 10=1.44%
  cpu          : usr=0.52%, sys=0.20%, ctx=4103, majf=0, minf=1
  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued    : total=r=4096/w=0/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
     latency   : target=0, window=0, percentile=100.00%, depth=1

Run status group 0 (all jobs):
   READ: io=1024.0MB, aggrb=99278KB/s, minb=99278KB/s, maxb=99278KB/s, mint=10562msec, maxt=10562msec

Disk stats (read/write):
    dm-0: ios=0/126, merge=0/0, ticks=0/17, in_queue=17, util=0.16%, aggrios=0/370, aggrmerge=0/5,
          aggrticks=0/7720, aggrin_queue=7720, aggrutil=1.71%
  sda: ios=0/370, merge=0/5, ticks=0/7720, in_queue=7720, util=1.71%
```
