做存储，iscsi一定会听到，比如常用的命令iscsiadm。

#### 什么是iSCSI
iSCSI来源于SCSI。SCSI，wikipedia上看的话，最早1986年就开始指定SCSI标准。而iSCSI，在2003年才成为标准。

#### 解决什么问题
通过互联网来解决数据传输问题，SCSI解决的是数据传输，iSCSI主要的特点是两个，一是通过互联网，而是解决存储数据。
相比SCSI，iSCSI主要针对存储相关的数据传输，它基于SCSI-3来解决存储数据传输。

#### iSCSI的 initiator 和 target
用iscsiadm来管理initiator，包括登入登出target，错误处理，连接。

#### iscsiadm的使用步骤
发现
```
[SDS_Admin@node72 wsh]$ sudo iscsiadm -m discovery -t st -p 172.16.21.74
172.16.21.74:3260,1 iqn.2018-01.com.h3c.onestor:1f370e6107474f82a56d7810199c1f50
```
发现的target会保存在本地数据库中，可以用用命令查看。
```
[SDS_Admin@node72 wsh]$ sudo iscsiadm -m node
172.16.21.75:3260,1 iqn.2018-01.com.h3c.onestor:1f370e6107474f82a56d7810199c1f50
172.16.21.74:3260,1 iqn.2018-01.com.h3c.onestor:1f370e6107474f82a56d7810199c1f50
172.16.21.73:3260,1 iqn.2018-01.com.h3c.onestor:1f370e6107474f82a56d7810199c1f50
```
登入所有的target，下面的命令会尝试登入发现的所有target，现在我们有三个target，尽管这三个target的IQN相同，但是portal不同。

#### target portal 和 target iqn唯一确定一个target

#### 什么是IQN
 IQN = iSCSI Qualified Name

#### login target
```
$ sudo iscsiadm -m node -l
```

#### logout target
```
$ sudo iscsiadm -m node -u
```

#### 什么是 node
Open-iscsi uses the term node to refer to a portal on a target.

#### 什么是 target
target =  targetname + portal(= node)


