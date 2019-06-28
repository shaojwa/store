#### stringstream 字符串流中的clear() 接口注意点

    ss.clear() 不会清空流内容，只会设置错误标记，如果要清空内容，请用ss.str("")
   
#### Option.set_default("").set_description（""）写法
 
    Option类有set_default()和set_description（）接口，返回的是对象自己的应用，即*this
  
