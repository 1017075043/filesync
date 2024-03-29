#ifndef __filesync__
#define __filesync__

//程序依赖sqlite/uuid,需要提前编译安装

using namespace std;

#include "include/wnh_base_class/wnh_base_class.h"
#include "include/wnh_filesync_init/wnh_filesync_init.h"
#include "include/wnh_config/wnh_config.h"
#include "include/wnh_system_operation/wnh_system_operation.h"
#include "include/wnh_check_string/wnh_check_string.h"
#include "include/wnh_filesync_client_concurrent/wnh_filesync_client_concurrent.h"
#include "include/wnh_filesync_server/wnh_filesync_server.h"
#include "include/wnh_filesync_control/wnh_filesync_control.h"
#include "include/wnh_shell_tables/wnh_shell_tables.h"
#include "include/wnh_config_ini_ex/wnh_config_ini_ex.h"

#include "filesync_define.h"

class filesync : public wnh_base_class
{
private:
    //wnh_config conf;//存储配置信息
    enum CLIENT_USE_MODE{ip_mode=1, config_mode=2};
    enum GET_VALUES_MODE{sequential_mode=1, parameter_mode=2};

    string filesync_start_mode;
    string filesync_server_ip;
    string filesync_server_port;

    string filesync_server_config_path;
    string filesync_server_pid_path;
    string filesync_server_root_limit;
    string filesync_server_logs_level;

    CLIENT_USE_MODE filesync_client_mode;
    string filesync_client_config_path;
    string filesync_client_pid_path;
    string filesync_client_root_limit;
    string filesync_client_logs_level;

    string filesync_control_use_parameter;
    string filesync_control_pid_path;
    string filesync_control_root_limit;
    string filesync_control_logs_level;

    string  server_serial_number; //服务器序列号
    unsigned long validity_time; //有效时间
    string license_use_key; //许可秘钥
    string license_file; //许可文件

public:
    filesync();
    ~filesync();

    wnh_filesync_init init;

    void startup_mode(const int argc,const char **argv); //程序启动方式
    void init_parameter(const int argc,const char **argv); //初始化配置
    void select_start_command_mode(const int argc,const char **argv, GET_VALUES_MODE & start_command_mode); //选择启动方式
    void sequential_mode_get_values(const int argc,const char **argv); //顺序方式取值
    void parameter_mode_get_values(const int argc,const char **argv); //参数传参方式取值

    void server_mode();
    void client_mode();
    void control_mode();
    void license_mode(); //许可创建模式

};

#endif
