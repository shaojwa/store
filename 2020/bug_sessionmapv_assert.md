```
-2> 2020-05-06 19:22:27.932056 7efefafff700 3713701 10 DEBUG mds.0.journal EMetaBlob.replay inotable tablev 32 <= table 32
-1> 2020-05-06 19:22:27.932057 7efefafff700 3713701 10 DEBUG mds.0.journal EMetaBlob.replay sessionmap v 45600 -(1|2) == table 45599 prealloc [] used 0x0
 0> 2020-05-06 19:22:27.933650 7efefafff700 3713701 10 ERROR /home/wsh/git/UniStorOS_V100R001B01_opm/src/mds/journal.cc: In function 'void EMetaBlob::replay
(MDSRank*, LogSegment*, MDSlaveUpdate*)' thread 7efefafff700 time 2020-05-06 19:22:27.932061
/home/wsh/git/UniStorOS_V100R001B01_opm/src/mds/journal.cc: 1893: FAILED assert(sessionmapv == mds->sessionmap.get_version())

 ceph version 12.2.1-NAS_V100R002B05D006SP (070e2e96888b38445d09868d143d5bd38198bd8b) luminous (stable)
 1: (ceph::__ceph_assert_fail(char const*, char const*, int, char const*)+0x110) [0x55be7a0f3220]
 2: (EMetaBlob::replay(MDSRank*, LogSegment*, MDSlaveUpdate*)+0x5873) [0x55be7a08dba3]
 3: (EUpdate::replay(MDSRank*)+0x39) [0x55be7a08ee09]
 4: (MDLog::_replay_thread()+0x4ae) [0x55be7a028dae]
 5: (MDLog::ReplayThread::entry()+0xd) [0x55be79cf7ffd]
 6: (()+0x7e25) [0x7eff1a758e25]
 7: (clone()+0x6d) [0x7eff19a4cbad]
 NOTE: a copy of the executable, or `objdump -rdS <executable>` is needed to interpret this.
```
