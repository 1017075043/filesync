#include "wnh_filesync_control.h"
#include "wnh_filesync_control_server_status.cpp"
#include "wnh_filesync_control_client_status.cpp"
#include "wnh_filesync_control_server_and_client_status.cpp"
#include "wnh_filesync_control_use_instructions.cpp"
#include "wnh_filesync_control_sync_rule.cpp"
#include "wnh_filesync_control_license.cpp"
#include "wnh_filesync_control_sync_transfer.cpp"
#include "wnh_filesync_control_sync_fail_task_list.cpp"
#include "wnh_filesync_control_sync_complete_task_list.cpp"
#include "wnh_filesync_control_wait_sync_task_list.cpp"

wnh_filesync_control::wnh_filesync_control()
{
    WNHDEBUG("wnh_filesync_control 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    this->ip = IP;
    this->port = PORT;
    this->fail_task_list_info_page = 0;
    WNHDEBUG("服务端IP:" << this->ip << ", 端口:" << this->port);
    create_temp_list_dir();
}

wnh_filesync_control::wnh_filesync_control(const string &conf_parameter)
{
    WNHDEBUG("wnh_filesync_control 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    string ip_address_and_port = conf_parameter;
    this->ip = ip_address_and_port.substr(0, ip_address_and_port.find(":"));
    this->port = atoi(ip_address_and_port.substr(ip_address_and_port.find(":")+1).c_str());
    this->fail_task_list_info_page = 0;
    WNHDEBUG("服务端IP:" << this->ip << ", 端口:" << this->port);
    create_temp_list_dir();
}

wnh_filesync_control::wnh_filesync_control(const int argc, const char **argv)
{
    WNHDEBUG("wnh_filesync_control 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    string ip_address_and_port = argv[2];
    this->ip = ip_address_and_port.substr(0, ip_address_and_port.find(":"));
    this->port = atoi(ip_address_and_port.substr(ip_address_and_port.find(":")+1).c_str());
    this->fail_task_list_info_page = 0;
    WNHDEBUG("服务端IP:" << this->ip << ", 端口:" << this->port);
    create_temp_list_dir();
}

wnh_filesync_control::wnh_filesync_control(const string &ip, const int &port)
{
    WNHDEBUG("wnh_filesync_control 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:控制端");
    this->ip = ip;
    this->port = port;
    this->fail_task_list_info_page = 0;
    WNHDEBUG("服务端IP:" << this->ip << ", 端口:" << this->port);
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

bool wnh_filesync_control::get_direction_keyboard_input_update_page(int & num, const int & change_num) //通过获取方向键输入更新页码
{
    while(1)
    {
        string stemp_s = get_keyboard_input_string();
        if(stemp_s == "up" || stemp_s == "W" || stemp_s == "w")
        {
            if(num >= change_num )
            {
                num = num - change_num;
                break;
            }
            else
            {
                continue;
            }
        }
        else if(stemp_s == "down" || stemp_s == "S" || stemp_s == "s")
        {
            num = num + change_num;
            break;
        }
        else
        {
            return false;
        }
    }
    return true;
}

template <typename Type_v, typename Type>
void wnh_filesync_control::set_vector_values(const bool & status, Type_v & values, const Type & arg) //设置vector变量值
{
    //WNHINFO("argc=" << arg);
    if(status == true)
    {
        values.clear();
    }
    values.push_back(arg);
}

template <typename Type_v, typename Type, typename ... Types>
void wnh_filesync_control::set_vector_values(const bool & status, Type_v & values, const Type & arg,const Types & ... args) //设置vector变量值
{
    //WNHINFO("argc=" << arg);
    if(status == true)
    {
        values.clear();
    }
    values.push_back(arg);
    set_vector_values(false, values, args...);
}

template <typename Type_v, typename Type>
void wnh_filesync_control::set_vector_values(Type_v & values, const Type & arg) //设置vector变量值
{
    //WNHINFO("argc=" << arg);
    values.push_back(arg);
}

template <typename Type_v, typename Type, typename ... Types>
void wnh_filesync_control::set_vector_values(Type_v & values, const Type & arg,const Types & ... args) //设置vector变量值
{
    //WNHINFO("argc=" << arg);
    values.push_back(arg);
    set_vector_values(false, values, args...);
}
