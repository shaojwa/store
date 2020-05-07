```
UnknownHostException: hd=hd1,system=55.55.56.223
```
master解析配置，实际执行负载的是slave，master的ip从hostname解析出来。slave的ip我们在配置文件中设置。
所以运行master主机必须能在host中通过hostname找到ip才行，因为slave运行的时候-m参数指定master的时候需要这个ip。
