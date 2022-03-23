#### yum install from iso
1. mount iso
```
mount -t iso9660 CentOS.iso /mnt/cdrom 
```
2 edit /etc/yum.repos.d/CentOS-Base.repo the \[base\] part
```
  [base]
  name=CentOS-$releasever - Base
  baseurl=file:///mnt/cdrom
  gpgcheck=1
  gpgkey=file:///mnt/cdrom/RPM-GPG-KEY-CentOS-7
```
3.disable others:
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
