## journaler 的操作

journaler操作分两大类，可以在journaler.h中看到 Asynchronous operations 和 Synchronous setters

其中flush，wait_for_flush 都是异步操作，都有回调参数。

### journaler的flush 

journaler->flush()来完成日志的落盘：

    Journaler::flush(Context *onsafe)
        \-Journaler::_flush(C_OnFinisher *onsafe)
            \-_do_flush();
            \-_wait_for_flush(onsafe);
    

* 少数几处调用Journaler::flush时onsafe参数不为NULL，正常的日志下刷一般不指定回调的，调用_flush时onsafe也是null。

* _fulsh() 主要调用_do_flush和wait_for_flush接口。

#### 问题：journaler->flush()参数onsafe，但为什么没看到带参数的调用？

只有一处，恢复线程_recovery_thread中的 _reformat_journal()接口中的 new_journal->flush(&flush_waiter)

在正常流程下，journaler->flush() 接口都不需要回调，但是 _wait_for_flush() 一般都有。

#### _do_flush()

主要工作：commit日志，调用filer.write() 接口进行日志落盘。

几个相关位置：

* prezero_pos: 预置为0的位置。
* write_pos: 日志写入位置，下一条日志要写入，就从此处写入。
* flush_pos: 将此处之前的日志落盘，完成落盘后safe_pos等于flush_pos。
* safe_pos : 已经落盘的日志位置。

几个注意点：

1. 在调用_do_flush时, 一定是 write_pos > flush_pos.(write_pos == flush_pos的情况已经在调用者_flush中处理)
2. 需要要求flush_pos + len 的位置应该距离 prezero_pos 至少两个 perion (默认情况下一个perion=4M)
3. 如果flush_pos + len 的位置不满足条件，且flush_pos + period 距离大于 prezero_pos，那么返回等待perzero完成。
4. 如果flush_pos + len 的位置不满足条件，且flush_pos + period 距离 prezero_pos 小于len，那么会先flush一部分（导致有的entry被部分flush）。
5. 调整next_safe_pos
6. filer.write进行flush

#### _wait_for_flush()

把回调上下文放到队列中，日志落盘完成后会调用这里设置的回调函数。

#### 回调上下文的处理 waitfor_safe map

waitfor_safe 存储从write_pos -> list<context>的映射，用来在日志落盘之后的处理流程获取回调上下文。

    C_Flush->finish()
        \- ls->_finish_flush()


#### 回调上下文处理 pending_safe 

pending_safe 存储flush_pos -> safe_pos

flush_pos 已经flush的位置，即在journaler中的位置。safe_pos 已经落盘的位置，所以 safe_pos < flush_pos.

在_do_flush 中设置 pending_safe[flush_pos] = next_safe_pos;

### _issue_prezero()

* 先找到置0的位置：比write_pos至少多num_periods个period（4M）的period整数倍的数值，设置为to。
* 只要prezeroing_pos没达到to，就每次一个perion得进行zero，如果一开始prezeroing_pos不是perion的整数倍，就先prezeroing_pos到整数倍。

## get_layout_period()

默认情况下返回一个对象的大小4M
