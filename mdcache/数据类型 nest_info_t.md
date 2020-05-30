也是派生自scatter_info_t，字段有5个：
  1. utime_t rctime;
  1. int64_t rbytes;   // 某个目录下
  1. int64_t rfiles;   // 某个目录下直接子目录包含的所有文件数
  1. int64_t rsubdirs; // 某个目录下直接子目录包含的所有子目录数
