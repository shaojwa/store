```
[root@li984-80 lib.3]# readelf -d cephfs.cpython-36m-x86_64-linux-gnu.so

Dynamic section at offset 0x53cb0 contains 30 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libcephfs.so.2]
 0x0000000000000001 (NEEDED)             Shared library: [libpython3.6m.so.1.0]
 0x0000000000000001 (NEEDED)             Shared library: [libpthread.so.0]
 0x0000000000000001 (NEEDED)             Shared library: [libdl.so.2]
 0x0000000000000001 (NEEDED)             Shared library: [libutil.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000c (INIT)               0x9138
 0x000000000000000d (FINI)               0x4d854
 0x0000000000000019 (INIT_ARRAY)         0x253c98
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x253ca0
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x228
 0x0000000000000005 (STRTAB)             0x1670
 0x0000000000000006 (SYMTAB)             0x260
 0x000000000000000a (STRSZ)              3592 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000003 (PLTGOT)             0x254000
 0x0000000000000002 (PLTRELSZ)           4152 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x8100
 0x0000000000000007 (RELA)               0x2658
 0x0000000000000008 (RELASZ)             23208 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000006ffffffe (VERNEED)            0x2628
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x2478
 0x000000006ffffff9 (RELACOUNT)          929
 0x0000000000000000 (NULL)               0x0
[root@li984-80 lib.3]#
```
