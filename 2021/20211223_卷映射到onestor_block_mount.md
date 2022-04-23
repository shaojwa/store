## 1. 先在【卷管理】下创建卷
在存储池`blkpool0`下创建一个卷`lun0`

## 2. 然后在【卷映射】中依次如下配置

####  (1) 配置业务主机
- 选择【创建业务主机】，设置【名称】blkhost0，选择操作系统【linux】，【Agent IP】和【描述】都不用写。
- 填写【启动器】，启动器的查询命令如下：
```
[SDS_Admin@node73 ~]$  cat /etc/iscsi/initiatorname.iscsi
InitiatorName=iqn.1994-05.com.redhat:92fb21dd818
```
将`InitiatorName`填进去。

#### (2) 配置业务主机组
选择【新建】然后选择名称`blkhostgroup1`，创建成功。

#### (3) 映射管理
选择业务主机组`blkhostgroup1`然后选择【添加】，把`lun0`添加到主机组`blkhostgroup1`中。

在主机中组`blkhostgroup1`中的主机182.200.21.73上运行
```
# -t type=st, -p=portal=ip[:port]
$ sudo iscsiadm -m discovery -t st -p 172.16.21.60
172.16.21.60:3260,1 iqn.2018-01.com.h3c.onestor:20c5611213f64c0d9500f7096d9f390e
```

#### (4) 配置完成之后的挂载和卸载
挂载
```
sudo iscsiadm -m node -T iqn.2018-01.com.h3c.onestor:20c5611213f64c0d9500f7096d9f390e -l
```
卸载
```
sudo iscsiadm -m node -T iqn.2018-01.com.h3c.onestor:20c5611213f64c0d9500f7096d9f390e -u
```
刷新：
```
sudo iscsiadm -m session -R
```
