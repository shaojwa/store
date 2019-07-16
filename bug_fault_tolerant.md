#### 第一个对象中有文件的layout和parnet属性。
#### 获取文件的layout信息时往osd发送的请求。

先查看对象所在的主osd

    ceph osd map .capfs.data.datapool0 100000003ea.00000000
  
找到 acting set 为[4, 7, 5], pg 为 2.7b93bfe5  

然后发送查询请求：

    getfattr -n ceph.file.layout file
