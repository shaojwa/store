```
/opt/bin/dse: symbol lookup error: /opt/bin/dse: undefined symbol: _ZTVN8Objecter13EngineSessionE
```

```
nm /opt/bin/dse  | grep -n EngineSession
99535:                 U _ZTVN8Objecter13EngineSessionE
```
