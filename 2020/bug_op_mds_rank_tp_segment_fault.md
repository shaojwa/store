```
2020-05-07 09:31:21.318598 7f03923fb700 4065150 60  INFO mds.0.server op-merge, got 1 dentries
2020-05-07 09:31:21.318600 7f03923fb700 4065150 60  INFO mds.0.server op-merge, begin the dentries-loop
2020-05-07 09:31:21.318605 7f03923fb700 4065150 60  INFO mds.0.server op-merge, req->filepath #0x1/ auto_commit=0
2020-05-07 09:31:21.318713 7f03923fb700 4065150 60  INFO mds.0.server op-merge, file exists, continue
2020-05-07 09:31:21.318714 7f03923fb700 4065150 60  INFO mds.0.server op-merge, end of dentries-loop
2020-05-07 09:31:21.318718 7f03923fb700 4065150 60  INFO mds.0.server op-merge, check mdcache 0x7f03990a1000
2020-05-07 09:31:21.318719 7f03923fb700 4065150 60  INFO mds.0.server op-merge, set layout
2020-05-07 09:31:21.318721 7f03923fb700 4065150 60  INFO mds.0.server op-merge, auto-balancing
2020-05-07 09:31:21.318721 7f03923fb700 4065150 60  INFO mds.0.server op-merge, fill special params.
2020-05-07 09:31:21.318733 7f03923fb700 4065150 60  INFO mds.0.server op-merge, get inode.
2020-05-07 09:31:21.320823 7f03923fb700 4065150 60 ERROR *** Caught signal (Segmentation fault) **
 in thread 7f03923fb700 thread_name:tp_mds_rank_tp

 ceph version 12.2.1-NAS_V100R002B05D006SP (070e2e96888b38445d09868d143d5bd38198bd8b) luminous (stable)
 1: (()+0x7099a0) [0x55b12f4789a0]
 2: (()+0xf6d0) [0x7f03a53d76d0]
 3: (Server::handle_client_createv(boost::intrusive_ptr<MDRequestImpl>&)+0x206d) [0x55b12f1745ed]
 4: (Server::dispatch_client_request(boost::intrusive_ptr<MDRequestImpl>&)+0x10c0) [0x55b12f18a8d0]
 5: (Server::sharded_dispatch(Message*)+0xcc) [0x55b12f18ac3c]
 6: (MDSRank::handle_sharded_message(Message*, unsigned int)+0x2e7) [0x55b12f08f387]
 7: (MDSRank::ShardedReqWQ::_process(unsigned int, ceph::heartbeat_handle_d*)+0xc2) [0x55b12f0a5532]
 8: (ShardedThreadPool::shardedthreadpool_worker(unsigned int)+0x754) [0x55b12f4c8a14]
 9: (ShardedThreadPool::WorkThreadSharded::entry()+0x10) [0x55b12f4cab80]
 10: (()+0x7e25) [0x7f03a53cfe25]
 11: (clone()+0x6d) [0x7f03a46c3bad]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
```
