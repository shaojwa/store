https://www.xsky.com/tec/6898/

cache tier has 4 modes： writeback, readproxy, readonly, none, pay attention to the name "None", not "unknown".
performance of the cache tier is usually unstable， because of the capacity of cache tier is limited， and in common workloads， the hot data varies.
cache tier is far less  than the backend pool.

XSpeed, the size of the cache-chunk is 4~64K, not the total object of 4M. using the "LogAppend" to improve the performance of small-write.
