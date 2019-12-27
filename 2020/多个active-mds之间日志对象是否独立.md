#### 日志对象以 200开头
```
#define MDS_INO_LOG_OFFSET        (2*MAX_MDS)
```

#### 开启多个mds后，将某个目录export到rank-1上

当前rank0是mds1，注意必须要以/data/开始指定路径：

```
ceph daemon mds.mds1 export dir /data/dir_rank1 1
```

#### 通过 get subtrees 查看到 dir_rank1目录在 rank1 上

```
$ ceph daemon mds.mds2 get subtrees | less
{
        "is_auth": true,
        "auth_first": 1,
        "auth_second": -2,
        "export_pin": -1,
        "dir": {
            "path": "/data/dir_rank1"
        ....
}
            

#####　在往 /data/dir_rank1 下写数据后查看日志对象就发现200和201对象都有

```
[root@node12 rank1]# rados -p .capfs.metadata.Metadata ls | grep ^20 | sort
200.00000000
200.00000002
200.00000003
200.00000004
200.00000005
200.00000006
200.00000007
200.00000008
200.00000009
200.0000000a
200.0000000b
200.0000000c
200.0000000d
200.0000000e
200.0000000f
200.00000010
201.00000000
201.00000001
````

#### flush journal 之后rank0 里的日志只剩下俩
```
[root@node12 rank1]# rados -p .capfs.metadata.Metadata ls | grep ^200 | sort
200.00000000
200.00000010
````
