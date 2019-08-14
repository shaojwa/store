#### shutdown -h now

      $ shutdown -h now 
      2019-08-14 20:28:11  [INFO] Run shutdown -h now
      2分钟后启动系统
    
    * operation的日志记录的是机子起来之后的时间  
    * last reboot之前记录截止时间是shutdown的时间
    * last reboot最新记录开始时间是系统启动的的时间
    * message 关闭时间是shutdown的时间（一定有的日志是 Stopping Login Prompts）
    * message 启动时间是 20:32:02 (一定有的日志是 BOOT_IMAGE=/vmlinuz)
    
#### shutdown now

  $ shutdown now
  2019-08-14 20:43:23 [INFO] Run shutdown now
      
#### reboot

