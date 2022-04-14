#### ACID VS BASE
|ACID|BASE|
|:-|:-|
|strong consistency| weak consistency (stale data ok)|
|Isolation||
|Focus on commit| Availability first|
|Nested transaction|Best effort|
|Availability?|Approximate answers OK|
|Conservative(pessimistic)|Aggressive(optimistic)|
||Simpler|
||Faster|
|Difficult evolution|Easier evolution |

```
CAP Take Homes CAP Take Homes
 Can have consistency & availability within a cluster, but it is still hard in practice.
 OS/Networking good at OS/Networking, but BASE/Availability.
 Databases better at C than Availability.
 Wide-area databases can’t have both.
 Disconnected clients can’t have both.
 All systems are probabilistic…
```
