```
[root@node118 ceph]# ceph tell mds.mds0 config set debug_mds -1
2020-05-09 12:00:24.387187 7f4b79e27740 2798932 63  INFO client.0  opmbatcher init
2020-05-09 12:00:24.387297 7f4b35ffb700 2799044 4 DEBUG client.0  opmbatcher _work_thread_routine start
2020-05-09 12:00:24.387789 7f4b357fa700 2799045 19 DEBUG client.0 ms_handle_connect on 55.55.57.118:6789/0
2020-05-09 12:00:24.387885 7f4b357fa700 2799045 19 DEBUG client.0 ms_handle_connect on 55.55.57.120:6789/0
2020-05-09 12:00:24.388058 7f4b357fa700 2799045 19 DEBUG client.0 ms_handle_connect on 55.55.57.119:6789/0
2020-05-09 12:00:24.388966 7f4b79e27740 2798932 63 DEBUG client.8230374 fetch_fsmap learned FSMap version 483
2020-05-09 12:00:24.389159 7f4b79e27740 2798932 63 DEBUG client.8230374 fetch_fsmap finished waiting for FSMap version 483
2020-05-09 12:00:24.389169 7f4b79e27740 2798932 63 DEBUG client.8230374 resolve_mds: resolved ID 'mds0' to GID 5141404
2020-05-09 12:00:24.389212 7f4b79e27740 2798932 63 DEBUG client.8230374 mds_command: new command op to 5141404 tid=0[{"prefix": "get_command_descriptions"}]
2020-05-09 12:00:24.389531 7f4b357fa700 2799045 19 DEBUG client.8230374 ms_handle_connect on 55.55.57.118:6813/813882857
2020-05-09 12:00:24.389913 7f4b357fa700 2799045 19 DEBUG client.8230374 handle_command_reply: tid=0
2020-05-09 12:00:24.389956 7f4b79e27740 2798932 63  INFO client.8230374 shutdown
2020-05-09 12:00:24.390130 7f4b79e27740 2798932 63  INFO client.0  opmbatcher shutdown
2020-05-09 12:00:24.390625 7f4b357fa700 2799045 19 WARNING client.8230374 ms_handle_reset on 55.55.57.118:6813/813882857
2020-05-09 12:00:24.423056 7f4b79e27740 2798932 63  INFO client.0  opmbatcher init
2020-05-09 12:00:24.423116 7f4b357fa700 2799085 54 DEBUG client.0  opmbatcher _work_thread_routine start
2020-05-09 12:00:24.423574 7f4b34ff9700 2799086 40 DEBUG client.0 ms_handle_connect on 55.55.57.118:6789/0
2020-05-09 12:00:24.423701 7f4b34ff9700 2799086 40 DEBUG client.0 ms_handle_connect on 55.55.57.119:6789/0
2020-05-09 12:00:24.423704 7f4b34ff9700 2799086 40 DEBUG client.0 ms_handle_connect on 55.55.57.120:6789/0
2020-05-09 12:00:24.424633 7f4b79e27740 2798932 63 DEBUG client.8230377 fetch_fsmap learned FSMap version 483
2020-05-09 12:00:24.424800 7f4b79e27740 2798932 63 DEBUG client.8230377 fetch_fsmap finished waiting for FSMap version 483
2020-05-09 12:00:24.424811 7f4b79e27740 2798932 63 DEBUG client.8230377 resolve_mds: resolved ID 'mds0' to GID 5141404
2020-05-09 12:00:24.424854 7f4b79e27740 2798932 63 DEBUG client.8230377 mds_command: new command op to 5141404 tid=0[{"prefix": "config set", "key": "debug_mds", "value": "-1"}]
2020-05-09 12:00:24.425146 7f4b34ff9700 2799086 40 DEBUG client.8230377 ms_handle_connect on 55.55.57.118:6813/813882857
2020-05-09 12:00:24.428079 7f4b34ff9700 2799086 40 DEBUG client.8230377 handle_command_reply: tid=0
2020-05-09 12:00:24.428122 7f4b79e27740 2798932 63  INFO client.8230377 shutdown
2020-05-09 12:00:24.428294 7f4b79e27740 2798932 63  INFO client.0  opmbatcher shutdown
2020-05-09 12:00:24.428809 7f4b34ff9700 2799086 40 WARNING client.8230377 ms_handle_reset on 55.55.57.118:6813/813882857
```
