```
read_op(snap = HEAD or n)
snap 1
write_op(snap = HEAD, snap_seq = 1) // COW1->clone1, write->head

------
data:0000
snap 1
write(snap = HEAD, snap_seq = 1) data:2222, clone1:1111 head
write(snap = HEAD, snap_seq = 1) data:3333, need filling
write(snap = HEAD, snap_seq = 1) data:4444, 

snap 2
snap 3
write(snap = HEAD, snap_seq = 2) data:5555   clone3:4444 head


replay
data1 read_row(hobject_t(snap = 2)) 
-----
write(snap = HEAD, snap_seq = 0) data:bbb 
```
