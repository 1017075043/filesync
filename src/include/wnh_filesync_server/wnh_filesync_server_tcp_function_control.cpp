#include "wnh_filesync_server.h"

bool wnh_filesync_server::accept_get_sync_fail_task_list_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收获取同步失败任务列表信息
{
    if(info.substr(0, strlen(WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO)) == WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO)
    {
        string sync_fail_task_list_file_path;
        sync_fail_task_list_file_path = sync_fail_task_list_file_path + DEFAULT_SYNC_FAIL_TASK_LIST_PATH_FORMAT;
        string line = info.substr(strlen(WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO), info.find(",") - strlen(WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO));
        string num = info.substr(info.find(",") + 1);
        //WNHWARN("line:" << line << ", num:" << num);
        if(create_sync_fail_task_list_info(sync_fail_task_list_file_path, line, num) == false)
        {
            sync_fail_task_list_file_path.clear();
            sync_fail_task_list_file_path = sync_fail_task_list_file_path + WNH_FILESYNC_NOT_OR_FAIL_SYNC_FAIL_TASk_LIST_INFO;
        }
        if(send_info(nfp, WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO + sync_fail_task_list_file_path))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收获取同步传输过程信息, 同步传输过程信息文件路径:" << sync_fail_task_list_file_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收获取同步传输过程信息时失败了, 同步传输过程信息文件路径:" << sync_fail_task_list_file_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::create_sync_fail_task_list_info(const string & sync_fail_task_list_file_path, const string & line, const string & num) //创建同步失败任务列表信息文件
{
    vector<vector<string> > result_data = watch.get_fail_task_list(line, num);
    //for(int i = 0; i < (int)result_data.size(); i++)
    //{
    //    WNHWARN("client_ip: " << result_data[i][0] << ", event_id: " << result_data[i][1] << ", src_path: " << result_data[i][2] << ", dst_path: " << result_data[i][3] << ", update_date: " << result_data[i][4]);
    //}

    ofstream file_open;
    file_open.open(sync_fail_task_list_file_path, ios::out | ios::trunc);
    if(!file_open.is_open())
    {
        WNHERROR("打开文件" << sync_fail_task_list_file_path <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    for(int i = 0; i < (int)result_data.size(); i++)
    {
        file_open << "[" << WNH_FILESYNC_RULE_FAIL_TASk_LIST_ID << "_" << i << "]" << endl;
        file_open << "client_ip=" << result_data[i][0] << endl;
        file_open << "event_id=" << watch.event_transform(result_data[i][1]) << endl;
        file_open << "src_path=" << result_data[i][2] << endl;
        file_open << "dst_path=" << result_data[i][3] << endl;
        file_open << "update_date=" << result_data[i][4] << endl;
        WNHDEBUG("client_ip: " << result_data[i][0] << ", event_id: " << result_data[i][1] << ", src_path: " << result_data[i][2] << ", dst_path: " << result_data[i][3] << ", update_date: " << result_data[i][4]);
    }
    if((int)result_data.size() == 0)
    {
        WNHDEBUG("查询到当前不存在同步失败任务列表数据");
        return false;
    }
    file_open.close();
    return true;
}

bool wnh_filesync_server::accept_get_sync_transfer_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收获取同步传输过程信息
{
    if(info.substr(0, strlen(WNH_FILESYNC_SYNC_TRANSFER_INFO)) == WNH_FILESYNC_SYNC_TRANSFER_INFO)
    {
        string sync_transfer_file_path;
        sync_transfer_file_path = sync_transfer_file_path + DEFAULT_SYNC_TRANSFER_PATH_FORMAT;
        if(create_sync_transfer_info(sync_transfer_file_path) == false)
        {
            sync_transfer_file_path.clear();
            sync_transfer_file_path = sync_transfer_file_path + WNH_FILESYNC_NOT_OR_FAIL_SYNC_TRANSFER_INFO;
        }
        if(send_info(nfp, WNH_FILESYNC_SYNC_TRANSFER_INFO + sync_transfer_file_path))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收获取同步传输过程信息, 同步传输过程信息文件路径:" << sync_transfer_file_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收获取同步传输过程信息时失败了, 同步传输过程信息文件路径:" << sync_transfer_file_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::create_sync_transfer_info(const string & sync_transfer_file_path) //创建同步传输过程文件
{
    vector<vector<string> > result_data = watch.get_real_time_complete_task_list(SYNC_TRANSFER_MAXIMUM_TIME, SYNC_TRANSFER_MAXIMUM_LINE_NUM);
    //for(int i = 0; i < (int)result_data.size(); i++)
    //{
    //    WNHWARN("client_ip: " << result_data[i][0] << ", event_id: " << result_data[i][1] << ", src_path: " << result_data[i][2] << ", dst_path: " << result_data[i][3] << ", update_date: " << result_data[i][4] << ", complete_date: " << result_data[i][5] << ", read_id:" << result_data[i][6]);
    //}

    ofstream file_open;
    file_open.open(sync_transfer_file_path, ios::out | ios::trunc);
    if(!file_open.is_open())
    {
        WNHERROR("打开文件" << sync_transfer_file_path <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    for(int i = 0; i < (int)result_data.size(); i++)
    {
        file_open << "[" << WNH_FILESYNC_RULE_TRANSFER_ID << "_" << i << "]" << endl;
        file_open << "client_ip=" << result_data[i][0] << endl;
        file_open << "event_id=" << watch.event_transform(result_data[i][1]) << endl;
        //file_open << "src_path=" << result_data[i][2] << endl;
        file_open << "dst_path=" << result_data[i][3] << endl;
        //file_open << "update_date=" << result_data[i][4] << endl;
        file_open << "complete_date=" << result_data[i][5] << endl;
        WNHDEBUG("client_ip: " << result_data[i][0] << ", event_id: " << result_data[i][1] << ", src_path: " << result_data[i][2] << ", dst_path: " << result_data[i][3] << ", update_date: " << result_data[i][4] << ", complete_date: " << result_data[i][5] << ", read_id:" << result_data[i][6]);
    }
    if((int)result_data.size() == 0)
    {
        WNHDEBUG("查询到当前不存在实时同步传输过程数据");
        return false;
    }
    file_open.close();
    return true;
}

bool wnh_filesync_server::accept_get_server_status_info_v1(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收获取服务端状态信息
{
    static int temp_client_nfp = 0;
    static string temp_client = "";
    static int client_port = 0;
    static string server_status_info_temp = "";
    if(info.substr(0, strlen(WNH_FILESYNC_GET_SERVER_STATUS_INFO)) == WNH_FILESYNC_GET_SERVER_STATUS_INFO)
    {
        string server_status_info = create_server_status_info();
        if(client_port == CONNECT_INFO.client_port && temp_client_nfp == CONNECT_INFO.client_nfp && temp_client == CONNECT_INFO.client_ip && server_status_info_temp == server_status_info)
        {
            server_status_info = WNH_FILESYNC_GET_SERVER_STATUS_IGNORE_INFO;
        }
        else
        {
            client_port = CONNECT_INFO.client_port;
            temp_client_nfp = CONNECT_INFO.client_nfp;
            temp_client = CONNECT_INFO.client_ip;
            server_status_info_temp = server_status_info;
        }
        if(send_info(nfp, WNH_FILESYNC_GET_SERVER_STATUS_INFO + server_status_info))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收接收获取服务端状态信息, 服务端状态:" << server_status_info);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收获取服务端状态信息时失败了, 服务端状态:" << server_status_info);
        return true;
    }
    return false;
}

bool wnh_filesync_server::accept_get_server_status_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收获取服务端状态信息
{
    static int temp_client_nfp = 0;
    static string temp_client = "";
    static int client_port = 0;
    static string server_status_info_file_hash = "";
    if(info.substr(0, strlen(WNH_FILESYNC_GET_SERVER_STATUS_INFO)) == WNH_FILESYNC_GET_SERVER_STATUS_INFO)
    {
        string server_status_info_file_path;
        server_status_info_file_path = server_status_info_file_path + DEFAULT_SERVER_STATUS_PATH_FORMAT;
        if(!create_server_status_info(server_status_info_file_path))
        {
            server_status_info_file_path = WNH_FILESYNC_GET_SERVER_STATUS_FAIL_INFO;
        }
        else
        {
            string temp_file_hash = file_hash.get_file_md5(server_status_info_file_path);
            if(client_port == CONNECT_INFO.client_port && temp_client_nfp == CONNECT_INFO.client_nfp && temp_client == CONNECT_INFO.client_ip && server_status_info_file_hash == temp_file_hash)
            {
                server_status_info_file_path = WNH_FILESYNC_GET_SERVER_STATUS_IGNORE_INFO;
            }
            else
            {
                client_port = CONNECT_INFO.client_port;
                temp_client_nfp = CONNECT_INFO.client_nfp;
                temp_client = CONNECT_INFO.client_ip;
                server_status_info_file_hash = temp_file_hash;
            }
        }
        //server_status_info_file_path = WNH_FILESYNC_GET_SERVER_STATUS_INFO + server_status_info_file_path;
        if(send_info(nfp, WNH_FILESYNC_GET_SERVER_STATUS_INFO + server_status_info_file_path))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收获取服务端状态信息, 服务端状态文件路径:" << server_status_info_file_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收获取服务端状态信息时失败了, 服务端状态文件路径:" << server_status_info_file_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::create_server_status_info(const string & server_status_info_file_path) //创建服务端状态文件
{
    int online_client_num = 0; //在线客户端数量
    int offline_client_num = 0; //离线客户端数量
    unsigned long task_num = 0; //全部任务数(全部客户端)
    unsigned long complete_task_num = 0; //已完成任务数(全部客户端)
    unsigned long unfinished_task_num = 0; //未完成任务数(全部客户端)
    unsigned long fail_task_num = 0; //失败任务数(全部客户端)
    unsigned long event_num = 0; //未转化事件数量(全部客户端)

    for(unsigned int i= 0; i < client_num; i ++)
    {
        if((client_info+i)->status)
        {
            online_client_num ++;
        }
        complete_task_num += (client_info+i)->task_num;
        fail_task_num += (client_info+i)->fail_task_num;
    }
    offline_client_num = client_num - online_client_num;
    unfinished_task_num = watch.get_task_list_num() - 1;
    event_num = watch.get_event_list_num();
    task_num = complete_task_num + unfinished_task_num + fail_task_num;
    WNHDEBUG("pid:" << pid << ", 启动时间:" << start_time << ", 客户端数量:" << client_num << ", 在线客户端数量:" << online_client_num << ", 离线客户端数量:" << offline_client_num << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数" << fail_task_num << ", 未转化事件数量" << event_num);

    ofstream file_open;
    file_open.open(server_status_info_file_path, ios::out | ios::trunc);
    if(!file_open.is_open())
    {
        WNHERROR("打开文件" << server_status_info_file_path <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    file_open << "[" << WNH_FILESYNC_SERVER_STATUS_ID << "]" << endl;
    file_open << "pid=" << pid << endl; //服务端进程号
    file_open << "start_time=" << start_time << endl; //服务端启动时间
    file_open << "client_num=" << client_num << endl; //客户端全部数量
    file_open << "online_client_num=" << online_client_num << endl; //在线客户端数量
    file_open << "offline_client_num=" << offline_client_num << endl; //离线客户端数量
    file_open << "task_num=" << task_num << endl; //全部任务数
    file_open << "complete_task_num=" << complete_task_num << endl; //已完成任务数
    file_open << "unfinished_task_num=" << unfinished_task_num << endl; //未完成任务数
    file_open << "fail_task_num=" << fail_task_num << endl; //失败任务数
    file_open << "event_num=" << event_num << endl; //未转化事件数量
    file_open.close();
    return true;
}

string wnh_filesync_server::create_server_status_info() //创建服务端状态信息
{
    int online_client_num = 0; //在线客户端数量
    int offline_client_num = 0; //离线客户端数量
    unsigned long task_num = 0; //全部任务数(全部客户端)
    unsigned long complete_task_num = 0; //已完成任务数(全部客户端)
    unsigned long unfinished_task_num = 0; //未完成任务数(全部客户端)
    unsigned long fail_task_num = 0; //失败任务数(全部客户端)
    unsigned long event_num = 0; //未转化事件数量(全部客户端)

    //for(unsigned int i= 0; i < client_num; i ++)
    //{
    //    if((client_info+i)->status)
    //    {
    //        online_client_num ++;
    //        complete_task_num += (client_info+i)->task_num;
    //        fail_task_num += (client_info+i)->fail_task_num;
    //    }
    //}
    for(unsigned int i= 0; i < client_num; i ++)
    {
        if((client_info+i)->status)
        {
            online_client_num ++;
        }
        complete_task_num += (client_info+i)->task_num;
        fail_task_num += (client_info+i)->fail_task_num;
    }

    offline_client_num = client_num - online_client_num;
    unfinished_task_num = watch.get_task_list_num() - 1;
    event_num = watch.get_event_list_num();
    task_num = complete_task_num + unfinished_task_num + fail_task_num;
    WNHDEBUG("pid:" << pid << ", 启动时间:" << start_time << ", 客户端数量:" << client_num << ", 在线客户端数量:" << online_client_num << ", 离线客户端数量:" << offline_client_num << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数" << fail_task_num << ", 未转化事件数量" << event_num);
    string resule = to_string(pid) + "," + start_time + "," + to_string(client_num) + "," + to_string(online_client_num) + "," + to_string(offline_client_num) + "," + to_string(task_num) + "," + to_string(complete_task_num) + "," + to_string(unfinished_task_num) + "," + to_string(fail_task_num) + "," + to_string(event_num);
    return resule;
}

bool wnh_filesync_server::accept_get_client_status_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收获取客户端状态信息
{
    static int temp_client_nfp = 0;
    static string temp_client = "";
    static int client_port = 0;
    static string client_status_info_file_hash = "";
    if(info.substr(0, strlen(WNH_FILESYNC_GET_CLIENT_STATUS_INFO)) == WNH_FILESYNC_GET_CLIENT_STATUS_INFO)
    {
        string client_status_info_file_path;
        client_status_info_file_path = client_status_info_file_path + DEFAULT_client_STATUS_PATH_FORMAT;
        if(!create_client_status_info(client_status_info_file_path))
        {
            client_status_info_file_path = WNH_FILESYNC_GET_CLIENT_STATUS_FAIL_INFO;
        }
        else
        {
            string temp_file_hash = file_hash.get_file_md5(client_status_info_file_path);
            if(client_port == CONNECT_INFO.client_port && temp_client_nfp == CONNECT_INFO.client_nfp && temp_client == CONNECT_INFO.client_ip && client_status_info_file_hash == temp_file_hash)
            {
                client_status_info_file_path = WNH_FILESYNC_GET_CLIENT_STATUS_IGNORE_INFO;
            }
            else
            {
                client_port = CONNECT_INFO.client_port;
                temp_client_nfp = CONNECT_INFO.client_nfp;
                temp_client = CONNECT_INFO.client_ip;
                client_status_info_file_hash = temp_file_hash;
            }
        }
        if(send_info(nfp, WNH_FILESYNC_GET_CLIENT_STATUS_INFO + client_status_info_file_path))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收获取客户端状态信息, 客户端状态文件路径:" << client_status_info_file_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收获取客户端状态信息时失败了, 客户端状态文件路径:" << client_status_info_file_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::create_client_status_info(const string & client_status_info_file_path) //创建客户端状态文件
{
    ofstream file_open;
    file_open.open(client_status_info_file_path, ios::out | ios::trunc);
    if(!file_open.is_open())
    {
        WNHERROR("打开文件" << client_status_info_file_path <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    unsigned long unfinished_task_num = 0; //未完成任务数
    unsigned long fail_task_num = 0; //失败任务数
    unsigned long task_num = 0; //全部任务数
    int status = 0; //客户端状态
    for(unsigned int i= 0; i < client_num; i ++)
    {
        unfinished_task_num = 0; //未完成任务数
        fail_task_num = 0; //失败任务数
        task_num = 0; //全部任务数
        status = 0; //客户端状态
        unfinished_task_num = watch.get_task_list_num((client_info+i)->client_ip);
        fail_task_num = watch.get_fail_task_list_num((client_info+i)->client_ip);
        task_num = unfinished_task_num + (client_info+i)->task_num + fail_task_num;
        if((client_info+i)->status)
        {
            status = 1;
        }
        else
        {
            status = 0;
        }

        file_open << "[" << WNH_FILESYNC_CLIENT_STATUS_ID << "_" << i << "]" << endl;
        file_open << "client_ip=" << (client_info+i)->client_ip << endl; //客户端IP
        file_open << "status=" << status << endl; //状态
        file_open << "begin_connect_time=" << (client_info+i)->begin_connect_time << endl; //开始时间
        file_open << "last_connect_time=" << (client_info+i)->last_connect_time << endl; //最后活动时间
        file_open << "task_num=" << task_num << endl; //全部任务数
        file_open << "complete_task_num=" << (client_info+i)->task_num << endl; //已完成任务数
        file_open << "unfinished_task_num=" << unfinished_task_num << endl; //未完成任务数
        file_open << "fail_task_num=" << (client_info+i)->fail_task_num << endl; //失败任务数
        file_open << endl;
        WNHDEBUG("客户端IP:" << (client_info+i)->client_ip << ", 状态:" << status << ", 启动时间:" << (client_info+i)->begin_connect_time << ", 最后活动时间:" << (client_info+i)->last_connect_time << ", 全部任务数:" << task_num << ", 已完成任务数:" << (client_info+i)->task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数:" << (client_info+i)->fail_task_num );
    }
    file_open.close();
    return true;
}

bool wnh_filesync_server::accept_get_sync_rule_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收获取同步规则信息信息
{
    if(info.substr(0, strlen(WNH_FILESYNC_GET_SYNC_RULE_INFO)) == WNH_FILESYNC_GET_SYNC_RULE_INFO)
    {
        string sync_rule_info_file_path;
        sync_rule_info_file_path = sync_rule_info_file_path + DEFAULT_SYNC_RULE_PATH_FORMAT;
        if(!create_sync_rule_info(sync_rule_info_file_path))
        {
            sync_rule_info_file_path = WNH_FILESYNC_GET_SYNC_RULE_FAIL_INFO;
        }
        if(send_info(nfp, WNH_FILESYNC_GET_SYNC_RULE_INFO + sync_rule_info_file_path))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收获取同步规则信息, 同步规则信息文件路径:" << sync_rule_info_file_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收获取同步规则信息时失败了, 同步规则信息文件路径:" << sync_rule_info_file_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::create_sync_rule_info(const string & sync_rule_info_file_path) //创建同步规则信息文件
{
    ofstream file_open;
    file_open.open(sync_rule_info_file_path, ios::out | ios::trunc);
    if(!file_open.is_open())
    {
        WNHERROR("打开文件" << sync_rule_info_file_path <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    set<string>::iterator it; //定义前向迭代器
    for(int i = 0; i < sync_rule_num; i++)
    {
        file_open << "[" << WNH_FILESYNC_GET_SYNC_RULE_ID << "_" << i << "]" << endl;
        file_open << "src_dir=" << sync_rule[i].src_dir << endl;
        for(int n = 0; n < (int)sync_rule[i].dst_dir.size(); n++)
        {
            file_open << "dst_ip_and_dir=" << sync_rule[i].dst_ip[n] << "," << sync_rule[i].dst_dir[n] << endl;
        }
        for(it = sync_rule[i].ignore_rule.begin(); it != sync_rule[i].ignore_rule.end(); it++)
        {
            file_open << "ignore_rule=" << *it << endl;
        }
        for(it = sync_rule[i].ignore_dir.begin(); it != sync_rule[i].ignore_dir.end(); it++)
        {
            file_open << "ignore_dir=" << *it << endl;
        }
        file_open << endl;
    }
    file_open.close();
    return true;
}

bool wnh_filesync_server::accept_get_license_info(const int & nfp, const string & info, const CONNECT_INFO & CONNECT_INFO) //接收获取许可信息
{
    if(info.substr(0, strlen(WNH_FILESYNC_GET_LICENSE_INFO)) == WNH_FILESYNC_GET_LICENSE_INFO)
    {
        get_license_info();
        string license_info_temp;
        //lic.file_path; //许可文件路径
        //lic.begin_time; //开始时间
        //lic.end_time; //结束时间
        //lic.all_time; //有效期
        //lic.remaining_time; //剩余有效期
        license_info_temp = license_info_temp + lic.file_path + "," + lic.begin_time + "," + lic.end_time + "," + to_string(lic.all_time) + "," + to_string(lic.remaining_time) + "," + lic.serial_number;
        if(send_info(nfp, WNH_FILESYNC_GET_LICENSE_INFO + license_info_temp))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收获取许可信息, 许可信息:" << license_info_temp);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收获取许可信息时失败了, 许可信息:" << license_info_temp);
        return true;
    }
    return false;
}
