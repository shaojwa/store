
#### mds 性能命令

* 需要在handy节点上运行
* mds 相关数据取自 ceph daemon mds.mds0 perf dump

#### 使用步骤

先clean：

        onestor-cli perf -m mds -t clean
 
然后open：

        onestor-cli perf -m mds -t open
        
开始业务

然后关闭：
        
        onestor-cli perf -m mds -t close
        
最后显示：

        onestor-cli perf -m mds -t show
