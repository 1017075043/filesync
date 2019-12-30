#include "wnh_filesync_control.h"

void wnh_filesync_control::get_server_status_info_while() //获取服务端状态信息(循环)
{
    while(1)
    {
        if(!unblock_connect(ip, to_string(port)))
        {
            WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
            close(socket_num);
            return;
        }
        if(!send_start_session_info())
        {
            close(socket_num);
            return;
        }
        string server_status_info_file_path;
        for(int i = 0; i < MAXIMUM_NUMBER_OF_REQUESTS_PER_SESSION; i++)
        {
            if(!send_get_server_status_info(server_status_info_file_path))
            {
                close(socket_num);
                return;
            }

            if(server_status_info_file_path != WNH_FILESYNC_GET_SERVER_STATUS_IGNORE_INFO)
            {
                if(!download_file(server_status_info_file_path, server_status_info_file_path + SERVER_STATUS_INFO_FILE_SUFFIX))
                {
                    close(socket_num);
                    return;
                }
                show_server_status_info(server_status_info_file_path + SERVER_STATUS_INFO_FILE_SUFFIX); //显示服务端状态
            }
            if(i != 9)
            {
                sleep(REQUEST_INTERVAL);
            }
        }
        send_end_session_info();
        sleep(REQUEST_INTERVAL);
    }
    return;
}

void wnh_filesync_control::get_server_status_info() //获取服务端状态信息
{
    if(!unblock_connect(ip, to_string(port)))
    {
        WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
        close(socket_num);
        return;
    }
    if(!send_start_session_info())
    {
        close(socket_num);
        return;
    }
    string server_status_info_file_path;
    if(!send_get_server_status_info(server_status_info_file_path))
    {
        close(socket_num);
        return;
    }
    if(!download_file(server_status_info_file_path, server_status_info_file_path + SERVER_STATUS_INFO_FILE_SUFFIX))
    {
        close(socket_num);
        return;
    }
    show_server_status_info(server_status_info_file_path + SERVER_STATUS_INFO_FILE_SUFFIX); //显示服务端状态
    send_end_session_info();
    return;
}

