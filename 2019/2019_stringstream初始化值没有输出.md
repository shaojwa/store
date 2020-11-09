#### stringstream ss(" mds_load is ")之后通过operator<<之后为什么没有输出

其实是原有的数据被operator<<操作覆盖掉。stringstream继承iostream，所有的ostream都有一个位置属性。  
有对应的接口tellp()可以查看位置。在ss初始化之后，write的位置并没有改变，所以<<操作会覆盖原有数据。  
当<<之后再去看这个值就发现已经改变，所以<<是在追加。如果要让初始化的数据不会被覆盖，那么需要通过seekp来设置位置。  
对应的，对于输入流，有tellg()和seekg()接口。  
