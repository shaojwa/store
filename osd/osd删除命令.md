```
$ ceph osd crush remove osd.19
device 'osd.19' does not appear in the crush map.no need to remove item names 'osd.19' from crush map
$ ceph auth del osd.19
entity osd.19 does not exist 
$ ceph osd rm 19
```
