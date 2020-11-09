#! /bin/bash

mds_id=$(basename $(ls /var/lib/ceph/mds/)  | egrep -o mds[0-9])
echo "mds-id is ${mds_id}"

#cephfs-journal-tool journal reset
#ceph mds repaired 0

echo "reset-failed"
systemctl reset-failed ceph-mds@${mds_id}.service
echo "restart"
systemctl restart ceph-mds.target
