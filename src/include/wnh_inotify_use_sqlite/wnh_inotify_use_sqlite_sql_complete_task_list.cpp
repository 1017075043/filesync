#include "wnh_inotify_use_sqlite.h"

bool wnh_inotify_use_sqlite::complete_task_list_create_table() //创建一张数据表-成功任务列表
{
    WNHINFO("使用数据表" << COMPLETE_TASK_LIST_TABLE_NAME << "来进行数据记录");
    string sql;
    sql = sql + "CREATE TABLE IF NOT EXISTS " + COMPLETE_TASK_LIST_TABLE_NAME + " (id TEXT NOT NULL, client_ip TEXT NOT NULL, event_id INT NOT NULL, src_path TEXT NOT NULL, dst_path TEXT NOT NULL, update_date DATE NOT NULL, complete_date DATE NOT NULL, read_id int NOL NULL, PRIMARY KEY (id, client_ip, event_id, src_path, dst_path, update_date, complete_date));";
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
