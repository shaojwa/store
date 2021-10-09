## What is consensus
collins-dict says 'a consensus is general agreement among a group of people.'

## What is consensus problem
一般叫做共识问题，Consensus problem is a critical and fundamental problem in distributed system.

## Paxos算法
这是解决共识问题（consensus problem）的通用算法。

## Atomic Commitment Protocal
原子提交协议，这个和是否为分布式没有关系。

## 分布式的 ACP
分布式的原子提交问题，要求分布式系统中的所有节点，都对commit还是abort这个事情达成一致。注意，是所有节点。

## uniform consensus
一种新的一致性问题，就是上面说的分布式的ACP（原子提交问题），不同于consensus problem，它要求所有的节点都达成一致，包括故障的节点。

## Paxos和2PC/3PC 算法的区别
