#### 现象
````
1: (()+0x56710) [0x55b4960a9710]
2: (()+0xf6d0) [0x7efefba3b6d0]
3: (pthread_mutex_lock()+0) [0x7efefba35c80]
4: (Objecter::ms_handle_reset_dse(Connection*)+0x85) [0x7eff050c5d25]
5: (Objecter::ms_handle_reset(Connection*)+0x8b) [0x7eff050ccbdb]
6: (DispatchQueue::entry()+0x1d7) [0x7efefc04b547]
7: (DispatchQueue::DispatchThread::entry()+0xe) [0x7efefc04e51e]
8: (()+0x7e25) [0x7efefba33e25]
9: (clone()+0x6d) [0x7efef96d1bad]
````
