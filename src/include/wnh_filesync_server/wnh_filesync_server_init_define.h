#ifndef __wnh_filesync_server_init_define__
#define __wnh_filesync_server_init_define__

//服务端使用的端口,默认port=54088
#define PORT 54088
//网络超时时间,单位:秒,默认network_timeout=10
#define NETWORK_TIMEOUT 10
//自动恢复失败任务,1：开启,0:不开启,默认auto_restore_fail_task=1
//这里的失败任务是指客户端离线导致的失败任务
#define AUTO_RESTORE_FAIL_TASK 1
//任务持久化,1：开启,0:不开启,默认persistence_task=1
//当服务端重启,若上一次有未完成的任务时，是否继续执行
#define PERSISTENCE_TASK 1
//同步规则标识头
#define RULE_IDENTIFICATION "rule::"
//许可文件
#define LICENSE_FILE "filesync.license"

//事件转换时间间隔,单位:秒
#define EVENT_TRANSITION_TIME_INTERVAL 3
//再次创建事件时间间隔,单位:秒
#define AGAIN_CREATED_EVENT_TIME_INTERVAL 1

#define CONNECT_INFO_LOGS "nfp:" << nfp << ", 客户端IP:" << CONNECT_INFO.client_ip << ", "

//临时文件最大保存时间,单位:秒
#define MAX_STORAGE_TIME_FOR_TEMP_FILES 20

//许可检查时间间隔,单位:秒
#define CLEARANCE_INSPECTION_INTERVAL 3600

//单次任务列表最大数量
#define SINGLE_TASK_LIST_MAX_NUM 10
//默认任务列表路径格式
#define DEFAULT_TASK_LIST_PATH_FORMAT  WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH + "/" + "task_list-" + CONNECT_INFO.client_ip + "-" + to_string(LOCALTIMENUM) + ".list"
//默认服务端状态状态路径格式
#define DEFAULT_SERVER_STATUS_PATH_FORMAT  WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH + "/" + "server_status-" + CONNECT_INFO.client_ip + "-" + to_string(LOCALTIMENUM) + ".info"
//默认客户端状态状态路径格式
#define DEFAULT_client_STATUS_PATH_FORMAT  WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH + "/" + "client_status-" + CONNECT_INFO.client_ip + "-" + to_string(LOCALTIMENUM) + ".info"
//默认同步规则信息路径格式
#define DEFAULT_SYNC_RULE_PATH_FORMAT  WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH + "/" + "sync_rule-" + CONNECT_INFO.client_ip + "-" + to_string(LOCALTIMENUM) + ".info"
//默认同步传输过程信息路径格式
#define DEFAULT_SYNC_TRANSFER_PATH_FORMAT  WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH + "/" + "sync_transfer-" + CONNECT_INFO.client_ip + "-" + to_string(LOCALTIMENUM) + ".info"
//同步传输过程数据最久时间，单位：秒
#define SYNC_TRANSFER_MAXIMUM_TIME 600
//单次同步传输过程数据最大数量
#define SYNC_TRANSFER_MAXIMUM_LINE_NUM 20
//默认同步失败任务列表信息路径格式
#define DEFAULT_SYNC_FAIL_TASK_LIST_PATH_FORMAT  WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH + "/" + "sync_fail_task_list-" + CONNECT_INFO.client_ip + "-" + to_string(LOCALTIMENUM) + ".info"

#endif
