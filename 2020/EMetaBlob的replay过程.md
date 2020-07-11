其中有一段代码如下：
```
if (used_preallocated_ino)
{
  if (!session->info.prealloc_inos.empty()) {
    inodeno_t       next = session->next_ino();
    inodeno_t       i   = session->take_ino(used_preallocated_ino);

    if (next != i) {
      mds->clog->warn() << " replayed op " << client_reqs << " used ino " << i
      << " but session next is " << next;
    }
    assert(i == used_preallocated_ino);
    session->info.used_inos.clear();
  }
  mds->sessionmap.replay_dirty_session(session);
}
```
如果replay某个日志的时候，发现以后used_preallocated_ino，表示日志对应的事务有使用的ino。
所以这ino通过replay会放到used_inos中，然后当这个事务提交并记录日志之后后，
used_preallocated_ino会从used_inos中移调。
