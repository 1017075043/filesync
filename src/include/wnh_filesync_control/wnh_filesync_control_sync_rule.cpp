#include "wnh_filesync_control.h"

void wnh_filesync_control::get_synv_rule_info() //获取同步规则信息信息
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
    string sync_rule_info_file_path;
    if(!send_get_sync_rule_info(sync_rule_info_file_path))
    {
        close(socket_num);
        return;
    }
    if(!download_file(sync_rule_info_file_path, sync_rule_info_file_path + SYNC_RULE_INFO_FILE_SUFFIX))
    {
        close(socket_num);
        return;
    }
    show_sync_info_info(sync_rule_info_file_path + SYNC_RULE_INFO_FILE_SUFFIX); //显示同步规则信息
    send_end_session_info();
    return;
}

bool wnh_filesync_control::send_get_sync_rule_info(string & sync_rule_info_file_path) //向服务器发送获取同步规则信息信号, 且获取同步规则信息文件路径
{
    if(send_info(WNH_FILESYNC_GET_SYNC_RULE_INFO))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取同步规则信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_GET_SYNC_RULE_INFO)) == WNH_FILESYNC_GET_SYNC_RULE_INFO)
        {
            sync_rule_info_file_path = info.substr(strlen(WNH_FILESYNC_GET_SYNC_RULE_INFO));
            WNHINFO(SERVER_INFO_LOGS <<  "向服务器请求获取同步规则信息成功, 客户端状态信息文件路径:" << sync_rule_info_file_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取同步规则信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取同步规则信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_control::show_sync_info_info(const string & sync_info_info_file_path) //显示同步规则信息
{
    WNH_DISPLAY_STYLE_HIDE_CURSOR(); // 隐藏光标
    sync_rule_info.read_config_ini(sync_info_info_file_path, false);
    static bool temp_id = false;
    if(temp_id)
    {
        WNH_DISPLAY_STYLE_MOVEUP(6 + (sync_rule_info.unit_num+1)*2);
    }
    else
    {
        temp_id = true;
    }
    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    vector<string> dst_ip_and_dir;
    vector<string> ignore_rule;
    vector<string> ignore_dir;
    bool temp_sss = false;
    cout << WNH_COLOR_BOLDWHITE << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│                                                  " << WNH_COLOR_BOLDMAGENTA << PROGRAM_NAME << " 同步规则信息显示" << WNH_COLOR_BOLDWHITE << "                                                  │" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────┬───────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    for(int i = 0; i <= sync_rule_info.unit_num; i++)
    {
        if(sync_rule_info.unit[i]->name.substr(0, strlen(WNH_FILESYNC_GET_SYNC_RULE_ID)) == WNH_FILESYNC_GET_SYNC_RULE_ID)
        {
            if(temp_sss)
            {
                cout << WNH_COLOR_BOLDWHITE << "├┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┤" << WNH_COLOR_RESET << endl;
                cout << WNH_COLOR_BOLDWHITE << "├┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┤" << WNH_COLOR_RESET << endl;
            }
            else
            {
                temp_sss = true;
            }
            cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED   << "           源目录           " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  " << format_string_right_fill(sync_rule_info.unit[i]->conf.get_one_config("src_dir"), 100, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
            //WNHINFO(sync_rule_info.unit[i]->conf.get_one_config("src_dir"));
            dst_ip_and_dir = sync_rule_info.unit[i]->conf.get_config("dst_ip_and_dir");
            ignore_rule = sync_rule_info.unit[i]->conf.get_config("ignore_rule");
            ignore_dir = sync_rule_info.unit[i]->conf.get_config("ignore_dir");
            for(unsigned int j = 0; j < dst_ip_and_dir.size(); j++)
            {
                cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
                cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN   << "     客户端IP,目标目录      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN << "  " << format_string_right_fill(dst_ip_and_dir[j], 100, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
                //WNHINFO(dst_ip_and_dir[j]);
            }
            for(unsigned int j = 0; j < ignore_rule.size(); j++)
            {
                cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
                cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW   << "        忽略同步规则        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "  " << format_string_right_fill(ignore_rule[j], 100, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
                //WNHINFO(ignore_rule[j]);
            }
            for(unsigned int j = 0; j < ignore_dir.size(); j++)
            {
                cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
                cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE   << "        忽略监视目录        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << "  " << format_string_right_fill(ignore_dir[j], 100, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
                //WNHINFO(ignore_dir[j]);
            }
        }
    }
    cout << WNH_COLOR_BOLDWHITE << "└────────────────────────────┴───────────────────────────────────────────────────────────────────────────────────────────────────────┘" << WNH_COLOR_RESET << endl;
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();
    sync_rule_info.clean_configure_ini();
    if(unlink(sync_info_info_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << sync_info_info_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return true;
}
