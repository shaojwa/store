# run fio with job file
just give it the job file(2)
```
$ fio [options] [jobfile] ...
```

# run fio with command line paramters

job file parameter`iodepth=2` is the same as `--iodepth 2 or --iodepth=2` in command line option.

## basic parameters
- **global section** defining shared parameters.
- and one or more **job sections** describing the jobs involved. 

## parmeters in details
- I/O engine
- I/O type
- I/O 

fio --name=vol_base_test --numjobs=1 --ioengine=rbd --rw=write --direct=1 --bs=256K --iodepth=1 --size=1G  --pool=.disk01.rbd -rbdname=vol0  --group_reporting=1

## --name=vol_base_test (Job description)
job name

## --numjobs=1 (Job description)

## --ioengine=rbd
direct access to Ceph RBD via librbd without the need to use the kernel rbd driver.
 
- rados, using librados, direct access to Ceph Reliable Autonomic Distributed Object Store.
- rbd, using librbd, direct access to Ceph Rados Block Devices whitout the need to use the kernel rbd driver. 
 
## --rw=write (I/O Type)
--Type of I/O pattern

## --direct=1 (I/O Type)
Defines the I/O pattern, no buffer.

## --bs=256K (Block Size)
The block size in bytes used for I/O units

## --size=1G (I/O Size)
The total size of file I/O for each thread of this job.

## --iodepth=1 (I/O Depth)
Number of I/O units to keep in flight against the file.

## --pool=.disk01.rbd 
Specifies the name of the Ceph pool containing RBD or RADOS data. disk pool.

## --rdbname
Specifies the name of the RBD.

## --group_reporting
isplay statistics for groups of jobs as a whole instead of for each individual job.


## the kernel rbd driver is placed at
```
/lib/modules/<kernel-version>/kernel/drives/block/rbd.so
```
like kernel-cephfs at
```
/lib/modules/<kernel-version>/kernel/fs/ceph/ceph.ko
```
comparing with the user-space lib at
```
/opt/xxx/lib/librdb.so
/opt/xxx/lib/libcephfs.so
```
and the rados lib at
```
/opt/xxx/lib/librados.so
```
