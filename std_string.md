#### string中的substr接口用来获取子串

#### string中的find接口如果找到的字串在开头那么会返回0

    所以不能通过 if (str.find("pattern"))来判断能找到，而要通过 if (string::npos != str.find("pattern")) 来进行。
