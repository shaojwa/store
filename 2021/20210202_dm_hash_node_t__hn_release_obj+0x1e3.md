liaoli环境
```
ceph version 12.2.1-UniStorOS_V100R001B51 (557aad1b6b2d42bb7c0c9ce1583c3457e506df42) luminous (stable)
 1: (()+0x2e3f70) [0x559d4829cf70]
 2: (()+0xf6d0) [0x7f0b4fab96d0]
 3: (gsignal()+0x37) [0x7f0b4e030277]
 4: (abort()+0x148) [0x7f0b4e031968]
 5: (()+0x2f096) [0x7f0b4e029096]
 6: (()+0x2f142) [0x7f0b4e029142]
 7: (()+0x6b1d88) [0x7f0b519f3d88]
 8: (dm_hash_node_t::hn_release_obj(dm_user_obj_t&)+0x1e3) [0x7f0b519f96d3]
 9: (dm_user_obj_t::handle_destage_post()+0x445) [0x7f0b51a17c65]
 10: (Destage::delete_operation()+0xf73) [0x7f0b519e5363]
 11: (()+0x6a8cc7) [0x7f0b519eacc7]
 12: (()+0x114159) [0x7f0b52a96159]
 13: (co::Task::Run()+0xba) [0x7f0b52a962a6]
 14: (co::Task::StaticRun(long)+0x20) [0x7f0b52a96a4e]
 15: (make_fcontext()+0x21) [0x7f0b52b2d471]
```
应该是destage刷盘这边没处理好，导致已经通知dm析构。
