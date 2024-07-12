maybe we have several steps in a transaction, and sometime we need to refer to some critical data in changing, such as engine map or osd map.
we should make sure that we always refer to the identical data, or we may make the program error-prone. such as the following scenario:

we use the latest version of critical-data to submit, but using the old version to calculate the target to submit.
maybe the old target will ignore the requests but not return the errorcode because of the latest version the request with.

if the target recived the request with the old version, in most cases the target will tell to retry insteed of ignoring.
