#include "wnh_inotify_use_sqlite.h"

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
