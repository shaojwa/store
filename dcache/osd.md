1. OSD对象的元数据在rocksdb中，attr，omap也在rocksdb中。 
1. OSD中的对象大小最大是4M，可以比4M小。
1. OSD对象可以使sparse的，实际写入的数据可能只是其中1M，bluestore中存的就是这1M的数据。
1. 和OSD对象相对应的一般叫user_obj。
