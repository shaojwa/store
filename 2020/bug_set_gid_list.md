```
#0  0x00007f37d6a95277 in raise () from /lib64/libc.so.6
#1  0x00007f37d6a96968 in abort () from /lib64/libc.so.6
#2  0x00007f37c7c17ac5 in __gnu_cxx::__verbose_terminate_handler() () from /opt/h3c/lib/libstdc++.so.6
#3  0x00007f37c7c15a36 in ?? () from /opt/h3c/lib/libstdc++.so.6
#4  0x00007f37c7c15a63 in std::terminate() () from /opt/h3c/lib/libstdc++.so.6
#5  0x00007f37c7c15c83 in __cxa_throw () from /opt/h3c/lib/libstdc++.so.6
#6  0x00007f37c7c6aa97 in std::__throw_length_error(char const*) () from /opt/h3c/lib/libstdc++.so.6
#7  0x00007f37d1d5837c in std::vector<unsigned long, std::allocator<unsigned long> >::reserve (this=this@entry=0x7f37bac3dec8, __n=__n@entry=18446744073709551614)
    at /usr/include/c++/4.8.2/bits/vector.tcc:69
#8  0x00007f37d1cbabfb in set_gid_list (gids=0x0, count=-2, this=0x7f37bac3dc00) at /src/messages/MClientRequest.h:143
#9  Client::build_client_request (this=this@entry=0x7f37c6d73000, request=request@entry=0x7f37bac2c600)
````

perm 不能用引用，因为之前的请求处理之后perm会释放，所以不要用引用。
```
const UserPerm perms;
```
