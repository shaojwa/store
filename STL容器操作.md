## std 容器插入原则

1. 容器都有insert系列接口。
1. 无序容器：插入不保序，因为无序所有没有push_back系列接口。
1. 有序容器：插入后保序，所以有push_back系列接口。

## std 容器删除原则

都有erase接口。
无序容器：（1）迭代器删除（2）指定值删除。
有序容器：（1）迭代器删除（2）指定值删除（3）指定索引值删除。

## std 容器查询原则

是否存在都可以用count么？


## string
string放在list后面是因为string和list最像。

* 中的substr接口用来获取子串
* string中的find接口如果找到的字串在开头那么会返回0

所以不能通过 if (str.find("pattern"))来判断能找到，而要通过 if (string::npos != str.find("pattern")) 来进行。

## map

中判断一个key是否存在用count函数
```
std::map<int, int> level_to_expire;
level_to_expire.count(k);
```

## set

* 插入用insert
* 删除用erase
* 没有直接修改的接口
* 查找用find，count 也可以，都是用的log复杂度，contains是C++20才有的接口。

注意：

* set中按照位置的删除同erase。
* set中没有remove借口，按照元数值的删除已经在erase中体现。

## list

* list 两头插入用push，中间插入用insert。
* list 两头删除用pop，中间删除用erase。
* list 没有直接修改的接口。
* 没有直接的find接口。

问题：

* 为什么list的pop_back没有返回值？
stackoverflow上的解释是，对象的构造函数可能会抛异常，这样通过pop系列函数返回时，对象已经pop掉，而因为异常可能没有获取到这个对象，那么这个对象就会丢失。容器的pop都无法实现成exception safe。

参考：

```
https://stackoverflow.com/questions/12600330/pop-back-return-value
http://www.gotw.ca/gotw/008.htm
```

* list 的删除接口为什么用erase，而不用remove？
受限remove这个词已经被用于一个算法名，定义在<algorithm>中。要留意remove的实现原理。remove其实不会真的删除元数，只是将不用删除的元数过滤出来。
类属于属组中把不需要删除的元数往前移，这样移动之后访问到的就都是不需要删除的远处。其实remove算法设计的时候是没有删除元数权限的，只有遍历以及赋值。
但是需要注意的是，list有erase也有remove接口，因为如果要真的删除某个值，只有earse是不够的，因为earse一般都是针对位置的删除（当然set中也有针对值的），所以list中原先针对值的删除需要remove和erase配合，remove返回需要删除的位置，然后erase开始从该位置进行删除，所以list中也有remove接口。
    
所以需要区别对待不同的container中的同名接口其实参数有时候是有区别的。

注意：
* 空list的pop行为是undefined，也就是说不可控，实际情况在linux下是 abort。

## boost中的侵入式指针

typedef boost::intrusive_ptr<Inode> InodeRef 的 get()
```  
void intrusive_ptr_add_ref(Inode *in) {
  in->get();
}
```
什么时候会调用intrusive_ptr_add_ref(), intrusive_ptr递增一个非空指针上的引用计数时。
