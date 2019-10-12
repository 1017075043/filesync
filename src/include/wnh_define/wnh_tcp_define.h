#ifndef __wnh_tcp_define__
#define __wnh_tcp_define__

#define DIS_TRAN_LOG_0 0  //不显示数据传输过程日志
#define DIS_TRAN_LOG_1 1  //是否显示数据传输过程日志,长度
#define DIS_TRAN_LOG_2 2  //显示数据传输过程日志,内容+长度

#define WNH_TCP_IGNORE_RESULTS 0 //返回忽略结果
#define WNH_TCP_FAIL_RESULTS -1  //返回失败结果
#define WNH_TCP_SUCCESS_RESULTS 1//返回成功结果

#define TCP_LISTEN_CONCURRENT_MAX_NUM 100 //最大监听并发数

#define WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT 60 //独占会话最大超时时间,单位:秒
#define WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID "WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID" //独占会话最大超时时间标示ID

#define TCP_INFO_SZIE 1025 //使用TCP协议信息发送的尺寸
#define TCP_INFO_SZIE_RESERVE 1 //使用TCP协议信息发送的尺寸预留尺寸

#define WNH_TCP_START_SESSION_INFO "WNH_TCP_START_SESSION_INFO" //开始会话标识语
#define WNH_TCP_END_SESSION_INFO "WNH_TCP_END_SESSION_INFO" //结束会话标识语

#define WNH_TCP_START_SEND_FILE_INFO "WNH_TCP_START_SEND_FILE_INFO" //开始发送文件标识语
#define WNH_TCP_END_SEND_FILE_INFO "WNH_TCP_END_SEND_FILE_INFO" //结束发送文件标识语

#define WNH_TCP_START_SEND_FILE_CONTENT_INFO "WNH_TCP_START_SEND_FILE_CONTENT_INFO" //开始发送文件内容标识语
#define WNH_TCP_END_SEND_FILE_CONTENT_INFO "WNH_TCP_END_SEND_FILE_CONTENT_INFO" //结束发送文件内容标识语

#define WNH_TCP_START_ACCEPT_FILE_CONTENT_INFO "WNH_TCP_START_ACCEPT_FILE_CONTENT_INFO" //成功接收一行文件内容标识语

#define WNH_TCP_SEND_FILE_SIZE_INFO "WNH_TCP_SEND_FILE_SIZE_INFO:" //发送文件大小标识语
#define WNH_TCP_SEND_FILE_NAME_INFO "WNH_TCP_SEND_FILE_NAME_INFO:" //发送文件名称标识语

#define WNH_TCP_APPLY_DOWNLOAD_FILE_INFO "WNH_TCP_APPLY_DOWNLOAD_FILE_INFO:" //请求下载一个文件
#define WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_ERROR_END "WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_ERROR_END" //错误结束请求下载一个文件
#define WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_SIZE "WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_SIZE:" //回复请求下载一个文件的文件大小
#define WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_COMPLETE "WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_COMPLETE" //请求下载一个文件完成

#define WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_START "WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_START" //请求下载一个文件开始发送文件内容
#define WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_STOP "WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_STOP" //请求下载一个文件完成发送文件内容
#define WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_RESULT "WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_RESULT" //请求下载一个文件成功发送一行文件内容标识语

#endif
