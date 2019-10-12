#include "filesync.h"

void filesync::control_mode()
{
    WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");

    wnh_check_string chk_str;
    if(!chk_str.is_ip_address_and_num(filesync_server_ip + ":" + filesync_server_port))
    {
        WNHERROR(filesync_server_ip << ":" << filesync_server_port << ", 不是有效的IP地址和端口");
        return;
    }

    if(filesync_control_root_limit == "limit root")
    {
        if((int)getuid() != 0)
        {
            WNHWARN("当前用户无权限运行程序, 请使用root用户来运行程序!");
            return ;
        }
    }

    if(init.check_process_exist(filesync_client_pid_path.c_str()))
    {
        return ;
    }

    if(chk_str.is_logs_level(filesync_control_logs_level))
    {
        init.set_logs_mode(filesync_control_logs_level);
    }
    else
    {
        WNHERROR("无效的日志等级");
        return ;
    }

    WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    wnh_filesync_control control(filesync_server_ip, stoi(filesync_server_port, NULL, 10));
    if(filesync_control_use_parameter == "1" || filesync_control_use_parameter == "list")
    {
        control.ues_instructions();
    }
    else if(filesync_control_use_parameter == "2" || filesync_control_use_parameter == "server client")
    {
        control.get_server_and_client_status_info();
    }
    else if(filesync_control_use_parameter == "3" || filesync_control_use_parameter == "server client s")
    {
        control.get_server_and_client_status_info_while();
    }
    else if(filesync_control_use_parameter == "4" || filesync_control_use_parameter == "server")
    {
        control.get_server_status_info_v1();
    }
    else if(filesync_control_use_parameter == "5" || filesync_control_use_parameter == "server s")
    {
        control.get_server_status_info_while_v1();
    }
    else if(filesync_control_use_parameter == "6" || filesync_control_use_parameter == "client")
    {
        control.get_client_status_info();
    }
    else if(filesync_control_use_parameter == "7" || filesync_control_use_parameter == "client s")
    {
        control.get_client_status_info_while();
    }
    else
    {
        control.ues_instructions();
    }
}
