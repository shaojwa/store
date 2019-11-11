## Lock基础

## 状态机

锁的底层基础是状态机，mds中一共4种：

* sm_simplelock
* sm_scatterlock
* sm_filelock
* sm_locallock

基于状态机，抽象出LockType，锁类型，通用。

基于LockType，有三种具体的锁类型，SimpleLock, LocalLock, ScatterLock, 其中 LocalLock, ScatterLock由 SimpleLock派生。

元数据锁底层类型一共有12中，CEPH_LOCK_INO不算，2中CDentry特有，10种CInode特有，CDir中没有特有的锁。

应该是因为CDir不是和CDentry和CInode同一层的概念，CDir更上层一些，包含CDir 和 CInode。

```
// dentry
CEPH_LOCK_DVERSION-> versionlock_type -> LocalLock

// inode 
CEPH_LOCK_IVERSION -> versionlock_type -> LocalLock
CEPH_LOCK_IAUTH -> authlock_type -> SimpleLock
CEPH_LOCK_ILINK -> linklock_type -> SimpleLock
CEPH_LOCK_IDFT ->  dirfragtreelock_type -> ScatterLock
CEPH_LOCK_IFILE ->  filelock_type -> ScatterLock
CEPH_LOCK_IXATTR ->  xattrlock_type -> SimpleLock
CEPH_LOCK_ISNAP ->  snaplock_type -> SimpleLock
CEPH_LOCK_INEST ->  nestlock_type -> ScatterLock
CEPH_LOCK_IFLOCK -> flocklock_type -> SimpleLock
CEPH_LOCK_IPOLICY -> policylock_type -> SimpleLock
```

用到ScatterLock的只有，CEPH_LOCK_IDFT，CEPH_LOCK_IFILE，CEPH_LOCK_INEST。

但是这三个Scatter中，CEPH_LOCK_IFILE用的状态机是sm_filelock，而其他两个是sm_scatterlock。

所以ScatterLock的锁用的状态机并不一定是sm_catterlock，filelock比较特殊，ScatterLock和状态其中的scatterlock应该有不同的意思。


```
    case CEPH_LOCK_DN:
    case CEPH_LOCK_IAUTH:
    case CEPH_LOCK_ILINK:
    case CEPH_LOCK_IXATTR:
    case CEPH_LOCK_ISNAP:
    case CEPH_LOCK_IFLOCK:
    case CEPH_LOCK_IPOLICY:
      sm = &sm_simplelock;
      break;
    case CEPH_LOCK_IDFT:
    case CEPH_LOCK_INEST:
      sm = &sm_scatterlock;
      break;
    case CEPH_LOCK_IFILE:
      sm = &sm_filelock;
      break;
    case CEPH_LOCK_DVERSION:
    case CEPH_LOCK_IVERSION:
      sm = &sm_locallock;
```

## lock 打印

```
例子：
(ifile sync->mix) 
(ifle mix flushed)

说明
ifile： lock type name
sync->mix: lock state name 
g= 1: gather set
l= ：number of client lease
r= ：number of rdlocks
w= : number of wrlocks
x= ：number of xlocks
by=： xlock by

flushed：_more->state_flags & FLUSHED

```

## lock的状态机

比如 filelock中，如果当前权威状态是MIX，那么副本一定也是MIX：

```
[LOCK_MIX] = { 0, false, LOCK_MIX, ... }
```

其中每个字段的意思是：

```
// 下一个状态，如果当前状态是stable，那么这里就是0。
next;

// 是否处于loner模式，loner是针对client的。
loner;

// 副本的状态，lock都会对应一个object，这个object的权威节点处于某个状态时，副本所处的状态。
// 在simplelock中，除非权威是SYNC此时副本时SYNC，否则副本都是LOCK状态。
replica_state; 

// 谁可以读元数据
// ANY：权威或者副本都可以。AUTH：只有权威。EXCL：权威或者独占的client。 
can_read;
 
// 谁可以读projected里的元数据信息。
// 在simplelock中，只有读占的客户端可以。
// 在scatterlock中，谁都不可以。
// 在filelock中获得EXCL的客户端或者是权威的MDS节点，或者当前砖状态是LOCK_SYNC_MIX谁都可以。
can_read_projected;

// 谁可以获得读锁
// ANY: 谁都可以
// REQ：如果是副本MDS就需要从权威那请求状态改变。
can_rdlock;

// 谁可以获得写锁
// simplelock中，只有EXCL的可以，即要么是权威MDS，要么是某个独占客户端。
// scatterlock中，只有权威MDS，或者LOCK_MIX时，谁都可以。
can_wrlock; 

// 谁可以强制获得写锁
can_force_wrlock;

// 能否给MDS或者client租期
can_lease;

// 能否获得独占锁
can_xlock;

// 权限
caps;
loner_caps;
xlocker_caps;
replica_caps;

```

simplelock状态机的分析：
simplelock中，比如ilink。

```
SYNC:
LOCK:
MIX：
```
