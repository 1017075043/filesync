./filesync: /lib64/libc.so.6: version `GLIBC_2.14' not found (required by ./filesync)
出现这个问题是应该 服务器的GLIBC版本过低,c++11最低要求GLIBC_2.14
请按照https://blog.csdn.net/h952520296/article/details/83856261这个博客进行升级
