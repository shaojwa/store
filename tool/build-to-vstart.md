https://github.com/ceph/ceph
#### pull
#### build
```
[root@li984-80 ceph]# ./do_cmake.sh
+ git submodule update --init --recursive
+ test -e build
+ echo 'build dir already exists; rm -rf build and re-run'
build dir already exists; rum -rf build and re-run
+ exit 1
[root@li984-80 ceph]# cd build
[root@li984-80 build]# make
```

#### run
config: /root/ceph/build/ceph.conf
```
RGW=0 MON=1 MDS=1 FS=0 ../src/vstart.sh -d -n -X --localhost --memstore --without-dashboard
RGW=0 MON=1 MDS=1 FS=1 ../src/vstart.sh -d -n -X --memstore --without-dashboard
../src/stop.sh
```

####
```
/root/ceph/build/bin/ceph -c /root/ceph/build/ceph.conf fs volume ls
```
