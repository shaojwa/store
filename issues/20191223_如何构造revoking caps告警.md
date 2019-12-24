## 环境

* 集群环境：存储前后端合一 172.16.84.0/24：
* 部署文件系统
* 部署nas组，至少两个nas节点，nas业务ip192.168.84.10。

## 步骤：

* 在 /NAS/CAPFS/data 下创建wsh目录 后dump inode查看

```
filelock: excl
"client_caps": [
            {
                "client_id": 4659005,
                "pending": "pAsLsXsFsx",
                "issued": "pAsLsXsFsx",
                "wanted": "AsLsXsFsx",
                "last_sent": 2
            }
        ]
```

* 在 node2节点上，/NAS/CAPFS/data/wsh 下创建文件 ddfile 并dump inode

写完之后filelock是sync，client_caps是 pAsLsXsFsc， loner 模式
写的过程中，authlock，filelock，xattrlock 都是excl，caps是 pAsxLsXsxFsxcrwb。

* 在写的过程中在node3节点ls一下。

马上能看到，几乎没有延时。ls的客户端的权限只需要pLs

* 在node2的存储前端网上阻断特定的ip

在主mds节点上找到监听的端口 6856

````
[root@node12 ceph]# netstat -ltnp | grep ceph-mds
tcp        0      0 172.16.84.12:6856       0.0.0.0:*               LISTEN      3481339/ceph-mds
````
 
 然后用6556这个端口匹配内核客户端的链接，最后一列为"-"应该就是内核客户端的链接：
 
```
[root@node12 ceph]# netstat -tnp | grep 6856 | grep " - "
tcp        0      0 172.16.84.12:33856      172.16.84.12:6856       ESTABLISHED -
```

通过配置iptables规则来阻断报文：

```
iptables -I INTPUT -p tcp --dport 33856 -j DROP
iptables -I OUTPUT -p tcp --sport 33856 -j DROP
```
## 在node3上尝试写入

此时node3上的内核客户端需要写权限，mds应该会给node2发送revoking caps消息，但node2没有响应。

## 观察mds的日志
