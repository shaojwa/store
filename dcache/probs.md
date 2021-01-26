####  ceph status
```
[root@node0 log]# ceph -s
  cluster:
    id:     5675ff85-220f-4f85-b1ec-fdf03a316c91
    health: HEALTH_WARN
            2 cache pools are missing hit_sets
            Reduced data availability: 335 pgs inactive, 276 pgs peering
            Degraded data redundancy: 1021 pgs unclean, 686 pgs degraded, 685 pgs undersized

  services:
    mon: 3 daemons, quorum node0,node1,node2
    mgr: node0(active), standbys: node1, node2
    osd: 36 osds: 32 up, 32 in

  data:
    pools:   6 pools, 6144 pgs
    objects: 272 objects, 2170 MB
    usage:   21491 MB used, 16335 GB / 16356 GB avail
    pgs:     0.928% pgs unknown
             4.525% pgs not active
             5123 active+clean
             685  active+undersized+degraded
             272  creating+peering
             57   unknown
             4    peering
             2    creating+activating
             1    active+recovering+degraded
```

#### 2 cache pools are missing hit_sets

#### Reduced data availability: 335 pgs inactive, 276 pgs peering

#### Degraded data redundancy: 1021 pgs unclean, 686 pgs degraded, 685 pgs undersized
