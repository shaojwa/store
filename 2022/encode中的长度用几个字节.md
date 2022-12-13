#### string 长度用u32
```
// string
inline void encode(std::string_view s, bufferlist& bl, uint64_t features=0)
{
  __u32 len = s.length();
  encode(len, bl);
  if (len)
    bl.append(s.data(), len);
}
```

#### list 也用32位
```
// std::list<T>
template<class T, class Alloc, typename traits>
inline std::enable_if_t<!traits::supported>
  encode(const std::list<T, Alloc>& ls, bufferlist& bl)
{
  __u32 n = (__u32)(ls.size());  // c++11 std::list::size() is O(1)
  encode(n, bl);
  for (auto p = ls.begin(); p != ls.end(); ++p)
    encode(*p, bl);
}
```


#### set 强转为u32
```
// std::set<T>
template<class T, class Comp, class Alloc, typename traits>
inline std::enable_if_t<!traits::supported>
  encode(const std::set<T,Comp,Alloc>& s, bufferlist& bl)
{
  __u32 n = (__u32)(s.size());
  encode(n, bl);
  for (auto p = s.begin(); p != s.end(); ++p)
    encode(*p, bl);
}
```

#### multiset 强转为u32
```
// multiset
template<class T, class Comp, class Alloc>
inline void encode(const std::multiset<T,Comp,Alloc>& s, bufferlist& bl)
{
  __u32 n = (__u32)(s.size());
  encode(n, bl);
  for (auto p = s.begin(); p != s.end(); ++p)
    encode(*p, bl);
}
```
