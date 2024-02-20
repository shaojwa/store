def get_omap_vals(self, oid, start, prefix, max_return):
    with rados.ReadOpCtx(self.ioctx) as op:
        print("get_omap_vals obj [{}], start [{}], prefix [{}], max_return [{}]".format(oid, start, prefix, max_return))
        iter, ret = self.ioctx.get_omap_vals(op, start, prefix, max_return)
        self.ioctx.operate_read_op(op, oid)
        print("{}".format(list(iter)))
