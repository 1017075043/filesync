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

    if(chk_str.is_logs_level(filesync_control_logs_level))
    {
        init.set_logs_mode(filesync_control_logs_level);
    }
    else
    {
        WNHERROR("无效的日志等级");
        return ;
    }

    wnh_filesync_control control(filesync_server_ip, stoi(filesync_server_port, NULL, 10));
    if(filesync_control_use_parameter == "0" || filesync_control_use_parameter == "show use")
    {
        control.ues_instructions();
    }
    else if(filesync_control_use_parameter == "1" || filesync_control_use_parameter == "show list")
    {
        control.control_use_instructions();
    }
    else if(filesync_control_use_parameter == "2" || filesync_control_use_parameter == "show server client")
    {
        control.get_server_and_client_status_info();
    }
    else if(filesync_control_use_parameter == "3" || filesync_control_use_parameter == "show server client s")
    {
        control.get_server_and_client_status_info_while();
    }
    else if(filesync_control_use_parameter == "4" || filesync_control_use_parameter == "show server")
    {
        control.get_server_status_info_v1();
    }
    else if(filesync_control_use_parameter == "5" || filesync_control_use_parameter == "show server s")
    {
        control.get_server_status_info_while_v1();
    }
    else if(filesync_control_use_parameter == "6" || filesync_control_use_parameter == "show client")
    {
        control.get_client_status_info();
    }
    else if(filesync_control_use_parameter == "7" || filesync_control_use_parameter == "show client s")
    {
        control.get_client_status_info_while();
    }
    else if(filesync_control_use_parameter == "8" || filesync_control_use_parameter == "show sync rule")
    {
        control.get_synv_rule_info();
    }
    else if(filesync_control_use_parameter == "9" || filesync_control_use_parameter == "show system var")
    {
        control.show_system_var();
    }
    else if(filesync_control_use_parameter == "10" || filesync_control_use_parameter == "show license")
    {
        control.show_server_license();
    }
    else if(filesync_control_use_parameter == "11" || filesync_control_use_parameter == "show transfer")
    {
        control.get_sync_transfer_info();
    }
    else
    {
        control.ues_instructions();
    }
}
