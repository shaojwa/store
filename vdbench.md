#### master 和 slave
master解析配置，决定运行哪些负载，以及上报结果。master的ip从hostname解析出来。而实际执行负载的是slave，slave的ip我们在配置文件中设置。

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

## block + thread=64
块的方式，对一个lun来说，所有的io都是串行的，及时 thread有多个线程，最终也会串行化。
