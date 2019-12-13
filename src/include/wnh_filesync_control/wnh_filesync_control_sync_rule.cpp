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

vector<string>  wnh_filesync_control::get_sync_info_info(const string & sync_info_info_file_path) //获取同步规则信息
{
    sync_rule_info.read_config_ini(sync_info_info_file_path, false);
    vector<string> values_ss_temp;
    for(int i = 0; i <= sync_rule_info.unit_num; i++)
    {
        if(sync_rule_info.unit[i]->name.substr(0, strlen(WNH_FILESYNC_GET_SYNC_RULE_ID)) == WNH_FILESYNC_GET_SYNC_RULE_ID)
        {
            values_ss_temp.push_back("src_dir=" + sync_rule_info.unit[i]->conf.get_one_config("src_dir"));
            vector<string> dst_ip_and_dir;
            vector<string> ignore_rule;
            vector<string> ignore_dir;
            dst_ip_and_dir = sync_rule_info.unit[i]->conf.get_config("dst_ip_and_dir");
            ignore_rule = sync_rule_info.unit[i]->conf.get_config("ignore_rule");
            ignore_dir = sync_rule_info.unit[i]->conf.get_config("ignore_dir");
            for(unsigned int j = 0; j < dst_ip_and_dir.size(); j++)
            {
                values_ss_temp.push_back("dst_ip_and_dir=" + dst_ip_and_dir[j]);
            }
            for(unsigned int j = 0; j < ignore_rule.size(); j++)
            {
                values_ss_temp.push_back("ignore_rule=" + ignore_rule[j]);
            }
            for(unsigned int j = 0; j < ignore_dir.size(); j++)
            {
                values_ss_temp.push_back("ignore_dir=" + ignore_dir[j]);
            }
        }
    }
    sync_rule_info.clean_configure_ini();
    if(unlink(sync_info_info_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << sync_info_info_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return values_ss_temp;
}

bool wnh_filesync_control::show_sync_info_info(const string & sync_info_info_file_path) //显示同步规则信息
{
    vector<string> values_ss_temp = get_sync_info_info(sync_info_info_file_path);
    vector<string> values;
    vector<WNH_SHELL_TABLES_FONT_COLOR> color;
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    vector<unsigned int> values_width;

    string str_temp;
    str_temp = str_temp + PROGRAM_NAME + " 同步规则信息显示";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_COLOR::BOLDMAGENTA);
    set_vector_values(true, values_width, 70);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values_width, 19, 50);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left);
    for(unsigned int i = 0; i < values_ss_temp.size(); i++)
    {
        string str_temp_ss = values_ss_temp[i].substr(values_ss_temp[i].find("=") + 1);
        if(values_ss_temp[i].substr(0, values_ss_temp[i].find("=")) == "src_dir")
        {
            set_vector_values(true, values, " 服务端IP", " " + ip, " 源目录", " " + str_temp_ss );
            set_vector_values(true, color, WNH_SHELL_TABLES_FONT_COLOR::BOLDRED, WNH_SHELL_TABLES_FONT_COLOR::BOLDYELLOW, WNH_SHELL_TABLES_FONT_COLOR::BOLDRED, WNH_SHELL_TABLES_FONT_COLOR::BOLDYELLOW);
            set_vector_values(true, values_width, 10, 17, 10, 30);
            set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left);

            shell_tables.add_unit(values, color, align, values_width);
        }
        else if(values_ss_temp[i].substr(0, values_ss_temp[i].find("=")) == "dst_ip_and_dir")
        {
            set_vector_values(true, values, " 客户端IP", " " + str_temp_ss.substr(0, str_temp_ss.find(",")), " 目标目录", " " + str_temp_ss.substr(str_temp_ss.find(",") + 1));
            set_vector_values(true, color, WNH_SHELL_TABLES_FONT_COLOR::BOLDCYAN, WNH_SHELL_TABLES_FONT_COLOR::BOLDGREEN, WNH_SHELL_TABLES_FONT_COLOR::BOLDCYAN, WNH_SHELL_TABLES_FONT_COLOR::BOLDGREEN);
            set_vector_values(true, values_width, 10, 17, 10, 30);
            set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left);
            shell_tables.add_unit(values, color, align, values_width);
        }
        else if(values_ss_temp[i].substr(0, values_ss_temp[i].find("=")) == "ignore_rule")
        {
            set_vector_values(true, values, " 忽略同步规则", " " + str_temp_ss);
            set_vector_values(true, color, WNH_SHELL_TABLES_FONT_COLOR::BOLDYELLOW, WNH_SHELL_TABLES_FONT_COLOR::BOLDYELLOW);
            set_vector_values(true, values_width, 14, 55);
            set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left);
            shell_tables.add_unit(values, color, align, values_width);
        }
        else if(values_ss_temp[i].substr(0, values_ss_temp[i].find("=")) == "ignore_dir")
        {
            set_vector_values(true, values, " 忽略监视目录", " " + str_temp_ss);
            set_vector_values(true, color, WNH_SHELL_TABLES_FONT_COLOR::BOLDBLUE, WNH_SHELL_TABLES_FONT_COLOR::BOLDBLUE);
            set_vector_values(true, values_width, 14, 55);
            set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left);
            shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT);
        }
    }

    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    shell_tables.show_tables();
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();

    return true;
}
