#### 一个与_md_config_t_解析相关的死锁问题的定位

#### 现象：通过config set命令设置配置时，概率性出现命令卡死。
命令卡死的原因在于admin_socket线程等待mds_lock，而持有mds_lock锁的线程，尝试获取admin_socket线程持有的md_config_t对象中的锁。 

这是admin_socket线程的调用栈：

```
  #0  0x00007f0e2ce2551d in __lll_lock_wait () from /lib64/libpthread.so.0
  #1  0x00007f0e2ce20e1b in _L_lock_812 () from /lib64/libpthread.so.0
  #2  0x00007f0e2ce20ce8 in pthread_mutex_lock () from /lib64/libpthread.so.0
  #3  0x000055eabd579397 in Mutex::Lock(bool) ()
  #4  0x000055eabd202bb0 in MDSDaemon::handle_conf_change(md_config_t const*, std::set<std::string,     std::less<std::string>, std::allocator<std::string> > const&) ()
  #5  0x000055eabd7af046 in md_config_t::_apply_changes(std::ostream*) ()
  #6  0x000055eabd7af264 in md_config_t::apply_changes(std::ostream*) ()
  #7  0x000055eabd6ee286 in CephContext::do_command(...) ()
  #8  0x000055eabd6f1b0f in CephContextHook::call(...) ()
  #9  0x000055eabd580f29 in AdminSocket::do_accept() ()
  #10 0x000055eabd582738 in AdminSocket::entry() ()
  #11 0x00007f0e2ce1ee25 in start_thread () from /lib64/libpthread.so.0
  #12 0x00007f0e2c112bad in clone () from /lib64/libc.so.6
```

frame 4可以看到，handle_conf_change()接口就发现有对mds_lock的获取，看代码如下：

```
const bool initially_locked = mds_lock.is_locked_by_me();
if (!initially_locked) {
  mds_lock.Lock();
}
```

接下去我们去看所有的线程调用栈，几乎都是在等待mds_lock，但是有一个不是：

```
  (gdb) bt
  #0  0x00007f36339d951d in __lll_lock_wait () from /lib64/libpthread.so.0
  #1  0x00007f36339d4e36 in _L_lock_870 () from /lib64/libpthread.so.0
  #2  0x00007f36339d4d2f in pthread_mutex_lock () from /lib64/libpthread.so.0
  #3  0x0000564d13c16397 in Mutex::Lock(bool) ()
  #4  0x0000564d13e167c4 in md_config_t::get_val_generic(std::string const&) const ()
  #5  0x0000564d138fd189 in long md_config_t::get_val<long>(std::string const&) const ()
  #6  0x0000564d138f73b2 in Beacon::notify_health(MDSRank const*) ()
  #7  0x0000564d138c0b74 in MDSRankDispatcher::tick() ()
  #8  0x0000564d138ab22a in FunctionContext::finish(int) ()
  #9  0x0000564d138a8739 in Context::complete(int) ()
  #10 0x0000564d13c36414 in SafeTimer::timer_thread() ()
  #11 0x0000564d13c37e3d in SafeTimerThread::entry() ()
  #12 0x00007f36339d2e25 in start_thread () from /lib64/libpthread.so.0
  #13 0x00007f3632cc6bad in clone () from /lib64/libc.so.6
```

尽管frame上看也是Mutex::Lock(bool)，但看代码发现，他针对的是某个md_config_t对象内部的lock。
对比admin_socket的栈，猜想这两个md_config_t可能是同一个实例？ 
这样的话admin_socket在获取到md_config_t的lock之后尝试获取mds_lock锁。 而safe_timer线程在持有mds_lock锁时，尝试获取md_config_t的lock，这就会触发死锁。 那怎么判断这两个md_config_t是同一个实例？我们看代码发现safe_timer里的md_config_t实例是g_conf， 那么只要证明admin_socket中的conf也是这个g_conf，所以我们在MDSDaemon::handle_conf_change()接口处加一条日志打印证实这个问题：

```
  dout(0) << __func__ << " conf: " << conf << ", g_conf: " << g_conf << dendl;
```

我们最终确认是这个死锁问题，但是我们仍然不清楚，为什么MDSDaemon::handle_conf_change需要去拿到mds_lock锁，我们也不请清楚为什么 Beacon::notify_health()接口会调用md_config_t::get_val（），代码里并没有这个接口。
注意到ceph tell 好像不会有这个问题（MDSDaemon::handle_conf_change()接口开头加锁有说明）。
经过测试确实可以，因为tell是mon给mds发消息，mds走ms_dispatch流程：

```
  (gdb) bt
  #0  MDSDaemon::handle_conf_change (this=0x7f5e3c406000, conf=0x7f5e4307a000, changed=...)
  #1  0x000055f6380a0256 in md_config_t::_apply_changes (this=<optimized out>, oss=<optimized out>)
  #2  0x000055f6380a30a3 in md_config_t::injectargs (this=<optimized out>, s=..., oss=oss@entry=0x7f5e3c3fd290)
  #3  0x000055f637af97c3 in MDSDaemon::_handle_command (this=this@entry=0x7f5e3c406000, cmdmap=..., m=m@entry=0x7f5e3e018200, outbl=outbl@entry=0x7f5e3c3fd500, 
      outs=outs@entry=0x7f5e3c3fd480, run_later=run_later@entry=0x7f5e3c3fd4a8, need_reply=need_reply@entry=0x7f5e3c3fd47d)
  #4  0x000055f637afa81a in MDSDaemon::handle_command (this=0x7f5e3c406000, m=0x7f5e3e018200)
  #5  0x000055f637afae41 in MDSDaemon::handle_core_message (this=this@entry=0x7f5e3c406000, m=m@entry=0x7f5e3e018200)
  #6  0x000055f637afb66b in MDSDaemon::ms_dispatch (this=0x7f5e3c406000, m=0x7f5e3e018200)
  #7  0x000055f6381a15ab in ms_deliver_dispatch (m=0x7f5e3e018200, this=0x7f5e43085800)
  #8  MDSDispatchQueue::entry (this=0x7f5e431a8400)
  #9  0x000055f637f189ee in DispatchQueue::DispatchThread::entry (this=<optimized out>)
  #10 0x00007f5e44aade25 in start_thread () from /lib64/libpthread.so.0
  #11 0x00007f5e43da1bad in clone () from /lib64/libc.so.6
```
