找到一个pool的crush_rule，然后看着crush_rule所使用的osd。
```
ceph osd pool ls detail
```
得到 .diskpool0.rbd 这个pool的crush_rule 1:
```
pool 65539 '.diskpool0.rbd' replicated size 3 min_size 2 crush_rule 1 
```
然后用这个crush_rule 1 得到 osd列表：
```
ceph osd crush dump
```
可以看到rules:
```
 "rule_id": 1,
 "rule_name": "diskpool0_rule",
 "ruleset": 1,
 "type": 1,
 "min_size": 1,
 "max_size": 10,
 "steps": [
     {
         "op": "take",
         "item": -9,
         "item_name": "diskpool0"
     },
     {
         "op": "chooseleaf_firstn",
         "num": 0,
         "type": "host"
     },
     {
         "op": "emit"
     }
 ]
```
或者指定rule name：
```
ceph osd crush dump diskpool0_rule
```
但是还是看不到pool对应的osd，所以，估计需要先找出pg：
```
ceph pg ls_by_pool .diskpool0.rbd
```
然后可以看到这些pg对应的osd。可以通过awk过滤出所有的osd，就可以看到是否一致。
