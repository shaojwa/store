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

说明
ifile： lock type name
sync->mix: lock state name 
g= 1: gather set
l= ：number of client lease
r= ：number of rdlocks
w= : number of wrlocks
x= ：number of xlocks
by=： xlock by


inest mix flushed
flushed：scatter 锁的状态标记。

state_flags有：
SCATTER_WANTED
UNSCATTER_WANTED
DIRTY
FLUSHING
FLUSHED
REJOIN_MIX

```

## SimpleLock

```
  int get_rdlock() { 
    if (!num_rdlock)
      // 标记这个Object是被什么引用而PIN住。
      parent->get(MDSCacheObject::PIN_LOCK);
    return ++num_rdlock; 
  }

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

// 副本的状态，lock都会对应一个object，这个object的其他副本所处的状态，这里和object的权威非权威看起来没什么关系。
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


## rdlock/wrlock 到底是什么意思

首先，对个inode的元数据所有权是分读，写，互斥等状态的。如果你需要修改一个元数据，那至少得用wr的权限，为了得到这个权限对应的就是你得得到这个锁，就是wrlock。
从 get_rdlock和get_wrlock看，开始部分的代码都非常简单，就是应用计数增加，另外设置PIN_LOCK，好像没什么特殊。
这是因为当前的状态能让你顺利拿到锁，那是没什么问题的，比如MIX状态的时候，wrlock锁谁都可以拿到。
类比本地锁，就是当前的锁是没有被锁住的，谁都可以获取。但是如果当前自己的锁状态无法顺利拿到wrlock的时候，就需要主动去获取。
当你获取到一个锁时，你会改变其他副本中的锁状态，其他副本获取锁也一样会改变你的锁状态，所以你只需要看看自己的状态就知道能否获取到需要的锁。
分布式锁的意思就是这样，锁不只有一把，每个副本对象都有一把锁，但是同一个对象的不同副本上的锁需要一同遵守一个规则，就是状态机。

在主动去获取锁的过程中，都会先把自己的锁设置到一个中间状态。
比如simple_lock的流程中，如果当前不满足，那么就需要充当前的四个稳态中进行迁移：

```
LOCK_SYNC -> LOCK_SYNC_LOCK
LOCK_XSYN -> LOCK_EXCL_LOCK
LOCK_MIX -> LOCK_MIX_LOCK
LOCK_TSYN -> LOCK_TSYN_LOCK
```

很显然，这四种中间锁的下一个状态都是LOCK这个稳态，也就是获取到了锁，什么时候设置成LOCK？在eval_gather中。
先获取当前锁的下一个状态：

```
lock->set_state(next);
``` 

并在下半副本设置,当然少数状态下，这个next是会修正的，比如：

    当前状态如果是：LOCK_MIX_SYNC，next就会修正为： LOCK_MIX_SYNC2
    当前状态如果是：LOCK_SYNC_MIX，next就会修正为： LOCK_SYNC_MIX2

从状态机里就可以看到，LOCK_MIX_SYNC的next一定是LOCK_MIX_SYNC2，LOCK_SYNC_MIX的next也一定是LOCK_SYNC_MIX2，但是LOCK_MIX_LOCK不一样，LOCK_SYNC_MIX的next是LOCK_MIX,所以它不会被设置成LOCK_MIX_LOCK2。


#### simple_lock

simple_lock() 接口的目的就是当自己的锁达到lock状态，简单就是得到锁，并不一定独占。
所以，它专门处理的稳态是：

    LOCK_SYNC
    LOCK_XSYN
    LOCK_EXCL
    LOCK_MIX
    LOCK_TSYN

对应的重中间态就是：

    LOCK_SYNC_LOCK
    LOCK_EXCL_LOCK
    LOCK_EXCL_LOCK
    LOCK_MIX_LOCK
    LOCK_TSYN_LOCK

#### simple_xlock()

simple_xlock接口的目的就是让自己的锁达到xlock的状态，就是独占锁。

    LOCK_LOCK
    LOCK_SYNC
    LOCK_XSYN
对应的重中间态就是：

    LOCK_LOCK_EXCL
    LOCK_SYNC_EXCL
    LOCK_XSYN_EXCL

#### 状态机的含义

以simplelock状态机的初浅分析

```
SYNC: 就可以简单认为是一种初始状态，或者说未获取锁的状态，或者在分布式中就是谁都可以获取锁的状态。
LOCK:
MIX：
```

#### 锁触发在权威节点上

我们观察下面几个函数发现，这些函数都不必须在object的权威节点上执行。

    simple_eval()
    simple_excl()
    simple_lock()
    simple_xlock()
    simple_sync()

#### 如果是非权威节点受限要发起锁的获取该怎么处理？

待分析
