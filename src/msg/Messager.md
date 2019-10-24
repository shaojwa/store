### Messager

这是一个基类，被SimplePolicyMessenger继承，最终的派生类是，SimpleMessager，或者XioMessager，或者AsyncMessager.cc。
我们现在用的是AsyncMessager，Messager中定义很多接口，dispatch_queue等等。在MDS中用的是Messager这个基类指针。
MDS的ceph-mds中调用Messenger *msgr = Messenger::create()来创建实例，这里面用的是Async。
