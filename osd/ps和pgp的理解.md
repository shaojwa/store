#### PG和PGP的全称
PG = Placement Group，PGP = PGP = Placement Group for Placement purpose

#### 什么是PGP
pgp就是一个osd的组合，在osd分布确定的情况下，pgp的数量是有限的。而pg其实就是一个poolid.hash，其实没有直接和osd对应，而是pg会关联一个pgp。

#### 为什么需要PGP
一个pool中，可能有很多pg，但是pgp并不一定那么多，这是增加有一层逻辑划分。
