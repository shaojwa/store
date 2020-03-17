#### stat是否修改文件的atime

元数据write，影响ctime，元数据read，不影响任何时间。数据write，影响mtime。数据read，影响atime。
stat命令不会改变atime，因为stat通过getxatttr访问元数据，不改变atime，否者stat一次,atime就变化一次不合理。

file命令会影响atime，因为file会读取文件数据，来判断文件类型。file文件之后，文件的部分数据已经在内存中，再次file就不会更新。
