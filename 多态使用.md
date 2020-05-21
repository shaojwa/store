## 关于多态使用
基类  LogEvent 中定义很多虚函数，比如 encode，decode，dump。
```
class EOpen : public LogEvent
```
在使用EOpen的接口中，比如start_entry（），submit_entry（） 都是用的基类参数：

```
void start_entry(LogEvent *e) {}
void submit_entry(LogEvent *e, MDSLogContextBase *c = 0) 
```

## 多态函数的定义

多态函数参数一定是基类类型，派生类override虚函数的时候，派生类中的接口参数也还是基类的参数。

```
virtual void set_object_info(MDSCacheObjectInfo &info) { ceph_abort(); }
```

## 多态函数中无法操作派生类中的成员

因为传入的是基类的指针，虚函数是通用接口，操作积累中共有的元素。派生类中特有的成员应该用派生类中的接口单独处理。


## 派生类中override的虚函数也无法访问基类中的private成员

应该只能由基类的虚函数来访问。
