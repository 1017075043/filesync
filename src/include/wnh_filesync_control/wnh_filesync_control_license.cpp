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
    WNHINFO(license_info);
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

    WNHINFO("file_path:" << file_path << ", begin_time:" << begin_time << ", end_time:" << end_time << ", all_time" << all_time << ", remaining_time:" << remaining_time << ", serial_number:" << serial_number);
    string serial_number_title = format_string_centro_fill("产品序列号", 35, ' ');
    string file_path_title = format_string_centro_fill("许可文件路径", 20, ' ');
    string begin_time_title = format_string_centro_fill("许可生成时间", 24, ' ');
    string end_time_title = format_string_centro_fill("许可到期时间", 24, ' ');
    string all_time_title = format_string_centro_fill("许可有效期", 20, ' ');
    string remaining_time_title = format_string_centro_fill("许可剩余有效期", 20, ' ');
    serial_number = format_string_centro_fill(serial_number, 35, ' ');
    file_path = format_string_centro_fill(file_path, 109, ' ');
    begin_time = format_string_centro_fill(begin_time, 24, ' ');
    end_time = format_string_centro_fill(end_time, 24, ' ');
    all_time = format_string_centro_fill(all_time + "天", 20, ' ');
    remaining_time = format_string_centro_fill(remaining_time + "天", 20, ' ');
    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    cout << WNH_COLOR_BOLDWHITE << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│                                                  " << WNH_COLOR_BOLDMAGENTA << PROGRAM_NAME << " 服务端许可信息显示" << WNH_COLOR_BOLDWHITE << "                                                │" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├─────────────────────┬──────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << file_path_title << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << file_path << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << serial_number_title << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << begin_time_title << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN  << end_time_title  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << all_time_title << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << remaining_time_title << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼─────────────────────────┼─────────────────────────┼─────────────────────┼─────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << serial_number << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << begin_time << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED  << end_time  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << all_time << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << remaining_time << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "└────────────────────────────────────┴─────────────────────────┴─────────────────────────┴─────────────────────┴─────────────────────┘" << WNH_COLOR_RESET << endl;
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();
    return true;
}





