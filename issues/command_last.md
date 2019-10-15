#### shutdown -h now

      $ shutdown -h now 
      2019-08-14 20:28:11  [INFO] Run shutdown -h now
      2分钟后启动系统
      
      # message 关闭时间是 20:28:11
      # message 启动时间是 20:30:02   
      # operation记录的shutdown时间是：20:31:30 (重启后root登入shell的时间）
      # last -x：
      reboot   system boot 20:30-21:18 (开始时间是系统启动时间)
      shutdown system down 20:28-20:30
      # last reboot最新记录开始时间是系统启动的的时间      
      # ceph-mds中有Terminate信号
      # message shutdown日志：
      Stopping Login Prompts
      # message boot日志：
      Linux version 4.14.0-49
      Command line：BOOT_IMAGE=/vmlinuz
    
    
#### shutdown now

      $ shutdown now
      2019-08-14 20:43:23 [INFO] Run shutdown now
      # message   中关闭时间是 20:43:23
      # message   中启动时间是 20:48:58      
      # operation记录的shutdown时间是：20:54:50
      # last -x：
      reboot system boot 20:49-21:18 
      没有shutdown system down 事件
      # ceph-mds中有Terminate信号      
      # message shutdown日志：
      Stopping Command Scheduler...
      Stopped Command Scheduler.
      Stopped target Timers
      Stopping Timers.
      Stopping Login Prompts
      
#### reboot

