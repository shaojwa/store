强大呀，直接能看：
```
[root@node11 ~]# slabtop -o
 Active / Total Objects (% used)    : 613241 / 705934 (86.9%)
 Active / Total Slabs (% used)      : 22007 / 22007 (100.0%)
 Active / Total Caches (% used)     : 82 / 116 (70.7%)
 Active / Total Size (% used)       : 162435.93K / 185330.82K (87.6%)
 Minimum / Average / Maximum Object : 0.01K / 0.26K / 18.69K

  OBJS ACTIVE  USE OBJ SIZE  SLABS OBJ/SLAB CACHE SIZE NAME
 99057  88931  89%    0.19K   4717       21     18868K dentry
 58624  46065  78%    0.06K    916       64      3664K anon_vma_chain
 58180  53707  92%    0.20K   2909       20     11636K vm_area_struct
 58170  57889  99%    0.13K   1939       30      7756K kernfs_node_cache
 57984  34460  59%    0.06K    906       64      3624K kmalloc-64
 31824  31824 100%    0.04K    312      102      1248K Acpi-Namespace
 29256  25189  86%    0.09K    636       46      2544K anon_vma
 24384  15641  64%    0.25K    762       32      6096K kmalloc-256
 23464  23464 100%    0.07K    419       56      1676K Acpi-Operand
 19376  19342  99%    0.57K    692       28     11072K radix_tree_node
 17792  13214  74%    0.03K    139      128       556K kmalloc-32
 17664  17478  98%    0.69K    768       23     12288K shmem_inode_cache
 14850  14256  96%    0.59K    550       27      8800K inode_cache
 14352  14210  99%    0.66K    598       24      9568K proc_inode_cache
```
