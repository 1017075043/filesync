#include "wnh_inotify_use_sqlite.h"

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

vector<vector<string> > wnh_inotify_use_sqlite::get_task_list(const string & line, const string & num) //获取等待同步任务列表数据
{
    string sql = "";
    sql = sql + "SELECT client_ip, event_id, src_path, dst_path, update_date FROM " + TASK_LIST_TABLE_NAME + " ORDER BY update_date ASC LIMIT " + num + " OFFSET " + line + ";";
    //WNHWARN(sql);
    vector<vector<string> > result_data;
    string **result;
    int nrow;
    int ncolumn;
    //sql_query(string sql, string **&result, int &nrow ,int &ncolumn);
    if(!sqlite_op.sql_query(sql, result, nrow, ncolumn))
    {
        WNHERROR("获取等待同步任务列表数据失败了");
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
