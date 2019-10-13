#ifndef __wnh_filesync_control_define__
#define __wnh_filesync_control_define__

//服务端默认IP
#define IP "127.0.0.1"
//服务端默认PORT
#define PORT 54088

#define SERVER_INFO_LOGS  "服务端:" << ip << ":" << port << ", "

//服务端状态信息文件后缀
#define SERVER_STATUS_INFO_FILE_SUFFIX ".control"

//客户端状态信息文件后缀
#define CLIENT_STATUS_INFO_FILE_SUFFIX ".control"

//同步规则信息文件后缀
#define SYNC_RULE_INFO_FILE_SUFFIX ".control"

//单次会话最大请求次数
#define MAXIMUM_NUMBER_OF_REQUESTS_PER_SESSION 60

//请求时间间隔
#define REQUEST_INTERVAL 1

//客户端状态信息显示
#define CLIENT_STATUS_INFO_DISPLAY_1  WNH_COLOR_BOLDWHITE << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << WNH_COLOR_WHITE
#define CLIENT_STATUS_INFO_DISPLAY_2  WNH_COLOR_BOLDWHITE << "│                                                  " << WNH_COLOR_BOLDMAGENTA << PROGRAM_NAME << " 客户端状态信息显示" << WNH_COLOR_BOLDWHITE << "                                                │" << WNH_COLOR_WHITE
#define CLIENT_STATUS_INFO_DISPLAY_3  WNH_COLOR_BOLDWHITE << "├──────────────────────────┬───────────┬───────────────────┬───────────────────┬────────────┬──────────────┬─────────────┬───────────┤" << WNH_COLOR_WHITE
#define CLIENT_STATUS_INFO_DISPLAY_4  WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN   << "         客户端IP         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN  << "客户端状态 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  客户端启动时间   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "客户端最后活动时间 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << " 全部任务数 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << " 已完成任务数 "  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN   << "未完成任务数 "     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "失败任务数 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_WHITE
#define CLIENT_STATUS_INFO_DISPLAY_5  WNH_COLOR_BOLDWHITE << "├──────────────────────────┼───────────┼───────────────────┼───────────────────┼────────────┼──────────────┼─────────────┼───────────┤" << WNH_COLOR_WHITE
#define CLIENT_STATUS_INFO_DISPLAY_6  WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << client_ip                    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN << status        << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << begin_connect_time    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << last_connect_time     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << task_num       << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << complete_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << unfinished_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << fail_task_num  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_WHITE
#define CLIENT_STATUS_INFO_DISPLAY_7  WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << client_ip                    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED   << status        << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << begin_connect_time    << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED  << last_connect_time     << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << task_num       << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << complete_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << unfinished_task_num << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << fail_task_num  << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_WHITE
#define CLIENT_STATUS_INFO_DISPLAY_8  WNH_COLOR_BOLDWHITE << "└──────────────────────────┴───────────┴───────────────────┴───────────────────┴────────────┴──────────────┴─────────────┴───────────┘" << WNH_COLOR_WHITE
    

#endif
