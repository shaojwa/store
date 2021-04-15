#### �handy�亥砭���憬靽⊥ 
```
/opt/h3c/lib/python2.7/site-packages/onestor/cs/hostmanager.py +3533 撠?if is_ceph_ok �寞�  if 0嚗?�leader�?```

#### �函蔡憿箏�瘚��?
/etc/ceph/ceph.conf�辣
```
rbd_readahead2 = true
```
�冽摮��扯�
```
kill -9 tgtd
```

#### 瘚��黎蝵��蔭
```
蝞∠�蝵? 182.200.65.111/16
�挾蝵? 172.17.65.111/24
摮蝵? 192.169.65.112/24
```

#### �唳���?```
[root@node0]# rados -p blkpool0 df
POOL_NAME USED OBJECTS CLONES COPIES MISSING_ON_PRIMARY UNFOUND DEGRADED RD_OPS RD WR_OPS WR SIZE_ACCURACY
blkpool0     0       0      0      0                  0       0        0      0  0      0  0             0

total_objects    269
total_used       27053M
total_avail      16730G
total_space      16756G
```

#### rcache銝剖笆鞊∠�evcit
destage銝摰�銋�嚗���璅∪��row銋�嚗隡��禿cche�笆鞊〔vict��嚗�摨行撖寡情嚗�瘜evict�典��唳�?
#### 摮�垢蝵挾銝銝DMA�∩�IP��畾?```
vim /opt/h3c/lib/python2.7/site-packages/onestor/plat/cm/cluster/cluster_util.py +426
```

#### �亙�蝑漣
```
debug_engine = 4
debug_dse = 4
```
#### �亙�銝�湔扳�瘚?���瘚��亙��Ｗ��詨�其�����其�IO銋�嚗��亙�銝�湔扳�瘚��賣�撘嚗?```
ceph daemon dse.node64 engine all dcache lsm plus_on
```

#### engine-id 銝剔� pool-id
�舐頂蝏葉��瘙�id嚗�銝芸���撖孵�銝銝泥se瘙�銝銝泥cache瘙?dcache瘙�亙��典����敹?dse瘙�亙��沖OW撖寡情���唳�?
#### op_cancel_dse engine_timeout

�牠ngine�敹葉隡�躬failed to open db` 霂湔�摨��唳瘛瑚僚嚗�銝泥se����銝河ngine �?rocksdb嚗�閬��啣�撱歉ool�?```
3159819 60 ERROR row init failed to open db, r = -5
3159819 51 ERROR row init failed to open db, r = -5
```
閬��啗�銝芷憸��臭誑��dse銝剜�瘝⊥�憒��敹try_boot wait for`


#### �券��唳霂餃�
1. ���唳霂餃�嚗隡�隞Cache霂鳴�DCache憒�瘝⊥�嚗停隞OW霂颯?1. ����閬����湔蝏pproc銝�憸�op嚗pproc霂餃��唳���充OW�?
#### 憸��圻�?```
blk撘�舫◇摨�霂�寞找���隡蜓�典憸�嚗�僕銝支辣鈭�1嚗��充cache嚗?嚗��充OW
```

#### 瘥�蝘′���賣�銝蝘��?��餈�辣嚗��臬笆鞊～?
#### ���函�蝖祉�瘙?瘥葵���函′��銝�憭�賢�撱箔�銝況ool�?
#### ����祉��?�?�舀

### ���舐�孵�
install摰roduct�券蝵脣�嚗耨�?
```
# /etc/onestor/onestor.conf
handy_ha_needed = no
```
撠勗隞乩��券�蝵害handyha`嚗�鈭銵supervisorctl restart all`

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
