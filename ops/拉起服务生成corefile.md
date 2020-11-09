service起服务时，服务挂掉有corefile，用systemctl起就没有。首要怀疑就是服务的启动脚本，
比如`/etc/rc.d/init.d/ganesha` 和 `/usr/lib/systemd/system/ganesha.service` 中有没有设置ulimit。
