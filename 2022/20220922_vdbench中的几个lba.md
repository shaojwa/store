```
17:47:16.138 localhost-0: 17:47:16.098         Data Validation error for fsd=fsd1; FSD lba: 0x4afe0000; Key block size: 4096; relative sector in data block: 0x00
17:47:16.138 localhost-0: 17:47:16.098         File name: /lwq/95g/vdb.1_2.dir/vdb_f0200.file; file block lba: 0x000c0000; bad sector file lba: 0x000e0000
17:47:16.138 localhost-0: 17:47:16.101 0x000   00000000 4afe0000 ........ ........   00000000 4afe0000 00000183 5f70d461
17:47:16.138 localhost-0: 17:47:16.101 0x010   25..0000 31647366 20202020 00000000   23880000 31647366 20202020 0003e168
17:47:16.138 localhost-0: 17:47:16.101         There are no mismatches in bytes 32-511
```
其中lba 0x4afe0000是全局fsd的地逻辑块地址。file block lba 0x000c0000，原因是，这个文件1m大小，这个地址应该是0x4afe0000 对 1m取模的余。
1m，16进制就是0x100000，所以0x4afe0000取余之后的是0xe0000，但是为什么显示为
