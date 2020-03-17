#### NAS本地创建文件

    [root@node93 nfs]# ll
    total 0
    -rw-r--r-- 1 root root 0 Oct  9 16:11 file_nas

mask is 644

#### nfs挂载后创建文件

    [root@node94 nas_nfs]# touch file_nfs
    [root@node94 nas_nfs]# ll
    total 0
    -rw-r--r-- 1 root root 0 Oct  9 16:11 file_nas
    -rw-r--r-- 1 root root 0 Oct  9  2019 file_nfs
