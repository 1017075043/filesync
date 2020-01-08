#include "wnh_inotify_use_sqlite.h"

bool wnh_inotify_use_sqlite::fail_task_list_create_table() //创建一张数据表-失败任务列表
{
    WNHINFO("使用数据表" << TAIL_TASK_LIST_TABLE_NAME << "来进行数据记录");
    string sql;
    sql = sql + "CREATE TABLE IF NOT EXISTS " + TAIL_TASK_LIST_TABLE_NAME + " (id TEXT NOT NULL, client_ip TEXT NOT NULL, event_id INT NOT NULL, src_path TEXT NOT NULL, dst_path TEXT NOT NULL, update_date DATE NOT NULL, PRIMARY KEY (id, client_ip, src_path, dst_path));";
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

vector<vector<string> > wnh_inotify_use_sqlite::get_fail_task_list(const string & line, const string & num) //获取同步失败任务数据
{
    string sql = "";
    sql = sql + "SELECT client_ip, event_id, src_path, dst_path, update_date FROM " + TAIL_TASK_LIST_TABLE_NAME + " ORDER BY update_date ASC LIMIT " + num + " OFFSET " + line + ";";
    //WNHWARN(sql);
    vector<vector<string> > result_data;
    string **result;
    int nrow;
    int ncolumn;
    //sql_query(string sql, string **&result, int &nrow ,int &ncolumn);
    if(!sqlite_op.sql_query(sql, result, nrow, ncolumn))
    {
        WNHERROR("获取同步失败任务数据失败了");
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
