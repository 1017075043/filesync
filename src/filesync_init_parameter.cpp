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

    getenv(FILESYNC_CLIENT_CONFIG_PATH) != NULL ? filesync_client_config_path = getenv(FILESYNC_CLIENT_CONFIG_PATH) : filesync_client_config_path = FILESYNC_CLIENT_CONFIG_PATH_DEFAULT;
    getenv(FILESYNC_CLIENT_PID_PATH) != NULL ? filesync_client_pid_path = getenv(FILESYNC_CLIENT_PID_PATH) : filesync_client_pid_path = FILESYNC_CLIENT_PID_PATH_DEFAULT;
    getenv(FILESYNC_CLIENT_LOGS_LEVEL) != NULL ? filesync_client_logs_level = getenv(FILESYNC_CLIENT_LOGS_LEVEL) : filesync_client_logs_level = FILESYNC_CLIENT_LOGS_LEVEL_DEFAULT;
    getenv(FILESYNC_CLIENT_ROOT_LIMIT) != NULL ? filesync_client_root_limit = getenv(FILESYNC_CLIENT_ROOT_LIMIT) : filesync_client_root_limit = FILESYNC_CLIENT_ROOT_LIMIT_DEFAULT;

    getenv(FILESYNC_CONTROL_USE_PARAMETER) != NULL ? filesync_control_use_parameter = getenv(FILESYNC_CONTROL_USE_PARAMETER) : filesync_control_use_parameter = FILESYNC_CONTROL_USE_PARAMETER_DEFAULT;
    getenv(FILESYNC_CONTROL_LOGS_LEVEL) != NULL ? filesync_control_logs_level = getenv(FILESYNC_CONTROL_LOGS_LEVEL) : filesync_control_logs_level = FILESYNC_CONTROL_LOGS_LEVEL_DEFAULT;

    server_serial_number = "";
    validity_time = 0;
    license_use_key = "";
    license_file = "";

    if(argc > 1)
    {
        filesync_start_mode = argv[1];
    }

    WNHDEBUG("argc:" << argc);
    for(int i = 0; i < argc; i++)
    {
        WNHDEBUG("argv[" << i << "]=" << argv[i]);
    }
    GET_VALUES_MODE start_command_mode = sequential_mode;
    select_start_command_mode(argc, argv, start_command_mode);
    if(start_command_mode == parameter_mode)
    {
        WNHDEBUG("使用参数传参的方式启动");
        parameter_mode_get_values(argc, argv); //参数传参方式取值
    }
    else
    {
        WNHDEBUG("使用顺序传参方式启动");
        sequential_mode_get_values(argc, argv); //顺序方式取值
    }

    if(filesync_start_mode == "server")
    {

        WNHDEBUG("启动参数, filesync_start_mode=" << filesync_start_mode << ", filesync_server_config_path=" << filesync_server_config_path << ", filesync_server_pid_path=" << filesync_server_pid_path << ", filesync_server_root_limit=" << filesync_server_root_limit << ", filesync_server_logs_level=" << filesync_server_logs_level);
    }
    else if(filesync_start_mode == "client")
    {
        if(filesync_client_mode == ip_mode)
        {
            WNHDEBUG("启动参数, filesync_start_mode=" << filesync_start_mode << ", filesync_server_ip=" << filesync_server_ip << ", filesync_server_port=" << filesync_server_port << ", filesync_client_pid_path=" << filesync_client_pid_path << ", filesync_client_root_limit=" << filesync_client_root_limit << ", filesync_client_logs_level=" << filesync_client_logs_level);
        }
        else if(filesync_client_mode == config_mode)
        {
            WNHDEBUG("启动参数, filesync_start_mode=" << filesync_start_mode << ", filesync_client_config_path=" << filesync_client_config_path << ", filesync_client_pid_path=" << filesync_client_pid_path << ", filesync_client_root_limit=" << filesync_client_root_limit << ", filesync_client_logs_level=" << filesync_client_logs_level);
        }
    }
    else if(filesync_start_mode == "control")
    {
        WNHDEBUG("启动参数, filesync_start_mode=" << filesync_start_mode << ", filesync_control_use_parameter=" << filesync_control_use_parameter << ", filesync_server_ip=" << filesync_server_ip << ", filesync_server_port=" << filesync_server_port << ", filesync_control_logs_level=" << filesync_control_logs_level);
    }
}

void filesync::select_start_command_mode(const int argc,const char **argv, GET_VALUES_MODE & start_command_mode) //选择启动方式
{
    for(int i = 2; i < argc; i++)
    {
        string parameter_temp = argv[i];
        if(parameter_temp.substr(0, 2) == "--")
        {
            if(to_lower_string(parameter_temp.substr(0, strlen("--conf="))) == "--conf=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--pid="))) == "--pid=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--limit="))) == "--limit=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--log="))) == "--log=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--logs="))) == "--logs=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--ip="))) == "--ip=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--port="))) == "--port=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--passwd="))) == "--passwd=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--key="))) == "--key=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--time="))) == "--time=" ||
                    to_lower_string(parameter_temp.substr(0, strlen("--license="))) == "--license=")
            {
                start_command_mode = parameter_mode;
                break;
            }
        }
    }
}

