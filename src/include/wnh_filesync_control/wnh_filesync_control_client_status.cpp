#include "wnh_filesync_control.h"

void wnh_filesync_control::get_client_status_info_while() //获取客户端状态信息(循环)
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
        string client_status_info_file_path;
        for(int i = 0; i < MAXIMUM_NUMBER_OF_REQUESTS_PER_SESSION; i++)
        {
            if(!send_get_client_status_info(client_status_info_file_path))
            {
                close(socket_num);
                return;
            }
            if(client_status_info_file_path != WNH_FILESYNC_GET_CLIENT_STATUS_IGNORE_INFO)
            {
                if(!download_file(client_status_info_file_path, client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX))
                {
                    close(socket_num);
                    return;
                }
                show_client_status_info(client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX);
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

void wnh_filesync_control::get_client_status_info() //获取客户端状态信息
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
    string client_status_info_file_path;
    if(!send_get_client_status_info(client_status_info_file_path))
    {
        close(socket_num);
        return;
    }
    if(!download_file(client_status_info_file_path, client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX))
    {
        close(socket_num);
        return;
    }
    show_client_status_info(client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX);
    send_end_session_info();

    return;
}

bool wnh_filesync_control::send_get_client_status_info(string & client_status_info_file_path) //向服务器发送获取客户端状态信息信号, 且获取客户端状态信息文件路径
{
    if(send_info(WNH_FILESYNC_GET_CLIENT_STATUS_INFO))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取服务端状态信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_GET_CLIENT_STATUS_INFO)) == WNH_FILESYNC_GET_CLIENT_STATUS_INFO)
        {
            client_status_info_file_path = info.substr(strlen(WNH_FILESYNC_GET_CLIENT_STATUS_INFO));
            WNHDEBUG(SERVER_INFO_LOGS <<  "向服务器请求获取客户端状态信息成功, 客户端状态信息文件路径:" << client_status_info_file_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取客户端状态信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取客户端状态信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_control::show_client_status_info(const string & client_status_info_file_path) //显示客户端状态
{
    WNH_DISPLAY_STYLE_HIDE_CURSOR(); // 隐藏光标
    status_info.read_config_ini(client_status_info_file_path, false);
    static bool temp_id = false;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(6 + (status_info.unit_num+1)*2);
    }
    else
    {
        temp_id = true;
    }
    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    cout << WNH_COLOR_BOLDWHITE << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│                                                  " << WNH_COLOR_BOLDMAGENTA << PROGRAM_NAME << " 客户端状态信息显示" << WNH_COLOR_BOLDWHITE << "                                                │" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────────────────────────┬───────────┬───────────────────┬───────────────────┬────────────┬──────────────┬─────────────┬───────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN   << "         客户端IP         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN  << "客户端状态 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  客户端启动时间   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "客户端最后活动时间 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << " 全部任务数 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << " 已完成任务数 "  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN   << "未完成任务数 "     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "失败任务数 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    bool status_temp = true;
    for(int i = 0; i <= status_info.unit_num; i++)
    {
        if(status_info.unit[i]->name.substr(0, strlen(WNH_FILESYNC_CLIENT_STATUS_ID)) == WNH_FILESYNC_CLIENT_STATUS_ID)
        {
            string client_ip = status_info.unit[i]->conf.get_one_config("client_ip"); //客户端IP
            string status = status_info.unit[i]->conf.get_one_config("status"); //状态
            string begin_connect_time = status_info.unit[i]->conf.get_one_config("begin_connect_time"); //启动时间
            string last_connect_time = status_info.unit[i]->conf.get_one_config("last_connect_time"); //最后活动时间
            string task_num = status_info.unit[i]->conf.get_one_config("task_num"); //全部任务数
            string complete_task_num = status_info.unit[i]->conf.get_one_config("complete_task_num"); //已完成任务数
            string unfinished_task_num = status_info.unit[i]->conf.get_one_config("unfinished_task_num"); //未完成任务数
            string fail_task_num = status_info.unit[i]->conf.get_one_config("fail_task_num"); //失败任务数
            status == "0" ? status_temp = false : status_temp = true;
            status == "0" ? status = "离线" : status = "在线";
            //LOCALTIMENUM = (unsigned long)t;
            char timestring[20] = "";
            time_t t = (time_t)stoul(begin_connect_time, 0, 10);
            strftime(timestring, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
            begin_connect_time = timestring;
            t = (time_t)stoul(last_connect_time, 0, 10);
            strftime(timestring, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
            last_connect_time = timestring;
            begin_connect_time == "1970/01/01 08:00:00" ? begin_connect_time = "0000/00/00 00:00:00" : begin_connect_time;
            last_connect_time == "1970/01/01 08:00:00" ? last_connect_time = "0000/00/00 00:00:00" : last_connect_time;
            client_ip = format_string_centro_fill(client_ip, 25, ' ');
            status = format_string_centro_fill(status, 10, ' ');
            begin_connect_time = format_string_centro_fill(begin_connect_time, 19, ' ');
            last_connect_time = format_string_centro_fill(last_connect_time, 19, ' ');
            task_num = format_string_centro_fill(task_num, 11, ' ');
            complete_task_num = format_string_centro_fill(complete_task_num, 13, ' ');
            unfinished_task_num = format_string_centro_fill(unfinished_task_num, 12, ' ');
            fail_task_num = format_string_centro_fill(fail_task_num, 10, ' ');
            //WNHINFO("客户端IP:" << client_ip << ", 状态:" << status << ", 启动时间:" << begin_connect_time << ", 最后活动时间:" << last_connect_time << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数:" << fail_task_num );
            cout << WNH_COLOR_BOLDWHITE << "├──────────────────────────┼───────────┼───────────────────┼───────────────────┼────────────┼──────────────┼─────────────┼───────────┤" << WNH_COLOR_RESET << endl;
            if(status_temp == true)
            {
                cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << client_ip                    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN << status        << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << begin_connect_time    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << last_connect_time     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << task_num       << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << complete_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << unfinished_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << fail_task_num  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
            }
            else
            {
                cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << client_ip                    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED   << status        << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << begin_connect_time    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED  << last_connect_time     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << task_num       << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << complete_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << unfinished_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << fail_task_num  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
            }
        }
    }
    cout << WNH_COLOR_BOLDWHITE << "└──────────────────────────┴───────────┴───────────────────┴───────────────────┴────────────┴──────────────┴─────────────┴───────────┘" << WNH_COLOR_RESET << endl;
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();
    status_info.clean_configure_ini();
    if(unlink(client_status_info_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << client_status_info_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return true;
}

int wnh_filesync_control::show_client_status_info(const string & client_status_info_file_path, const int & offset) //显示客户端状态
{
    status_info.read_config_ini(client_status_info_file_path, false);
    static bool temp_id = false;
    int temp_offset = 6 + (status_info.unit_num+1)*2;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(offset);
    }
    else
    {
        temp_id = true;
    }
    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    cout << WNH_COLOR_BOLDWHITE << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│                                                  " << WNH_COLOR_BOLDMAGENTA << PROGRAM_NAME << " 客户端状态信息显示" << WNH_COLOR_BOLDWHITE << "                                                │" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────────────────────────┬───────────┬───────────────────┬───────────────────┬────────────┬──────────────┬─────────────┬───────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN   << "         客户端IP         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN  << "客户端状态 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  客户端启动时间   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "客户端最后活动时间 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << " 全部任务数 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << " 已完成任务数 "  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN   << "未完成任务数 "     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "失败任务数 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    bool status_temp = true;
    for(int i = 0; i <= status_info.unit_num; i++)
    {
        if(status_info.unit[i]->name.substr(0, strlen(WNH_FILESYNC_CLIENT_STATUS_ID)) == WNH_FILESYNC_CLIENT_STATUS_ID)
        {
            string client_ip = status_info.unit[i]->conf.get_one_config("client_ip"); //客户端IP
            string status = status_info.unit[i]->conf.get_one_config("status"); //状态
            string begin_connect_time = status_info.unit[i]->conf.get_one_config("begin_connect_time"); //启动时间
            string last_connect_time = status_info.unit[i]->conf.get_one_config("last_connect_time"); //最后活动时间
            string task_num = status_info.unit[i]->conf.get_one_config("task_num"); //全部任务数
            string complete_task_num = status_info.unit[i]->conf.get_one_config("complete_task_num"); //已完成任务数
            string unfinished_task_num = status_info.unit[i]->conf.get_one_config("unfinished_task_num"); //未完成任务数
            string fail_task_num = status_info.unit[i]->conf.get_one_config("fail_task_num"); //失败任务数
            status == "0" ? status_temp = false : status_temp = true;
            status == "0" ? status = "离线" : status = "在线";
            //LOCALTIMENUM = (unsigned long)t;
            char timestring[20] = "";
            time_t t = (time_t)stoul(begin_connect_time, 0, 10);
            strftime(timestring, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
            begin_connect_time = timestring;
            t = (time_t)stoul(last_connect_time, 0, 10);
            strftime(timestring, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
            last_connect_time = timestring;
            begin_connect_time == "1970/01/01 08:00:00" ? begin_connect_time = "0000/00/00 00:00:00" : begin_connect_time;
            last_connect_time == "1970/01/01 08:00:00" ? last_connect_time = "0000/00/00 00:00:00" : last_connect_time;
            client_ip = format_string_centro_fill(client_ip, 25, ' ');
            status = format_string_centro_fill(status, 10, ' ');
            begin_connect_time = format_string_centro_fill(begin_connect_time, 19, ' ');
            last_connect_time = format_string_centro_fill(last_connect_time, 19, ' ');
            task_num = format_string_centro_fill(task_num, 11, ' ');
            complete_task_num = format_string_centro_fill(complete_task_num, 13, ' ');
            unfinished_task_num = format_string_centro_fill(unfinished_task_num, 12, ' ');
            fail_task_num = format_string_centro_fill(fail_task_num, 10, ' ');
            //WNHINFO("客户端IP:" << client_ip << ", 状态:" << status << ", 启动时间:" << begin_connect_time << ", 最后活动时间:" << last_connect_time << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数:" << fail_task_num );
            cout << WNH_COLOR_BOLDWHITE << "├──────────────────────────┼───────────┼───────────────────┼───────────────────┼────────────┼──────────────┼─────────────┼───────────┤" << WNH_COLOR_RESET << endl;
            if(status_temp == true)
            {
                cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN << client_ip                    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN << status        << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << begin_connect_time    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << last_connect_time     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << task_num       << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << complete_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << unfinished_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << fail_task_num  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
            }
            else
            {
                cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << client_ip                    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED   << status        << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << begin_connect_time    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED  << last_connect_time     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << task_num       << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << complete_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << unfinished_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << fail_task_num  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
            }
        }
    }
    cout << WNH_COLOR_BOLDWHITE << "└──────────────────────────┴───────────┴───────────────────┴───────────────────┴────────────┴──────────────┴─────────────┴───────────┘" << WNH_COLOR_RESET << endl;
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();
    status_info.clean_configure_ini();
    if(unlink(client_status_info_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << client_status_info_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return temp_offset;
}
