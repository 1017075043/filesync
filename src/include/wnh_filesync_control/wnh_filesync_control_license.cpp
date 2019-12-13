#include "wnh_filesync_control.h"

void wnh_filesync_control::show_server_license()//显示许可信息
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
    string license_info;
    if(!send_get_server_license_info(license_info))
    {
        close(socket_num);
        return;
    }
    show_server_license_info(license_info);
    send_end_session_info();
//    if(!download_file(server_status_info_file_path, server_status_info_file_path + SERVER_STATUS_INFO_FILE_SUFFIX))
//    {
//        close(socket_num);
//        return;
//    }
//    show_server_status_info(server_status_info_file_path + SERVER_STATUS_INFO_FILE_SUFFIX); //显示服务端状态
//    send_end_session_info();
    return;
}

bool wnh_filesync_control::send_get_server_license_info(string & license_info) //向服务器发送获许可信息信号, 且获取许可
{
    if(send_info(WNH_FILESYNC_GET_LICENSE_INFO))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取许可信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_GET_LICENSE_INFO)) == WNH_FILESYNC_GET_LICENSE_INFO)
        {
            license_info = info.substr(strlen(WNH_FILESYNC_GET_LICENSE_INFO));
            WNHDEBUG(SERVER_INFO_LOGS <<  "向服务器请求获取许可信息成功, 许可信息为:" << license_info);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取许可信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取许可信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_control::show_server_license_info(const string & license_info) //显示许可信息
{
    //WNHINFO(license_info);
    string license_info_temp = license_info;
    string file_path = license_info_temp.substr(0, license_info_temp.find(","));

    license_info_temp = license_info_temp.substr(license_info_temp.find(",")+1);
    string begin_time = license_info_temp.substr(0, license_info_temp.find(","));

    license_info_temp = license_info_temp.substr(license_info_temp.find(",")+1);
    string end_time = license_info_temp.substr(0, license_info_temp.find(","));

    license_info_temp = license_info_temp.substr(license_info_temp.find(",")+1);
    string all_time = license_info_temp.substr(0, license_info_temp.find(","));

    license_info_temp = license_info_temp.substr(license_info_temp.find(",")+1);
    string remaining_time = license_info_temp.substr(0, license_info_temp.find(","));

    string serial_number = license_info_temp.substr(license_info_temp.find(",")+1);

    //WNHINFO("file_path:" << file_path << ", begin_time:" << begin_time << ", end_time:" << end_time << ", all_time" << all_time << ", remaining_time:" << remaining_time << ", serial_number:" << serial_number);

    vector<string> values;
    vector<WNH_SHELL_TABLES_FONT_COLOR> color;
    vector<unsigned int> values_width;;

    string str_temp;
    str_temp = str_temp + PROGRAM_NAME + " 服务端许可信息显示";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_COLOR::BOLDMAGENTA);
    set_vector_values(true, values_width, 132);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "产品序列号", "许可生成时间", "许可到期时间", "许可有效期", "许可剩余有效期", "许可文件路径");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_COLOR::BOLDRED, WNH_SHELL_TABLES_FONT_COLOR::BOLDBLUE, WNH_SHELL_TABLES_FONT_COLOR::BOLDYELLOW, WNH_SHELL_TABLES_FONT_COLOR::BOLDBLUE, WNH_SHELL_TABLES_FONT_COLOR::BOLDRED, WNH_SHELL_TABLES_FONT_COLOR::BOLDBLUE);
    set_vector_values(true, values_width, 32, 19, 19, 10, 14, 33);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, serial_number, begin_time, end_time, all_time + "天", remaining_time + "天", file_path);
    shell_tables.add_unit(values, color, values_width);

    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    shell_tables.show_tables();
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();
    shell_tables.clear();

    return true;
}





