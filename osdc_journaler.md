## get_layout_period()

默认情况下返回一个对象的大小4M

## flush 流程

MDLog模块通过journaler->flush()来完成日志的下刷：

    Journaler::flush(Context *onsafe)
        \-Journaler::_flush(C_OnFinisher *onsafe)
            \-_do_flush();
            \-_wait_for_flush(onsafe);
    

* 少数几处调用Journaler::flush时onsafe参数不为NULL，正常的日志下刷可以认为就是不指定回调的，调用_flush时onsafe也是null。

* _fulsh() 主要调用_do_flush和wait_for_flush接口。


## _do_flush()

几个相关postion：

* prezero_pos : 预置为0的位置。
* write_pos   ：日志写入位置，下一条日志要写入，就从此处写入。
* flush_pos   ：将此处之前的日志落盘，完成落盘后safe_pos等于flush_pos。
* safe_pos    : 已经落盘的日志位置。

几个注意点：

* 在调用_do_flush时, 一定是 write_pos > flush_pos.(write_pos == flush_pos的情况已经在调用者_flush中处理)



    write_pos > flush_pos > saft_pos
    write_pos = flush_pos + write_buf.length()

## _wait_for_flush()

## _issue_prezero()

* 先找到置0的位置：比write_pos至少多num_periods个period（4M）的period整数倍的数值，设置为to。
* 只要prezeroing_pos没达到to，就每次一个perion得进行zero，如果一开始prezeroing_pos不是perion的整数倍，就先prezeroing_pos到整数倍。

