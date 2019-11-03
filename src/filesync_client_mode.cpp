#include "filesync.h"

void filesync::client_mode()
{
    WNHINFO(PROGRAM_NAME << "程序启动,启动方式:客户端");

    wnh_check_string chk_str;
    if(filesync_client_mode == ip_mode)
    {
        if(!chk_str.is_ip_address_and_num(filesync_server_ip + ":" + filesync_server_port))
        {
            WNHERROR(filesync_server_ip << ":" << filesync_server_port << ", 不是有效的IP地址和端口");
            return;
        }
    }
    else if(filesync_client_mode == config_mode)
    {
        wnh_system_operation sys_oper;
        if(!sys_oper.file_is_exist(filesync_client_config_path))
        {
            WNHERROR(filesync_client_config_path << ", 该配置文件不存在");
            return;
        }
    }

    if(filesync_client_root_limit == "limit root")
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

    if(chk_str.is_logs_level(filesync_client_logs_level))
    {
        init.set_logs_mode(filesync_client_logs_level);
    }
    else
    {
        WNHERROR("无效的日志等级");
        return ;
    }

    if(filesync_client_mode == ip_mode)
    {
        wnh_filesync_client_concurrent client;
        client.core(filesync_server_ip, stoi(filesync_server_port, NULL, 10));
    }
    else if(filesync_client_mode == config_mode)
    {
        wnh_filesync_client_concurrent client;
        client.core(filesync_client_config_path);
    }
}
