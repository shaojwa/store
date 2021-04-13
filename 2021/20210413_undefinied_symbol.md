## issue
```
/opt/bin/dse: symbol lookup error: /opt/bin/dse: undefined symbol: _ZTVN8Objecter13EngineSessionE
```

## debug
```
nm /opt/bin/dse  | grep -n EngineSession
99535:                 U _ZTVN8Objecter13EngineSessionE
```
it is not the dse's matter. on issue host:
```
[root@node95 ceph]# nm libceph-common.so.0 | grep  -i _ZTVN8Objecter13EngineSessionE
[root@node95 ceph]#
```
on the works host
```
[root@node0 ceph]# nm libceph-common.so.0 | grep  -i _ZTVN8Objecter13EngineSessionE
0000000000d493a0 V _ZTVN8Objecter13EngineSessionE
```


