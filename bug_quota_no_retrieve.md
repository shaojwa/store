#### 断开NAS节点和MDS的连接网络后发现配额多算

* 问题分析

（1）	比较正常场景和断网卡场景，发现断网卡场景下配额多算59M

（2）	client1的写入操作出现过网卡中断，而client2写入过程中没有中断，所以对比两者日志发现是否有明显区别。

注意到，client1写入的4个文件中有3个文件最后的old_max大于10G，但有配额回退。而client2写入的4个文件没有这个现象。

（3）分析针对client1和client2的日志

client1的日志：

```
#/data/nfs/abcd/1/vdb.1_1.dir/vdb_f0001.file
size 10727981056 -> 10737418240
max_size 10744758272 -> 0 
_do_cap_update  old_max 10744758272  new_max 10737418240 _bytes:-7340032
回退7M

#/data/nfs/abcd/1/vdb.1_2.dir/vdb_f0001.file
size 10732175360 -> 10737418240 
max_size 10748952576 -> 0 
_do_cap_update old_max 10748952576 new_max 10737418240  _bytes:-11534336
回退11M

#/data/nfs/abcd/1/vdb.1_3.dir/vdb_f0001.file
size 10736001024 -> 10737418240
max_size 10737418240 -> 0 
没有回退，max_size 等于10G

#/data/nfs/abcd/1/vdb.1_4.dir/vdb_f0001.file
size 10723786752 -> 10737418240
max_size 10757341184 -> 0 
_do_cap_update old_max 10757341184 new_max 10737418240  _bytes:-19922944
回退19M
```

client2的日志：

```
#/data/nfs/abcd/2/vdb.1_1.dir/vdb_f0001.file
size 10729029632 -> 10737418240
max_size 10737418240 -> 0 

#/data/nfs/abcd/2/vdb.1_2.dir/vdb_f0001.file
size 10729029632 -> 10737418240
max_size 10737418240 -> 0 

#/data/nfs/abcd/2/vdb.1_3.dir/vdb_f0001.file
size 10736369664 -> 10737418240
max_size 10737418240 -> 0 

#/data/nfs/abcd/2/vdb.1_4.dir/vdb_f0001.file
size 10720641024 -> 10737418240
max_size 10737418240 -> 0 
```

（4）	观察client1的写入，从max_size看，三个多分配的客户端总共多分配（7+11+19=37M），但最后通过 _do_cap_update 回收，所以原因不再这里。

（5）	考虑到配额分配更新的接口是calc_new_quota_size()，所以从日志中分析该操作，
了解到日志中的old_max是原先分配的配额大小，每次bytes 为33554432字节（32M）。
正常情况下，下一条的old_max等于上一条日志old_max + 32M，通过观察client2的日志确认了这一点。
所以初步估计重新观察client1的日志中和calc_new_quota_size有关的操作可能有线索。

（6）	考虑到网络异常对配额计算的影响，重点关注断网卡期间，每个文件old_max大小的变化，发现：

```
#/data/nfs/abcd/1/vdb.1_1.dir/vdb_f0001.file
old_max 2617245696
----此时因为网络异常中断----
old_max 2624585728
中断前后相差7M

#/data/nfs/abcd/1/vdb.1_2.dir/vdb_f0001.file
old_max 2583691264
----此时因为网络异常中断----
old_max 2595225600
中断前后相差11M

#/data/nfs/abcd/1/vdb.1_3.dir/vdb_f0001.file
old_max 2583691264
----此时因为网络异常中断----
old_max 2617245696
中断前后相差32M（等同网络没有异常）

#/data/nfs/abcd/1/vdb.1_4.dir/vdb_f0001.file
old_max 2550136832
----此时因为网络异常中断----
old_max 2570059776
中断前后相差19M
```

（7）	对比数据发现old_max的差值无法和多计算的59M对应上，但是考虑到第3个文件相差32M的情况，联想到配额的增长方式：
比较\[old_max1, old_max1+32M\]和\[old_max2, old_max2+32M\]，如果old_max2  < old_max1 + 32M，那么两者的差值就是多计算的部分，如果这部分没有回收就会导致问题。
所以（32M-7M）+ (32M-11M) + (32M-19M) 应该等于多算的部分，和实际相符。

