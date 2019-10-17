#include "wnh_filesync_server.h"
#include "wnh_filesync_server_conf.cpp"
#include "wnh_filesync_server_core.cpp"
#include "wnh_filesync_server_tcp.cpp"
#include "wnh_filesync_server_watch.cpp"
#include "wnh_filesync_server_tcp_function.cpp"
#include "wnh_filesync_server_client_manage.cpp"
#include "wnh_filesync_server_tcp_function_control.cpp"
#include "wnh_filesync_server_email_send.cpp"
#include "wnh_filesync_server_timer_task.cpp"
#include "wnh_filesync_server_license.cpp"

wnh_filesync_server::wnh_filesync_server()
{
    WNHDEBUG("wnh_filesync_server 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:服务端");
    init();
}

wnh_filesync_server::wnh_filesync_server(const string &conf_path)
{
    WNHDEBUG("wnh_filesync_server 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:服务端");
    this->conf_path = conf_path;
    init();
}

wnh_filesync_server::wnh_filesync_server(const int argc, const char **argv)
{
    WNHDEBUG("wnh_filesync_server 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:服务端");
    init();
}

wnh_filesync_server::~wnh_filesync_server()
{
    WNHDEBUG("~wnh_filesync_server 析构");
    survival_id = false;  //标志位死亡状态
    close(socket_num); //关闭套接字
    delete [] rule;
    delete [] sync_rule;
}

void wnh_filesync_server::init()
{
    start_time = LOCALTIME;
    pid = (int)getpid();
    port = PORT;
    network_timeout = NETWORK_TIMEOUT;
    auto_restore_fail_task = AUTO_RESTORE_FAIL_TASK;
    persistence_task = PERSISTENCE_TASK;
    rule_identification = RULE_IDENTIFICATION;
    license_file = LICENSE_FILE;
    client_num = 0;
    rule_num = 0;
    license_remaining_effectiveness_time = 1;
}
