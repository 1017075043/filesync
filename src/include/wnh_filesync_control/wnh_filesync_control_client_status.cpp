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

vector<string> wnh_filesync_control::get_client_status_info(const string & client_status_info_file_path) //获取客户端状态信息
{
    status_info.read_config_ini(client_status_info_file_path, false);
    bool status_temp = true;
    vector<string> values_ss_temp;
    for(int i = 0; i <= status_info.config_unit_num; i++)
    {
        if(status_info.config_unit[i].name.substr(0, strlen(WNH_FILESYNC_CLIENT_STATUS_ID)) == WNH_FILESYNC_CLIENT_STATUS_ID)
        {
            string client_ip = status_info.get_conf_one(i, "client_ip"); //客户端IP
            string status = status_info.get_conf_one(i, "status"); //状态
            string begin_connect_time = status_info.get_conf_one(i, "begin_connect_time"); //启动时间
            string last_connect_time = status_info.get_conf_one(i, "last_connect_time"); //最后活动时间
            string task_num = status_info.get_conf_one(i, "task_num"); //全部任务数
            string complete_task_num = status_info.get_conf_one(i, "complete_task_num"); //已完成任务数
            string unfinished_task_num = status_info.get_conf_one(i, "unfinished_task_num"); //未完成任务数
            string fail_task_num = status_info.get_conf_one(i, "fail_task_num"); //失败任务数
            status == "0" ? status_temp = false : status_temp = true;
            status == "0" ? status = "离线" : status = "在线";
            char timestring[20] = "";
            time_t t = (time_t)stoul(begin_connect_time, 0, 10);
            strftime(timestring, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
            begin_connect_time = timestring;
            t = (time_t)stoul(last_connect_time, 0, 10);
            strftime(timestring, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
            last_connect_time = timestring;
            begin_connect_time == "1970/01/01 08:00:00" ? begin_connect_time = "0000/00/00 00:00:00" : begin_connect_time;
            last_connect_time == "1970/01/01 08:00:00" ? last_connect_time = "0000/00/00 00:00:00" : last_connect_time;
            //WNHINFO("客户端IP:" << client_ip << ", 状态:" << status << ", 启动时间:" << begin_connect_time << ", 最后活动时间:" << last_connect_time << ", 全部任务数:" << task_num << ", 已完成任务数:" << complete_task_num << ", 未完成任务数:" << unfinished_task_num << ", 失败任务数:" << fail_task_num );
            values_ss_temp.push_back(client_ip);
            values_ss_temp.push_back(status);
            values_ss_temp.push_back(begin_connect_time);
            values_ss_temp.push_back(last_connect_time);
            values_ss_temp.push_back(task_num);
            values_ss_temp.push_back(complete_task_num);
            values_ss_temp.push_back(unfinished_task_num);
            values_ss_temp.push_back(fail_task_num);
        }
    }
    //status_info.clean_configure_ini();
    if(unlink(client_status_info_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << client_status_info_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return values_ss_temp;
}

bool wnh_filesync_control::show_client_status_info(const string & client_status_info_file_path) //显示客户端状态
{
    vector<string> values_ss_temp = get_client_status_info(client_status_info_file_path);
    static bool temp_id = false;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(6 + ((int)values_ss_temp.size() / 8) * 2);
    }
    else
    {
        temp_id = true;
    }
    show_client_status_info_son(values_ss_temp);
    return true;
}

int wnh_filesync_control::show_client_status_info(const string & client_status_info_file_path, const int & offset) //显示客户端状态
{
    vector<string> values_ss_temp = get_client_status_info(client_status_info_file_path);
    static bool temp_id = false;
    int temp_offset = 6 + ((int)values_ss_temp.size() / 8) * 2;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(offset);
    }
    else
    {
        temp_id = true;
    }
    show_client_status_info_son(values_ss_temp);
    return temp_offset;
}

bool wnh_filesync_control::show_client_status_info_son(const vector<string> & values_ss_temp)
{
    vector<string> values;
    vector<WNH_SHELL_TABLES_FONT_STYLE> color;
    vector<unsigned int> values_width;

    string str_temp;
    str_temp = str_temp + PROGRAM_NAME + " 客户端状态信息显示";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA);
    set_vector_values(true, values_width, 132);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "客户端IP", "客户端状态", "客户端启动时间", "客户端最后活动时间", "全部任务数", "已完成任务数", "未完成任务数", "失败任务数");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN);
    set_vector_values(true, values_width, 33, 10, 19, 19, 10, 12, 12, 10);
    shell_tables.add_unit(values, color, values_width);

    for(unsigned int i = 0; i < values_ss_temp.size() / 8; i ++)
    {
        set_vector_values(true, values, values_ss_temp[i * 8 + 0], values_ss_temp[i * 8 + 1], values_ss_temp[i * 8 + 2], values_ss_temp[i * 8 + 3], values_ss_temp[i * 8 + 4], values_ss_temp[i * 8 + 5], values_ss_temp[i * 8 + 6], values_ss_temp[i * 8 + 7]);
        if(values_ss_temp[i * 8 + 1] == "在线")
        {
            if(values_ss_temp[i * 8 + 7] != "0")
            {
                set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDRED);
            }
            else
            {
                set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN);
            }
        }
        else
        {
            if(values_ss_temp[i * 8 + 7] != "0")
            {
                set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDRED);
            }
            else
            {
                set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN);
            }
        }
        shell_tables.add_unit(values, color, values_width);
        //WNHINFO("客户端IP:" << values_ss_temp[i * 8 + 0] << ", 状态:" << values_ss_temp[i * 8 + 1] << ", 启动时间:" << values_ss_temp[i * 8 + 2] << ", 最后活动时间:" << values_ss_temp[i * 8 + 3] << ", 全部任务数:" << values_ss_temp[i * 8 + 4] << ", 已完成任务数:" << values_ss_temp[i * 8 + 5] << ", 未完成任务数:" << values_ss_temp[i * 8 + 6] << ", 失败任务数:" << values_ss_temp[i * 8 + 7]);
    }
    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    shell_tables.show_tables();
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();
    shell_tables.clear();
    return true;
}
