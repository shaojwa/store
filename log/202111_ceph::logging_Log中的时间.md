ceph中的Log在`src/log/Log.h`中定义。这种公共模块，一般都是定义在特定的namespace中的：
```
namespace ceph {
namespace logging {
class Log: private Thread
{
  Entry *create_entry(int level, int subsys);
}
```
看实现，我们就知道，日志中显示的时间，就是日志create的时间，而不是日志打印出来的时间，而且也应该这样，这样才合理。
而在dendl中我们会看会先std::flush;然后就会`submit_entry()`。
