#include "wnh_mysql.h"

wnh_mysql::wnh_mysql()
{
    WNHDEBUG("wnh_mysql 构造");
}

wnh_mysql::~wnh_mysql()
{
    WNHDEBUG("~wnh_mysql 析构");
    if( mysql != nullptr )  //关闭数据连接
    {
        mysql_close(mysql);
    }
}

bool wnh_mysql::initDB(string host,string user,string passwd,string db_name)
{
    // 函数mysql_real_connect建立一个数据库连接
    // 成功返回MYSQL*连接句柄，失败返回nullptr
    mysql = mysql_init(nullptr);   //初始化数据库连接变量
    if( mysql == nullptr )
    {
        WNHERROR("初始化数据库连接失败 " << mysql_error(mysql));
        return false;
    }
    else
    {
        WNHDEBUG("初始化数据库连接成功");
    }
    WNHDEBUG("尝试建立一个数据库连接 host:" << host << ", user:" << user << ", passwd:" << passwd << ", db_name:" << db_name);
    mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(), 0, nullptr, 0);
    if(mysql == nullptr)
    {
        WNHERROR("建立一个数据库连接失败 " << mysql_error(mysql));
        //cout << "Error: " << mysql_error(mysql) << endl;
        //exit(1);
        return false;
    }
    else
    {
        WNHDEBUG("建立一个数据库连接成功");
        mysql_set_character_set(mysql, "utf8");
    }
    return true;
}

bool wnh_mysql::exeSQL(string sql)//执行sql语句，返回是否执行成功
{
    //mysql_query()执行成功返回0,执行失败返回非0值。
    WNHDEBUG("sql:" << sql);
    if ( mysql_query(mysql,sql.c_str()) )
    {
        WNHERROR(sql << " 执行失败, " << mysql_error(mysql));
        return false;
    }
    else
    {
        WNHDEBUG(sql << " 执行成功");
    }
    return true;
}

bool wnh_mysql::exeSQL(string sql, int &rows)//执行sql语句,返回影响的行数
{
    WNHDEBUG("sql:" << sql);
    MYSQL_RES *result = nullptr;   //指向查询结果的指针
    //mysql_query()执行成功返回0,执行失败返回非0值。
    if ( mysql_query(mysql,sql.c_str()) )
    {
        WNHERROR(sql << " 执行失败, " << mysql_error(mysql));
    }
    else // 查询成功
    {
        result = mysql_store_result(mysql);  //获取结果集
        if(mysql_field_count(mysql) == 0)   //代表执行的是update,insert,delete类的非查询语句
        {
            int rows = mysql_affected_rows(mysql);  //返回update,insert,delete影响的行数
            WNHDEBUG(sql << "获取结果集成功 更新行数=" << rows);
            return true;
        }
        else
        {
            WNHERROR(sql << "获取结果集失败" << mysql_error(mysql));
        }
        mysql_free_result(result);
    }
    return false;
}

MYSQL_ROW wnh_mysql::exeSQLs(string sql, int &rows)   //执行sql语句,返回一行结果
{
    WNHDEBUG("sql:" << sql);
    MYSQL_RES *result = nullptr;   //指向查询结果的指针
    MYSQL_ROW row = nullptr;       //按行返回的查询信息
    //mysql_query()执行成功返回0,执行失败返回非0值。
    if ( mysql_query(mysql,sql.c_str()) )
    {
        WNHERROR(sql << " 执行失败, " << mysql_error(mysql));
    }
    else // 查询成功
    {
        result = mysql_store_result(mysql);  //获取结果集
        int list = mysql_num_rows(result);
        if(list <= 0)
        {
            WNHWARN(sql << " 执行成功,但是存在多行结果集, " << list << "行");
        }
        else
        {
            rows = mysql_num_fields(result);
            row = mysql_fetch_row(result); //从结果集中获取一行
            WNHDEBUG(sql << " 执行成功,获取一行结果集, " << list << "行, " << rows << "列");
            for(int i=0; i<rows; i++)
            {
                WNHDEBUG("rows[" << i << "]=" << row[i]);
            }
        }
        mysql_free_result(result);
    }
    return row;
}

MYSQL_RES * wnh_mysql::exeSQLs(string sql, int &list, int &rows)
{
    WNHDEBUG("sql:" << sql);
    MYSQL_RES *result = nullptr;   //指向查询结果的指针
    //mysql_query()执行成功返回0,执行失败返回非0值。
    if ( mysql_query(mysql,sql.c_str()) )
    {
        WNHERROR(sql << " 执行失败, " << mysql_error(mysql));
    }
    else // 查询成功
    {
        result = mysql_store_result(mysql);  //获取结果集
        list = mysql_num_rows(result);
        rows = mysql_num_fields(result);
        WNHDEBUG(sql << " 执行成功,获取多行结果集, " << list << "行, " << rows << "列");
    }
    return result;
}

