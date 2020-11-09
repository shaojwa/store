
#### stringstream 字符串流中的clear() 接口并不会清空原有数据
ss.clear() 不会清空流内容，只会设置错误标记，如果要清空内容，请用ss.str("")
