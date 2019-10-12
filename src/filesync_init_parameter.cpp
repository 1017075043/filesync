#include "filesync.h"

void filesync::init_parameter(const int argc,const char **argv) //初始化配置
{
    //从系统变量中获取配置
    getenv(FILESYNC_START_MODE) != NULL ? filesync_start_mode = getenv(FILESYNC_START_MODE) : filesync_start_mode = FILESYNC_START_MODE_DEFAUL;
    getenv(FILESYNC_SERVER_IP) != NULL ? filesync_server_ip = getenv(FILESYNC_SERVER_IP) : filesync_server_ip = FILESYNC_SERVER_IP_DEFAULT;
    getenv(FILESYNC_SERVER_PORT) != NULL ? filesync_server_port = getenv(FILESYNC_SERVER_PORT) : filesync_server_port = FILESYNC_SERVER_PORT_DEFAULT;

    getenv(FILESYNC_SERVER_CONFIG_PATH) != NULL ? filesync_server_config_path = getenv(FILESYNC_SERVER_CONFIG_PATH) : filesync_server_config_path = FILESYNC_SERVER_CONFIG_PATH_DEFAULT;
    getenv(FILESYNC_SERVER_PID_PATH) != NULL ? filesync_server_pid_path = getenv(FILESYNC_SERVER_PID_PATH) : filesync_server_pid_path = FILESYNC_SERVER_PID_PATH_DEFAULT;
    getenv(FILESYNC_SERVER_LOGS_LEVEL) != NULL ? filesync_server_logs_level = getenv(FILESYNC_SERVER_LOGS_LEVEL) : filesync_server_logs_level = FILESYNC_SERVER_LOGS_LEVEL_DEFAULT;
    getenv(FILESYNC_SERVER_ROOT_LIMIT) != NULL ? filesync_server_root_limit = getenv(FILESYNC_SERVER_ROOT_LIMIT) : filesync_server_root_limit = FILESYNC_SERVER_ROOT_LIMIT_DEFAULT;

    getenv(FILESYNC_CLIENT_PID_PATH) != NULL ? filesync_client_pid_path = getenv(FILESYNC_CLIENT_PID_PATH) : filesync_client_pid_path = FILESYNC_CLIENT_PID_PATH_DEFAULT;
    getenv(FILESYNC_CLIENT_LOGS_LEVEL) != NULL ? filesync_client_logs_level = getenv(FILESYNC_CLIENT_LOGS_LEVEL) : filesync_client_logs_level = FILESYNC_CLIENT_LOGS_LEVEL_DEFAULT;
    getenv(FILESYNC_CLIENT_ROOT_LIMIT) != NULL ? filesync_client_root_limit = getenv(FILESYNC_CLIENT_ROOT_LIMIT) : filesync_client_root_limit = FILESYNC_CLIENT_ROOT_LIMIT_DEFAULT;


    getenv(FILESYNC_CONTROL_USE_PARAMETER) != NULL ? filesync_control_use_parameter = getenv(FILESYNC_CONTROL_USE_PARAMETER) : filesync_control_use_parameter = FILESYNC_CONTROL_USE_PARAMETER_DEFAULT;
    getenv(FILESYNC_CONTROL_PID_PATH) != NULL ? filesync_control_pid_path = getenv(FILESYNC_CONTROL_PID_PATH) : filesync_control_pid_path = FILESYNC_CONTROL_PID_PATH_DEFAULT;
    getenv(FILESYNC_CONTROL_LOGS_LEVEL) != NULL ? filesync_control_logs_level = getenv(FILESYNC_CONTROL_LOGS_LEVEL) : filesync_control_logs_level = FILESYNC_CONTROL_LOGS_LEVEL_DEFAULT;
    getenv(FILESYNC_CONTROL_ROOT_LIMIT) != NULL ? filesync_control_root_limit = getenv(FILESYNC_CONTROL_ROOT_LIMIT) : filesync_control_root_limit = FILESYNC_CONTROL_ROOT_LIMIT_DEFAULT;

    if(argc > 1)
    {
        filesync_start_mode = argv[1];
    }
    //0        1      2             3                   4            5
    //filesync server filesync.conf filesync_server.pid "limit root" WNH_INFO_XS
    if(filesync_start_mode == "server")
    {
        if(argc > 2)
        {
            filesync_server_config_path = argv[2];
        }
        if(argc > 3)
        {
            filesync_server_pid_path = argv[3];
        }
        if(argc > 4)
        {
            filesync_server_root_limit = argv[4];
        }
        if(argc > 5)
        {
            filesync_server_logs_level = argv[5];
        }
    }
    else if(filesync_start_mode == "client")
    {
        if(argc > 2)
        {
            filesync_server_ip = argv[2];
        }
        if(argc > 3)
        {
            filesync_server_port = argv[3];
        }
        if(argc > 4)
        {
            filesync_client_pid_path = argv[4];
        }
        if(argc > 5)
        {
            filesync_client_root_limit = argv[5];
        }
        if(argc > 6)
        {
            filesync_client_logs_level = argv[6];
        }
    }
    else if(filesync_start_mode == "control")
    {
        if(argc > 2)
        {
            filesync_control_use_parameter = argv[2];
        }
        if(argc > 3)
        {
            filesync_server_ip = argv[3];
        }
        if(argc > 4)
        {
            filesync_server_port = argv[4];
        }
        if(argc > 5)
        {
            filesync_control_pid_path = argv[5];
        }
        if(argc > 6)
        {
            filesync_control_root_limit = argv[6];
        }
        if(argc > 7)
        {
            filesync_control_logs_level = argv[7];
        }
    }
    else
    {
        WNHERROR("错误的启动方式, 以服务端方式启动:filesync server 配置文件,以客户端方式启动:filesync client IP PORT, 以控制端方式启动:filesync client parameter IP PORT");
    }

    if(filesync_start_mode == "server")
    {
        WNHINFO("启动参数, filesync_start_mode=" << filesync_start_mode);
        WNHINFO("启动参数, filesync_server_config_path=" << filesync_server_config_path);
        WNHINFO("启动参数, filesync_server_pid_path=" << filesync_server_pid_path);
        WNHINFO("启动参数, filesync_server_root_limit=" << filesync_server_root_limit);
        WNHINFO("启动参数, filesync_server_logs_level=" << filesync_server_logs_level);
    }
    else if(filesync_start_mode == "client")
    {
        WNHINFO("启动参数, filesync_start_mode=" << filesync_start_mode);
        WNHINFO("启动参数, filesync_server_ip=" << filesync_server_ip);
        WNHINFO("启动参数, filesync_server_port=" << filesync_server_port);
        WNHINFO("启动参数, filesync_client_pid_path=" << filesync_client_pid_path);
        WNHINFO("启动参数, filesync_client_root_limit=" << filesync_client_root_limit);
        WNHINFO("启动参数, filesync_client_logs_level=" << filesync_client_logs_level);
    }
    else if(filesync_start_mode == "control")
    {
        WNHINFO("启动参数, filesync_start_mode=" << filesync_start_mode);
        WNHINFO("启动参数, filesync_control_use_parameter=" << filesync_control_use_parameter);
        WNHINFO("启动参数, filesync_server_ip=" << filesync_server_ip);
        WNHINFO("启动参数, filesync_server_port=" << filesync_server_port);
        WNHINFO("启动参数, filesync_control_pid_path=" << filesync_control_pid_path);
        WNHINFO("启动参数, filesync_control_root_limit=" << filesync_control_root_limit);
        WNHINFO("启动参数, filesync_control_logs_level=" << filesync_control_logs_level);
    }
}
