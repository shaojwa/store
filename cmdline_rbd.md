#### 常用命令
```
rbd [detail] ls -p blkpool0   // 查看这个块池中的所有块设备
rbd du -p .diskpool0.rbd      // 查看这个块池中的所有块设备使用情况
rbd info .diskpl.rbd/wcw8 --debug_objecter=20
rbd stat .diskpl.rbd/wcw8 --debug_objecter=20
```
