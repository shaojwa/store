### cluster not support
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
