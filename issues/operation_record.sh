#### 脚本文件

     /opt/bin/operation_record.sh
     
用户从shell登入之后才从history中把最后一条日志读出来写入operation.log。
     
#### 包含脚本

     /etc/profile.d/set_operation.sh
     

#### 记录的时间

shell下正常运行一条命令，这条命令记录到operation的时间也是这条命令执行完的时间。可以通过以下脚本测试：

     date; sleep 120; date

等这条命令执行完之后才会记录到operation中。