void filesync::sequential_mode_get_values(const int argc,const char **argv) //顺序传参方式取值
{
    wnh_check_string chk_str;
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
    //0        1      2         3     4                   5            6
    //filesync client 127.0.0.1 10086 filesync_server.pid "limit root" WNH_INFO_XS
    //0        1      2             3                   4            5
    //filesync client filesync.conf filesync_server.pid "limit root" WNH_INFO_XS
    else if(filesync_start_mode == "client")
    {
        if(argc > 2)
        {
            if(chk_str.is_ip_address(argv[2]))
            {
                filesync_client_mode = ip_mode;
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
            else
            {
                filesync_client_mode = config_mode;
                if(argc > 2)
                {
                    filesync_client_config_path = argv[2];
                }
                if(argc > 3)
                {
                    filesync_client_pid_path = argv[3];
                }
                if(argc > 4)
                {
                    filesync_client_root_limit = argv[4];
                }
                if(argc > 5)
                {
                    filesync_client_logs_level = argv[5];
                }
            }
        }
    }
    //0        1       2 3         4     5
    //filesync control 1 127.0.0.1 10086 WNH_INFO_XS
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
            filesync_control_logs_level = argv[5];
        }
    }
    //argc == 5 许可文件生成
    //argc == 3 查看许可文件中的许可信息

    //0        1       2                3                                4
    //filesync license 'admin123!@#QWE' f9dee3c5dc3bd38da006406a168bc88f 10
    //0        1       2
    //filesync license filesync.license
    else if(filesync_start_mode == "license" && (argc == 5 || argc == 3))
    {
        if(argc == 3)
        {
            license_file = argv[2];
        }
        else if(argc == 5)
        {
            license_use_key = argv[2];
            if(license_use_key != FILESYNC_LICENSE_USER_KEY)
            {
                filesync_start_mode = "control";
            }
            server_serial_number = argv[3];
            validity_time = stoul(argv[4], 0, 10);
        }
    }
    else
    {
        filesync_control_use_parameter = filesync_start_mode;
        filesync_start_mode = "control";
        //WNHINFO("filesync_control_use_parameter=" << filesync_control_use_parameter);
        //WNHERROR("错误的启动方式, 以服务端方式启动:filesync server 配置文件,以客户端方式启动:filesync client IP PORT, 以控制端方式启动:filesync control parameter IP PORT");
    }
}

