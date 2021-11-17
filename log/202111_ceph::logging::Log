Log中的 dendl_imp中的std:flush的用法。这个功法的名字叫`manipulator`，有点类似`operator`，一般翻译为操纵器。
中文一般叫控制符，其实很让人搞不清楚到底什么意思。怎么用的？很简单，必须是 `out << std::flush;`
flush就是函数名，如果说，operator<<这个运算符支持函数参数。那么这个语句`out << std::flush`就可以理解成为：
```
operator << (out, std::flush);
```
我们查看std::basic_ostream类对`opeartor<<()`的重载，我们课可以看到这个：
```
basic_ostream& operator<<(
    std::basic_ostream<CharT,Traits>& (*func)(std::basic_ostream<CharT,Traits>&) );
```
所以，std::flush就是一个特化的函数名，用来作为`operator<<()`的参数。
