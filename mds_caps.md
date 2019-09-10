#### 在目录下创建文件所需要的cap是pAsLsXsFs

在92节点的/data目录下创建文件，内核客户端需要的cap是：

    {
      "client_id": 1328753,
      "pending": "pAsLsXsFs",
      "issued": "pAsLsXsFs",
      "wanted": "pAsLsXsFsx",
      "last_sent": 47
     }
     {
      "client_id": 6837004,
      "pending": "pAsLsXs",
      "issued": "pAsLsXs",
      "wanted": "-",
      "last_sent": 3
     }
     // last sent 47 是cap的int值，the caps of 47 is pAsxLx，不清楚为什么有Ax和Lx
  
 然后在91节点的/data目录下创建文件，会观察到cap的转移：
 
      {
          "client_id": 1328753,
          "pending": "pAsLsXsFs",
          "issued": "pAsLsXsFs",
          "wanted": "-",
          "last_sent": 47
      },
      {
          "client_id": 6837004,
          "pending": "pAsLsXsFs",
          "issued": "pAsLsXsFs",
          "wanted": "AsLsXsFsx",
          "last_sent": 5
      }
