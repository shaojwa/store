#### test code
```
 cout << " _cct "  << _cct << ", &(_cct->conf) " << &(_cct->_conf)
        << ", _cct->_conf " << _cct->_conf << ", _cct->_conf->log_switch "
        << &(_cct->_conf->log_switch) << endl;
```
#### result
```
_cct                    0x7f805b420800,
&(_cct->conf)           0x7f805b420808,
_cct->_conf             0x7f805b630000,
_cct->_conf->log_switch 0x7f805b630648

_conf 0ffset = 0x8
log_switch   = 0x288
```
