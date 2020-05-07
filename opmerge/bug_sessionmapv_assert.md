```
-2> 2020-05-06 19:22:27.932056 7efefafff700 3713701 10 DEBUG mds.0.journal EMetaBlob.replay inotable tablev 32 <= table 32
-1> 2020-05-06 19:22:27.932057 7efefafff700 3713701 10 DEBUG mds.0.journal EMetaBlob.replay sessionmap v 45600 -(1|2) == table 45599 prealloc [] used 0x0
 0> 2020-05-06 19:22:27.933650 7efefafff700 3713701 10 ERROR /home/wsh/git/UniStorOS_V100R001B01_opm/src/mds/journal.cc: In function 'void EMetaBlob::replay
(MDSRank*, LogSegment*, MDSlaveUpdate*)' thread 7efefafff700 time 2020-05-06 19:22:27.932061
/home/wsh/git/UniStorOS_V100R001B01_opm/src/mds/journal.cc: 1893: FAILED assert(sessionmapv == mds->sessionmap.get_version())
```
