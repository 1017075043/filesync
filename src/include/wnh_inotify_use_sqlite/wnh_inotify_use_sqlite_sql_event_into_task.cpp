#include "wnh_inotify_use_sqlite.h"

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
                sql = sql + "REPLACE INTO " + TASK_LIST_TABLE_NAME + " (id, client_ip, event_id, src_path, dst_path, update_date, sync_lock) VALUES ('" + get_uuid() + "', '" + client_ip[n] + "', '" + event_id + "', '" + sqlite_op.sqlite_escape(src_path) + "', '" + sqlite_op.sqlite_escape(dst_path) + "', datetime(CURRENT_TIMESTAMP,'localtime'), 0);";
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
                sql = sql + "REPLACE INTO " + TASK_LIST_TABLE_NAME + " (id, client_ip, event_id, src_path, dst_path, update_date, sync_lock) VALUES ('" + get_uuid() + "', '" + client_ip[n] + "', '" + event_id + "', '" + sqlite_op.sqlite_escape(src_path) + "', '" + sqlite_op.sqlite_escape(dst_path) + "', datetime(CURRENT_TIMESTAMP,'localtime'), 0);";
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
