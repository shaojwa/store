#### atop shows
2022/02/28  17:40:04
```
DSK |          sdk |  busy     97% | read  364586 |  write 1036e3
```

#### who is SDK
```
sdk       8:160  1  3.5T  0 disk
├─sdk1    8:161  1   16M  0 part
├─sdk2    8:162  1  100M  0 part /var/lib/ceph/osd/ceph-8
├─sdk3    8:163  1  224G  0 part
├─sdk4    8:164  1  100M  0 part /var/lib/ceph/osd/ceph-11
├─sdk5    8:165  1  100G  0 part
├─sdk6    8:166  1  300G  0 part
├─sdk7    8:167  1  348G  0 part
├─sdk8    8:168  1    2G  0 part
├─sdk9    8:169  1  300G  0 part
├─sdk10   8:170  1  348G  0 part
├─sdk11   8:171  1    2G  0 part
├─sdk12   8:172  1  300G  0 part
├─sdk13   8:173  1  348G  0 part
└─sdk14   8:174  1    2G  0 part
```

#### who is ceph-8 and ceph-11
```
[SDS_Admin@test110 dcache]$ ceph osd tree
ID  CLASS WEIGHT   TYPE NAME                           STATUS REWEIGHT PRI-AFF
-19              0 root maintain
-18        0.29306 root dcache-d0
-37        0.29306     rack rack.dcache-d0
-67        0.09769         host test110.dcache-d0
 11        0.09769             osd.11                      up  1.00000 1.00000
-82        0.09769         host test111.dcache-d0
 10        0.09769             osd.10                      up  1.00000 1.00000
-97        0.09769         host test112.dcache-d0
  9        0.09769             osd.9                       up  1.00000 1.00000
-17        0.65639 root row-d0
-40        0.65639     rack rack.row-d0
-64        0.21880         host test110.row-d0
  8   ssd  0.21880             osd.8                       up  1.00000 1.00000
-79        0.21880         host test111.row-d0
  7   ssd  0.21880             osd.7                       up  1.00000 1.00000
-94        0.21880         host test112.row-d0
  6   ssd  0.21880             osd.6                       up  1.00000 1.00000
-16       32.73830 root d0
-20       32.73830     rack rack.d0
-55       10.91277         host test110.d0
 26   hdd  3.63759             osd.26                      up  1.00000 1.00000
 29   hdd  3.63759             osd.29                      up  1.00000 1.00000
 32   hdd  3.63759             osd.32                      up  1.00000 1.00000
-70       10.91277         host test111.d0
 25   hdd  3.63759             osd.25                      up  1.00000 1.00000
 28   hdd  3.63759             osd.28                      up  1.00000 1.00000
 31   hdd  3.63759             osd.31                      up  1.00000 1.00000
-85       10.91277         host test112.d0
 24   hdd  3.63759             osd.24                      up  1.00000 1.00000
 27   hdd  3.63759             osd.27                      up  1.00000 1.00000
 30   hdd  3.63759             osd.30                      up  1.00000 1.00000
-15        0.29306 root dcache-wenjian
-46        0.29306     rack rack.dcache-wenjian
-61        0.09769         host test110.dcache-wenjian
  5        0.09769             osd.5                       up  1.00000 1.00000
-76        0.09769         host test111.dcache-wenjian
  4        0.09769             osd.4                       up  1.00000 1.00000
-91        0.09769         host test112.dcache-wenjian
  3        0.09769             osd.3                       up  1.00000 1.00000
-14        0.65639 root row-wenjian
-49        0.65639     rack rack.row-wenjian
-58        0.21880         host test110.row-wenjian
  2   ssd  0.21880             osd.2                       up  1.00000 1.00000
-73        0.21880         host test111.row-wenjian
  1   ssd  0.21880             osd.1                       up  1.00000 1.00000
-88        0.21880         host test112.row-wenjian
  0   ssd  0.21880             osd.0                       up  1.00000 1.00000
-13       43.65106 root wenjian
-43       43.65106     rack rack.wenjian
-52       14.55035         host test110.wenjian
 14   hdd  3.63759             osd.14                      up  1.00000 1.00000
 17   hdd  3.63759             osd.17                      up  1.00000 1.00000
 20   hdd  3.63759             osd.20                      up  1.00000 1.00000
 23   hdd  3.63759             osd.23                      up  1.00000 1.00000
-10       14.55035         host test111.wenjian
 13   hdd  3.63759             osd.13                      up  1.00000 1.00000
 16   hdd  3.63759             osd.16                      up  1.00000 1.00000
 19   hdd  3.63759             osd.19                      up  1.00000 1.00000
 22   hdd  3.63759             osd.22                      up  1.00000 1.00000
 -7       14.55035         host test112.wenjian
 12   hdd  3.63759             osd.12                      up  1.00000 1.00000
 15   hdd  3.63759             osd.15                      up  1.00000 1.00000
 18   hdd  3.63759             osd.18                      up  1.00000 1.00000
 21   hdd  3.63759             osd.21                      up  1.00000 1.00000
 -1              0 root default
```

#### pool names
```
pool_wenjian ## filesystem data pool
Metadata     ## filesystem meta pool
```
