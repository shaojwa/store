1. ROW是新引入的一层，ROW对象基于OSD对象，ROW对象可以远远大于4M。
1. 写row时，offset，len均为8k对齐。
1. 读offset超过userobj的size时，不会报错，返回读取到的数据为0。
1. 读offset没有超过size，加上len之后超过size，此时len会重置为size-offset。
1. 读offset,len如果都在size范围内，read()接口时，读多长返回多长，没有写过的数据补0。
1. 读offset,len如果都在size范围内，sparse_read()，返回一个map，有完整的8k数据不会返回。
