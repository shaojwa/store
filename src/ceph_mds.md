#### MDS中的数据结构层次

      *msgr(pointer)
      mc (monclient)     // 这里应该是可以用指针的，奇怪为什么没用，因为这个mc是做为参数下传的，msgr就是指针传给mds的。
      *mds(pointer)
          mds_lock
          timer
          beacon          
          *messenger (pointer, =msgr)
          *monc (ponter, =mc)
          mgrc      // 同样疑问为什么这里没有用指针
          *mdsmap (pointer)
          log_client
          clog
          *mds_rank (pointer)
              mds_lock (ref, = mds_lock)
              clog (ref,  = clog)
              timer (ref, = timer)
              rm_timer (ref, = rm_timer)
              mdsmap (ref, = mdsmap)
              
              // pointers
              *balancer (pointer)
              *finisher (pointer)
              *locker (pointer)
              *mdlog (pointer)
              *mdcache (pointer)
              *server (pointer)
              *inotable (pointer)
              *snapserver (pointer)
              *snapclient (pointer)
              *scrubstack (pointer)
    
分析：社区开发者说，这一块用指针还是不用，没有非常严格，是比较随意的。但是感觉起来，lock，timer，beacon这个几个都没有用指针。
不知道是不是因为这样代码写起来比较简洁，或者本身像mutex，习惯上都是用的实例而不是指针。
