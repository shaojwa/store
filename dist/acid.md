**从ACID开始说起**

## 什么是数据库事务
事务，在数据库中，英文原文是transaction，那什么是transaction？wikipedia说的很好：
>  In the context of databases, a sequence of database operations that satisfies the ACID properties 
>  (which can be perceived as a single logical operation on the data) is called a transaction. 

翻译下就是，事务是一串操作，只要这一连串操作满足ACID，那么这一连串操作就认为是一个事务，即满足ACID的多个操作可以称为事务。
据说，在有事务这个范式(paradigm)之前，就已经有了ACD的说法，但直到需要定义transaction的时候，才加入Isolation，组成事务的4个属性。

## 什么是事务的ACID
ACID到底是事务的什么，是规范，还是特征，wikipedia说是属性(property)，那么什么是属性？属性就是一定会满足的特征。
我先分析另外三个：

A，Atomicity，原子性。我一个操作是更新一个表中满足条件的所有行，这个操作要么把这个表中的所有行更新，要么返回失败，一行都没有更新。这就是原子性，不能说更新了一部分，此时不管说成功，还是失败，都多出一个状态，这就不是原子的。所以在我看来，原子性就是数据状态的固定。一个操作，触发的数据状态改变是固定的，不能出现其他状态。


I，Isolation，是隔离性，根据wikipedia的说法，因为有了事务，但是事务可能并发(multiple transactions reading and writing to a table at the same time)。
对事务来说，你要么不做，要么全做，从流程上来说是没问题的。但是数据层面也要保证正确，不然结果是不能做到状态可控的，所以，隔离性就是从数据角度来提出要求。
保证的标准是什么，或者说Isolation到底是达到的目的是什么，目的就是，多个事务开始的时间有先后顺序，此时，实现上可以并发，但是最终的结果是确定的，就是相当于把
这些操作按照开始的先后顺序依次执行得到的结果是一样的。这就是隔离性：你可以并发，但是结果是确定的。

D，Durability，collins上说是 lasts a long time without breaking or becoming weaker.我们翻译成持久性。
根据wikipedia的说法，持久性承诺，只要一个事务被提交，就算是系统宕机，这个事务也一定会提交。这话什么意思？
其实就是只要一个事务完成，那么这个事件就会被记录在非易失性介质中。
(This usually means that completed transactions (or their effects) are recorded in non-volatile memory.)

## 为什么需要C

Consistency是一个非常通用的术语，只是要求数据必须满足所有的可用性规则。比如一个表要求A列中的值加上B列中的值和为100，A+B=100。所有的验证规格都需要check来保证或数据一致性。在提交(commit)之前，这些校验都要通过。从这里看，C似乎并不是要求，只要AID满足，C似乎自然就满足？真的这样么？

## Failures

我们了解下几个不满足的情况：
wikipedia上有个例子来进一步说明会ACID属性，假设一张数据库表有两列A和B，一个完整性约数要求，
同一行中A列的值和B列中的值加起来必须为100。而下面的这个SQL语句创建了上面说的一张表。
```
CREATE TABLE acidtest (A INTEGER, B INTEGER, CHECK (A + B = 100));
```

#### Isolation failure
为了示范隔离性Failure，我们假设两个事物同时进执行，每个事务视图修改同样的数据，两个中的一个必须要等待另一个完成，才能保持隔离性。假设T1是从A转10到B，而T2是从B是转20到A。那么有四个步骤：
```
1. T1 从A中减去10
2. T1 在B上加10
3. T2 在B中减去20
4. T2 在A上加20
```
如果按顺序执行，那么隔离性能得到维持，但是T2必须得等待。
如果T1半路失败，那么数据库可以撤销T1的作用，此时T2看到的是可用的数据。
如何把两个事务夹杂，那么实际的顺序可能是这样的：
```
1. T1 从A中减去10
2. T2 在B中减去20
3. T2 在A上加20
4. T1 在B上加10
```
如果第四步中T1执行失败，此时T2已经执行完毕，A已经被修改。我们不能把A恢复到T1开始之前的值。
这就是常常说的写写冲突(write-write conflict)，因为两个事务试图写同样的数据段。
在一个典型的系统中，这个问题通常以恢复到最近的一个good state状态，取消T1。
然后从good state重新开始被打断的事务T2。
