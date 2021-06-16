
#### ERROR: Product is already installed in t hsi environment, Please uninstall the old version and try again!
1. `install.sh`脚本中有`_check_install_record()`接口检查UniStor的安装情况。
2. `_check_install_record()`接口的调用`get_install_record()`，而`get_install_record()`的定义在`unistor_utils.sh`中。
3. 这个接口会检查PACKAGES_INFO_FILE文件，这个文件路径是：`/opt/hccc/packages.inbfo`。
4. 但是直接清空这个文件，或者删除其中的某一行记录没什么用。正常的恢复环境应该执行脚本:`bash install.sh --restore-env`。

#### 主机"182.200.21.74/182.200.21.75" 软件安装失败
在`/var/log/shell_util`下查看相关日志：
```
install_soft.log
```
显示`install module succeed`, 没发现什么异常, 然后查看`package.log`,似乎也没发现什么异常。

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
```
[root@node0]# rados -p blkpool0 df
POOL_NAME USED OBJECTS CLONES COPIES MISSING_ON_PRIMARY UNFOUND DEGRADED RD_OPS RD WR_OPS WR SIZE_ACCURACY
blkpool0     0       0      0      0                  0       0        0      0  0      0  0             0

total_objects    269
total_used       27053M
total_avail      16730G
total_space      16756G
```

#### do NOT check nic
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

#### disable HA
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
