#include "wnh_inotify_use_sqlite.h"

bool wnh_inotify_use_sqlite::watch_list_create_db()//创建一个数据进行数据存储
{
    WNHINFO("使用数据库" << DB_NAME << "来进行数据存储");
    return sqlite_op.create_db(DB_NAME);//创建一个数据库
}

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

bool wnh_inotify_use_sqlite::event_list_create_table() //创建一张数据表-事件列表
{
    WNHINFO("使用数据表" << EVENT_LIST_TABLE_NAME << "来进行数据记录");
    string sql;
    sql = sql + "CREATE TABLE " + EVENT_LIST_TABLE_NAME + " (event_id INT NOT NULL, event_path TEXT NOT NULL, update_date DATE NOT NULL, PRIMARY KEY (event_path));";
    return sqlite_op.sql_query(sql);
}

bool wnh_inotify_use_sqlite::event_list_drop_table() //删除数据表-事件列表
{
    WNHDEBUG("删除数据表" << EVENT_LIST_TABLE_NAME);
    string sql;
    sql = sql + "DROP TABLE IF EXISTS " + EVENT_LIST_TABLE_NAME + ";";
    return sqlite_op.sql_query(sql);
}

bool wnh_inotify_use_sqlite::event_list_add_one_record(const string & event_id, const string & event_path) //添加一行数据-事件列表
{
    string sql, result;
    sql = sql + "SELECT event_id FROM " + EVENT_LIST_TABLE_NAME + " where event_path = '" + sqlite_op.sqlite_escape(event_path) + "';";
    sqlite_op.sql_query(sql, result);
    if(!result.empty() && atoi(event_id.c_str()) == WNH_INOTIFY_IN_ATTRIB)
    {
        WNHDEBUG("事件列表中存在大于或等于当前的事件:动作:" << event_transform(result) << ", 忽略事件:动作:" << event_transform(event_id) << ", src_path:" << event_path);
        return true;
    }
    sql = "";
    sql = sql + "REPLACE INTO " + EVENT_LIST_TABLE_NAME + " (event_id, event_path, update_date) VALUES ('" + event_id + "', '" + sqlite_op.sqlite_escape(event_path) + "', datetime(CURRENT_TIMESTAMP,'localtime'));";
    //WNHINFO("sql:" << sql);
    if(sqlite_op.sql_query(sql))
    {
        return true;
    }
    return false;
}

bool wnh_inotify_use_sqlite::event_list_add_one_record(const int & event_id, const string & event_path) //添加一行数据-事件列表
{
    return event_list_add_one_record(to_string(event_id), event_path);
}

bool wnh_inotify_use_sqlite::task_list_create_table() //创建一张数据表-任务列表
{
    WNHINFO("使用数据表" << TASK_LIST_TABLE_NAME << "来进行数据记录");
    string sql;
    //sql = sql + "CREATE TABLE " + TASK_LIST_TABLE_NAME + " (client_ip TEXT NOT NULL, event_id INT NOT NULL, src_path TEXT NOT NULL, dst_path src_path TEXT NOT NULL, update_date DATE NOT NULL, PRIMARY KEY (client_ip, src_path, dst_path));";
    sql = sql + "CREATE TABLE IF NOT EXISTS " + TASK_LIST_TABLE_NAME + " (client_ip TEXT NOT NULL, event_id INT NOT NULL, src_path TEXT NOT NULL, dst_path TEXT NOT NULL, update_date DATE NOT NULL, PRIMARY KEY (client_ip, src_path, dst_path));";
    sqlite_op.sql_query(sql);
    sql = "";
    sql = sql + "REPLACE INTO task_list_table (client_ip, event_id, src_path, dst_path, update_date) VALUES ('0', '0', '0', '0', datetime(CURRENT_TIMESTAMP,'localtime'));";
    return sqlite_op.sql_query(sql);
}

