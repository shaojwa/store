#### 视频容错开启后 PG down掉osd就不会out
#### 第一个对象中有文件的layout和parent属性。
#### 获取文件的layout信息时往osd发送的请求。

先查看对象所在的主osd

    ceph osd map .capfs.data.datapool0 100000003ea.00000000
  
找到 acting set 为(4, 7, 5), pg 为 2.7b93bfe5  

然后发送查询请求：

    getfattr -n ceph.file.layout ddfile

发现osd4没有收到对应的请求，怀疑点是msd缓存中有对应的数据导致的，清掉缓存后再次尝试，发现并没有发往数据池，只能猜测是否从数据池。
先确定对象，因为数据池的对象都是目录对象，所以先找到ddfile所在目录的对象，以inode号命名，为1099511628777,16进制1000000039。
用ceph osd map查到10000003e9.00000000对应的osd集合为（2，1，0），所以找osd2所在的日志，时间区间在16:44:04.829624618和16:44:04:841199778 之间。
发现，请求确实发送给元数据池，op是，CEPH_OSD_OPGETXATTR。

现在还是不能当mds和数据池通信，查看代码，找到可能的数据池读取流程，找到scrub_dir_inode()和scrub_file_inode()等接口，最后找到enqueue_srcub_work()以及最后的enqueue_scrub，发现scrub_path命令可以触发。

    ceph daemon mds.mds1 scrub_path /data/ft/ddfile recursive force
    
发现注入错误之后，mds还是认为scrub error on inode \[inode 0x10000003ea。   
我发现 damage ls 这命令必须在ceph tell mds.mds0 中才有，ceph daemon mds.mds0 中没有。 
通过ceph tall mds.mds0 damage ls 看到：

    {
        ”damage_type": "backtrace",
        "id": 129562276,
        "inode": 1099511628778,
        "path": "/data/ft/ddfile"
    }



PG write时，如果osd处于down/out/imcompete时，osd都会直接丢弃op

#### truncate 导致assert复现步骤

* mon_osd_down_out_interval

    ceph tell mon.* injectargs --mon_osd_down_out_interval=600

我们知道，mon_osd_down_out_interval默认值是1800秒，这个时间之后，mon对把osd标为out。
osd中down，只是临时性故障，不会触发PG迁移。而out是mon检测到某个osd处于down超过一段时间，mon将其设置为out，即为永久性故障。下次CRUSH的选择过程中会被自然淘汰。

* down掉3个数据池osd

* dd写入数据发现错误

        # dd if=/dev/zero of=ddfile bs=1k count=102400
        dd error writing 'ddfile': Input/output error
        
* 把 一个osd down掉，写入数据后，truncate就可以。


#### 构造PG的imcomplete状态

* 假如对象对应的三个osd是(3, 4, 7), 冗余策略是2+1纠删码。
* 首先 down osd 4
* 然后写一个对象，数据可以写入，分布在3, 7上
* 然后 down osd 3
此时pg中两个osd down掉，PG为down状态
* ceph osd lost 3
此时表示放弃osd 3上的同步，再次出发peering
lost操作只能针对down的osd，up的不能lost
* 最终会达到imcomplete状态

恢复lost的osd只需要把systemctl restart ceph-osd@3.service即可。

* 构造imcomplete状态一般有两种方式，一种是在冗余度足够的情况下构造，这种比较难。二是冗余度不够的情况下触发peering。

* 确认那个pg处于imcomplete状态

    ceph pg 2.1e5 query | grep state

#### down掉一个osd节点后为什么有的PG是active+undersized+degraded而有的只是active+undersized

对2+1来说，小于3的osd数量就是undersized

#### mds和osd交互

* 发起

        fetch_backtrace_and_tag()
        ObjectOperation::getxattr()
        ObjectOperation::add_xattr()
        objecter::read() # out_handler = NULL
        

* 收到
    
        MOSDOpReply::decode_payload()
        OSDOp::split_osd_op_vector_out_data(ops, data);
        Objecter::handle_osd_op_reply() 处理osd的返回，线程是 mds-worker-X,  # the result from osd messager


* 处理请求 

        bool _backtrace(int rval) # fn_anonymouns线程处理回调函数

