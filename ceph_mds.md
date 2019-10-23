#### 数据结构层次图

      msgr(pointer)
      mc (monclient) // 这里应该是可以用指针的，奇怪为什么没用，因为这个mc是做为参数下传的，msgr就是指针传给mds的。
      mds(pointer)
          mds_lock
          timer
          beacon
          messenger (pointer, =msgr)
          monc (ponter, =mc)
          mgrc
          mdsmap (pointer)
          log_client
          mds_rank (pointer)
              mds_lock (ref, = mds_lock)
              clog (ref,  = clog)
              timer (ref, = timer)
              rm_timer (ref, = rm_timer)
              mdsmap (ref, = mdsmap)
              // pointers
              balancer (pointer)
              finisher (pointer)
              locker (pointer)
              mdlog (pointer)
              mdcache (pointer)
              server (pointer)
              inotable (pointer)
              snapserver (pointer)
              snapclient (pointer)
              scrubstack (pointer)
