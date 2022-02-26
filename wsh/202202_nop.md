#### ceph 中的nop操作
对于部分流程，不需要实际做什么处理的流程，ceph会调用nop接口，参数会传入hobject，但是里面会调用
```
void nop(const hobject_t &hobj) {
  get_object_op_for_modify(hobj)
}
```
但是get_object_op_for_modify这个接口干的事情也只是通过hobj拿到op单后断言这个op不是delete，具体为什么要这么做不是很清楚。
