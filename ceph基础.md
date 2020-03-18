#### pool 的几个属性

* pool type：池的类型定义了数据持久化方式。
* Placement Groups：
* CRUSH Ruleset：
* Durability：可靠性

#### 集群要做的事

 * 数据持久化
 * 数据完整性
 * 数据备份
 * 数据平衡
 * 数据恢复
 
#### crash做的事

* 把一个对象所在的pg算出来
* 把一个pg对应的acting set 算出来。
