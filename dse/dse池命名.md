块存储在硬盘池diskpool0中创建一个块池 blockpool0，那么就会有两个池：
```
blockpool0
diskpool0.rbd
```
然后基于这两个池，就会有另外四个池，每个池衍生出两个：
```
dcache.<pool_name>
<pool_name>.dse
```
例如
```
dcache.blockpool0
blockpool0.dse
```