bool wnh_filesync_control::send_get_server_status_info(string & server_status_info_file_path) //向服务器发送获取服务端状态信息信号, 且获取服务端状态信息文件路径
{
    if(send_info(WNH_FILESYNC_GET_SERVER_STATUS_INFO))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取服务端状态信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_GET_SERVER_STATUS_INFO)) == WNH_FILESYNC_GET_SERVER_STATUS_INFO)
        {
            server_status_info_file_path = info.substr(strlen(WNH_FILESYNC_GET_SERVER_STATUS_INFO));
            WNHDEBUG(SERVER_INFO_LOGS <<  "向服务器请求获取服务端状态信息成功, 服务端状态信息文件路径:" << server_status_info_file_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取服务端状态信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取服务端状态信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_control::show_server_status_info(const string & server_status_info_file_path) //显示服务端状态
{
    static bool temp_id = false;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(7);
    }
    else
    {
        temp_id = true;
    }
    status_info.read_config_ini(server_status_info_file_path, false);
    string pid; //服务端进程号
    string start_time; //服务端启动时间
    string client_num; //客户端全部数量
    string online_client_num; //在线客户端数量
    string offline_client_num; //离线客户端数量
    string task_num; //全部任务数(全部客户端)
    string complete_task_num; //已完成任务数(全部客户端)
    string unfinished_task_num; //未完成任务数(全部客户端)
    string fail_task_num; //失败任务数(全部客户端)
    string event_num; //未转化事件数量(全部客户端)

    pid = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "pid");
    start_time = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "start_time");
    client_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "client_num");
    online_client_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "online_client_num");
    offline_client_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "offline_client_num");
    task_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "task_num");
    complete_task_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "complete_task_num");
    unfinished_task_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "unfinished_task_num");
    fail_task_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "fail_task_num");
    event_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "event_num");

    WNHDEBUG("pid:" << pid << ", 启动时间:" << start_time << ", 客户端数量:" << client_num << ", 在线客户端数量:" << online_client_num << ", 离线客户端数量:" << offline_client_num << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数" << fail_task_num << ", 未转化事件数量" << event_num);
    show_server_status_info_son(pid, start_time, client_num, online_client_num, offline_client_num, task_num, complete_task_num, unfinished_task_num, fail_task_num, event_num);

    //status_info.clean_configure_ini();
    if(unlink(server_status_info_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << server_status_info_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return true;
}

int wnh_filesync_control::show_server_status_info(const string & server_status_info_file_path, const int & offset) //显示服务端状态
{
    static bool temp_id = false;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(offset);
    }
    else
    {
        temp_id = true;
    }
    status_info.read_config_ini(server_status_info_file_path, false);
    string pid; //服务端进程号
    string start_time; //服务端启动时间
    string client_num; //客户端全部数量
    string online_client_num; //在线客户端数量
    string offline_client_num; //离线客户端数量
    string task_num; //全部任务数(全部客户端)
    string complete_task_num; //已完成任务数(全部客户端)
    string unfinished_task_num; //未完成任务数(全部客户端)
    string fail_task_num; //失败任务数(全部客户端)
    string event_num; //未转化事件数量(全部客户端)

    pid = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "pid");
    start_time = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "start_time");
    client_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "client_num");
    online_client_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "online_client_num");
    offline_client_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "offline_client_num");
    task_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "task_num");
    complete_task_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "complete_task_num");
    unfinished_task_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "unfinished_task_num");
    fail_task_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "fail_task_num");
    event_num = status_info.get_conf_one(WNH_FILESYNC_SERVER_STATUS_ID, "event_num");

    WNHDEBUG("pid:" << pid << ", 启动时间:" << start_time << ", 客户端数量:" << client_num << ", 在线客户端数量:" << online_client_num << ", 离线客户端数量:" << offline_client_num << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数" << fail_task_num << ", 未转化事件数量" << event_num);
    show_server_status_info_son(pid, start_time, client_num, online_client_num, offline_client_num, task_num, complete_task_num, unfinished_task_num, fail_task_num, event_num);

    //status_info.clean_configure_ini();
    if(unlink(server_status_info_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << server_status_info_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return 7;
}

void wnh_filesync_control::get_server_status_info_while_v1() //获取服务端状态信息(循环)
{
    while(1)
    {
        if(!unblock_connect(ip, to_string(port)))
        {
            WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
            close(socket_num);
            return;
        }
        if(!send_start_session_info())
        {
            close(socket_num);
            return;
        }
        string server_status_info;
        for(int i = 0; i < MAXIMUM_NUMBER_OF_REQUESTS_PER_SESSION; i++)
        {
            if(!send_get_server_status_info_v1(server_status_info))
            {
                close(socket_num);
                return;
            }
            if(server_status_info != WNH_FILESYNC_GET_SERVER_STATUS_IGNORE_INFO)
            {
                show_server_status_info_v1(server_status_info); //显示服务端状态
            }
            if(i != 9)
            {
                sleep(REQUEST_INTERVAL);
            }
        }
        send_end_session_info();
        sleep(REQUEST_INTERVAL);
    }
    return;
}

void wnh_filesync_control::get_server_status_info_v1() //获取服务端状态信息
{
    if(!unblock_connect(ip, to_string(port)))
    {
        WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
        close(socket_num);
        return;
    }
    if(!send_start_session_info())
    {
        close(socket_num);
        return;
    }
    string server_status_info;
    if(!send_get_server_status_info_v1(server_status_info))
    {
        close(socket_num);
        return;
    }
    show_server_status_info_v1(server_status_info); //显示服务端状态
    send_end_session_info();
    return;
}

bool wnh_filesync_control::send_get_server_status_info_v1(string & server_status_info) //向服务器发送获取服务端状态信息信号, 且获取服务端状态信息
{
    if(send_info(WNH_FILESYNC_GET_SERVER_STATUS_INFO))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取服务端状态信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_GET_SERVER_STATUS_INFO)) == WNH_FILESYNC_GET_SERVER_STATUS_INFO)
        {
            server_status_info = info.substr(strlen(WNH_FILESYNC_GET_SERVER_STATUS_INFO));
            WNHDEBUG(SERVER_INFO_LOGS <<  "向服务器请求获取服务端状态信息成功, 服务端状态信息:" << server_status_info);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取服务端状态信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取服务端状态信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_control::show_server_status_info_v1(const string & server_status_info) //显示服务端状态
{
    static bool temp_id = false;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(8);
    }
    else
    {
        temp_id = true;
    }
    string server_status_info_temp = server_status_info;
    string pid; //服务端进程号
    string start_time; //服务端启动时间
    string client_num; //客户端全部数量
    string online_client_num; //在线客户端数量
    string offline_client_num; //离线客户端数量
    string task_num; //全部任务数(全部客户端)
    string complete_task_num; //已完成任务数(全部客户端)
    string unfinished_task_num; //未完成任务数(全部客户端)
    string fail_task_num; //失败任务数(全部客户端)
    string event_num; //未转化事件数量(全部客户端)
    pid = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    start_time = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    client_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    online_client_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    offline_client_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    task_num =server_status_info_temp. substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    complete_task_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    unfinished_task_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    fail_task_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    event_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));

    WNHDEBUG("pid:" << pid << ", 启动时间:" << start_time << ", 客户端数量:" << client_num << ", 在线客户端数量:" << online_client_num << ", 离线客户端数量:" << offline_client_num << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数" << fail_task_num << ", 未转化事件数量" << event_num);
    show_server_status_info_son(pid, start_time, client_num, online_client_num, offline_client_num, task_num, complete_task_num, unfinished_task_num, fail_task_num, event_num);
    return true;
}

