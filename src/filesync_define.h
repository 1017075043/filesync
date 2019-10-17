#ifndef __filesync_define__
#define __filesync_define__

//export FILESYNC_START_MODE=control
#define FILESYNC_START_MODE                     "FILESYNC_START_MODE"           //程序启动模式
#define FILESYNC_START_MODE_DEFAUL              "control"                       //默认启动模式
//export FILESYNC_SERVER_IP=127.0.0.1
#define FILESYNC_SERVER_IP                      "FILESYNC_SERVER_IP"            //服务端服务器IP,针对客户端,控制端的配置
#define FILESYNC_SERVER_IP_DEFAULT              "127.0.0.1"                     //默认服务端服务器IP,针对客户端,控制端的配置
//export FILESYNC_SERVER_PORT=10086
#define FILESYNC_SERVER_PORT                    "FILESYNC_SERVER_PORT"          //服务端服务器端口,针对客户端,控制端的配置
#define FILESYNC_SERVER_PORT_DEFAULT            "10086"                         //默认服务端服务器端口,针对客户端,控制端的配置
//export FILESYNC_SERVER_CONFIG_PATH=filesync.conf
#define FILESYNC_SERVER_CONFIG_PATH             "FILESYNC_SERVER_CONFIG_PATH"   //配置文件路径,针对服务端的配置
#define FILESYNC_SERVER_CONFIG_PATH_DEFAULT     "filesync.conf"                 //默认配置文件路径,针对服务端的配置
//export FILESYNC_SERVER_PID_PATH=/var/run/filesync_server.pid
#define FILESYNC_SERVER_PID_PATH                "FILESYNC_SERVER_PID_PATH"      //PID文件路径,针对服务端的配置
#define FILESYNC_SERVER_PID_PATH_DEFAULT        "/var/run/filesync_server.pid"  //默认PID文件路径,针对服务端的配置
//export FILESYNC_SERVER_LOGS_LEVEL=WNH_INFO_XS
#define FILESYNC_SERVER_LOGS_LEVEL              "FILESYNC_SERVER_LOGS_LEVEL"    //日志等级,针对服务端的配置
#define FILESYNC_SERVER_LOGS_LEVEL_DEFAULT      "WNH_INFO_XS"                   //默认日志等级,针对服务端的配置
//export FILESYNC_SERVER_ROOT_LIMIT="limit root"
#define FILESYNC_SERVER_ROOT_LIMIT              "FILESYNC_SERVER_ROOT_LIMIT"    //root用户限制,针对服务端的配置
#define FILESYNC_SERVER_ROOT_LIMIT_DEFAULT      "limit root"                    //默认root用户限制,针对服务端的配置
//export FILESYNC_CLIENT_PID_PATH=/var/run/filesync_client.pid
#define FILESYNC_CLIENT_PID_PATH                "FILESYNC_CLIENT_PID_PATH"      //PID文件路径,针对客户端的配置
#define FILESYNC_CLIENT_PID_PATH_DEFAULT        "/var/run/filesync_client.pid"  //默认PID文件路径,针对客户端的配置
//export FILESYNC_CLIENT_LOGS_LEVEL=WNH_INFO_XS
#define FILESYNC_CLIENT_LOGS_LEVEL              "FILESYNC_CLIENT_LOGS_LEVEL"    //日志等级,针对客户端的配置
#define FILESYNC_CLIENT_LOGS_LEVEL_DEFAULT      "WNH_INFO_XS"                   //默认日志等级,针对客户端的配置
//export FILESYNC_CLIENT_ROOT_LIMIT="limit root"
#define FILESYNC_CLIENT_ROOT_LIMIT              "FILESYNC_CLIENT_ROOT_LIMIT"    //root用户限制,针对客户端的配置
#define FILESYNC_CLIENT_ROOT_LIMIT_DEFAULT      "limit root"                    //默认root用户限制,针对客户端的配置
//export FILESYNC_CONTROL_USE_PARAMETER=1
#define FILESYNC_CONTROL_USE_PARAMETER          "FILESYNC_CONTROL_USE_PARAMETER"//客户端默认使用参数,针对控制端的配置
#define FILESYNC_CONTROL_USE_PARAMETER_DEFAULT  "0"                             //默认客户端默认使用参数,针对控制端的配置
//export FILESYNC_COMTROL_PID_PATH=/var/run/filesync_control.pid
#define FILESYNC_CONTROL_PID_PATH               "FILESYNC_COMTROL_PID_PATH"     //PID文件路径,针对控制端的配置
#define FILESYNC_CONTROL_PID_PATH_DEFAULT       "/var/run/filesync_control.pid" //默认PID文件路径,针对控制端的配置
//export FILESYNC_COMTROL_LOGS_LEVEL=WNH_INFO_XS
#define FILESYNC_CONTROL_LOGS_LEVEL             "FILESYNC_COMTROL_LOGS_LEVEL"   //日志等级,针对控制端的配置
#define FILESYNC_CONTROL_LOGS_LEVEL_DEFAULT     "WNH_INFO_XS"                   //默认日志等级,针对控制端的配置
//export FILESYNC_CONTROL_ROOT_LIMIT="no limit root"
#define FILESYNC_CONTROL_ROOT_LIMIT             "FILESYNC_CONTROL_ROOT_LIMIT"   //root用户限制,针对控制端的配置
#define FILESYNC_CONTROL_ROOT_LIMIT_DEFAULT     "no limit root"                 //默认root用户限制,针对控制端的配置

