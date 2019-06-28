#### 怎么用iso安装nfs客户端

1. 上传CentOS.iso镜像
2. 创建/mnt/cdrom目录后运行 mount -t iso9660 CentOS.iso /mnt/cdrom 将镜挂载到/mnt/cdrom目录
3. 备份/etc/yum.repos .d/CentOS-Base.repo文件并修改原文件中的[base]部分为如下：

     [base]
     name=CentOS-$releasever - Base
     baseurl=file:///mnt/cdrom
     gpgcheck=1
     gpgkey=file:///mnt/cdrom/RPM-GPG-KEY-CentOS-7
     
4.yum install nfs-utils安装客户端

#### nfs共享怎么看

     showmount -e

#### nfs配置文件在哪里

    /etc/exports.d/

#### nfs挂载命令

    mount -t nfs 192.168.0.22:/share/nfs /mnt/nfs
