```
ceph daemon dse.$(hostname) coro_setlog <int>
ceph daemon dse.$(hostname) coro_getlog
```
日志在`/var/log/ceph`下，其中level是一个bimap，那些模块需要答应日志，就位与上，目前一般设置为28（16+8+4）。

