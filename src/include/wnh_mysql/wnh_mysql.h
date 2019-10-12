#ifndef __wnh_mysql__
#define __wnh_mysql__

using namespace std;

//使用mysql需要先安装mysql开发包mysql-devel,在centos可以使用命令:yum install -y mysql-devel
//并且需要在链接的时候加上编译代码:`mysql_config --cflags --libs`
//例如:
//链接:$(CC) -o $(EXEC) $(OBJS) $(LIB) -lcrypto `mysql_config --cflags --libs`

#include <mysql/mysql.h>

#include "../wnh_base_class/wnh_base_class.h"

class wnh_mysql : public wnh_base_class
{
private:
    MYSQL *mysql;        //连接mysql句柄指针

public:
    wnh_mysql();
    ~wnh_mysql();
    bool initDB(string host,string user,string pwd,string db_name); //连接mysql
    //bool exeSQL(string sql);   //执行sql语句
    bool exeSQL(string sql);   //执行sql语句,返回是否执行成功
    bool exeSQL(string sql, int &rows);   //执行sql语句,返回影响的行数
    MYSQL_ROW exeSQLs(string sql, int &rows);   //执行sql语句,返回一行结果
    MYSQL_RES * exeSQLs(string sql,int &list, int &rows);   //执行sql语句,返回多行结果
};

#endif

