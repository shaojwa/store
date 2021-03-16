## 什么是consistency
我们先从这个单词的英文解释开始，用collins字典查，结果是"Consistency is the quality or condition of being consistent"，好像什么都没解释。
我们再查下consistent，解释是，"Someone who is consistent always behaves in the same way"，单单看英文翻译，好像很难看出什么问题。

**从ACID开始说起**

## 什么是数据库事务
事务，在数据库中，英文原文是transaction，那什么是transaction？wikipedia说的很好：
>  In the context of databases, a sequence of database operations that satisfies the ACID properties 
>  (which can be perceived as a single logical operation on the data) is called a transaction. 

翻译下就是，事务是一串操作，只要这一连串操作满足ACID，那么这一连串操作就认为是一个事务，即满足ACID的多个操作可以称为事务。
据说，在有事务这个范式(paradigm)之前，就已经有了ACD的说法，但直到需要定义transaction的时候，才加入Isolation，组成事务的4个属性。

## 什么是事务的ACID
ACID到底是事务的什么，是规范，还是特征，wikipedia说是属性(property)，那么什么是属性？属性就是一定会满足的特征。

我分析另外三个，A，Atomicity，原子性。我一个操作是更新一个表中满足条件的所有行，这个操作要么把这个表中的所有行更新，要么返回失败，一行都没有更新。
这就是原子性，不能说更新了一部分，此时不管说成功，还是失败，都多出一个状态，这就不是原子的。所以在我看来，原子性就是数据状态的固定。
一个操作，触发的数据状态改变是固定的，不能出现其他状态。

I，Isolation，是隔离性，根据wikipedia的说法，因为有了事务，但是事务可能并发(multiple transactions reading and writing to a table at the same time)。
对事务来说，你要么不做，要么全做，从流程上来说是没问题的。但是数据层面也要保证正确，不然结果是不能做到状态可控的，所以，隔离性就是从数据角度来提出要求。
保证的标准是什么，或者说Isolation到底是达到的目的是什么，目的就是，多个事务开始的时间有先后顺序，此时，实现上可以并发，但是最终的结果是确定的，就是相当于把
这些操作按照开始的先后顺序依次执行得到的结果是一样的。这就是隔离性：你可以并发，但是结果是确定的。

D，Durability，collins上说是 lasts a long time without breaking or becoming weaker.我们翻译成持久性。
根据wikipedia的说法，持久性承诺，只要一个事务被提交，就算是系统宕机，这个事务也一定会提交。这话什么意思？
其实就是只要一个事务完成，那么这个事件就会被记录在非易失性介质中。
(This usually means that completed transactions (or their effects) are recorded in non-volatile memory.)

**了解AID之后** 我们重点来说下**C**

## ACID中的一致性 consistency
ACID数据库中的一致性，整理的C就是consistency，数据库事务的一致性到底什么意思，已经有了AID，为什么非要有个C。

