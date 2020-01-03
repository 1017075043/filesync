#include "wnh_filesync_control.h"

void wnh_filesync_control::get_sync_fail_task_list_info() //获取同步失败任务列表信息
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
    string sync_fail_task_list_file_path;
    while(1)
    {
        if(!send_get_fail_task_list_info(sync_fail_task_list_file_path))
        {
            close(socket_num);
            return;
        }
        if(sync_fail_task_list_file_path != WNH_FILESYNC_NOT_OR_FAIL_SYNC_FAIL_TASk_LIST_INFO)
        {
            if(!download_file(sync_fail_task_list_file_path, sync_fail_task_list_file_path + SYNC_FAIL_TASK_LIST_INFO_FILE_SUFFIX))
            {
                close(socket_num);
                return;
            }
            show_sync_fail_task_list_info(sync_fail_task_list_file_path + SYNC_FAIL_TASK_LIST_INFO_FILE_SUFFIX); //显示同步传输过程数据信息
        }
        string stemp_s = get_keyboard_input_string();
        WNHINFO(stemp_s);
    }
    send_end_session_info();
    return;
}

bool wnh_filesync_control::send_get_fail_task_list_info(string & sync_fail_task_list_file_path) //向服务器发送获取同步失败任务列表信号, 且获取同步失败任务列表文件路径
{
    string info;
    static int temp_i = -10;
    temp_i = temp_i + SYNC_FAIL_TASK_LIST_INFO_LINE_NUM;
    info = info + WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO + to_string(temp_i) + "," + to_string(SYNC_FAIL_TASK_LIST_INFO_LINE_NUM);
    if(send_info(info.c_str()))
    {
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取同步失败任务列表信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO)) == WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO)
        {
            sync_fail_task_list_file_path = info.substr(strlen(WNH_FILESYNC_SYNC_FAIL_TASk_LIST_INFO));
            WNHDEBUG(SERVER_INFO_LOGS <<  "向服务器请求获取同步失败任务列表信息成功, 同步传输过程信息文件路径:" << sync_fail_task_list_file_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取同步失败任务列表信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取同步失败任务列表信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_control::show_sync_fail_task_list_info(const string & sync_fail_task_list_file_path) //显示同步失败任务列表信息
{
    sync_fail_task_list_info.read_config_ini(sync_fail_task_list_file_path, false);
    for(int i = 0; i < sync_fail_task_list_info.config_unit_num; i ++)
    {
        if(sync_fail_task_list_info.config_unit[i].name.substr(0, strlen(WNH_FILESYNC_RULE_FAIL_TASk_LIST_ID)) == WNH_FILESYNC_RULE_FAIL_TASk_LIST_ID)
        {
            string client_ip = sync_fail_task_list_info.get_conf_one(i, "client_ip");
            string event_id = sync_fail_task_list_info.get_conf_one(i, "event_id");
            string src_path = sync_fail_task_list_info.get_conf_one(i, "src_path");
            string dst_path = sync_fail_task_list_info.get_conf_one(i, "dst_path");
            string update_date = sync_fail_task_list_info.get_conf_one(i, "update_date");
            cout << WNH_FONT_COLOR_CYAN << update_date << WNH_FONT_COLOR_RED << " " << client_ip <<  WNH_FONT_COLOR_BLUE << " " << event_id << WNH_FONT_COLOR_YELLOW << " " << src_path  << WNH_FONT_COLOR_YELLOW << " " << dst_path << WNH_FONT_COLOR_RESET << endl;
            usleep(20000);
        }
    }
    if(unlink(sync_fail_task_list_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << sync_fail_task_list_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return true;
}
