#### HDD/SDD/NVME的硬盘速度测试
我是用dd来测试的`dd if=/dev/zero of=ddfile oflag=direct bs=1G count=10"

- HDD的写入速度是 169M/s，并且，direct和sync接近。
- SSD的写入速度是 441M/s，并且，
- NVME的写入速度是 839M/s (HDD的5倍)，并且，direct速度大于sync。

#### 什么是 sync-write
本来，写入操作的调用返回和数据落盘没有关系，但是 sync将两者关联起来。
sync会增加IO的耗时。


####  什么是 sync-read
读请求总是同步的，调用的时候，希望的到的就是那个时候的数据，而不是过一阵子之后的数据，没法异步返回。

#### 什么是 直接IO
绕过系统内核的缓存，缓冲，以及设备和应用之间的IO管理。direct会是的内核对IO管理的影响最小化。
IO会忽略掉页缓存机制，直接对用户控件缓冲区和设备进行初始化，所有的操作都是同步的，在操作完成之前不会返回。
