```
commit 701ae00462386f5f12080d43116cc6671b6bb7be
Author: Sage Weil <sage@newdream.net>
Date:   Mon Dec 22 19:09:39 2008 -0800

    mds: fix inotable project, sessionmap projection, ino (pre)allocation.

    Table changes must be projected so that the saved table is never
    newer than the end of the journal.
```
