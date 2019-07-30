#### reset used 

    #!/opt/bin/python2.7

    import rados
    import sys
    import struct

    _CLUSTER_CONFFILE = '/etc/ceph/ceph.conf'
    META_POOL_KEY = 'Metadata'
    MAX_NORMAL_QUOTA_COUNT = 4096
    MAX_DEFAULT_QUOTA_COUNT = 1024
    QUOTA_OBJ_NAME = 'quota'
    fmt = '=2BIQB3QI2QB'

    class QuotaValST:
        def __init__(self):
            pass
        VERSION = 0
        COMPAT = 1
        LENGTH = 2
        CREATETIME = 3
        METHOD = 4
        HARD = 5
        WARN = 6
        SOFT = 7
        EXTEND = 8
        SOFTHIT = 9
        USED = 10
        ALARM = 11


    def list_quota_kvs():
        """
        """
        omap_list = []
        start_after = ''
        filter_prefix = ''
        try:
            with rados.Rados(conffile=_CLUSTER_CONFFILE) as cluster:
                pool_list = cluster.list_pools()
                meta_pool = [p for p in pool_list if META_POOL_KEY in p][0]
                with cluster.open_ioctx(meta_pool) as ioctx:
                    with rados.ReadOpCtx(ioctx) as read_op:
                        ret = ioctx.get_omap_vals(read_op, start_after, filter_prefix,
                                                  MAX_NORMAL_QUOTA_COUNT + MAX_DEFAULT_QUOTA_COUNT)
                        ioctx.operate_read_op(read_op, QUOTA_OBJ_NAME)
                        omap_list = list(ret[0])
            return omap_list
        except rados.ObjectNotFound:
            print('there is no quota object: {}'.format(QUOTA_OBJ_NAME))
            raise e
        except rados.TimedOut:
            print('read omap timed out')
            raise e
        except Exception as e:
            print('caught exception with message: {}'.format(e))
            raise e


    def quota_get_value_by_key(key):
        """
        """
        value_list = []
        try:
            with rados.Rados(conffile=_CLUSTER_CONFFILE) as cluster:
                pool_list = cluster.list_pools()
                meta_pool = [p for p in pool_list if META_POOL_KEY in p][0]
                with cluster.open_ioctx(meta_pool) as ioctx:
                    with rados.ReadOpCtx(ioctx) as read_op:
                        ret = ioctx.get_omap_vals_by_keys(read_op, (key,))
                        ioctx.operate_read_op(read_op, QUOTA_OBJ_NAME)
                        value_list = list(ret[0])
            return value_list
        except rados.ObjectNotFound:
            print('there is no quota object: {}'.format(QUOTA_OBJ_NAME))
            raise e
        except rados.TimedOut:
            print('read omap timed out')
            raise e
        except Exception as e:
            print('caught exception with message: {}'.format(e))
            raise e


    def set_quota_value_by_key(key, value):
        """
        """
        try:
            with rados.Rados(conffile=_CLUSTER_CONFFILE) as cluster:
                pool_list = cluster.list_pools()
                meta_pool = [p for p in pool_list if META_POOL_KEY in p][0]
                with cluster.open_ioctx(meta_pool) as ioctx:
                    with rados.WriteOpCtx(ioctx) as write_op:
                        ret = ioctx.set_omap(write_op, (key,), (value,))
                        ioctx.operate_write_op(write_op, QUOTA_OBJ_NAME)
        except rados.ObjectNotFound:
            print('there is no quota object: {}'.format(QUOTA_OBJ_NAME))
            raise e
        except rados.TimedOut:
            print('read omap timed out')
            raise e
        except Exception as e:
            print('caught exception with message: {}'.format(e))


    def quota_decode_value(value):
        """
        """
        try:
            value_items = struct.unpack(fmt, value)
            return value_items
        except Exception as e:
            print('quota decode exception occurs: {}'.format(e))
            raise e


    def quota_encode_value(value_items):
        """
        """
        try:
            # print('value_items: {}'.format(value_items))
            new_value = struct.pack(fmt, *value_items)
            return new_value
        except Exception as e:
            print('quota decode exception occurs: {}'.format(e))
            raise e


    def quota_query_all():
        quota_list = list_quota_kvs()
        for quota_kv in quota_list:
            value = quota_decode_value(quota_kv[1])
            print("quota: key: {}, value: {}".format(quota_kv[0], value))


    def quota_query_spec(key):
        value_list = quota_get_value_by_key(key)
        if len(value_list) == 0: 
            print("ERROR: no such quota key: {}".format(key))
            return
        value_items = quota_decode_value(value_list[0][1])
        print("quota: key: {}, value: {}".format(key, value_items))


    def quota_set_used(key, used):
        """
        """
        value_list = quota_get_value_by_key(key)
        if len(value_list) == 0: 
            print("ERROR: no such quota key: {}".format(key))
            return
        value_items = quota_decode_value(value_list[0][1])
        item_list = list(value_items)
        item_list[QuotaValST.USED] = used
        new_value = quota_encode_value(item_list)
        set_quota_value_by_key(key, new_value)


    def usage():
        print("Usage:\n"
              "\t{0} query [all]\n"
              "\t{0} query <key>\n"    
              "\t{0} set-used <key> <used>".format(sys.argv[0])) 
        return 

    def main():
        if len(sys.argv) == 1:
            return usage()
        if sys.argv[1] == "query":
            if len(sys.argv) == 2 or sys.argv[2] == "all": 
                quota_query_all()
            else:
                quota_query_spec(sys.argv[2])
        elif sys.argv[1] == "set-used":
            if len(sys.argv) < 4: 
                return usage()
            key = sys.argv[2]
            used = sys.argv[3]
            quota_set_used(key, int(used))
        else:
            return usage()

    if __name__ == '__main__' :
        retval = main()
        sys.exit(retval)
