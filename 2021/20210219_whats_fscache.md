1. https://www.kernel.org/doc/Documentation/filesystems/caching/fscache.txt
2. https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/storage_administration_guide/ch-fscache
3. https://people.redhat.com/dhowells/fscache/FS-Cache.pdf
4. https://www.kernel.org/doc/Documentation/filesystems/caching/

#### 什么是 FSCache
FSCache 是内核组件，通过FSCache，网络文件系统以及其他的一些服务可以把数据缓存在本地，用磁盘空间去换性能的提升。特别是访问慢速网络和介质。

#### 给谁用
它可以给很多文件系统使用，比如AFS，ISOFS，NFS，CIFS等等。
