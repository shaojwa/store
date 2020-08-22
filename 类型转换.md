cpp中因为继承关系引入的四种类型强转方式，：

1. static_cast
1. dynamic_cast
1. const_cast
1. reinterpret_cast

《Effective C++》中将c语言强制类型转换称为旧式转型，c++强制类型转换称为新式转型。

## 上行与下行

画图是，基类一般在上，派生类在下，所以派生类指针转基类指针叫上行转换，基类指正转派生类指针叫下行转换。

## static_cast
1. 支持上行和下行转换，相当于C语言里的强制转换，用于基本类型转换和类转换。
1. 上行转换安全，下行转换时，因为没有运行时类型检查，所以转换不安全。
1. static_cast不能转换掉expression的const，volatile 或者__unaligned属性，所以引入const_cast。
1. 支持多重继承中的上行转换。

## dynamic_cast
1. 支持上行和下行转换。
1. 在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全。
1. 基类中必须存在虚函数。
1. 支持交叉转换，基于同一个基类的两个派生类之间的转换。
1. dynamic_cast是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作。

## const_cast
1. 用于修改类型的const或volatile属性，除了const或volatile修饰之外， new_type和expression的类型是一样的。
1. 一般是将const转为non-const。

## reinterpret_cast
1. 它可以把一个指针转换成一个整数，也可以把一个整数转换成一个指针。
1. reinterpret_cast意图执行低级转型，实际动作（及结果）可能取决于编辑器，这也就表示它不可移植。
1. 一般用于把地址转为int，比如地址随机化计算。
