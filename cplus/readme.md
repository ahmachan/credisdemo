首先上网站下载hiredis.tar.gz包，解压后发现里面有一个Makefile文件，然后执行make进行编译.
接下来把libhiredis.so放到/usr/local/lib/中，把hiredis.h放到/usr/local/inlcude/hiredis/中。
或者直接用命令make install配置。

编译代码：
gcc -o testhiredis testhiredis.c -L/usr/local/lib -lhiredis
或者：
g++ testhiredis.c -o testhiredis  -L/usr/local/lib -lhiredis

其中的-L参数指定 gcc 的库文件的搜索路径，在这里为/usr/local/lib。/usr/local/lib包含了 hiredis 的库文件。
-l参数则指明使用的库文件，-lhiredis的意思即是搜索libhiredis.a的库文件。
1.libhiredis.a实际上已安装在/usr/local/lib目录下了。
(如果使用libhiredis.so动态库，则在/etc/ld.so.conf.d/目录的libc.conf或usr-libs.conf的最后加上一句:/usr/local/lib,然后/sbin/ldconfig更新一下配置)
2.将这三头文件hiredis.h  read.h  sds.h 放到/usr/local/include/hiredis目录下

Makefile文件
redis: redis.cpp redis.h
     g++ redis.cpp -o redis -L/usr/local/lib/ -lhiredis
clean:
     rm redis.o redis

注意在g++和rm之前都是一个tab键。

在编译的时候需要加参数，假设文件为redis.cpp，那么编译命令如下:
g++ redis.cpp -o redis -L/usr/local/lib/ -lhiredis

在/etc/ld.so.conf.d/目录下新建文件usr-libs.conf，内容是：/usr/local/lib

在执行的时候如果出现动态库无法加载,如“libhiredis.so.0.10”，这是因为程序启动时,需要更新一下库的cache，会去/etc/ld.so.cache来查找所要用的库，
不然会出现如下错误：error while loading shared libraries: libhiredis.so.0.10: cannot open shared object file: No such file or directory。
执行命令：sudo ldconfig /usr/local/lib/,也可能是sudo ldconfig /usr/lib/

或者直接使用命令/sbin/ldconfig更新一下配置即可。


主要包括如下四个方法

1. redisContext* redisConnect(const char *ip, int port)

该函数用来连接redis数据库， 两个参数分别是redis数据库的ip和端口，端口号一般为6379。类似的还提供了一个函数，供连接超时限定，即

redisContext* redisConnectWithTimeout(const char *ip, int port, timeval tv)。

2. void *redisCommand(redisContext *c, const char *format...)

该函数用于执行redis数据库中的命令，第一个参数为连接数据库返回的redisContext，剩下的参数为变参，如同C语言中的prinf()函数。此函数的返回值为void*，但是一般会强制转换为redisReply类型，以便做进一步的处理。

3. void freeReplyObject(void *reply)

释放redisCommand执行后返回的的redisReply所占用的内存。

4. void redisFree(redisContext *c)

释放redisConnect()所产生的连接
