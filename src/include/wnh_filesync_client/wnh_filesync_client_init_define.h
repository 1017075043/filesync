#ifndef __wnh_filesync_init_define__
#define __wnh_filesync_init_define__

//服务端默认IP
#define IP "127.0.0.1"
//服务端默认PORT
#define PORT 54088

#define SERVER_INFO_LOGS  "服务端:" << ip << ":" << port << ", "

//在线信息发送时间间隔
#define ONLINE_MESSAGE_SENDING_INTERVAL 10
//工作线程运行间隔
#define INTERVAL_BETWEEN_WORKER_THREADS 3
//单次会话最大获取任务次数
#define SIGNAL_SESSION_MAX_GET_TASK_NUM 10
//任务列表文件后缀
#define TASK_LIST_FILE_SUFFIX ".client"

//服务端链接间隔,当和服务端连接失败时,下一次连接的时间间隔
#define SERVER_LINK_INTERVAL 10

#endif
