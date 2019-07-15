#### nfsd进程都处在D状态，堆栈打印卡在write_get_caps阶段

在calc_new_quota_size()接口中,filelock并不是正在等待STABLE状态，也就是说他是相对稳定的状态下：

   if (!in->filelock.is_waiter_for(SimpleLock::WAIT_STABLE)) {
   ...
   }
   
   此时的 update_quota_ret 为0，calc_new_quota_size返回的也是原来的max_size，此时注意阅读代码流程。
