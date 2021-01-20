#### 用iso安装nfs客户端

1. 上传CentOS.iso镜像

1. 创建/mnt/cdrom目录后运行 mount -t iso9660 CentOS.iso /mnt/cdrom 将镜挂载到/mnt/cdrom目录

1. 备份/etc/yum.repos .d/CentOS-Base.repo文件并修改原文件中的[base]部分为如下：

    ```
    [base]
    name=CentOS-$releasever - Base
    baseurl=file:///mnt/cdrom
    gpgcheck=1
    gpgkey=file:///mnt/cdrom/RPM-GPG-KEY-CentOS-7
    ```

1. 将其他分段禁止掉:

    ```
    enabled=0
    ```

1. yum install nfs-utils安装客户端