int wnh_filesync_control::show_server_status_info_v1(const string & server_status_info, const int & offset) //显示服务端状态
{
    static bool temp_id = false;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(offset);
    }
    else
    {
        temp_id = true;
    }
    string server_status_info_temp = server_status_info;
    string pid; //服务端进程号
    string start_time; //服务端启动时间
    string client_num; //客户端全部数量
    string online_client_num; //在线客户端数量
    string offline_client_num; //离线客户端数量
    string task_num; //全部任务数(全部客户端)
    string complete_task_num; //已完成任务数(全部客户端)
    string unfinished_task_num; //未完成任务数(全部客户端)
    string fail_task_num; //失败任务数(全部客户端)
    string event_num; //未转化事件数量(全部客户端)
    pid = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    start_time = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    client_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    online_client_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    offline_client_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    task_num =server_status_info_temp. substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    complete_task_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    unfinished_task_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    fail_task_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));
    server_status_info_temp = server_status_info_temp.substr(server_status_info_temp.find(",")+1);
    event_num = server_status_info_temp.substr(0, server_status_info_temp.find(","));

    WNHDEBUG("pid:" << pid << ", 启动时间:" << start_time << ", 客户端数量:" << client_num << ", 在线客户端数量:" << online_client_num << ", 离线客户端数量:" << offline_client_num << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数" << fail_task_num << ", 未转化事件数量" << event_num);
    show_server_status_info_son(pid, start_time, client_num, online_client_num, offline_client_num, task_num, complete_task_num, unfinished_task_num, fail_task_num, event_num);

    return 8;
}

bool wnh_filesync_control::show_server_status_info_son(string & pid, string & start_time, string & client_num, string & online_client_num, string & offline_client_num, string & task_num, string & complete_task_num, string & unfinished_task_num, string & fail_task_num, string & event_num) //显示服务端状态
{
    vector<string> values;
    vector<WNH_SHELL_TABLES_FONT_STYLE> color;
    vector<unsigned int> values_width;

    string str_temp;
    str_temp = str_temp + PROGRAM_NAME + " 服务端状态信息显示";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA);
    set_vector_values(true, values_width, 132);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "服务端PID", "服务端启动时间", "客户端数" ,"在线客户端数" ,"离线客户端数" ,"全部任务数" ,"已完成任务数" ,"未完成任务数" ,"失败任务数" ,"未转化事件数");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN);
    set_vector_values(true, values_width, 9, 19, 8, 12, 12, 15, 14, 12, 10, 12);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, pid, start_time, client_num, online_client_num, offline_client_num, task_num, complete_task_num, unfinished_task_num, fail_task_num, event_num);
    if(fail_task_num != "0")
    {
        set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW);
    }
    else
    {
        set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW);
    }

    shell_tables.add_unit(values, color, values_width);

    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    shell_tables.show_tables();
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();
    shell_tables.clear();

    return true;
}




