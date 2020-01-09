#include "wnh_filesync_control.h"

void wnh_filesync_control::get_sync_transfer_info() //获取同步传输过程信息
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
    string sync_transfer_file_path;
    while(1)
    {
        if(!send_get_sync_transfer_info(sync_transfer_file_path))
        {
            close(socket_num);
            return;
        }
        if(sync_transfer_file_path != WNH_FILESYNC_NOT_OR_FAIL_SYNC_TRANSFER_INFO)
        {
            if(!download_file(sync_transfer_file_path, sync_transfer_file_path + SYNC_TRANSFER_INFO_FILE_SUFFIX))
            {
                close(socket_num);
                return;
            }
            show_sync_transfer_info(sync_transfer_file_path + SYNC_TRANSFER_INFO_FILE_SUFFIX); //显示同步传输过程数据信息
        }
        else
        {
            sleep(REQUEST_INTERVAL);
        }
    }
    send_end_session_info();
    return;
}

bool wnh_filesync_control::send_get_sync_transfer_info(string & sync_transfer_file_path) //向服务器发送获取同步传输过程信息信号, 且获取同步传输过程信息文件路径
{
    if(send_info(WNH_FILESYNC_SYNC_TRANSFER_INFO))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取同步传输过程信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_SYNC_TRANSFER_INFO)) == WNH_FILESYNC_SYNC_TRANSFER_INFO)
        {
            sync_transfer_file_path = info.substr(strlen(WNH_FILESYNC_SYNC_TRANSFER_INFO));
            WNHDEBUG(SERVER_INFO_LOGS <<  "向服务器请求获取同步传输过程信息成功, 同步传输过程信息文件路径:" << sync_transfer_file_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取同步传输过程信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取同步传输过程信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

vector<string> wnh_filesync_control::get_sync_transfer_data_info(const string & sync_transfer_file_path) //获取同步传输过程数据信息
{
    sync_transfer_info.read_config_ini(sync_transfer_file_path, false);
    //sync_transfer_info.show_configure_ini();
    vector<string> values_ss_temp;
    for(int i = 0; i < sync_transfer_info.config_unit_num; i ++)
    {
        if(sync_transfer_info.config_unit[i].name.substr(0, strlen(WNH_FILESYNC_TRANSFER_ID)) == WNH_FILESYNC_TRANSFER_ID)
        {
            values_ss_temp.push_back(sync_transfer_info.get_conf_one(i, "client_ip"));
            values_ss_temp.push_back(sync_transfer_info.get_conf_one(i, "event_id"));
            values_ss_temp.push_back(sync_transfer_info.get_conf_one(i, "dst_path"));
            values_ss_temp.push_back(sync_transfer_info.get_conf_one(i, "complete_date"));
        }
    }
    //for(int i = 0; i < (int)values_ss_temp.size(); i ++)
    //{
    //    WNHINFO(values_ss_temp[i]);
    //}
    if(unlink(sync_transfer_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << sync_transfer_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return values_ss_temp;
}

bool wnh_filesync_control::show_sync_transfer_info(const string & sync_transfer_file_path) //显示同步传输过程数据信息
{
    //get_sync_transfer_data_info(sync_transfer_file_path);
    sync_transfer_info.read_config_ini(sync_transfer_file_path, false);
    //sync_transfer_info.show_configure_ini();
    //vector<string> values_ss_temp;
    for(int i = 0; i < sync_transfer_info.config_unit_num; i ++)
    {
        if(sync_transfer_info.config_unit[i].name.substr(0, strlen(WNH_FILESYNC_TRANSFER_ID)) == WNH_FILESYNC_TRANSFER_ID)
        {
            string client_ip = sync_transfer_info.get_conf_one(i, "client_ip");
            string event_id = sync_transfer_info.get_conf_one(i, "event_id");
            string dst_path = sync_transfer_info.get_conf_one(i, "dst_path");
            string complete_date = sync_transfer_info.get_conf_one(i, "complete_date");
            cout << WNH_FONT_COLOR_CYAN << complete_date << WNH_FONT_COLOR_RED << " " << client_ip <<  WNH_FONT_COLOR_BLUE << " " << event_id << WNH_FONT_COLOR_YELLOW << " " << dst_path << WNH_FONT_COLOR_GREEN << " 完成" << WNH_FONT_COLOR_RESET << endl;
            usleep(20000);
        }
    }
    if(unlink(sync_transfer_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << sync_transfer_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return true;
}
