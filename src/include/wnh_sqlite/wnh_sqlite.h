#ifndef __wnh_sqlite__
#define __wnh_sqlite__

using namespace std;

//  需要先在linux环境下安装sqlite,步骤如下
//  tar -zxvf sqlite-autoconf-3280000.tar.gz
//  ./configure && make && make install
//  在编译连接时需要加上-l sqlite3, 例如$(CC) -o $(EXEC) $(OBJS) $(LIB) -lcrypto `mysql_config --cflags --libs` -lsqlite3

#include "sqlite3.h"
#include "../wnh_base_class/wnh_base_class.h"

class wnh_sqlite : public wnh_base_class
{
private:
    sqlite3 *db;//数据库句柄
    char *zErrMsg;//记录错误信息
    string sql;

public:
    wnh_sqlite();
    ~wnh_sqlite();
    bool create_db(const string &db_name);//创建一个数据库
    bool sql_query(string sql);//执行一条不会有结果返回的sql语句
    bool sql_query(string sql, string &result);//执行一条有一个结果返回的sql语句
    bool sql_query(string sql, string *&result, int &ncolumn);//执行一条有一行结果返回的sql语句
    bool sql_query(string sql, string **&result, int &nrow ,int &ncolumn);//执行一条有多行结果返回的sql语句

    string sqlite_escape(string sql);
};

