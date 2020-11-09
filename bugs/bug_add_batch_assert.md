```
#0  0x00007f9379632277 in raise () from /lib64/libc.so.6
#1  0x00007f9379633968 in abort () from /lib64/libc.so.6
#2  0x00007f936bdcb5c5 in ceph::__ceph_assert_fail (assertion=assertion@entry=0x7f93749b7ca8 "_batch_map[dir].count(batch->get_type()) == 0",
    file=file@entry=0x7f93749b4cc0 "/home/wsh/git/UniStorOS_V100R001B01_opm/src/client/Client.cc", line=line@entry=16103,
    func=func@entry=0x7f93749bdf40 <OpmBatcher::add_batch(Inode*, OpmBatchBase*)::__PRETTY_FUNCTION__> "void OpmBatcher::add_batch(Inode*, OpmBatchBase*)")
    at /home/wsh/git/UniStorOS_V100R001B01_opm/src/common/assert.cc:66
#3  0x00007f9374928373 in OpmBatcher::add_batch (this=this@entry=0x7f93699732b0, dir=dir@entry=0x7f935c0db000, batch=batch@entry=0x7f9355c55300)
    at /home/wsh/git/UniStorOS_V100R001B01_opm/src/client/Client.cc:16103
#4  0x00007f937493c7a1 in Client::_create (this=this@entry=0x7f9369973000, dir=dir@entry=0x7f935c0db000, name=name@entry=0x7f92fa0892c0 "vdb_f0004.file", flags=flags@entry=66,
    mode=mode@entry=420, inp=inp@entry=0x7f935c5f84d0, fhp=fhp@entry=0x7f935c5f8600, stripe_unit=stripe_unit@entry=0, stripe_count=stripe_count@entry=0,
    object_size=object_size@entry=0, data_pool=data_pool@entry=0x0, created=created@entry=0x7f935c5f830d, perms=...)
    at /home/wsh/git/UniStorOS_V100R001B01_opm/src/client/Client.cc:15845
```