/*
在Linux下，我们可以通过MySQL提供的C API连接数据库。
使用C API连接mysql数据库除了要安装mysql-client和mysql-server，还需要安装mysql的开发包mysql-devel。
mysql-devel 开发用到的库以及包含文件
mysql mysql 客户端
mysql-server 数据库服务器
centos下安装命令如下：sudo yum install mysql-devel
ubuntu下安装命令：sudo apt-get install libmysqld-dev
然后加上<mysql/mysql.h>头文件就可以使用了。
想要具体了解C API函数的可以参考官方文档：官方mysql C API函数说明：https://dev.mysql.com/doc/refman/5.7/en/c-api-functions.html

常用函数
MYSQL *mysql_init(MYSQL *mysql)     获取或初始化MYSQL结构
MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)    连接到MySQL服务器。
int mysql_query(MYSQL *mysql, const char *stmt_str)    执行指定为“以Null终结的字符串”的SQL查询。
MYSQL_RES *mysql_store_result(MYSQL *mysql)    将查询的整个结果读取到客户端，分配一个 MYSQL_RES结构，并将结果放入此结构中
unsigned int mysql_field_count(MYSQL *mysql)    返回上次执行语句的结果集的列数。
unsigned int mysql_num_fields(MYSQL_RES *result)    返回结果集中的列数。
my_ulonglong mysql_num_rows(MYSQL_RES *result)    返回结果集中的行数。
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)    从结果集中获取下一行数据
void mysql_free_result(MYSQL_RES *result)    释放结果集空间

相关数据结构
MYSQL结构体        此结构表示一个数据库连接的处理程序。它几乎用于所有MySQL功能。
MYSQL_RES结构体     存储查询结果数据。
MYSQL_ROW结构体     存储一行数据的结构

相关函数的介绍
1.mysql_init（）
分配或初始化MYSQL适合的对象 mysql_real_connect()。如果 mysql是nullptr指针，则该函数分配，初始化并返回一个新对象。否则，对象被初始化并返回对象的地址。如果 mysql_init()分配一个新的对象，当mysql_close()被调用来关闭该连接时它被释放 。如果没有足够的内存分配一个新对象,则返回nullptr。
2. mysql_query（）
执行指定为“以Null终结的字符串”的SQL查询。查询成功返回0，失败返回非0值。
3.mysql_field_count（）
返回连接上最近查询的列数。
这个函数的正常使用是 mysql_store_result()返回 nullptr（因此你没有结果集指针）。在这种情况下，您可以调用 mysql_field_count()确定是否 mysql_store_result()应该产生非空结果。这使得客户端程序能够在不知道查询是SELECT（或 类似SELECT））语句的情况下采取适当的操作。此处显示的示例说明了如何完成此操作。如果不理解的话，看完后面的代码示例就理解了。

基本步骤就是
使用mysql_init()初始化连接
使用mysql_real_connect()建立一个到mysql数据库的连接
使用mysql_query()执行查询语句
result = mysql_store_result(mysql)获取结果集
mysql_num_fields(result)获取查询的列数，mysql_num_rows(result)获取结果集的行数
通过mysql_fetch_row(result)不断获取下一行，然后循环输出
释放结果集所占内存mysql_free_result(result)
mysql_close(conn)关闭连接

（1）所需头文件： #include <mysql/mysql.h>
     功能： 获得或初始化一个MYSQL结构
     函数原型： MYSQL *mysql_init(MYSQL *mysql)
     函数返回值： 一个被始化的MYSQL*句柄
     备注： 在内存不足的情况下，返回nullptr

（2）所需头文件： #include <mysql/mysql.h>
     函数功能： 关闭一个服务器连接，并释放与连接相关的内存
     函数原型：void mysql_close(MYSQL *mysql);
     函数传入值： MYSQL:类型的指针
     函数返回值： 无

（3）所需头文件： #include <mysql/mysql.h>
     函数功能： 连接一个MySQL服务器
     函数原型： MYSQL * mysql_connect(MYSQL *mysql,constchar *host,constchar *user,constchar *passwd);
     函数传入值：
         mysql表示一个现存mysql结构的地址
         host表示MYSQL服务器的主机名或IP
         user表示登录的用户名
         passwd表示登录的密码
     函数返回值： 如果连接成功，一个MYSQL *连接句柄：如果连接失败，nullptr
     备注： 该函数不推荐，使用mysql_real_connect()代替

（4）所需头文件： #include <mysql/mysql.h>
     函数原型： MYSQL *mysql_real_connect(MYSQL *mysql,constchar *host,constchar *user,constchar *passwd,const        char*db,unsigned intport,const char *unix_socket,unsigned intclient_flag);
     函数传入值：
         mysql表示一个现存mysql结构的地址
         host表示MYSQL服务器的主机名或IP
         user表示登录的用户名
         passwd表示登录的密码
         db表示要连接的数据库
         port表示MySQL服务器的TCP/IP端口
         unix_socket表示连接类型
         client_flag表示MySQL运行ODBC数据库的标记
     函数返回值： 如果连接成功，一个MYSQL*连接句柄：如果连接失败，nullptr

（5）所需头文件： #include <mysql/mysql.h>
     函数功能： 返回最新的UPDATE，DELETE或INSERT查询影响的行数
     函数传入值： MYSQL:类型指针
     函数返回值： 大于零的一个整数表示受到影响或检索出来的行数。零表示没有区配查序中WHERE子句的记录或目前还没有查询      被执行;-1表示查询返回一个错误，或对于一个SELECT查询

（6）所需头文件： #include <mysql/mysql.h>
     函数功能： 对指定的连接执行查询
     函数原型：int mysql_query(MYSQL *mysql,constchar *query);
     函数传入值： query表示执行的SQL语句
     函数返回值： 如果查询成功，为零，出错为非零。
     相关函数： mysql_real_query

（7）所需头文件： #include <mysql/mysql.h>
     函数功能： 为无缓冲的结果集获得结果标识符
     函数原型： MYSQL_RES *mysql_use_result(MYSQL *mysql);
     函数传入值： MYSQL:类型的指针
     函数返回值： 一个MYSQL_RES结果结构，如果发生一个错误发nullptr

（8）所需头文件：#incluee <mysql/mysql.h>
     函数功能：检索一个结果集合的下一行
     函数原型：MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
     函数传入值：MYSQL_RES:结构的指针
     函数返回值：下一行的一个MYSQL_ROW结构。如果没有更多的行可检索或如果出现一个错误，nullptr

（9）所需头文件：#include <mysql/mysql.h>
     函数功能：指定结果集中列的数量
     函数原型：unsignedint mysql_num_fields(MYSQL_RES *res);
     函数传入值：MYSQL_RES 结构的指针
     函数返回值：结果集合中字段数量的一个无符号整数

（10）所需头文件：#include <mysql/mysql.h>
      函数功能：创建一个数据库
      函数原型：intmysql_create_db(MYSQL *mysql,constchar *db);
      函数传入值：
          MYSQL：类型的指针
          db:要创建的数据库名
      函数返回值：如果数据库成功地被创建，返回零，如果发生错误，为非零。

（11）所需头文件：#include <mysql/mysql.h>
          函数功能：选择一个数据库
      函数原型：int mysql_select_db(MYSQL *mysql,const char *db);
      函数传入值：
          MYSQL：类型的指针
          db:要创建的数据库名
     函数返回值：如果数据库成功地被创建，返回零，如果发生错误，为非零。
*/
