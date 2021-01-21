#### dse/dcache pools
```
data: pool_a -> dcache.pool_a(dcache_log_pool for pool_a) + .pool_a.dse (pool for ROW)
meta: .diskpool8.rbd-> dcache..diskpool8.rbd + ..diskpool8.rbd.dse
```

#### instance_id
```
instance_id = poolid << 16 + engineid
```

#### engine dump
```
ceph engine dump
```

#### env
```
[root@node231 etc]# cat onestor_external_version
UniStorOS-E1151
Release date 2020.10.22
[root@node231 etc]# cat onestor_internal_version
NAS V200R001B01D001
ONEStor V300R001B05D001
UniStorOS V100R001B51D001
NAS V100R003B02D008
```

#### IO

```
rados -p 1 bench 1200 write -b 8192 
// -p 1: pool
// 1200, seconds
```

```
ceph daemon dse.node23 engine 12.4 config set debug_engine 5
```

```
ceph daemon dse.node23 engine all dcache desage get_info
ceph daemon dse.node23 engine 12.4 dcache desage get_info

ceph daemon dse.node23 engine all dcache qm get_quota
ceph daemon dse.node23 engine 12.4 dcache qm get_quota
```

#### osd
```
ceph osd lspools
ceph osd pool ls
ceph osd pool ls detail
```

```
