ceph中，如果需要添加一个命令，那么需要注册命令，注册函数是`register_command()`。
在这个注册函数中，第二个参数是cmddsec，里面可以描述这个命令的参数，参数的类型，以及其他的一些属性。
那么在这些属性中，有一个属性常见的是`n=N`是什么含义？

经过搜索，我们知道，ceph的命令parse其实是python写的，也就是ceph的命令是先通过这个python模块进行过滤校验，而不是延后到admin-socket的解析。
对应的文件是:`src/pybind/ceph_argparse.py`，回到刚才说的问题，我们可以在这个文件的第653行的类argdesc看到答案：

```
n=numallowed|N
n is a numeric literal or 'n|N', meaing "at least one, but maybe more.
ref=False means  the argument need not be present in the list.
```
所以n表示允许的数字，`n=N`表示至少为1，可以更多，表示这个参数可以多个，比如这个命令：
```
ceph pg dump_stuck inactive unclean stale
```
