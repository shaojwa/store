https://www.intel.cn/content/www/cn/zh/architecture-and-technology/optane-dc-persistent-memory.html

1. 英特尔傲腾持久内存(PMem)是一项创新的内存技术，它将经济实惠的大容量和对数据持久性的支持进行了独一无二的组合。

#### 和DRAM的相同点
1. 封装在 DIMMS 中，与 DRAM 驻留在同一总线/通道上，并且可以采取与 DRAM 相同的方式来存储易失性数据。

#### 和DRAM区别
1. 英特尔傲腾持久内存的容量远远高于传统的 DRAM。英特尔傲腾持久内存模块具有 128GB、256GB 和 512GB 多种容量，远远大于通常从 4GB 到 32GB 的 DRAM 模块，尽管后者也存在更大的容量。
2. 英特尔傲腾持久内存甚至可以在不通电的情况下以持久模式存储数据，通过增加安全性来保证数据不受损。
3. 尽管英特尔傲腾持久内存模块的速度不如 DRAM 模块那么快，但从成本/GB 的角度以及可将容量扩展到超过 DRAM 的能力来看，前者的 TCO 情况与 DRAM 相比有了很大的改善。


#### 和固态盘的区别
英特尔傲腾持久内存 (PMem) 和英特尔傲腾固态盘都使用了相同的英特尔傲腾内存介质，但它们是完全不同的产品。

英特尔傲腾持久内存位于 DIMM 封装中，在 DRAM 总线上运行，可以是易失性的或持久的，并且能够作为 DRAM 的替代品。
而英特尔傲腾固态盘严格用于标准 NAND 封装模型（AIC、M.2、U.2、EDSFF 等）中的快速存储，并使用 NVMe 协议驻留于 PCIe 总线上，出于存储原因可始终保持持久，并且可以作为快速存储的替代品。

此外，英特尔傲腾固态盘在产品方面与标准英特尔3D NAND 固态盘有所不同。它在所有队列深度（比 NAND 快 6 倍）上都具有突破性的性能（并在低深度上有所区别），在负载下的持续响应（在写入压力下比 NAND 快 63 倍），高服务质量（比 NAND 快 60 倍），以及非常高的耐用性（总写入字节量比 NAND 多 20 倍）。
