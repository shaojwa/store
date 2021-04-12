## DSE instances
1. 8 instance per pool, instance is the independent unit of data.
2. in each instance, there are several modules, include engine, dcache, row ,dedup.
3. each instance will run on several processors, and each module run on the separated processors.
