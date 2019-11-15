#include "wnh_filesync_control.h"

void wnh_filesync_control::show_license()//显示许可信息
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
