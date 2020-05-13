```
explicit WorkThread(OpMerge *opmerge_) : opmerge(opmerge_) {}
void* entry() override {
  opmerge->_work_routine();
  return 0;
}
```