bool wnh_inotify_use_sqlite::event_into_task(const string & src_dir, const string & dst_dir, const vector<string> & client_ip) //将事件转为任务
{
    string sql;
    string **result;
    int row, column;
    sql = sql + "SELECT event_id, event_path FROM " +  EVENT_LIST_TABLE_NAME + " WHERE (event_path like '" + sqlite_op.sqlite_escape(src_dir) + "/%') AND (datetime(CURRENT_TIMESTAMP, 'localtime', '-3 seconds') > datetime(update_date));";
    if(!sqlite_op.sql_query(sql, result, row, column))
    {
        for( int i=0; i<row; i++ )
        {
            delete [] result[i];
        }
        delete result;
        return false;
    }
    for(int i = 0 ; i < row; i ++)
    {
        string event_id = result[i][0];
        string src_path = result[i][1];
        string dst_path = dst_dir + src_path.substr(src_dir.length());
        for(int n = 0; n < (int)client_ip.size(); n++)
        {
            sql = "";
            sql = sql + "SELECT SUM(event_id) from " + TASK_LIST_TABLE_NAME + " WHERE ((client_ip = '" + client_ip[n] + "') AND (src_path = '" + sqlite_op.sqlite_escape(src_path) + "')) OR (event_id  = '0');";
            string sql_result;
            sqlite_op.sql_query(sql, sql_result);
            int temp_sql_result = atoi(sql_result.c_str());
            int temp_event_id = atoi(event_id.c_str());
            if(temp_sql_result == 0)
            {
                sql = "";
                sql = sql + "REPLACE INTO " + TASK_LIST_TABLE_NAME + " (client_ip, event_id, src_path, dst_path, update_date) VALUES ('" + client_ip[n] + "', '" + event_id + "', '" + sqlite_op.sqlite_escape(src_path) + "', '" + sqlite_op.sqlite_escape(dst_path) + "', datetime(CURRENT_TIMESTAMP,'localtime'));";
                sqlite_op.sql_query(sql);
                WNHINFO("成功添加一个任务, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(event_id) << ", 源路径:" << src_path << ", 目标路径:" << dst_path);
                continue;
            }
            if((temp_sql_result == WNH_INOTIFY_IN_MOVED_FROM || temp_sql_result == WNH_INOTIFY_IN_DELETE) && (temp_event_id != WNH_INOTIFY_IN_MOVED_FROM && temp_event_id != WNH_INOTIFY_IN_DELETE))
            {
                sql = "";
                sql = sql + "UPDATE " + TASK_LIST_TABLE_NAME + " SET event_id = '" + event_id + "', update_date = datetime(CURRENT_TIMESTAMP,'localtime') WHERE (client_ip = '" + client_ip[n] + "') AND (src_path = '" + sqlite_op.sqlite_escape(src_path) + "') and (dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
                sqlite_op.sql_query(sql);
                WNHINFO("成功更新一个任务,修改删除, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(event_id) << ", 源路径:" << src_path << ", 目标路径:" << dst_path);
                continue;
            }
            if(temp_event_id == WNH_INOTIFY_IN_DELETE || temp_event_id == WNH_INOTIFY_IN_MOVED_FROM)
            {
                if(temp_sql_result == WNH_INOTIFY_IN_DELETE || temp_sql_result == WNH_INOTIFY_IN_MOVED_FROM)
                {
                    WNHINFO("数据库中存在大于或等于当前事件等级的任务, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(sql_result) << ", 忽略事件:动作:" << event_transform(event_id) << ", src_path:" << src_path);
                    continue;
                }
                else
                {
                    sql = "";
                    sql = sql + "UPDATE " + TASK_LIST_TABLE_NAME + " SET event_id = '" + event_id + "', update_date = datetime(CURRENT_TIMESTAMP,'localtime') WHERE (client_ip = '" + client_ip[n] + "') AND (src_path = '" + sqlite_op.sqlite_escape(src_path) + "') and (dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
                    sqlite_op.sql_query(sql);
                    WNHINFO("成功更新一个任务,提高任务等级, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(event_id) << ", 源路径:" << src_path << ", 目标路径:" << dst_path);
                    continue;
                }
            }
            if(temp_event_id == WNH_INOTIFY_IN_CREATE || temp_event_id == WNH_INOTIFY_IN_MODIFY || temp_event_id == WNH_INOTIFY_IN_MOVED_TO)
            {
                if(temp_sql_result == WNH_INOTIFY_IN_DELETE || temp_sql_result == WNH_INOTIFY_IN_MOVED_FROM || temp_sql_result == WNH_INOTIFY_IN_CREATE || temp_sql_result == WNH_INOTIFY_IN_MODIFY || temp_sql_result == WNH_INOTIFY_IN_MOVED_TO)
                {
                    WNHINFO("数据库中存在大于或等于当前事件等级的任务, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(sql_result) << ", 忽略事件:动作:" << event_transform(event_id) << ", src_path:" << src_path);
                    continue;
                }
                else
                {
                    sql = "";
                    sql = sql + "UPDATE " + TASK_LIST_TABLE_NAME + " SET event_id = '" + event_id + "', update_date = datetime(CURRENT_TIMESTAMP,'localtime') WHERE (client_ip = '" + client_ip[n] + "') AND (src_path = '" + sqlite_op.sqlite_escape(src_path) + "') and (dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
                    sqlite_op.sql_query(sql);
                    WNHINFO("成功更新一个任务,提高任务等级, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(event_id) << ", 源路径:" << src_path << ", 目标路径:" << dst_path);
                    continue;
                }
            }
            if((temp_event_id == WNH_INOTIFY_IN_ATTRIB))
            {
                WNHINFO("数据库中存在大于或等于当前事件等级的任务, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(sql_result) << ", 忽略事件:动作:" << event_transform(event_id) << ", src_path:" << src_path);
                continue;
            }
        }
        sql = "";
        sql = sql + "DELETE FROM " + EVENT_LIST_TABLE_NAME + " WHERE (event_path = '" + sqlite_op.sqlite_escape(src_path) + "');";
        sqlite_op.sql_query(sql);
    }
    for( int i=0; i<row; i++ )
    {
        delete [] result[i];
    }
    delete result;
    return true;
}

bool wnh_inotify_use_sqlite::event_into_task(const string & src_dir, const vector<string> & dst_dir, const vector<string> & client_ip) //将事件转为任务
{
    string sql;
    string **result;
    int row, column;
    sql = sql + "SELECT event_id, event_path FROM " +  EVENT_LIST_TABLE_NAME + " WHERE (event_path like '" + sqlite_op.sqlite_escape(src_dir) + "/%') AND (datetime(CURRENT_TIMESTAMP, 'localtime', '-3 seconds') > datetime(update_date));";
    if(!sqlite_op.sql_query(sql, result, row, column))
    {
        for( int i=0; i<row; i++ )
        {
            delete [] result[i];
        }
        delete result;
        return false;
    }
    for(int i = 0 ; i < row; i ++)
    {
        string event_id = result[i][0];
        string src_path = result[i][1];
        for(int n = 0; n < (int)dst_dir.size(); n++)
        {
            string dst_path = dst_dir[n] + src_path.substr(src_dir.length());
            sql = "";
            sql = sql + "SELECT SUM(event_id) from " + TASK_LIST_TABLE_NAME + " WHERE ((client_ip = '" + client_ip[n] + "') AND (src_path = '" + sqlite_op.sqlite_escape(src_path) + "')  AND (dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "')) OR (event_id  = '0');";
            string sql_result;
            sqlite_op.sql_query(sql, sql_result);
            int temp_sql_result = atoi(sql_result.c_str());
            int temp_event_id = atoi(event_id.c_str());
            if(temp_sql_result == 0)
            {
                sql = "";
                sql = sql + "REPLACE INTO " + TASK_LIST_TABLE_NAME + " (client_ip, event_id, src_path, dst_path, update_date) VALUES ('" + client_ip[n] + "', '" + event_id + "', '" + sqlite_op.sqlite_escape(src_path) + "', '" + sqlite_op.sqlite_escape(dst_path) + "', datetime(CURRENT_TIMESTAMP,'localtime'));";
                //sql = sql + "INSERT INTO " + TASK_LIST_TABLE_NAME + " (client_ip, event_id, src_path, dst_path, update_date) VALUES ('" + client_ip[n] + "', '" + event_id + "', '" + sqlite_op.sqlite_escape(src_path) + "', '" + sqlite_op.sqlite_escape(dst_path) + "', datetime(CURRENT_TIMESTAMP,'localtime'));";
                sqlite_op.sql_query(sql);
                WNHINFO("成功添加一个任务, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(event_id) << ", 源路径:" << src_path << ", 目标路径:" << dst_path);
                continue;
            }
            if((temp_sql_result == WNH_INOTIFY_IN_MOVED_FROM || temp_sql_result == WNH_INOTIFY_IN_DELETE) && (temp_event_id != WNH_INOTIFY_IN_MOVED_FROM && temp_event_id != WNH_INOTIFY_IN_DELETE))
            {
                sql = "";
                sql = sql + "UPDATE " + TASK_LIST_TABLE_NAME + " SET event_id = '" + event_id + "', update_date = datetime(CURRENT_TIMESTAMP,'localtime') WHERE (client_ip = '" + client_ip[n] + "') AND (src_path = '" + sqlite_op.sqlite_escape(src_path) + "') AND (dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
                sqlite_op.sql_query(sql);
                WNHINFO("成功更新一个任务,修改删除, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(event_id) << ", 源路径:" << src_path << ", 目标路径:" << dst_path);
                continue;
            }
            if(temp_event_id == WNH_INOTIFY_IN_DELETE || temp_event_id == WNH_INOTIFY_IN_MOVED_FROM)
            {
                if(temp_sql_result == WNH_INOTIFY_IN_DELETE || temp_sql_result == WNH_INOTIFY_IN_MOVED_FROM)
                {
                    WNHINFO("数据库中存在大于或等于当前事件等级的任务, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(sql_result) << ", 忽略事件:动作:" << event_transform(event_id) << ", src_path:" << src_path);
                    continue;
                }
                else
                {
                    sql = "";
                    sql = sql + "UPDATE " + TASK_LIST_TABLE_NAME + " SET event_id = '" + event_id + "', update_date = datetime(CURRENT_TIMESTAMP,'localtime') WHERE (client_ip = '" + client_ip[n] + "') AND (src_path = '" + sqlite_op.sqlite_escape(src_path) + "') and (dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
                    sqlite_op.sql_query(sql);
                    WNHINFO("成功更新一个任务,提高任务等级, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(event_id) << ", 源路径:" << src_path << ", 目标路径:" << dst_path);
                    continue;
                }
            }
            if(temp_event_id == WNH_INOTIFY_IN_CREATE || temp_event_id == WNH_INOTIFY_IN_MODIFY || temp_event_id == WNH_INOTIFY_IN_MOVED_TO)
            {
                if(temp_sql_result == WNH_INOTIFY_IN_DELETE || temp_sql_result == WNH_INOTIFY_IN_MOVED_FROM || temp_sql_result == WNH_INOTIFY_IN_CREATE || temp_sql_result == WNH_INOTIFY_IN_MODIFY || temp_sql_result == WNH_INOTIFY_IN_MOVED_TO)
                {
                    WNHINFO("数据库中存在大于或等于当前事件等级的任务, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(sql_result) << ", 忽略事件:动作:" << event_transform(event_id) << ", src_path:" << src_path);
                    continue;
                }
                else
                {
                    sql = "";
                    sql = sql + "UPDATE " + TASK_LIST_TABLE_NAME + " SET event_id = '" + event_id + "', update_date = datetime(CURRENT_TIMESTAMP,'localtime') WHERE (client_ip = '" + client_ip[n] + "') AND (src_path = '" + sqlite_op.sqlite_escape(src_path) + "') and (dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
                    sqlite_op.sql_query(sql);
                    WNHINFO("成功更新一个任务,提高任务等级, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(event_id) << ", 源路径:" << src_path << ", 目标路径:" << dst_path);
                    continue;
                }
            }
            if((temp_event_id == WNH_INOTIFY_IN_ATTRIB))
            {
                WNHINFO("数据库中存在大于或等于当前事件等级的任务, 客户端IP:" << client_ip[n] << ", 动作:" << event_transform(sql_result) << ", 忽略事件:动作:" << event_transform(event_id) << ", src_path:" << src_path);
                continue;
            }
        }
        sql = "";
        sql = sql + "DELETE FROM " + EVENT_LIST_TABLE_NAME + " WHERE (event_path = '" + sqlite_op.sqlite_escape(src_path) + "');";
        sqlite_op.sql_query(sql);
    }
    for( int i=0; i<row; i++ )
    {
        delete [] result[i];
    }
    delete result;
    return true;
}

bool wnh_inotify_use_sqlite::event_list_show() //查询事件表里面的所有数据
{
    string sql;
    string **result;
    int row, column;
    sql = sql + "select * from " + EVENT_LIST_TABLE_NAME + ";";
    if(sqlite_op.sql_query(sql, result, row, column))
    {
        for( int i=0; i<row; i++ )
        {
            delete [] result[i];
        }
        delete result;
        return true;
    }
    for( int i=0; i<row; i++ )
    {
        delete [] result[i];
    }
    delete result;
    return false;
}

bool wnh_inotify_use_sqlite::query_task_num(const string & client_ip, unsigned long & task_num) //根据客户端IP查询任务数量
{
    string sql, result;
    sql = sql + "SELECT COUNT(1) AS 'task_num' FROM " + TASK_LIST_TABLE_NAME + " t WHERE t.client_ip = '" + client_ip + "' AND (datetime(CURRENT_TIMESTAMP, 'localtime', '-3 seconds') > datetime(update_date));";
    if(sqlite_op.sql_query(sql, result))
    {
        task_num = strtoull(result.c_str(), NULL, 10);
        return true;
    }
    return false;
}

bool wnh_inotify_use_sqlite::create_task_list_file(const string & client_ip, const string & task_list_path, const int & max_task_num) //根据客户端IP生产任务列表文件
{
    wnh_system_operation wnh_sys_op;
    wnh_openssl file_hash;
    string sql;
    string **result;
    int row, column;
    sql = sql + "SELECT event_id, src_path, dst_path FROM " + TASK_LIST_TABLE_NAME + " t WHERE t.client_ip = '" + client_ip + "' AND (datetime(CURRENT_TIMESTAMP, 'localtime', '-3 seconds') > datetime(update_date)) ORDER BY update_date DESC LIMIT " + to_string(max_task_num) + ";";
    if(sqlite_op.sql_query(sql, result, row, column))
    {
        ofstream file_open;
        file_open.open(task_list_path, ios::out | ios::trunc);
        if(!file_open.is_open())
        {
            WNHERROR("打开文件" << task_list_path <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
            for( int i=0; i<row; i++ )
            {
                delete [] result[i];
            }
            delete result;\
            return false;
        }
        //#define WNH_INOTIFY_IN_ATTRIB 1
        //#define WNH_INOTIFY_IN_CREATE 2
        //#define WNH_INOTIFY_IN_DELETE 6
        //#define WNH_INOTIFY_IN_MODIFY 4
        //#define WNH_INOTIFY_IN_MOVED_FROM 5
        //#define WNH_INOTIFY_IN_MOVED_TO 3
        for(int i = 0; i< row; i++)
        {
            TASK_ATTR task_info;
            int temp_event_id;

            task_info.task_name = task_info.task_name + "[" + PROGRAM_NAME + "_task_" + to_string(i) + "]";
            task_info.event_id = result[i][0];
            task_info.src_path = result[i][1];
            task_info.dst_path = result[i][2];

            file_open << task_info.task_name << endl;
            file_open << "event_id=" << task_info.event_id << endl;
            file_open << "src_path=" << task_info.src_path << endl;
            file_open << "dst_path=" << task_info.dst_path << endl;

            temp_event_id = atoi(task_info.event_id.c_str());
            if(temp_event_id != WNH_INOTIFY_IN_MOVED_FROM && temp_event_id != WNH_INOTIFY_IN_DELETE)
            {
                if(!wnh_sys_op.get_file_uid(task_info.src_path, task_info.file_user))
                {
                    task_info.file_user = TASK_ATTR_DEFAULT_FILE_USER;
                }
                if(!wnh_sys_op.get_file_gid(task_info.src_path, task_info.file_group))
                {
                    task_info.file_group = TASK_ATTR_DEFAULT_FILE_GROUP;
                }
                if(!wnh_sys_op.get_file_power_s(task_info.src_path, task_info.file_power))
                {
                    task_info.file_power = TASK_ATTR_DEFAULT_FILE_POWER;
                }
                file_open << "file_user=" << task_info.file_user << endl;
                file_open << "file_group=" << task_info.file_group << endl;
                file_open << "file_power=" << task_info.file_power << endl;
                if(temp_event_id == WNH_INOTIFY_IN_CREATE || temp_event_id == WNH_INOTIFY_IN_MOVED_TO || temp_event_id == WNH_INOTIFY_IN_MODIFY)
                {
                    if(wnh_sys_op.is_dir(task_info.src_path))
                    {
                        task_info.file_type = "dir";
                        file_open << "file_type=" << task_info.file_type << endl;
                    }
                    else
                    {
                        task_info.file_type = "file";
                        file_open << "file_type=" << task_info.file_type << endl;
                        string hash_temp;
                        if(file_hash.get_file_md5(task_info.src_path, hash_temp))
                        {
                            task_info.file_hash = hash_temp;
                        }
                        else
                        {
                            task_info.file_hash = "NULL";
                        }
                        file_open << "file_hash=" << task_info.file_hash << endl;
                    }
                }
            }
            file_open << endl;
        }
        file_open.close();
        for( int i=0; i<row; i++ )
        {
            delete [] result[i];
        }
        delete result;
        return true;
    }
    for( int i=0; i<row; i++ )
    {
        delete [] result[i];
    }
    delete result;
    return false;
}

bool wnh_inotify_use_sqlite::delete_one_task(const string & client_ip, const string & event_id, const string & src_path) //根据客户端IP、事件ID、源路径删除一个任务
{
    string sql;
    sql = sql + "DELETE FROM " + TASK_LIST_TABLE_NAME + " WHERE (client_ip = '" + client_ip + "' AND event_id = '" + event_id + "' AND src_path = '" + sqlite_op.sqlite_escape(src_path) + "');";
    if(sqlite_op.sql_query(sql))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

bool wnh_inotify_use_sqlite::delete_one_task(const string & client_ip, const string & event_id, const string & src_path, const string & dst_path) //根据客户端IP、事件ID、源路径、目标路径删除一个任务
{
    string sql;
    sql = sql + "DELETE FROM " + TASK_LIST_TABLE_NAME + " WHERE (client_ip = '" + client_ip + "' AND event_id = '" + event_id + "' AND src_path = '" + sqlite_op.sqlite_escape(src_path) + "' AND dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
    if(sqlite_op.sql_query(sql))
    {
        WNHDEBUG("删除记录成功");
        return true;
    }
    WNHDEBUG("删除记录失败");
    return false;
}

bool wnh_inotify_use_sqlite::fail_task_list_create_table() //创建一张数据表-失败任务列表
{
    WNHINFO("使用数据表" << TAIL_TASK_LIST_TABLE_NAME << "来进行数据记录");
    string sql;
    sql = sql + "CREATE TABLE IF NOT EXISTS " + TAIL_TASK_LIST_TABLE_NAME + " (id TEXT NOT NULL, client_ip TEXT NOT NULL, event_id INT NOT NULL, src_path TEXT NOT NULL, dst_path TEXT NOT NULL, update_date DATE NOT NULL, PRIMARY KEY (client_ip, src_path));";
    return sqlite_op.sql_query(sql);
    //sql = "";
    //sql = sql + "REPLACE INTO task_list_table (client_ip, event_id, src_path, dst_path, update_date) VALUES ('0', '0', '0', '0', datetime(CURRENT_TIMESTAMP,'localtime'));";
    //return sqlite_op.sql_query(sql);
}

bool wnh_inotify_use_sqlite::add_fail_task_info(const string & client_ip, const string & event_id, const string & src_path) //添加一行失败任务信息
{
    //REPLACE INTO fail_task_list_table (client_ip, event_id, src_path, dst_path, update_date) SELECT client_ip, event_id, src_path, dst_path, update_date FROM task_list_table WHERE (client_ip = '192.168.31.32' AND event_id = '1' AND src_path = '/tmp/filesync/src1/a.txt');
    string sql = "";
    sql = sql + "REPLACE INTO " + TAIL_TASK_LIST_TABLE_NAME + " (id, client_ip, event_id, src_path, dst_path, update_date) SELECT '" + get_uuid() + "', client_ip, event_id, src_path, dst_path, update_date FROM " + TASK_LIST_TABLE_NAME + " WHERE (client_ip = '" + client_ip + "' AND event_id = '" + event_id + "' AND src_path = '" + sqlite_op.sqlite_escape(src_path) + "');";
    if(!sqlite_op.sql_query(sql))
    {
        return false;
    }
    return delete_one_task(client_ip, event_id, src_path);
}

bool wnh_inotify_use_sqlite::add_fail_task_info(const string & client_ip, const string & event_id, const string & src_path, const string & dst_path) //添加一行失败任务信息
{
    //REPLACE INTO fail_task_list_table (client_ip, event_id, src_path, dst_path, update_date) SELECT client_ip, event_id, src_path, dst_path, update_date FROM task_list_table WHERE (client_ip = '192.168.31.32' AND event_id = '1' AND src_path = '/tmp/filesync/src1/a.txt');
    string sql = "";
    sql = sql + "REPLACE INTO " + TAIL_TASK_LIST_TABLE_NAME + " (id, client_ip, event_id, src_path, dst_path, update_date) SELECT '" + get_uuid() + "', client_ip, event_id, src_path, dst_path, update_date FROM " + TASK_LIST_TABLE_NAME + " WHERE (client_ip = '" + client_ip + "' AND event_id = '" + event_id + "' AND src_path = '" + sqlite_op.sqlite_escape(src_path) + "' AND dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
    if(!sqlite_op.sql_query(sql))
    {
        return false;
    }
    return delete_one_task(client_ip, event_id, src_path, dst_path);
}

bool wnh_inotify_use_sqlite::complete_task_list_create_table() //创建一张数据表-成功任务列表
{
    WNHINFO("使用数据表" << COMPLETE_TASK_LIST_TABLE_NAME << "来进行数据记录");
    string sql;
    sql = sql + "CREATE TABLE IF NOT EXISTS " + COMPLETE_TASK_LIST_TABLE_NAME + " (id TEXT NOT NULL, client_ip TEXT NOT NULL, event_id INT NOT NULL, src_path TEXT NOT NULL, dst_path TEXT NOT NULL, update_date DATE NOT NULL, complete_date DATE NOT NULL, read_id int NOL NULL, PRIMARY KEY (client_ip, event_id, src_path, dst_path, update_date, complete_date));";
    return sqlite_op.sql_query(sql);
    //sql = "";
    //sql = sql + "REPLACE INTO task_list_table (client_ip, event_id, src_path, dst_path, update_date) VALUES ('0', '0', '0', '0', datetime(CURRENT_TIMESTAMP,'localtime'));";
    //return sqlite_op.sql_query(sql);
}

bool wnh_inotify_use_sqlite::add_complete_task_info(const string & client_ip, const string & event_id, const string & src_path) //添加一行失败任务信息
{
    //REPLACE INTO complete_task_list_table (client_ip, event_id, src_path, dst_path, update_date) SELECT client_ip, event_id, src_path, dst_path, update_date FROM task_list_table WHERE (client_ip = '192.168.31.32' AND event_id = '1' AND src_path = '/tmp/filesync/src1/a.txt');
    string sql = "";
    sql = sql + "REPLACE INTO " + COMPLETE_TASK_LIST_TABLE_NAME + " (id, client_ip, event_id, src_path, dst_path, update_date, complete_date, read_id) SELECT '" + get_uuid() + "', client_ip, event_id, src_path, dst_path, update_date, datetime(CURRENT_TIMESTAMP,'localtime'), 0 FROM " + TASK_LIST_TABLE_NAME + " WHERE (client_ip = '" + client_ip + "' AND event_id = '" + event_id + "' AND src_path = '" + sqlite_op.sqlite_escape(src_path) + "');";
    if(!sqlite_op.sql_query(sql))
    {
        return false;
    }
    return delete_one_task(client_ip, event_id, src_path);
}

bool wnh_inotify_use_sqlite::add_complete_task_info(const string & client_ip, const string & event_id, const string & src_path, const string & dst_path) //添加一行失败任务信息
{
    //REPLACE INTO complete_task_list_table (client_ip, event_id, src_path, dst_path, update_date) SELECT client_ip, event_id, src_path, dst_path, update_date FROM task_list_table WHERE (client_ip = '192.168.31.32' AND event_id = '1' AND src_path = '/tmp/filesync/src1/a.txt');
    string sql = "";
    sql = sql + "REPLACE INTO " + COMPLETE_TASK_LIST_TABLE_NAME + " (id, client_ip, event_id, src_path, dst_path, update_date, complete_date, read_id) SELECT '" + get_uuid() + "', client_ip, event_id, src_path, dst_path, update_date, datetime(CURRENT_TIMESTAMP,'localtime'), 0 FROM " + TASK_LIST_TABLE_NAME + " WHERE (client_ip = '" + client_ip + "' AND event_id = '" + event_id + "' AND src_path = '" + sqlite_op.sqlite_escape(src_path) + "' AND dst_path = '" + sqlite_op.sqlite_escape(dst_path) + "');";
    if(!sqlite_op.sql_query(sql))
    {
        return false;
    }
    return delete_one_task(client_ip, event_id, src_path, dst_path);
}

unsigned long wnh_inotify_use_sqlite::get_event_list_num() //获取事件数量
{
    string sql = "";
    sql = sql + "SELECT count(1) FROM " + EVENT_LIST_TABLE_NAME + ";";
    string sql_result;
    if(!sqlite_op.sql_query(sql, sql_result))
    {
        WNHERROR("查询事件列表获取事件数量失败了");
        return -1;
    }
    if(sql_result.empty())
    {
        WNHDEBUG("查询事件列表获取到事件数量:0");
        return 0;
    }
    unsigned long num = stoul(sql_result, 0, 10);
    WNHDEBUG("查询事件列表获取到事件数量:" << num);
    return num;
}

unsigned long wnh_inotify_use_sqlite::get_task_list_num() //获取任务数量
{
    string sql = "";
    sql = sql + "SELECT count(1) FROM " + TASK_LIST_TABLE_NAME + ";";
    string sql_result;
    if(!sqlite_op.sql_query(sql, sql_result))
    {
        WNHERROR("查询任务列表获取任务数量失败了");
        return -1;
    }
    if(sql_result.empty())
    {
        WNHDEBUG("查询任务列表获取到任务数量:0");
        return 0;
    }
    unsigned long num = stoul(sql_result, 0, 10);
    WNHDEBUG("查询任务列表获取到任务数量:" << num);
    return num;
}

unsigned long wnh_inotify_use_sqlite::get_fail_task_list_num() //获取失败任务数量
{
    string sql = "";
    sql = sql + "SELECT count(1) FROM " + TAIL_TASK_LIST_TABLE_NAME + ";";
    string sql_result;
    if(!sqlite_op.sql_query(sql, sql_result))
    {
        WNHERROR("查询失败任务列表获取失败任务数量失败了");
        return -1;
    }
    if(sql_result.empty())
    {
        WNHDEBUG("查询失败任务列表获取到失败任务数量:0");
        return 0;
    }
    unsigned long num = stoul(sql_result, 0, 10);
    WNHDEBUG("查询失败任务列表获取到失败任务数量:" << num);
    return num;
}

unsigned long wnh_inotify_use_sqlite::get_task_list_num(const string & client_ip) //根据客户端IP,获取任务数量
{
    string sql = "";
    sql = sql + "SELECT count(1) FROM " + TASK_LIST_TABLE_NAME + " WHERE client_ip = '" +  client_ip + "';";
    string sql_result;
    if(!sqlite_op.sql_query(sql, sql_result))
    {
        WNHERROR("根据客户端IP查询任务列表获取任务数量失败了");
        return -1;
    }
    if(sql_result.empty())
    {
        WNHDEBUG("根据客户端IP查询任务列表获取到任务数量:0");
        return 0;
    }
    unsigned long num = stoul(sql_result, 0, 10);
    WNHDEBUG("根据客户端IP查询任务列表获取到任务数量:" << num);
    return num;
}

unsigned long wnh_inotify_use_sqlite::get_fail_task_list_num(const string & client_ip) //根据客户端IP,获取失败任务数量
{
    string sql = "";
    sql = sql + "SELECT count(1) FROM " + TAIL_TASK_LIST_TABLE_NAME + " WHERE client_ip = '" + client_ip + "';";
    string sql_result;
    if(!sqlite_op.sql_query(sql, sql_result))
    {
        WNHERROR("根据客户端IP查询失败任务列表获取失败任务数量失败了");
        return -1;
    }
    if(sql_result.empty())
    {
        WNHDEBUG("根据客户端IP查询失败任务列表获取到失败任务数量:0");
        return 0;
    }
    unsigned long num = stoul(sql_result, 0, 10);
    WNHDEBUG("根据客户端IP查询失败任务列表获取到失败任务数量:" << num);
    return num;
}

vector<vector<string> > wnh_inotify_use_sqlite::get_real_time_complete_task_list(const int & real_time, const int & num) //获取同步完成实时数据
{
    string sql = "";
    //SELECT client_ip, event_id, src_path, dst_path, update_date, complete_date, read_id FROM complete_task_list_table WHERE (datetime(CURRENT_TIMESTAMP, 'localtime', '-3000 seconds') < datetime(complete_date)) AND read_id = 0 ORDER BY complete_date ASC LIMIT 20;
    sql = sql + "SELECT client_ip, event_id, src_path, dst_path, update_date, complete_date, read_id, id FROM " + COMPLETE_TASK_LIST_TABLE_NAME + " WHERE (datetime(CURRENT_TIMESTAMP, 'localtime', '-" + to_string(real_time) + " seconds') < datetime(complete_date)) AND read_id = 0 ORDER BY complete_date ASC LIMIT " + to_string(num) + ";";
    vector<vector<string> > result_data;
    string **result;
    int nrow;
    int ncolumn;
    //sql_query(string sql, string **&result, int &nrow ,int &ncolumn);
    if(!sqlite_op.sql_query(sql, result, nrow, ncolumn))
    {
        WNHERROR("获取同步完成实时数据失败了");
        return result_data;
    }
    string temp_sql;
    for(int i = 0; i < nrow; i ++)
    {
        vector<string> temp_line_date;
        for(int j = 0; j < ncolumn; j ++)
        {
            temp_line_date.push_back(result[i][j]);
        }
        result_data.push_back(temp_line_date);
        temp_sql = temp_sql + "'" + result[i][ncolumn - 1] + "',";
        //WNHWARN("client_ip:" << result[i][0] << ", event_id:" << result[i][1] << ", src_path:" << result[i][2] << ", dst_path:" << result[i][3] << ", update_date:" << result[i][4] << ", complete_date:" << result[i][5] << ", read_id:" << result[i][6]);
    }
    sql = "";
    delete_last_char(temp_sql, ',');
    sql = sql + "UPDATE " + COMPLETE_TASK_LIST_TABLE_NAME + " SET read_id = '1' WHERE id in (" + temp_sql + ");";
    if(!sqlite_op.sql_query(sql))
    {
        WNHWARN("执行更新" << COMPLETE_TASK_LIST_TABLE_NAME << "表, read_id = '1', 失败了");
    }
    return result_data;
}

vector<vector<string> > wnh_inotify_use_sqlite::get_fail_task_list(const string & line, const string & num) //获取同步失败任务数据
{
    string sql = "";
    sql = sql + "SELECT client_ip, event_id, src_path, dst_path, update_date FROM " + TAIL_TASK_LIST_TABLE_NAME + " ORDER BY update_date ASC LIMIT " + num + " OFFSET " + line + ";";
    vector<vector<string> > result_data;
    string **result;
    int nrow;
    int ncolumn;
    //sql_query(string sql, string **&result, int &nrow ,int &ncolumn);
    if(!sqlite_op.sql_query(sql, result, nrow, ncolumn))
    {
        WNHERROR("获取同步完成实时数据失败了");
        return result_data;
    }
    string temp_sql;
    for(int i = 0; i < nrow; i ++)
    {
        vector<string> temp_line_date;
        for(int j = 0; j < ncolumn; j ++)
        {
            temp_line_date.push_back(result[i][j]);
        }
        result_data.push_back(temp_line_date);
        temp_sql = temp_sql + "'" + result[i][ncolumn - 1] + "',";
        //WNHWARN("client_ip: " << result[i][0] << ", event_id:" << result[i][1] << ", src_path:" << result[i][2] << ", dst_path:" << result[i][3] << ", update_date:" << result[i][4]);
    }
    return result_data;
}
