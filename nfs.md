#### 从nfs-client 找到对应的 nfs-server
查看nfs-client的挂载信息：
```
$ mount
```
注意版本`vers=4.1`以及`addr=172.6.28.12`字段，然后通过addr找到对应的id
```
$ ctdb ip
Public IPs on node1
172.6.28.10 0
172.6.28.11 1
172.6.28.12 2
```
我们知道，挂载的客户端上的addr对应的ctdb pnn是2，然后运行`ctdb status`找到对应的server-ip
```
$ ctdb status
Number of node:3
pnn:0 172.6.28.244  OK
pnn:1 172.6.28.245  OK (THIS NODE)
pnn:2 172.6.28.246  OK 
Generation:1648927996
Size: 3
hash:0 lmaster:0
hash:1 lmaster:1
hash:2 lmaster:2
Recovery mode:NORMAL (0)
Recovery master:1
```

#### install from iso
1. mount iso
```
mount -t iso9660 CentOS.iso /mnt/cdrom 
```

2. edit /etc/yum.repos.d/CentOS-Base.repo the \[base\] part
```
  [base]
  name=CentOS-$releasever - Base
  baseurl=file:///mnt/cdrom
  gpgcheck=1
  gpgkey=file:///mnt/cdrom/RPM-GPG-KEY-CentOS-7
```

3. disable others:
```
enabled=0
```

4. check current repos:
```
yum repolist
```

#### cluster not support
```
yum install nfs-utils
```

#### show shared on nfs-server
```
cat /etc/ganesha/ganesha.conf
```

#### show mount in nfs-client
```
# showmount -e 192.9.10.100
Export list for 192.9.10.100:
/data/nfs0 *
```

#### mount
```
# 92.9.10.100 is dynamic ip 
mount -t nfs 192.9.10.100:/data/nfs0 /mnt/wsh/nfs0
```
