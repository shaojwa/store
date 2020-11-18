#### 社区的ceph如何运行起来

#### pull 代码

### build

配置文件在 /root/ceph/build/ceph.conf

```
RGW=0 MON=1 MDS=1 FS=0 ../src/vstart.sh -d -n -X --localhost --memstore --without-dashboard
RGW=0 MON=1 MDS=1 FS=1 ../src/vstart.sh -d -n -X --memstore --without-dashboard
../src/stop.sh
```

####
```
/root/ceph/build/bin/ceph -c /root/ceph/build/ceph.conf fs volume ls
```
