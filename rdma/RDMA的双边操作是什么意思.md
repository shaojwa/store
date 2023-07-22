RDMA的双边操作是什么意思？ 这是指RDMA的send/receive操作，所谓的双边，就是需要对端的应用程序参与才能完成收发。

AB两端要有自己的QP（queue-pare）和CQ（completion-queue完成队列）
A生成一个WQE，放到SQ中（因为A是发送数据，所以A的WQ就等于SQ), A中的RNIC（RDMA-NIC）RDMA网卡，解析到 WQE，发现是一个SEND消息。
就会把buffer中的数据向B发出，数据到大B的RNIC之后，B的WQE被消耗，数据直接存储到WQE指向的位置。通信完成后，Ａ和B的CQ中都会陈胜一个CQE，表示操作完成。

那什么叫参与呢？我用tcp不是一样需要对端参与么，是的，所以TCP也是双边操作，数据的收发，都需要双方参与。这对RDMA来说，是一种复杂的消息传输模式。
