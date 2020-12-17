private 的析构函数会导致派生类中的析构函数称为delete：
```
#include <iostream>
struct A {
  private: ~A();
};
struct B : A {
};
int main() {
  B b;
  return 0;
}
```
提示：
```
empty_dtor.cc: In function ‘int main()’:
empty_dtor.cc:11:5: error: use of deleted function ‘B::~B()’
   B b;
     ^
empty_dtor.cc:7:8: note: ‘B::~B()’ is implicitly deleted because the default definition would be ill-formed:
 struct B : A {
        ^
empty_dtor.cc:4:12: error: ‘A::~A()’ is private
   private: ~A();
            ^
empty_dtor.cc:7:8: error: within this context
 struct B : A {
```
为什么？
