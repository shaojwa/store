####  which python 和 sudo which python 结果不一致

* 最开始是发现 do_cmake 中的 Found PythonInterp 不一样

* 然后执行 which python 和 sudo which python 也不一样，而且有对应关系。

* 最后怀疑和 env的路径不一样有关系

      [wsh@dev]$ sudo env | grep PATH
      PATH=/sbin:/bin:/usr/sbin:/usr/bin
      [wsh@dev]$ env | grep PATH
      PATH=/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:
      
 * 这是我linode上的vps的显示，root和普通用户下的PATH是一样的
 
       [root@li984-80 ~]# env | grep PATH
       PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/root/bin
       [root@li984-80 ~]# su wsh
       [wsh@li984-80 root]$ env | grep PATH
       PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/root/bin
  
  * 这个路径受什么影响？

