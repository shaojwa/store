#### 业务模型
io： 写业务，小IO，IOPS 5800，带宽：88M，IO是15.5K左右。

#### 出问题时间
7月26，1点左右。

#### 恢复时间
7月26，

#### 满数据提示：
```
"event": "waiting for cache not full
```
#### 日志
```
2022-07-25 16:09:05.581579 7f5e323f0700 1455417 23 DEBUG
osd.136 pg_epoch: 2545 pg[3.192( v 2545'8598735 (2545'8595669,2545'8598735]
local-lis/les=2259/2260 n=4419927 ec=504/504 lis/c 2259/2259 les/c/f 2260/2260/0 1944/2259/2259)
bb 1939'7114825 [136,134,135] r=0 lpr=2259 crt=2545'8598735 lcod 2545'8598734 mlcod 2545'8598734
active+clean snaptrimq=[]] agent_choose_mode flush_mode: idle_has_whiteout evict_mode: idle promote_mode: idle
num_objects: 4419927 num_bytes: 2832458837 num_copy_ops: 0 num_objects_dirty: 19842
num_dirty_whiteouts: 1065 num_objects_omap: 0 num_dirty: 19842 num_user_objects: 4419922 
num_user_bytes: 4188869456 num_overhead_bytes: 1325976600
pool.info.target_max_bytes: 3039763103744 pool.info.target_max_objects: 0 divisor: 512 cap_ratio: 1000000
num_bytes_for_accuracy: 2862893294 delta size :-30434457  
```