#define FILESYNC_LICENSE_USER_KEY               "admin123!@#QWE"                 //许可生成使用秘钥

//export FILESYNC_START_MODE=control
//export FILESYNC_SERVER_IP=127.0.0.1
//export FILESYNC_SERVER_PORT=10086
//export FILESYNC_SERVER_CONFIG_PATH=filesync.conf
//export FILESYNC_SERVER_PID_PATH=/var/run/filesync_server.pid
//export FILESYNC_SERVER_LOGS_LEVEL=WNH_INFO_XS
//export FILESYNC_SERVER_ROOT_LIMIT="limit root"
//export FILESYNC_CLIENT_PID_PATH=/var/run/filesync_client.pid
//export FILESYNC_CLIENT_LOGS_LEVEL=WNH_INFO_XS
//export FILESYNC_CLIENT_ROOT_LIMIT="limit root"
//export FILESYNC_CONTROL_USE_PARAMETER=1
//export FILESYNC_COMTROL_PID_PATH=/var/run/filesync_control.pid
//export FILESYNC_COMTROL_LOGS_LEVEL=WNH_INFO_XS
//export FILESYNC_CONTROL_ROOT_LIMIT="no limit root"
//echo FILESYNC_START_MODE=$FILESYNC_START_MODE
//echo FILESYNC_SERVER_IP=$FILESYNC_SERVER_IP
//echo FILESYNC_SERVER_PORT=$FILESYNC_SERVER_PORT
//echo FILESYNC_SERVER_CONFIG_PATH=$FILESYNC_SERVER_CONFIG_PATH
//echo FILESYNC_SERVER_PID_PATH=$FILESYNC_SERVER_PID_PATH
//echo FILESYNC_SERVER_LOGS_LEVEL=$FILESYNC_SERVER_LOGS_LEVEL
//echo FILESYNC_SERVER_ROOT_LIMIT=$FILESYNC_SERVER_ROOT_LIMIT
//echo FILESYNC_CLIENT_PID_PATH=$FILESYNC_CLIENT_PID_PATH
//echo FILESYNC_CLIENT_LOGS_LEVEL=$FILESYNC_CLIENT_LOGS_LEVEL
//echo FILESYNC_CLIENT_ROOT_LIMIT=$FILESYNC_CLIENT_ROOT_LIMIT
//echo FILESYNC_CONTROL_USE_PARAMETER=$FILESYNC_CONTROL_USE_PARAMETER
//echo FILESYNC_COMTROL_PID_PATH=$FILESYNC_COMTROL_PID_PATH
//echo FILESYNC_COMTROL_LOGS_LEVEL=$FILESYNC_COMTROL_LOGS_LEVEL
//echo FILESYNC_CONTROL_ROOT_LIMIT=$FILESYNC_CONTROL_ROOT_LIMIT

#endif
