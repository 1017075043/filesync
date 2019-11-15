#include "wnh_filesync_control.h"
#include "wnh_filesync_control_server_status.cpp"
#include "wnh_filesync_control_client_status.cpp"
#include "wnh_filesync_control_server_and_client_status.cpp"
#include "wnh_filesync_control_use_instructions.cpp"
#include "wnh_filesync_control_sync_rule.cpp"
#include "wnh_filesync_control_license.cpp"

wnh_filesync_control::wnh_filesync_control()
{
    WNHDEBUG("wnh_filesync_control 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    this->ip = IP;
    this->port = PORT;
    WNHINFO("服务端IP:" << this->ip << ", 端口:" << this->port);
    create_temp_list_dir();
}

wnh_filesync_control::wnh_filesync_control(const string &conf_parameter)
{
    WNHDEBUG("wnh_filesync_control 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    string ip_address_and_port = conf_parameter;
    this->ip = ip_address_and_port.substr(0, ip_address_and_port.find(":"));
    this->port = atoi(ip_address_and_port.substr(ip_address_and_port.find(":")+1).c_str());
    WNHINFO("服务端IP:" << this->ip << ", 端口:" << this->port);
    create_temp_list_dir();
}

wnh_filesync_control::wnh_filesync_control(const int argc, const char **argv)
{
    WNHDEBUG("wnh_filesync_control 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    string ip_address_and_port = argv[2];
    this->ip = ip_address_and_port.substr(0, ip_address_and_port.find(":"));
    this->port = atoi(ip_address_and_port.substr(ip_address_and_port.find(":")+1).c_str());
    WNHINFO("服务端IP:" << this->ip << ", 端口:" << this->port);
    create_temp_list_dir();
}

wnh_filesync_control::wnh_filesync_control(const string &ip, const int &port)
{
    WNHDEBUG("wnh_filesync_control 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    this->ip = ip;
    this->port = port;
    WNHINFO("服务端IP:" << this->ip << ", 端口:" << this->port);
    create_temp_list_dir();
}

wnh_filesync_control::~wnh_filesync_control()
{
    WNHDEBUG("~wnh_filesync_control 析构");
}

void wnh_filesync_control::create_temp_list_dir()
{
    wnh_system_operation sys_oper;
    if(!sys_oper.is_dir(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH))
    {
        if(!sys_oper.create_dirs(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH))
        {
            WNHERROR("数据列表存放目录创建失败:" << WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH);
            exit(1);
        }
    }
    sys_oper.chmod_wnh(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH, "755");
}