#endif

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*  使用上面的步骤安装好sqlite后信息如下:                                                                                                                    */
/*  sqlite的库文件: libsqlite3.a  libsqlite3.la  libsqlite3.so  libsqlite3.so.0  libsqlite3.so.0.8.6  pkgconfig                                              */
/*  可执行文件: sqlite3                                                                                                                                      */
/*                                                                                                                                                           */
/*  sqlite3的库文件目录是：/usr/local/lib                                                                                                                    */
/*  可执行文件 sqlite3 的目录是： /usr/local/bin                                                                                                             */
/*  头文件 sqlite3.h 的目录是： /usr/local/include                                                                                                           */
/*                                                                                                                                                           */
/*  用ls命令查看如下：                                                                                                                                       */
/*  [root@localhost config]# ls /usr/local/lib                                                                                                               */
/*  libclamav.a         libclamunrar_iface.a         libclamunrar.so        libsqlite3.so                                                                    */
/*  libclamav.la        libclamunrar_iface.la        libclamunrar.so.5      libsqlite3.so.0                                                                  */
/*  libclamav.so        libclamunrar_iface.so        libclamunrar.so.5.0.3  libsqlite3.so.0.8.6                                                              */
/*  libclamav.so.5      libclamunrar_iface.so.5      libmstring.so          pkgconfig                                                                        */
/*  libclamav.so.5.0.3  libclamunrar_iface.so.5.0.3  libsqlite3.a                                                                                            */
/*  libclamunrar.a      libclamunrar.la              libsqlite3.la                                                                                           */
/*                                                                                                                                                           */
/*  此目录下包含库文件: libsqlite3.a  libsqlite3.la  libsqlite3.so  libsqlite3.so.0  libsqlite3.so.0.8.6  pkgconfig                                          */
/*                                                                                                                                                           */
/*  如果我们在编译安装的时候，选择了安装路径，例如这样的话: ./configure --prefix=/usr/local/sqlite3                                                          */
/*  这样编译安装时，sqlite的库文件将会生成在 /usr/local/sqlite3/lib 目录下                                                                                   */
/*  sqlite的头文件将会生成在 /usr/local/sqlite3/include 目录下                                                                                               */
/*  这时编译还要指定库文件路径，因为系统默认的路径没有包含 /usr/local/sqlite3/lib                                                                            */
/*  [root@localhost temp]# gcc opendbsqlite.c -o db.out -lsqlite3 -L/usr/local/sqlite3/lib                                                                   */
/*  如果还不行的话，可能还需要指定头文件 sqlite3.h 的路径，如下：                                                                                            */
/*  [root@localhost temp]# gcc opendbsqlite.c -o db.out -lsqlite3 -L/usr/local/sqlite3/lib -I/usr/local/sqlite3/include                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*  sqlite3使用范例 https://www.cnblogs.com/lzjsky/p/3688324.html                                                                                            */
/*  #include <stdio.h>                                                                                                                                       */
/*  #include <stdlib.h>                                                                                                                                      */
/*  #include "sqlite3.h"                                                                                                                                     */
/*                                                                                                                                                           */
/*  int main( void )                                                                                                                                         */
/*  {                                                                                                                                                        */
/*      sqlite3 *db=nullptr;                                                                                                                                    */
/*      char *zErrMsg = 0;                                                                                                                                   */
/*      int rc;                                                                                                                                              */
/*      rc = sqlite3_open("sqlite3.db", &db); //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件                                                    */
/*      if( rc )                                                                                                                                             */
/*      {                                                                                                                                                    */
/*          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));                                                                                */
/*          sqlite3_close(db);                                                                                                                               */
/*          exit(1);                                                                                                                                         */
/*      }                                                                                                                                                    */
/*      else                                                                                                                                                 */
/*      {                                                                                                                                                    */
/*          printf("You have opened a sqlite3 database named sqlite3.db successfully!\nCongratulations! Have fun !  ^-^ \n");                                */
/*      }                                                                                                                                                    */
/*      //创建一个表,如果该表存在，则不创建，并给出提示信息，存储在 zErrMsg 中                                                                               */
/*      char *sql = (char *)"CREATE TABLE SensorData( ID INTEGER PRIMARY KEY, SensorID INTEGER, SiteNum INTEGER, Time VARCHAR(12), SensorParameter REAL );"; */
/*      printf("sql = %s\n", sql);                                                                                                                           */
/*      sqlite3_exec( db , sql , 0 , 0 , &zErrMsg);                                                                                                          */
/*      if(zErrMsg != nullptr)                                                                                                                                  */
/*      {                                                                                                                                                    */
/*          printf("%s\n",zErrMsg);                                                                                                                          */
/*      }                                                                                                                                                    */
/*      //插入数据                                                                                                                                           */
/*      char* sql1 = (char *)"INSERT INTO \"SensorData\" VALUES( nullptr , 1 , 1 , '200605011206', 18.9 );";                                                    */
/*      sqlite3_exec( db , sql1 , 0 , 0 , &zErrMsg );                                                                                                        */
/*      if(zErrMsg != nullptr)                                                                                                                                  */
/*      {                                                                                                                                                    */
/*          printf("%s\n",zErrMsg);                                                                                                                          */
/*      }                                                                                                                                                    */
/*      char* sql2 = (char *)"INSERT INTO \"SensorData\" VALUES( nullptr , 1 , 1 , '200605011306', 16.4 );";                                                    */
/*      sqlite3_exec( db , sql2 , 0 , 0 , &zErrMsg );                                                                                                        */
/*      if(zErrMsg != nullptr)                                                                                                                                  */
/*      {                                                                                                                                                    */
/*          printf("%s\n",zErrMsg);                                                                                                                          */
/*      }                                                                                                                                                    */
/*                                                                                                                                                           */
/*      int nrow = 0, ncolumn = 0;                                                                                                                           */
/*      char **azResult; //二维数组存放结果                                                                                                                  */
/*      //查询数据                                                                                                                                           */
/*                                                                                                                                                           */
/*      int sqlite3_get_table(sqlite3*, const char *sql,char***result , int *nrow , int *ncolumn ,char **errmsg );                                           */
/*      result中是以数组的形式存放你所查询的数据，首先是表名，再是数据。                                                                                     */
/*      nrow ,ncolumn分别为查询语句返回的结果集的行数，列数，没有查到结果时返回0                                                                             */
/*                                                                                                                                                           */
/*      sql = (char *)"SELECT * FROM SensorData ";                                                                                                           */
/*      sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );                                                                             */
/*      printf( "row:%d column=%d \n" , nrow , ncolumn );                                                                                                    */
/*      printf( "The result of querying is : \n" );                                                                                                          */
/*                                                                                                                                                           */
/*      for(int i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )                                                                                                       */
/*      {                                                                                                                                                    */
/*          printf( "%s | " , azResult[i] );                                                                                                                 */
/*          if((i+1) % ncolumn == 0 && i != 0)                                                                                                               */
/*          {                                                                                                                                                */
/*              printf( "\n|");                                                                                                                              */
/*          }                                                                                                                                                */
/*          if(i == 0)                                                                                                                                       */
/*          {                                                                                                                                                */
/*              printf( "|");                                                                                                                                */
/*          }                                                                                                                                                */
/*      }                                                                                                                                                    */
/*      //释放掉  azResult 的内存空间                                                                                                                        */
/*      sqlite3_free_table( azResult );                                                                                                                      */
/*                                                                                                                                                           */
/*      if(zErrMsg != nullptr)                                                                                                                                  */
/*      {                                                                                                                                                    */
/*          printf("%s\n",zErrMsg);                                                                                                                          */
/*      }                                                                                                                                                    */
/*                                                                                                                                                           */
/*      //删除数据                                                                                                                                           */
/*      sql = "DELETE FROM SensorData WHERE SensorID = 1 ;" ;                                                                                                */
/*      sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );                                                                                                         */
/*      if(zErrMsg != nullptr)                                                                                                                                  */
/*      {                                                                                                                                                    */
/*          printf("%s\n",zErrMsg);                                                                                                                          */
/*      }                                                                                                                                                    */
/*                                                                                                                                                           */
/*      sql = (char *)"SELECT * FROM SensorData;";                                                                                                           */
/*      sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );                                                                             */
/*      printf( "row:%d column=%d \n" , nrow , ncolumn );                                                                                                    */
/*      printf( "\nThe result of querying is : \n" );                                                                                                        */
/*                                                                                                                                                           */
/*      for(int i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )                                                                                                       */
/*      {                                                                                                                                                    */
/*          printf( "%s | " , azResult[i] );                                                                                                                 */
/*          if((i+1) % ncolumn == 0 && i != 0)                                                                                                               */
/*          {                                                                                                                                                */
/*              printf( "\n|");                                                                                                                              */
/*          }                                                                                                                                                */
/*          if(i == 0)                                                                                                                                       */
/*          {                                                                                                                                                */
/*              printf( "|");                                                                                                                                */
/*          }                                                                                                                                                */
/*      }                                                                                                                                                    */
/*      //释放掉  azResult 的内存空间                                                                                                                        */
/*      sqlite3_free_table( azResult );                                                                                                                      */
/*                                                                                                                                                           */
/*      sqlite3_close(db); //关闭数据库                                                                                                                      */
/*      return 0;                                                                                                                                            */
/*  }                                                                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*  sqlite3 安装使用方法 https://www.jb51.net/article/44545.htm                                                                                              */
/*  1、安装sqlite3                                                                                                                                           */
/*                                                                                                                                                           */
/*  ubuntu下安装sqlite3直接在终端运行命令：                                                                                                                  */
/*  #apt-get install sqlite3                                                                                                                                 */
/*  查看版本信息：                                                                                                                                           */
/*  #sqlite3 -version                                                                                                                                        */
/*                                                                                                                                                           */
/*  2 、sqlite3常用命令                                                                                                                                      */
/*  当前目录下建立或打开test.db数据库文件，并进入sqlite命令终端，以sqlite>前缀标识：                                                                         */
/*  #sqlite3 test.db                                                                                                                                         */
/*                                                                                                                                                           */
/*  查看数据库文件信息命令(注意命令前带字符'.')：                                                                                                            */
/*  sqlite>.database                                                                                                                                         */
/*                                                                                                                                                           */
/*  查看所有表的创建语句：                                                                                                                                   */
/*  sqlite>.schema                                                                                                                                           */
/*                                                                                                                                                           */
/*  查看指定表的创建语句：                                                                                                                                   */
/*  sqlite>.schema table_name                                                                                                                                */
/*                                                                                                                                                           */
/*  以sql语句的形式列出表内容：                                                                                                                              */
/*  sqlite>.dump table_name                                                                                                                                  */
/*                                                                                                                                                           */
/*  设置显示信息的分隔符：                                                                                                                                   */
/*  sqlite>.separator symble                                                                                                                                 */
/*  Example：设置显示信息以‘：'分隔                                                                                                                          */
/*  sqlite>.separator :                                                                                                                                      */
/*                                                                                                                                                           */
/*  设置显示模式：                                                                                                                                           */
/*  sqlite>.mode mode_name                                                                                                                                   */
/*  Example:默认为list，设置为column，其他模式可通过.help查看mode相关内容                                                                                    */
/*  sqlite>.mode column                                                                                                                                      */
/*                                                                                                                                                           */
/*  输出帮助信息：                                                                                                                                           */
/*  sqlite>.help                                                                                                                                             */
/*                                                                                                                                                           */
/*  设置每一列的显示宽度：                                                                                                                                   */
/*  sqlite>.width width_value                                                                                                                                */
/*  Example:设置宽度为2                                                                                                                                      */
/*  sqlite>.width 2                                                                                                                                          */
/*                                                                                                                                                           */
/*  列出当前显示格式的配置：                                                                                                                                 */
/*  sqlite>.show                                                                                                                                             */
/*                                                                                                                                                           */
/*  退出sqlite终端命令：                                                                                                                                     */
/*  sqlite>.quit                                                                                                                                             */
/*  或                                                                                                                                                       */
/*  sqlite>.exit                                                                                                                                             */
/*                                                                                                                                                           */
/*  3、sqlite3指令                                                                                                                                           */
/*  sql的指令格式：所有sql指令都是以分号(;)结尾，两个减号(--)则表示注释。                                                                                    */
/*  如：                                                                                                                                                     */
/*  sqlite>create studen_table(Stu_no interger PRIMARY KEY, Name text NOT nullptr, Id interger UNIQUE, Age interger CHECK(Age>6), School text DEFAULT 'xx小学); */
/*  该语句创建一个记录学生信息的数据表。                                                                                                                     */
/*                                                                                                                                                           */
/*  3.1 sqlite3存储数据的类型                                                                                                                                */
/*  nullptr：标识一个nullptr值                                                                                                                                     */
/*  INTERGER：整数类型                                                                                                                                       */
/*  REAL：浮点数                                                                                                                                             */
/*  TEXT：字符串                                                                                                                                             */
/*  BLOB：二进制数                                                                                                                                           */
/*                                                                                                                                                           */
/*  3.2 sqlite3存储数据的约束条件                                                                                                                            */
/*  Sqlite常用约束条件如下：                                                                                                                                 */
/*  PRIMARY KEY - 主键：                                                                                                                                     */
/*  1）主键的值必须唯一，用于标识每一条记录，如学生的学号                                                                                                    */
/*  2）主键同时也是一个索引，通过主键查找记录速度较快                                                                                                        */
/*  3）主键如果是整数类型，该列的值可以自动增长                                                                                                              */
/*  NOT nullptr - 非空：                                                                                                                                        */
/*  约束列记录不能为空，否则报错                                                                                                                             */
/*  UNIQUE - 唯一：                                                                                                                                          */
/*  除主键外，约束其他列的数据的值唯一                                                                                                                       */
/*  CHECK - 条件检查：                                                                                                                                       */
/*  约束该列的值必须符合条件才可存入                                                                                                                         */
/*  DEFAULT - 默认值：                                                                                                                                       */
/*  列数据中的值基本都是一样的，这样的字段列可设为默认值                                                                                                     */
/*                                                                                                                                                           */
/*  3.3 sqlite3常用指令                                                                                                                                      */
/*                                                                                                                                                           */
/*  1）建立数据表                                                                                                                                            */
/*  create table table_name(field1 type1, field2 type1, ...);                                                                                                */
/*  table_name是要创建数据表名称，fieldx是数据表内字段名称，typex则是字段类型。                                                                              */
/*  例，建立一个简单的学生信息表，它包含学号与姓名等学生信息：                                                                                               */
/*  create table student_info(stu_no interger primary key, name text);                                                                                       */
/*                                                                                                                                                           */
/*  2）添加数据记录                                                                                                                                          */
/*  insert into table_name(field1, field2, ...) values(val1, val2, ...);                                                                                     */
/*  valx为需要存入字段的值。                                                                                                                                 */
/*  例，往学生信息表添加数据：                                                                                                                               */
/*  Insert into student_info(stu_no, name) values(0001, alex);                                                                                               */
/*                                                                                                                                                           */
/*  3）修改数据记录                                                                                                                                          */
/*  update table_name set field1=val1, field2=val2 where expression;                                                                                         */
/*  where是sql语句中用于条件判断的命令，expression为判断表达式                                                                                               */
/*  例，修改学生信息表学号为0001的数据记录：                                                                                                                 */
/*  update student_info set stu_no=0001, name=hence where stu_no=0001;                                                                                       */
/*                                                                                                                                                           */
/*  4）删除数据记录                                                                                                                                          */
/*  delete from table_name [where expression];                                                                                                               */
/*  不加判断条件则清空表所有数据记录。                                                                                                                       */
/*  例，删除学生信息表学号为0001的数据记录：                                                                                                                 */
/*  delete from student_info where stu_no=0001;                                                                                                              */
/*                                                                                                                                                           */
/*  5）查询数据记录                                                                                                                                          */
/*  select指令基本格式：                                                                                                                                     */
/*  select columns from table_name [where expression];                                                                                                       */
/*  a查询输出所有数据记录                                                                                                                                    */
/*  select * from table_name;                                                                                                                                */
/*  b限制输出数据记录数量                                                                                                                                    */
/*  select * from table_name limit val;                                                                                                                      */
/*  c升序输出数据记录                                                                                                                                        */
/*  select * from table_name order by field asc;                                                                                                             */
/*  d降序输出数据记录                                                                                                                                        */
/*  select * from table_name order by field desc;                                                                                                            */
/*  e条件查询                                                                                                                                                */
/*  select * from table_name where expression;                                                                                                               */
/*  select * from table_name where field in ('val1', 'val2', 'val3');                                                                                        */
/*  select * from table_name where field between val1 and val2;                                                                                              */
/*  f查询记录数目                                                                                                                                            */
/*  select count (*) from table_name;                                                                                                                        */
/*  g区分列数据                                                                                                                                              */
/*  select distinct field from table_name;                                                                                                                   */
/*  有一些字段的值可能会重复出现，distinct去掉重复项，将列中各字段值单个列出。                                                                               */
/*                                                                                                                                                           */
/*  6）建立索引                                                                                                                                              */
/*  当说数据表存在大量记录，索引有助于加快查找数据表速度。                                                                                                   */
/*  create index index_name on table_name(field);                                                                                                            */
/*  例，针对学生表stu_no字段，建立一个索引：                                                                                                                 */
/*  create index student_index on student_table(stu_no);                                                                                                     */
/*  建立完成后，sqlite3在对该字段查询时，会自动使用该索引。                                                                                                  */
/*                                                                                                                                                           */
/*  7）删除数据表或索引                                                                                                                                      */
/*  drop table table_name;                                                                                                                                   */
/*  drop index index_name;                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/



