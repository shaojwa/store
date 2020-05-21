 UserPerm(const UserPerm& o) : UserPerm() {
    deep_copy_from(o);
  }
  UserPerm(UserPerm && o) {
    m_uid = o.m_uid;
    m_gid = o.m_gid;
    gid_count = o.gid_count;
    gids = o.gids;
    alloced_gids = o.alloced_gids;
    o.gids = NULL;
    o.gid_count = 0;
  }
  
 UserPerm& operator=(const UserPerm& o) {
    deep_copy_from(o);
    return *this;
  }
  
  // 注意，operator= 不是构造函数，只是默认的赋值操作符重载。
