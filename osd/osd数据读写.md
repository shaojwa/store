OSD 读写关键的几个点：
|||
|:-|:-|
|OSD::ms_fast_distpath||
|distpath_op_fast||
|osd->dequeue_op()|取出op|
|pg->do_request()||
|C_OSD_RepopApplied|| 
|C_OSD_RepopCommit|| 
|pgbackend->submit_transaction()||
|ReplicatedBackend::issue_op|发送消息到副本OSD| 
|parent->log_operation()|| 
