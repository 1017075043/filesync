#include "filesync.h"

void filesync::client_mode()
{
    WNHINFO(PROGRAM_NAME << "程序启动,启动方式:客户端");

    wnh_check_string chk_str;
    if(!chk_str.is_ip_address_and_num(filesync_server_ip + ":" + filesync_server_port))
    {
        WNHERROR(filesync_server_ip << ":" << filesync_server_port << ", 不是有效的IP地址和端口");
        return;
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

    wnh_filesync_client client_status_core(filesync_server_ip, stoi(filesync_server_port, NULL, 10));
    client_status_core.status_core();

    wnh_filesync_client client_sync_core(filesync_server_ip, stoi(filesync_server_port, NULL, 10));
    client_sync_core.sync_core();
    //检查状态线程和同步线程
    while(client_sync_core.live_sign && client_status_core.live_sign)
    {
        sleep(1);
    }
    //当更新状态线程或者同步线程出现异常时,将这两个线程的存活标志设置为false,并使用5秒的时间等待线程结束。
    client_sync_core.live_sign = false;
    client_status_core.live_sign = false;
    sleep(5);
}
