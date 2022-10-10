目前一个节点上的processer是固定的，32个，每个engine是4个。
```
"modules":{"dse":"0","csd":"1-32" 
"processer_allocation": "{"dse":1,"csd":4, 
```
看起来，和当前节点上engine的数量为8有关系，其实是没有关系，但是当前节点上的CSD实例数量是2。


#### CSD的数量关系
CSD 的数量只和节点的盘有关系：
```
混闪/SSD+NVME，数据盘一个OSD，缓存盘上两个CSD
全闪，每个数据盘一个OSD，两个CSD
```
