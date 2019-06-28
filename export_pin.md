#### 根目录所在的子树一般是在rank值为0的mds上

    尽管在rank值为0的mds上，但是export_pin字段为-1，也就是并没有pin在rank值为0的mds上。

#### 每个active mds 都有一颗子树
  
    子树名为~mdsX，X即为该active mds 当前的rank值。
