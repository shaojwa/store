测试代码：
```
 cout << " _cct "  << _cct << ", &(_cct->conf) " << &(_cct->_conf)
        << ", _cct->_conf " << _cct->_conf << ", _cct->_conf->log_switch "
        << &(_cct->_conf->log_switch) << endl;
```
结果：
```
_cct                    0x7f805b420800,
&(_cct->conf)           0x7f805b420808,
_cct->_conf             0x7f805b630000,
_cct->_conf->log_switch 0x7f805b630648
```
