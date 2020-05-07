```
Missing separate debuginfos, use: debuginfo-install nss-softokn-3.34.0-2.el7.x86_64 nss-softokn-

freebl-3.34.0-2.el7.x86_64
(gdb) bt
#0  0x00007f6b5c438277 in raise () from /lib64/libc.so.6
#1  0x00007f6b5c439968 in abort () from /lib64/libc.so.6
#2  0x00007f6b4ce515c5 in ceph::__ceph_assert_fail (assertion=assertion@entry=0x7f6b55a37760 

"waiter_mutex == __null || waiter_mutex->is_locked()",
    file=file@entry=0x7f6b55a37720 "/home/wsh/git/UniStorOS_V100R001B01_opm/src/common/Cond.h", 

line=line@entry=126,
    func=func@entry=0x7f6b55a46550 <Cond::Signal()::__PRETTY_FUNCTION__> "int Cond::Signal()")
    at /home/wsh/git/UniStorOS_V100R001B01_opm/src/common/assert.cc:66
#3  0x00007f6b5591cc66 in Cond::Signal (this=0x1a927b0) at 

/home/wsh/git/UniStorOS_V100R001B01_opm/src/common/Cond.h:125
#4  0x00007f6b55932c75 in Signal (this=0x1a927b0) at 

/home/wsh/git/UniStorOS_V100R001B01_opm/src/client/Client.cc:16011
#5  OpmBatcher::delay_op_tick (this=this@entry=0x1a925b0) at 

/home/wsh/git/UniStorOS_V100R001B01_opm/src/client/Client.cc:16005
#6  0x00007f6b55932d9f in OpmBatcher::start_timer (this=this@entry=0x1a925b0) at 

/home/wsh/git/UniStorOS_V100R001B01_opm/src/client/Client.cc:16019
#7  0x00007f6b5597e2c3 in Client::mount (this=0x1a92300, mount_root=..., perms=..., 

require_mds=require_mds@entry=false)
    at /home/wsh/git/UniStorOS_V100R001B01_opm/src/client/Client.cc:7702
#8  0x00007f6b5591f8e8 in mount (perms=..., mount_root=..., this=0x196c4b0) at 

/home/wsh/git/UniStorOS_V100R001B01_opm/src/libcephfs.cc:130
#9  ceph_mount (cmount=0x196c4b0, root=root@entry=0x7f6b55ed0299 <__pyx_k_96> "/") at 

/home/wsh/git/UniStorOS_V100R001B01_opm/src/libcephfs.cc:464
#10 0x00007f6b55cac57e in __pyx_pf_6cephfs_9LibCephFS_28mount (__pyx_v_self=0x7f6b48f3f6d0) at 

cephfs.c:10856
#11 __pyx_pw_6cephfs_9LibCephFS_29mount (__pyx_v_self=0x7f6b48f3f6d0, unused=<optimized out>) at 

cephfs.c:10767
#12 0x00007f6b5d1d8a7c in PyEval_EvalFrameEx () from /lib64/libpython2.7.so.1.0
#13 0x00007f6b5d1db03d in PyEval_EvalCodeEx () from /lib64/libpython2.7.so.1.0
#14 0x00007f6b5d1db142 in PyEval_EvalCode () from /lib64/libpython2.7.so.1.0
#15 0x00007f6b5d1f457f in run_mod () from /lib64/libpython2.7.so.1.0
#16 0x00007f6b5d1f573e in PyRun_FileExFlags () from /lib64/libpython2.7.so.1.0
#17 0x00007f6b5d1f69c9 in PyRun_SimpleFileExFlags () from /lib64/libpython2.7.so.1.0
#18 0x00007f6b5d207b7f in Py_Main () from /lib64/libpython2.7.so.1.0
#19 0x00007f6b5c424445 in __libc_start_main () from /lib64/libc.so.6
#20 0x000000000040066e in _start ()
```
