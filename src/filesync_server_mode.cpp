#include "filesync.h"

void filesync::server_mode()
{
    WNHINFO(PROGRAM_NAME << "程序启动,启动方式:服务端");
    wnh_system_operation sys_oper;
    if(!sys_oper.file_is_exist(filesync_server_config_path))
    {
        WNHERROR(filesync_server_config_path << ", 该配置文件不存在");
        return;
    }

    if(filesync_server_root_limit == "limit root")
    {
        if((int)getuid() != 0)
        {
            WNHWARN("当前用户无权限运行程序, 请使用root用户来运行程序!");
            return ;
        }
    }

    if(init.check_process_exist(filesync_server_pid_path.c_str()))
    {
        return ;
    }

    wnh_check_string chk_str;
    if(chk_str.is_logs_level(filesync_server_logs_level))
    {
        init.set_logs_mode(filesync_server_logs_level);
    }
    else
    {
        WNHERROR("无效的日志等级");
        return ;
    }

    wnh_filesync_server server(filesync_server_config_path);
    server.core();
}
