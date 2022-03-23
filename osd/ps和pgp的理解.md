#### PG和PGP的全称是什么
PG = Placement Group，PGP = PGP = Placement Group for Placement purpose

#### 什么是PGP
pgp就是一个osd的组合，在osd分布确定的情况下，pgp的数量是有限的。

#### 什么是PG
pg其实就是一个集合（poolid.hash），并没有直接和osd对应，和osd关联的是PGP。

#### 为什么需要PGP
举个例子，假如说有1024个PG，和一个PGP，那么你会发现所有PG都映射到相同的OSD集合。
一个pool中，pg是可能会涨的，涨到一定程度，每个PG都会拆分成两个pg，这两个pg 的PGP和原来的不变。
但是，如果有osd变化，那么PGP就会发生变化，此时PG的PGP就会发生变化，这样数据就会发生迁移，所以PGP很重要。
