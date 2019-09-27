#### NAS机头查看export 出去的共享目录

   exportfs -v
   
其实 showmount -e 也能看到export出下的目录，不过好像信息没有 exportfs -v全

#### 没有 export出去的目录，在nfs客户端也能mount，但是是readonly

在4.0 以上的版本中，不是export出去的目录也能在nfs 客户端上挂载，只是为read only。
