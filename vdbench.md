## 术语
#### master 和 slave
master解析配置，决定运行哪些负载，以及上报结果。master的ip从hostname解析出来。而实际执行负载的是slave，slave的ip我们在配置文件中设置。


#### Data Validation
数据校验，用来检查数据一致性。


## 运行Vdbench
#### 常见启动失败原因
```
1. 总文件容量过大，空间不足
2. vdbench脚本中的java路径错误
3. 集群模式，免密没有配置
4. 集群模式，运行后显示slave连接不上，记得配/etc/hosts文件
```


#### no such file or directory
路径用相对路径，然后ssh到slave上之后，用相对路径就不一定能放到位对应目录的vdbench，所以相对路径在slave机子上有风险。


#### master 和 slave
master解析配置，实际执行负载的是slave，master的ip从hostname解析出来。slave的ip我们在配置文件中设置。


## openflags
这个参数可以用在很多定义中，包括SD/WD/FSD/FWD/RD中。

在FSD中使用，就是在创建文件系统结构时，如何打开文件，这对于写入有明显的影响。


## HD 
host definitions，主机定义，一般只会在多主机测试场景下用。
  * system	主机ip或者网络主机名。
  * shell	其实就是远程主机可以提供的连接方式。一般都是ssh。
	
## SD
storage definition，存储定义

## WD
workload definition，工作负载定义 

## FSD
filesystem definition， 文件件系统定义，参数包括，路径，深度，广度，文件数，文件大小。
一般是需要指定fsd的名字的，如果是fsd=default，那么这个就是fsd的默认配置，其他命名fsd就会严重这个里面分配置。

在 File system testing 一节中明确说道，FSD就是定义要生成的目录和文件结构的。

#### shared
shard是在FSD中用的参数，是定义文件系统用的，在有多少个slave的场景下，浙西slave就需要对文件系统中的文件进行分配，不同的lave访问不同的文件。

## FWD
filelesystem workload definition，文件系统工作负载定义，文件系统测试用fwd，不是wd，fwd依赖fsd。
* fwd=name，如果是default，那么该配置会当做默认配置被所有下面第你故意的fwd使用。
* operation
	one of mkdir, rmdir, create, delete, open, close, read, write, access, getattr and setattr
	
* fileio 在文件内怎么IO
	random: 在一个文件内随机IO，不是随机选文件，一个文件只有一个线程访问
	sequential: 在一个文件内顺序IO

* fileselect 怎么选择文件
* xfersize 读写传输文件大小，默认128k。
	
## RD
run definitions，rd依赖fwd。

#### format
这是RD中的参数，指定运行时的格式化配置。在执行每一个fwd之前都会先执行这个。

```
// 目录层次的完全创建以及所有文件的初始化，会先删除当前的文件结构，然后重建文件结构，之后再运行需要的RD
format=yes 

// 只会生成缺少的文件以及扩展大小不足的文件，并不会重新创建目录结构。
format=restart
```

但是，`fwd=format`是什么意思？


## 样例
```
# step 1: Host Definition
# hd is used in multi-vdbench instance
# hd=default,vdbench=./vdbench,user=root,shell=ssh
# hd=hd1,system=192.169.84.11
# hd=hd2,system=192.169.84.12

# step 2: FileSystem Definition, non-default fsd is required.
fsd=fsd1,anchor=/mnt/vdbench,depth=1,width=100,files=50,size=64k,shared=yes

# step 3: Filesytem Workload Definition, non-default fwd is required.
#fwd=format,xfersize=(32k,30,8k,30,4k,40),threads=64
#fwd=default,xfersize=(32k,30,8k,30,4k,40),fileio=random,fileselect=random,rdpct=60,threads=64
#fwd=fwd1,fsd=fsd1
#fwd=fwd1,fsd=fsd1,host=hd1
#fwd=fwd2,fsd=fsd1,host=hd2
fwd=fwd1,fsd=fsd1,xfersize=(32k,30,8k,30,4k,40),fileio=random,fileselect=random,rdpct=60,threads=64

# step 4: Run Definition
rd=rd1,fwd=fwd*,fwdrate=max,format=restart,elapsed=600,interval=1
```

样例二：
```
messagescan=no
hd=default,vdbench=/root/vdbench50406,user=root,shell=ssh
hd=hd1,system=55.55.56.223
hd=hd2,system=55.55.56.224
hd=hd3,system=55.55.56.43
hd=hd4,system=55.55.56.44
hd=hd5,system=55.55.56.88

fsd=fsd1,anchor=/mnt/opm,depth=1,width=1000,files=2000,size=32k,shared=yes
fwd=fwd1,fsd=fsd1,xfersize=32k,operation=create,threads=1
rd=rd1,fwd=fwd*,fwdrate=max,format=(restart,only),elapsed=10,interval=1
```
