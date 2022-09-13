1.主机通过multipath，计算出所在engine所在的controller，然后直接发往那个controller所在的tgt。
2. TGT。
3. dcache。
4. dcache调用daos-client刷数据，同时更新元数据到保电内存。
5. daos-server进行存储数据。
