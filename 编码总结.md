#### typedef boost::intrusive_ptr<Inode> InodeRef 的 get()
```  
void intrusive_ptr_add_ref(Inode *in) {
  in->get();
}
```
什么时候会调用intrusive_ptr_add_ref(), intrusive_ptr递增一个非空指针上的引用计数时。

#### interval_set 区间遍历
```
for (interval_set<inodeno_t>::const_iterator p = prealloc_inos.begin();
    p != prealloc_inos.end(); ++p) {
  f->open_object_section("ino_range");
  f->dump_unsigned("start", p.get_start());
  f->dump_unsigned("length", p.get_len());
  f->close_section();
}
```

#### interval_set 元素遍历：


#### 获取一个值和获取多个值的写法区别：

获取一个值：
```
inodeno_t InoTable::project_alloc_id(inodeno_t id) 
```
获取多个值：
```
void InoTable::project_alloc_ids(interval_set<inodeno_t>& ids, int want) 
```

#### 根据字段类型返回字段名接口参考
```
static inline const char *get_lock_action_name(int a)
```
    
#### google风格的变量命名
```
purge_queue(purge_queue_)
```

## std 总体原则

#### 增加

容器都有insert系列接口。
无序容器：插入后不报序？因为无序所有没有push_back系列接口。
有序容器：插入后保序号，所有有push_back系列接口。

#### 删除

都有erase接口。
无序容器：（1）迭代器删除（2）指定值删除。
有序容器：（1）迭代器删除（2）指定值删除（3）指定索引值删除。

#### 查询

## list

* list 两头插入用push，中间插入用insert。
* list 两头删除用pop，中间删除用erase。
* list 没有直接修改的接口。
* 没有直接的find接口。

问题：

* 为什么list的pop_back没有返回值？
stackoverflow上的解释是，对象的构造函数可能会抛异常，这样通过pop系列函数返回时，对象已经pop掉，而因为异常可能没有获取到这个对象，那么这个对象就会丢失。容器的pop都无法实现成exception safe。

[参考1](https://stackoverflow.com/questions/12600330/pop-back-return-value)

[参考2](http://www.gotw.ca/gotw/008.htm)

* list 的删除接口为什么用erase，而不用remove？
受限remove这个词已经被用于一个算法名，定义在<algorithm>中。要留意remove的实现原理。remove其实不会真的删除元数，只是将不用删除的元数过滤出来。
类属于属组中把不需要删除的元数往前移，这样移动之后访问到的就都是不需要删除的远处。其实remove算法设计的时候是没有删除元数权限的，只有遍历以及赋值。
但是需要注意的是，list有erase也有remove接口，因为如果要真的删除某个值，只有earse是不够的，因为earse一般都是针对位置的删除（当然set中也有针对值的），所以list中原先针对值的删除需要remove和erase配合，remove返回需要删除的位置，然后erase开始从该位置进行删除，所以list中也有remove接口。
    
所以需要区别对待不同的container中的同名接口其实参数有时候是有区别的。

注意：
* 空list的pop行为是undefined，也就是说不可控，实际情况在linux下是 abort。

## set

* 插入用insert
* 删除用erase
* 没有直接修改的接口
* 查找用find，count 也可以，都是用的log复杂度，contains是C++20才有的接口。

注意：

* set中按照位置的删除同erase。
* set中没有remove借口，按照元数值的删除已经在erase中体现。

## interval_set

这是一个区间集合，元数是一个区间，比如```{[1,10], [15,19]}```


#### 输出流和输入流

这里的输入输出流，都是针对程序本身。程序打算输出到外面的，不管是输出到文件还是显示器。
而输入就是要读入到程序中的，从外部文件或者标准输入读取。
所以对程序来说，针对输出流一般进行写操作，针对输入流一般进行读操作。

#### stringstream ss(" mds_load is ")之后通过operator<<之后为什么没有输出

其实是原有的数据被operator<<操作覆盖掉。stringstream继承iostream，所有的ostream都有一个位置属性。
有对应的接口tellp()可以查看位置。在ss初始化之后，write的位置并没有改变，所以<<操作会覆盖原有数据。
当<<之后再去看这个值就发现已经改变，所以<<是在追加。如果要让初始化的数据不会被覆盖，那么需要通过seekp来设置位置。
对应的，对于输入流，有tellg()和seekg()接口。

#### stringstream 字符串流中的clear() 接口并不会清空原有数据

ss.clear() 不会清空流内容，只会设置错误标记，如果要清空内容，请用ss.str("")

#### map

中判断一个key是否存在用count函数
```
std::map<int, int> level_to_expire;
level_to_expire.count(k);
```

#### string

* 中的substr接口用来获取子串
* string中的find接口如果找到的字串在开头那么会返回0
所以不能通过 if (str.find("pattern"))来判断能找到，而要通过 if (string::npos != str.find("pattern")) 来进行。

#### english

HEALTH_WARN
HEALTH_ERR


#### 自杀线程
```
pthread_kill(h->thread_id, SIGABRT);
```

#### 工作函数中不获取锁，接口函数中获取锁

```
  Journaler::wait_for_flush() -> _wait_for_flush()
  Journaler::flush() -> _flush()
```

#### Option.set_default("").set_description（""）写法
 
    Option类有set_default()和set_description（）接口，返回的是对象自己的应用，即*this

#### ceph中有get_str_vec接口来处理将string分割为vector

    vector<string> kvs;
    get_str_vec(config, ",",  kvs);
    
#### ceph中有 strict_strtol系列函数将string转为做整型
 
    int level = (int) strict_strtol(levelstr.c_str(), 10, &err);
    
#### CDir中的两个get_inode()函数
 
    CInode *get_inode()    { return inode; }
    const CInode *get_inode() const { return inode; }
  
  diri = dir->get_inode() 调用时会更具dir是不是const指针进行选择，如果dir是const指正，那么编译时只会调用第二个接口。
  所以，而如果CInode中获取字段的接口如果没有const属性，就不能调用，所以代码中很多时候以diri->inode的方式直接访问字段。
  
