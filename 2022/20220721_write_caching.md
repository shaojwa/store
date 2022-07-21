发现HDD好像都不支持这个配置：
```
[wsh@node61 ~]$ sudo hdparm -W  /dev/sdx

/dev/sdx:
SG_IO: bad/missing sense data, sb[]:  70 00 05 00 00 00 00 0a 00 00 00 00 20 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 write-caching = not supported
```
但是SSD好像支持：
```
[SDS_Admin@node61 ~]$ sudo hdparm -W /dev/sdy

/dev/sdy:
 write-caching =  1 (on)
[SDS_Admin@node61 ~]$ sudo hdparm -W /dev/sdz

/dev/sdz:
 write-caching =  0 (off)
```
