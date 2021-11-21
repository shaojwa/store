in ` Spinlock.h`

#### mutable
mutable, a keyword, and alse a type specifier.
permis modification of the class member even if the containing object is declared const.

#### constructor
```
Spinlock() {
ceph_spin_init(&_lock);
}
```
pay attention to the beginning underscore  of `_lock`;


#### distructor
```
~Spinlock() {
  ceph_spin_destory(&_lock);
}
```
pay attention to the selection of word `destory`

#### disable funcs
pay attention to the method of disabling the copy member-funcs: only declaration but without implementation
```
void operator=(Spinlock &lock);
Spinlock(const Spinlock &lock);
```

#### lock and unlock member-funcs
using `void` return-type and with `const` type-qualifier.

qualifier: in grammer, a qualifier is a word or group of words that comes after a noun
and gives more information about the person or thing that the noun refers to.

#### built-in helper class
const refer of Spinlock instence. pay attention to the const ref param of constructor;
```
Locker(const Spinlock &s): spinlock(s) {
   spinlock.lock();
}
```

#### the ceph_spin_lock_t defination
```
typedef struct {
#ifdef HAVE_PTHREAD_SPINLOCK
  pthread_spin_lock_t lock;
#else
  pthread_mutex_t lock;
#endif
} ceph_spin_lock_t;
```
