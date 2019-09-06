#### 测试在PG down的情况下MDS是否会重发请求给OSD


#### mds处理的几个关键event点

  "event": "throttled"
  "event": "all_read"
  "event": "dispatched"
  "event": "initiated"
  "event": "acquired locks"  
  "event": "early_replied"
  "event": "submit entry: journal_and_reply"
  

