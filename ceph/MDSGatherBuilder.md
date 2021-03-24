## MDSGatherBuilder

MDS收集器构造器，目标是调用new_sub()生产Context对象，由内部成员c_gather产生Context对象，所以常常MDSGatherBuilder类型的对象直接叫gather也说得过去。
其实这个对象本身是一个Builder，c_gather有两个成员cct和finisher。最终的这种context有什么特殊，和Gather有什么关系，为什么由gather来产生？

原因是，何种Gather（比如 MDSGather）都继承自C_GatherBase，而这种类型实现了最关键的一个接口new_sub()。
Gather相当于是一个虚拟的管理者，它统计已经创建了多少个sub（sub_created_count），当前存在多少个（sub_existing_count）

为什么需要Gather？
（1）自动化管理，用的时候随时创建，跳出作用域之后也不会析构掉，当所有创建出来的上下文都处理完毕之后，会自动析构，但是这个不是必须的。
（2）关键是，gather有一个finisher，但是这个finisher并不会马上掉，而是等gather中的最后一个上下文执行完成之后。
怎么实现最后一个？任何一个上下文（C_GatherSub类型）有finish(), 这个接口会判断 sub_existing_count是不是等于0，如果等于零表示当前是最后一个，才会调用delete_me():

```
void sub_finish(ContextType* sub, int r) {
    lock.Lock();
    --sub_existing_count;
    mydout(cct,10) << "C_GatherBase " << this << ".sub_finish(r=" << r << ") " << sub
    if (r < 0 && result == 0)
      result = r;
    if ((activated == false) || (sub_existing_count != 0)) {
      lock.Unlock();
      return;
    }
    lock.Unlock();
    delete_me();
  }
```
在delete_me()中才会执行finish：

```
void delete_me() {
    if (onfinish) {
      onfinish->complete(result);
      onfinish = 0;
    }
    delete this;
  }
```

所以 Gather干的主要工作就是，有多个事情要做，下一步事情要等到这些所有事情都完成之后才执行。


## C_IO_Wrapper

是MDSIOContext的一个包装，两参数mds_ 和 被包装的上下文 wrapped_。
