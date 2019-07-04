#### 一次 slow request 定位 （20190704）

先查看是哪个mds上报的slow request  
      
    ceph health detail
    
一般都是rank值为0的mds上报。  
然后查看这个mds的日志，查看是哪个client，什么请求导致的slow request。  
查看日志发现是client.21602 de setattr 请求没有得到处理，运行以下命令查看请求。  

    ceph daemon mds.mds1 ops
   
发现存在xlock获取失败，但是最终是已经获取到。
同时查看inode的缓存发现，client.21602是loner, 获取到所有的锁：

    ceph daemon mds.mds1 dump inode 1099617372501

查看有没有正在revoking的caps：

    ceph daemon mds.mds1 dump revoking caps 
    
结果为空，以上步骤确认不是因为cap的问题导致。

回到mds，查看mds和osd之前的请求：

    ceph daemon mds.mds1 objecter_requests
    
发现有请求正在处理，针对的正式我们之前发现的文件的对象：

    "ops": [
        {
            "tid": 386393975,
            "pg": "2.1280927c",
            "actual_pgid": "2.127c",
            "osd": 20,
            "object_id": "100064d8955.00000329",
            "object_locator": "@2",
            "target_object_id": "100064d8955.00000329",
            "target_object_locator": "@2",
            "paused": 0,
            "used_replica": 0,
            "precalc_pgid": 0,
            "target.flags": 32,
            "epoch": "5507",
            "last_force_resend": "0",
            "pg_num": 8192,
            "pg_num_mask": 8191,
            "up_primary": 20,
            "up": "[20,111,169]",
            "acting_primary": 20,
            "acting": "[20,111,169]",
            "size": 3,
            "min_size": 2,
            "recovery_deletes": 1,
            "last_sent": "5.94656e+06s",
            "attempts": 105,
            "snapid": "head",
            "snap_context": "1=[]",
            "mtime": "1970-01-01 08:00:00.000000s",
            "osd_ops": [
                "trimtrunc 4@0"
            ]
        }
    ]

有几个问题需要注意：

* /sys/kernel/debug/ceph/下的mdsc是客户端和mds之前的请求，一般和slow request能对应。
* /sys/kernel/debug/ceph/下的osdc是客户端和osd之前的请求，一般和slow request没关系。
* osd中，只要状态包含active+clean 就说明是可以正常处理请求，就算active+clean＋srubbing+deep状态也能处理请求。
* 这个问题原因是有一个pg是active+recovering状态。而这个pg正式我们objecter_requests命令看到的pg，此时无法处理请求。
