#include "wnh_inotify_use_mysql.h"

bool wnh_inotify_use_mysql::connont_mysql(string host,string user,string pwd,string db_name)//与数据进行链接
{
    if(watch_list.initDB(host, user, pwd, db_name))
    {
        return true;
    }
    return false;
}

bool wnh_inotify_use_mysql::create_table()//创建一张数据表
{
    table_name = LOCALTIME;
    this->trim(table_name, " ");
    this->trim(table_name, "/");
    this->trim(table_name, ":");
    table_name = "filesync_watch_list_" + table_name;
    WNHDEBUG("使用数据表" << table_name << "来进行数据记录");
    wnh_mysql_sql = "CREATE TABLE `" + table_name + "` (`key`  int NOT nullptr , `value`  varchar(255) NOT nullptr , PRIMARY KEY (`key`) , INDEX (`value`)) CHARACTER SET utf8 COLLATE utf8_general_ci;";
    WNHDEBUG("wnh_mysql_sql:" << wnh_mysql_sql);
    if(watch_list.exeSQL(wnh_mysql_sql))
    {
        return true;
    }
    return false;
}

bool wnh_inotify_use_mysql::add_one_record(int key, string value)//添加一行数据
{
    wnh_mysql_sql = "INSERT INTO `" + table_name + "` (`key`, `value`) VALUES ('" + to_string (key) + "', '" + value + "');";
    WNHDEBUG("wnh_mysql_sql:" << wnh_mysql_sql);
    if(watch_list.exeSQL(wnh_mysql_sql, rows))
    {
        WNHDEBUG("添加一行数据成功");
        return true;
    }
    WNHDEBUG("添加一行数据失败");
    return false;
}

bool wnh_inotify_use_mysql::check_unit_exist(int key)//查找指定一行记录是否存在
{
    wnh_mysql_sql = "SELECT count(1) FROM `" + table_name + "` t where t.`key` = '" + to_string (key) + "';";
    WNHDEBUG("wnh_mysql_sql:" << wnh_mysql_sql);
    row = watch_list.exeSQLs(wnh_mysql_sql, rows);
    if((string)row[0] != "0")
    {
        WNHDEBUG("查找指定一行记录存在");
        return true;
    }
    WNHDEBUG("查找指定一行记录不存在");
    return false;
}

bool wnh_inotify_use_mysql::check_unit_exist(string value)//查找指定一行记录是否存在
{
    wnh_mysql_sql = "SELECT count(1) FROM `" + table_name + "` t where t.`value` = '" + value + "';";
    WNHDEBUG("wnh_mysql_sql:" << wnh_mysql_sql);
    row = watch_list.exeSQLs(wnh_mysql_sql, rows);
    if((string)row[0] != "0")
    {
        WNHDEBUG("查找指定一行记录存在");
        return true;
    }
    WNHDEBUG("查找指定一行记录不存在");
    return false;
}

bool wnh_inotify_use_mysql::check_unit_exist(int key, string value)//查找指定一行记录是否存在
{
    wnh_mysql_sql = "SELECT count(1) FROM `" + table_name + "` t where t.`key` = '" + to_string (key) + "' and t.`value` = '" + value + "';";
    WNHDEBUG("wnh_mysql_sql:" << wnh_mysql_sql);
    row = watch_list.exeSQLs(wnh_mysql_sql, rows);
    if((string)row[0] != "0")
    {
        WNHDEBUG("查找指定一行记录存在");
        return true;
    }
    WNHDEBUG("查找指定一行记录不存在");
    return false;
}

bool wnh_inotify_use_mysql::delete_record(int key)//删除记录
{
    wnh_mysql_sql = "DELETE FROM `" + table_name + "` WHERE (`key`='" + to_string (key) + "');";
    if(watch_list.exeSQL(wnh_mysql_sql, rows))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}
bool wnh_inotify_use_mysql::delete_record(string value)//删除记录
{
    wnh_mysql_sql = "DELETE FROM `" + table_name + "` WHERE (`value`='" + value + "');";
    if(watch_list.exeSQL(wnh_mysql_sql, rows))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

bool wnh_inotify_use_mysql::delete_record(int key, string value)//删除记录
{
    wnh_mysql_sql = "DELETE FROM `" + table_name + "` WHERE (`key`='" + to_string (key) + "') AND (`value`='" + value + "');";
    if(watch_list.exeSQL(wnh_mysql_sql, rows))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

bool wnh_inotify_use_mysql::delete_record(string value, int &rows)//删除记录
{
    wnh_mysql_sql = "DELETE FROM `" + table_name + "` WHERE (`value` like '" + value + "%');";
    if(watch_list.exeSQL(wnh_mysql_sql, rows))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

int wnh_inotify_use_mysql::get_record(string value)//使用value获取key
{
    if(register_value == value)
    {
        WNHDEBUG("寄存器匹配,使用value获取key成功 key:" << register_key);
        return register_key;
    }
    wnh_mysql_sql = "SELECT t.`key` FROM `" + table_name + "` t where t.`value` = '" + value + "';";
    row = watch_list.exeSQLs(wnh_mysql_sql, rows);
    //if(row >= 0 && !((string)row[0]).empty())
    if(row >= 0)
    {
        WNHDEBUG("使用value获取key成功 key:" << row[0]);
        register_key = stoi(((string)row[0]).c_str());
        register_value = value;
        return register_key;
    }
    WNHWARN("使用value获取key失败,查找记录不存在");
    return 0;
}

string wnh_inotify_use_mysql::get_record(int key)//使用key获取value
{
    if(register_key == key)
    {
        WNHDEBUG("寄存器匹配,使用key获取value成功 value:" << register_value);
        return register_value;
    }
    wnh_mysql_sql = "SELECT t.`value` FROM `" + table_name + "` t where t.`key` = '" + to_string (key) + "';";
    row = watch_list.exeSQLs(wnh_mysql_sql, rows);
    //if(row >= 0 && !((string)row[0]).empty())
    if(row >= 0)
    {
        WNHDEBUG("使用key获取value成功 value:" << row[0]);
        register_key = key;
        register_value = ((string)row[0]);
        return register_value;
    }
    WNHWARN("使用key获取value失败,查找记录不存在");
    return "";
}

MYSQL_RES * wnh_inotify_use_mysql::get_record(string value, int &list, int &rows)//使用value模糊查询获取key
{
    wnh_mysql_sql = "SELECT t.`key`,t.`value` FROM `" + table_name + "` t where t.`value` like '" + value + "%';";
    return watch_list.exeSQLs(wnh_mysql_sql,list, rows);   //执行sql语句,返回多行结果
}
