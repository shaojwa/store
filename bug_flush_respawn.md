#### 因为刷日志导致MDS重启

mds日志：

      2019-09-06 10:02:08.382178 7f6863576700 370386 8  INFO mds.mds0 asok_command: flush journal (starting...)     
      2019-09-06 10:03:42.095377 7f68627ff700 370387 7  INFO mds.mds0 map removed me (mds.-1 gid:1001340) from cluster due to lost contact; respawning      
      2019-09-06 10:03:42.095385 7f68627ff700 370387 7  INFO mds.mds0 respawn
      2019-09-06 10:03:42.095388 7f68627ff700 370387 7 WARNING mds.mds0 debug timeout, dump log to get more info

#### 找到MON认为MDS超时的日志

先确定MON的版本，通过ceph mon dump 看到当前的版本为epoch2，比较第1期和第2期的monmap 发现没有区别（ceph mon dump 1 查找）
根据MDS respawn的时间为10:03:42.095385，我们在一个MON节点上（peon-MON）看到了mds map的变化：

在10:00:19分的mds map：

      2019-09-06 10:00:19.414396 7f8c9c3fb700 316672 4 WARNING mon.zd3@1(peon).mds e186 print_map
      created 2019-09-05 09:32:05.071527
      modified        2019-09-05 09:32:05.071527
      1001340:        17.17.18.4:6813/397306611 'mds0' mds.0.174 up:active seq 11775
      2146445:        17.17.18.7:6800/460191098 'mds2' mds.1.185 up:active seq 504
      
在10:03:46分的187期的 mds map中已经不包括mds0。
