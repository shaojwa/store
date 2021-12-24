#### 1. 修改vdbench文件属性
添加执行属性
```
chmod u+x vdbench
```
#### 2. 测试可用性
```
./vdbench -t
```

#### 3. 创建块设备镜像并映射为本地块设备
这部分参见 onestor_block_mount.md

#### 4 简单配置
```
#messsagescan=no

# all host default configs
hd=default,vdbench=./,user=root,shell=ssh

# test host1
hd=hd1,system=172.16.21.60

#sd storage definition
sd=sd1,host=hd1,lun=/dev/sdc,openflags=o_direct,threads=16


#wordload definition
wd=wd1,sd=sd1,xfersize=4k,rdpct=0

#last step, define run-definition
rd=rd1,wd=wd1,iorate=max,maxdata=100G,elapsed=60,interval=1
```
