#include "wnh_filesync_control.h"

void wnh_filesync_control::get_server_and_client_status_info() //获取服务端和客户端状态信息
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
    send_end_session_info();
    show_server_status_info_v1(server_status_info); //显示服务端状态
    show_client_status_info(client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX);
    return;
}

void wnh_filesync_control::get_server_and_client_status_info_while() //获取服务端和客户端状态信息(循环)
{
    int offset1 = 0;
    int offset2 = 0;
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
        for(int i = 0; i < MAXIMUM_NUMBER_OF_REQUESTS_PER_SESSION; i++)
        {
            string server_status_info;
            if(!send_get_server_status_info_v1(server_status_info))
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
            if(offset1 == 0 && offset1 == 0)
            {
                if(!download_file(client_status_info_file_path, client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX))
                {
                    close(socket_num);
                    return;
                }
                offset1 += show_server_status_info_v1(server_status_info, 0); //显示服务端状态
                offset2 += show_client_status_info(client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX, 0);
            }
            else
            {
                if(server_status_info != WNH_FILESYNC_GET_SERVER_STATUS_IGNORE_INFO)
                {
                    show_server_status_info_v1(server_status_info, offset1 + offset2); //显示服务端状态
                    WNH_DISPLAY_STYLE_MOVEDOWN(offset2);
                }
                if(client_status_info_file_path != WNH_FILESYNC_GET_CLIENT_STATUS_IGNORE_INFO)
                {
                    if(!download_file(client_status_info_file_path, client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX))
                    {
                        close(socket_num);
                        return;
                    }
                    show_client_status_info(client_status_info_file_path + CLIENT_STATUS_INFO_FILE_SUFFIX, offset2);
                }
            }
            if(i != 9)
            {
                sleep(1);
            }
        }
        send_end_session_info();
        sleep(1);
    }
    return;
}
