#### process management
https://access.redhat.com/documentation/en-us/red_hat_ceph_storage/2/html/administration_guide/process_management

#### 1. Starting, Stopping, Restarting All Daemons
```
Start All Ceph Daemons
# systemctl start ceph.target

Stop All Ceph Daemons
# systemctl stop ceph.target

Restart All Ceph Daemons
# systemctl restart ceph.target
```

#### 2. Starting, Stopping, Restarting All Daemons by Type
```
Starting:
# systemctl start ceph-mon.target
# systemctl start ceph-osd.target

Stopping:
# systemctl stop ceph-mon.target
# systemctl stop ceph-osd.target

Restarting:
# systemctl restart ceph-mon.target
# systemctl restart ceph-osd.target
```

### 3. Starting, Stopping, Restarting a Daemon by Instances
Monitor Instance
```
Starting:
# systemctl start ceph-mon@<monitor_hostname>

Stopping:
# systemctl stop ceph-mon@<monitor_hostname>

Restarting:
# systemctl restart ceph-mon@<monitor_hostname>
```

OSD Instance
```
Starting:
# systemctl start ceph-osd@<OSD_number>

Stopping:
# systemctl stop ceph-osd@<OSD_number>

Restarting:
# systemctl restart ceph-osd@<OSD_number>
```