（8）	同时通过比较calc_new_quota_size()调用次数发现，4个文件分别调用321,321，320,321次（10G文件，正常调用320次，每次32M）
所以有三个文件，每个多分配32M的，而最后通过_do_cap_update回收的只是网络恢复之后预分配超出的部分（此时old_max已经不是32M的整数倍，但每次配额增加还是32M）

（9）	通过第6步中的old_max发现，异常之后的old_max不是32M的整数倍，观察日志发现中断后的old_max就是会话恢复时的文件size，比如：
在 /data/nfs/abcd/1/vdb.1_4.dir/vdb_f0001.file文件日志中有：

    RecoveryQueue::_recovered _recovered r=0 size=2570059776 （和网络恢复之后的第一个old_max相同）

（10）	在基本确定是在session超时没回收预分配配额之后，进一步查看未回收的原因，通过查看代码知道，要进行回收，需要调用remove_client_cap()接口中如下流程：如果进行回收，会打印 hold the write caps日志，而实际上没有，进一步确认是配额没有回收。

（11）	没有回收原因看起来和没有WRITE权限有关系

（12）	找到附近代码，观察inode中client是否有相关cap：

将日志调到20后，复现问题，观察in中的权限：

```
2019-08-01 00:15:33.488793 7fb71eff9700 DEBUG mds.0.server  killing capability mds_int_caps 1 on 
[inode 0x100003a996a [2,head] /data/nfs/abcd/1/vdb.1_1.dir/vdb_f0001.file auth v466 dirtyparent s=1758461952 n(v0 b1758461952 1+0) (iversion lock) cr={835615=0- 
1778384896@1} 
caps={client:835615/ pending: mds_int_caps 1 / issued: mds_int_caps 1 / wanted: mds_int_caps 16333 / last_send: mds_int_caps 56} | ptrwaiter=0 request=0 lock=0 
caps=1 dirtyparent=1 dirty=1 authpin=0 0x7fb2aea29200]
```

可以看到，只有issued的cap值为1，即只有pin cap，没有write cap

（13）	进一步观察原日志，找出是什么时候将cap清掉的：

```
2019-07-31 17:16:37.348172 7fb7263fe700 DEBUG mds.0.locker  revoking mds_int_caps 16349 on [inode 0x100003a995d [2,head]         
/data/nfs/abcd/1/vdb.1_1.dir/vdb_f0001.file auth v604 dirtyparent s=2617245696 n(v0 b2617245696 1+0) (iauth excl) (ifile excl) (ixattr excl) (iversion lock) cr=    
{835615=0-2650800128@1} caps={client:835615/ pending: mds_int_caps 16349 / issued: mds_int_caps 16349 / wanted: mds_int_caps 16333 / last_send: mds_int_caps 
81},l=835615 | ptrwaiter=0 request=0 lock=0 caps=1 dirtyparent=1 dirty=1 authpin=0 0x7fb2ae8fc800]
2019-07-31 17:16:37.348184 7fb7263fe700 DEBUG mds.0.locker eval 2496 [inode 0x100003a995d [2,head] /data/nfs/abcd/1/vdb.1_1.dir/vdb_f0001.file auth v604 
needsrecover dirtyparent s=2617245696 n(v0 b2617245696 1+0) (iauth excl) (ifile excl) (ixattr excl) (iversion lock) cr={835615=0-2650800128@1} caps= 
{client:835615/ pending: mds_int_caps 1 / issued: mds_int_caps 1 / wanted: mds_int_caps 16333 / last_send: mds_int_caps 82},l=835615(-1) | ptrwaiter=0 request=0 
lock=0 caps=1 dirtyparent=1 dirty=1 authpin=0 0x7fb2ae8fc800]
```

（14）	根据日志找到对应的接口

（15）	最终为在find_idle_sessions中调用revoke_stale_caps, 对应日志:

（16）	所以，网络异常导致session 60秒超时，随后清空cap，之后在会话结束时没有触发配额回收，最终配额多算。


#### cap回收

    // tick to find stale session
    MDSRankDispatcher::tick()
        Server::find_idle_sessions()
            mds->locker->revoke_stale_caps(session);
                revoke_stale_caps(cap); # revoking mds_int_caps 853 (the caps of 853 is pAsLsXsFsx)

* 会话超时时间是60秒（mds_session_timeout）

    // remove client caps
    C_MDS_session_finish::finish()
        Server::_session_logged()
            mds->locker->remove_client_cap
