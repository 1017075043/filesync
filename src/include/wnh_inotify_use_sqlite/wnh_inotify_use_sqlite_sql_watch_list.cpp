#include "wnh_inotify_use_sqlite.h"

bool wnh_inotify_use_sqlite::watch_list_create_table()//创建一张数据表
{
    WNHINFO("使用数据表" << WATCH_LIST_TABLE_NAME << "来进行数据记录");
    string sql;
    sql = sql + "CREATE TABLE " + WATCH_LIST_TABLE_NAME + " (wd INT NOT NULL, watch_dir_path TEXT NOT NULL, PRIMARY KEY (wd, watch_dir_path));";
    return sqlite_op.sql_query(sql);
}

bool wnh_inotify_use_sqlite::watch_list_drop_table() //删除数据表
{
    WNHDEBUG("删除数据表" << WATCH_LIST_TABLE_NAME);
    string sql;
    sql = sql + "DROP TABLE IF EXISTS " + WATCH_LIST_TABLE_NAME + ";";
    return sqlite_op.sql_query(sql);
}

bool wnh_inotify_use_sqlite::watch_list_add_one_record(const int wd, const string watch_dir_path)//添加一行数据
{
    string sql;
    sql = sql + "INSERT INTO " + WATCH_LIST_TABLE_NAME + " (wd, watch_dir_path) VALUES ('" + to_string (wd) + "', '" + sqlite_op.sqlite_escape(watch_dir_path) + "');";
    if(sqlite_op.sql_query(sql))
    {
        return true;
    }
    return false;
}

bool wnh_inotify_use_sqlite::watch_list_check_unit_exist(const int wd)//查找指定一行记录是否存在
{
    string sql;
    sql = sql + "SELECT count(1) FROM " + WATCH_LIST_TABLE_NAME + " t where t.wd = '" + to_string(wd) + "';";
    string result;
    if(sqlite_op.sql_query(sql, result) && result != "0")
    {
        WNHDEBUG("查找指定一行记录存在");
        return true;
    }
    WNHDEBUG("查找指定一行记录不存在");
    return false;
}

bool wnh_inotify_use_sqlite::watch_list_check_unit_exist(const string watch_dir_path)//查找指定一行记录是否存在
{
    string sql;
    sql = sql + "SELECT count(1) FROM " + WATCH_LIST_TABLE_NAME + " t where t.watch_dir_path = '" + sqlite_op.sqlite_escape(watch_dir_path) + "';";
    string result;
    if(sqlite_op.sql_query(sql, result) && result != "0")
    {
        WNHDEBUG("查找指定一行记录存在");
        return true;
    }
    WNHDEBUG("查找指定一行记录不存在");
    return false;
}

bool wnh_inotify_use_sqlite::watch_list_check_unit_exist(const int wd, const string watch_dir_path)//查找指定一行记录是否存在
{
    string sql;
    sql = sql + "SELECT count(1) FROM " + WATCH_LIST_TABLE_NAME + " t where t.wd = '" + to_string (wd) + "' and t.watch_dir_path = '" + sqlite_op.sqlite_escape(watch_dir_path) + "';";
    string result;
    if(sqlite_op.sql_query(sql, result) && result != "0")
    {
        WNHDEBUG("查找指定一行记录存在");
        return true;
    }
    WNHDEBUG("查找指定一行记录不存在");
    return false;
}

bool wnh_inotify_use_sqlite::watch_list_delete_record(const int wd)//删除记录
{
    string sql;
    sql = sql + "DELETE FROM " + WATCH_LIST_TABLE_NAME + " WHERE (wd='" + to_string (wd) + "');";
    if(sqlite_op.sql_query(sql))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

bool wnh_inotify_use_sqlite::watch_list_delete_record(const string watch_dir_path)//删除记录
{
    string sql;
    sql = sql + "DELETE FROM " + WATCH_LIST_TABLE_NAME + " WHERE (watch_dir_path='" + sqlite_op.sqlite_escape(watch_dir_path) + "');";
    if(sqlite_op.sql_query(sql))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

bool wnh_inotify_use_sqlite::watch_list_delete_record(const int wd, const string watch_dir_path)//删除记录
{
    string sql;
    sql = sql + "DELETE FROM " + WATCH_LIST_TABLE_NAME + " WHERE (wd='" + to_string (wd) + "') AND (watch_dir_path='" + sqlite_op.sqlite_escape(watch_dir_path) + "');";
    if(sqlite_op.sql_query(sql))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

bool wnh_inotify_use_sqlite::watch_list_delete_record_like(const string watch_dir_path)//删除记录
{
    string sql;
    sql = sql + "DELETE FROM " + WATCH_LIST_TABLE_NAME + " WHERE (watch_dir_path like '" + sqlite_op.sqlite_escape(watch_dir_path) + "%');";
    if(sqlite_op.sql_query(sql))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

int wnh_inotify_use_sqlite::watch_list_get_record(const string watch_dir_path)//使用watch_dir_path获取wd
{
    if(register_watch_dir_path == watch_dir_path)
    {
        WNHDEBUG("寄存器匹配,使用watch_dir_path获取wd成功 wd:" << register_wd);
        return register_wd;
    }
    string sql;
    sql = sql + "SELECT t.wd FROM " + WATCH_LIST_TABLE_NAME + " t where t.watch_dir_path = '" + sqlite_op.sqlite_escape(watch_dir_path) + "';";
    string result;
    if(sqlite_op.sql_query(sql, result))
    {
        if(!result.empty())
        {
            register_wd = stoi(result.c_str());
            register_watch_dir_path = watch_dir_path;
            WNHDEBUG("使用watch_dir_path获取wd成功 wd:" << result);
            return register_wd;
        }
    }
    WNHWARN("使用watch_dir_path获取wd失败,查找记录不存在");
    return 0;
}

string wnh_inotify_use_sqlite::watch_list_get_record(const int wd)//使用wd获取watch_dir_path
{
    if(register_wd == wd)
    {
        WNHDEBUG("寄存器匹配,使用wd获取watch_dir_path成功 watch_dir_path:" << register_watch_dir_path);
        return register_watch_dir_path;
    }
    string sql;
    sql = sql + "SELECT t.watch_dir_path FROM " + WATCH_LIST_TABLE_NAME + " t where t.wd = '" + to_string (wd) + "';";
    string result;
    if(sqlite_op.sql_query(sql, result))
    {
        register_wd = wd;
        register_watch_dir_path = result;
        WNHDEBUG("使用wd获取watch_dir_path成功 watch_dir_path:" << result);
        return register_watch_dir_path;
    }
    WNHWARN("使用wd获取watch_dir_path失败,查找记录不存在");
    return "";
}

bool wnh_inotify_use_sqlite::watch_list_get_record(const string watch_dir_path, string **& result, int &list, int &rows)//使用watch_dir_path模糊查询获取wd
{
    string sql;
    sql = sql + "SELECT t.wd,t.watch_dir_path FROM " + WATCH_LIST_TABLE_NAME + " t where t.watch_dir_path like '" + sqlite_op.sqlite_escape(watch_dir_path) + "%';";
    if(sqlite_op.sql_query(sql, result, list, rows))
    {
        return true;
    }
    return false;
}
