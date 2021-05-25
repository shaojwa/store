#### 
```
/opt/h3c/lib/python2.7/site-packages/onestor/cs/hostmanager.py +3533 

#### block seq 
/etc/ceph/ceph.conf
```
rbd_readahead2 = true
```

```
kill -9 tgtd
```

#### network
```
manager 182.200.65.111/16
public  192.169.65.112/24
cluster 172.17.65.111/24
```

#### rados df
[root@node0]# rados -p blkpool0 df
POOL_NAME USED OBJECTS CLONES COPIES MISSING_ON_PRIMARY UNFOUND DEGRADED RD_OPS RD WR_OPS WR SIZE_ACCURACY
blkpool0     0       0      0      0                  0       0        0      0  0      0  0             0

total_objects    269
total_used       27053M
total_avail      16730G
total_space      16756G
```


#### disable HA
```
vim /opt/h3c/lib/python2.7/site-packages/onestor/plat/cm/cluster/cluster_util.py +426
```

#### log level
```
debug_engine = 4
debug_dse = 4
```
#### lsm 
```
ceph daemon dse.node64 engine all dcache lsm plus_on
```


#### op_cancel_dse engine_timeout
```
3159819 60 ERROR row init failed to open db, r = -5
3159819 51 ERROR row init failed to open db, r = -5
```

#### ha
```
$ vim /etc/onestor/onestor.conf
handy_ha_needed = no
```
```
supervisorctl restart all
```

#### dse/dcache pools
```
data: pool_a -> dcache.pool_a(dcache_log_pool for pool_a) + .pool_a.dse (pool for ROW)
meta: .diskpool8.rbd-> dcache..diskpool8.rbd + ..diskpool8.rbd.dse
```

#### instance_id
```
instance_id = poolid << 16 + engineid
```

#### ENV
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
