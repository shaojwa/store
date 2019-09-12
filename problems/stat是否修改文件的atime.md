atime的访问通过stat命令查看，getxatttr不应该修改atime，否者stat一次,atime就变化一次不合理。
一个文件，两种数据，元数据和数据。元数据set，影响ctime，元数据get，不影响任何时间。
数据set，影响mtime。数据get，影响atime。

xfs中stat不会修改atime，file命令会影响atime，因为file会读取文件数据，来判断文件类型。
file文件之后，文件的部分数据已经在内存中，再次file就不会更新。
