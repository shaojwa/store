#### bufferlist中的数据，可以深拷贝到一个bufferptr，但是不能深拷贝到一个bufferlist，为什么？
bufferlist的目录就是复用底层的数据，如果你只是复用，不修改，那么深拷贝bufferlist没有意义。

但是，如果你要修改呢？深拷贝就会有意义。此时，按照目前提供的接口，我们似乎只能先深拷贝bufferlist到bufferptr中。
如果处理的对象是bufferlist，那么需要把bufferptr，append到bufferlist。如果可以直接处理bufferptr，那么到此也就可以完成目的。

总体来说，深拷贝bufferlist的意义确实不大，而且，原来bufferlist中的ptr个数，在深拷贝中需要保持一致么？
是不需要的，但是list的拷贝从语义上来说，是需要保持其中元素个数相同的，所以感觉bufferlist的深拷贝意义不是很大。