void filesync::parameter_mode_get_values(const int argc,const char **argv) //参数传参方式取值
{
    wnh_check_string chk_str;
    //0        1      2                    3                         4                    5
    //filesync server --conf=filesync.conf --pid=filesync_server.pid --limit="limit root" --log=WNH_INFO_XS
    //filesync server --CONF=filesync.conf --PID=filesync_server.pid --LIMIT="limit root" --LOG=WNH_INFO_XS
    //filesync server --conf=filesync.conf --pid=filesync_server.pid --limit="limit root" --logs=WNH_INFO_XS
    //filesync server --CONF=filesync.conf --PID=filesync_server.pid --LIMIT="limit root" --LOGS=WNH_INFO_XS
    if(filesync_start_mode == "server")
    {
        for(int i = 2; i < argc; i++)
        {
            string parameter_temp = argv[i];
            if(to_lower_string(parameter_temp.substr(0, strlen("--conf="))) == "--conf=")
            {
                filesync_server_config_path = parameter_temp.substr(strlen("--conf="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--pid="))) == "--pid=")
            {
                filesync_server_pid_path = parameter_temp.substr(strlen("--pid="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--limit="))) == "--limit=")
            {
                filesync_server_root_limit = parameter_temp.substr(strlen("--limit="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--log="))) == "--log=")
            {
                filesync_server_logs_level = parameter_temp.substr(strlen("--log="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--logs="))) == "--logs=")
            {
                filesync_server_logs_level = parameter_temp.substr(strlen("--logs="));
            }
        }
    }
    //0        1      2              3            4                         5                    6
    //filesync client --ip=127.0.0.1 --port=10086 --pid=filesync_server.pid --limit="limit root" --log=WNH_INFO_XS
    //filesync client --IP=127.0.0.1 --PORT=10086 --PID=filesync_server.pid --LIMIT="limit root" --LOG=WNH_INFO_XS
    //filesync client --ip=127.0.0.1 --port=10086 --pid=filesync_server.pid --limit="limit root" --logs=WNH_INFO_XS
    //filesync client --IP=127.0.0.1 --PORT=10086 --PID=filesync_server.pid --LIMIT="limit root" --LOGS=WNH_INFO_XS
    //0        1      2                    3                         4                    5
    //filesync client --conf=filesync.conf --pid=filesync_server.pid --limit="limit root" --log=WNH_INFO_XS
    //filesync client --CONF=filesync.conf --PID=filesync_server.pid --LIMIT="limit root" --LOG=WNH_INFO_XS
    //filesync client --conf=filesync.conf --pid=filesync_server.pid --limit="limit root" --logs=WNH_INFO_XS
    //filesync client --CONF=filesync.conf --PID=filesync_server.pid --LIMIT="limit root" --LOGS=WNH_INFO_XS
    else if(filesync_start_mode == "client")
    {
        if(argc > 2)
        {
            if(chk_str.is_ip_address(argv[2]))
            {
                filesync_client_mode = ip_mode;
            }
            else
            {
                filesync_client_mode = config_mode;
            }
        }
        for(int i = 2; i < argc; i++)
        {
            string parameter_temp = argv[i];
            if(to_lower_string(parameter_temp.substr(0, strlen("--ip="))) == "--ip=")
            {
                filesync_server_ip = parameter_temp.substr(strlen("--ip="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--port="))) == "--port=")
            {
                filesync_server_port = parameter_temp.substr(strlen("--port="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--pid="))) == "--pid=")
            {
                filesync_client_pid_path = parameter_temp.substr(strlen("--pid="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--limit="))) == "--limit=")
            {
                filesync_client_root_limit = parameter_temp.substr(strlen("--limit="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--log="))) == "--log=")
            {
                filesync_client_logs_level = parameter_temp.substr(strlen("--log="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--logs="))) == "--logs=")
            {
                filesync_client_logs_level = parameter_temp.substr(strlen("--logs="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--conf="))) == "--conf=")
            {
                filesync_client_config_path = parameter_temp.substr(strlen("--conf="));
            }
        }
    }
    //0        1       2 3              4            5
    //filesync control 1 --ip=127.0.0.1 --port=10086 --log=WNH_INFO_XS
    //filesync control 1 --IP=127.0.0.1 --PORT=10086 --LOG=WNH_INFO_XS
    //filesync control 1 --ip=127.0.0.1 --port=10086 --logs=WNH_INFO_XS
    //filesync control 1 --IP=127.0.0.1 --PORT=10086 --LOGS=WNH_INFO_XS
    else if(filesync_start_mode == "control")
    {
        if(argc > 2)
        {
            filesync_control_use_parameter = argv[2];
        }
        for(int i = 3; i < argc; i++)
        {
            string parameter_temp = argv[i];
            if(to_lower_string(parameter_temp.substr(0, strlen("--ip="))) == "--ip=")
            {
                filesync_server_ip = parameter_temp.substr(strlen("--ip="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--port="))) == "--port=")
            {
                filesync_server_port = parameter_temp.substr(strlen("--port="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--log="))) == "--log=")
            {
                filesync_control_logs_level = parameter_temp.substr(strlen("--log="));
            }
            else if(to_lower_string(parameter_temp.substr(0, strlen("--logs="))) == "--logs=")
            {
                filesync_control_logs_level = parameter_temp.substr(strlen("--logs="));
            }
        }
    }

    //argc == 5 许可文件生成
    //argc == 3 查看许可文件中的许可信息

    //0        1       2                         3                                      4
    //filesync license --passwd='admin123!@#QWE' --key=f9dee3c5dc3bd38da006406a168bc88f --time=10
    //filesync license --PASSWD='admin123!@#QWE' --KEY=f9dee3c5dc3bd38da006406a168bc88f --TIME=10
    //0        1       2
    //filesync license --license=filesync.license
    //filesync license --LICENSE=filesync.license
    else if(filesync_start_mode == "license" && (argc == 5 || argc == 3))
    {
        if(argc == 3)
        {
            string parameter_temp = argv[2];
            if(to_lower_string(parameter_temp.substr(0, strlen("--license="))) == "--license=")
            {
                license_file = parameter_temp.substr(strlen("--license="));
            }
            else
            {
                filesync_start_mode = "control";
            }
        }
        else if(argc == 5)
        {
            for(int i = 2; i < argc; i++)
            {
                string parameter_temp = argv[i];
                if(to_lower_string(parameter_temp.substr(0, strlen("--passwd="))) == "--passwd=")
                {
                    license_use_key = parameter_temp.substr(strlen("--passwd="));
                    WNHDEBUG("license_use_key:" << license_use_key);
                }
                else if(to_lower_string(parameter_temp.substr(0, strlen("--key="))) == "--key=")
                {
                    server_serial_number = parameter_temp.substr(strlen("--key="));
                    WNHDEBUG("server_serial_number:" << server_serial_number);
                }
                else if(to_lower_string(parameter_temp.substr(0, strlen("--time="))) == "--time=")
                {
                    validity_time = stoul(parameter_temp.substr(strlen("--time=")));
                    WNHDEBUG("validity_time:" << validity_time);
                }
            }
            if(license_use_key != FILESYNC_LICENSE_USER_KEY || license_use_key.empty() || server_serial_number.empty() || validity_time == 0)
            {
                filesync_control_use_parameter = filesync_start_mode;
                filesync_start_mode = "control";
            }
        }
    }
    else
    {
        filesync_control_use_parameter = filesync_start_mode;
        filesync_start_mode = "control";
        //WNHINFO("filesync_control_use_parameter=" << filesync_control_use_parameter);
        //WNHERROR("错误的启动方式, 以服务端方式启动:filesync server 配置文件,以客户端方式启动:filesync client IP PORT, 以控制端方式启动:filesync control parameter IP PORT");
    }
}


