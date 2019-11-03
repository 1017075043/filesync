#ifndef __wnh_filesync_client__
#define __wnh_filesync_client__

using namespace std;

#include "../wnh_define/wnh_filesync_tcp_define.h"
#include "wnh_filesync_client_init_define.h"

#include "../wnh_tcp_client/wnh_tcp_client.h"
#include "../wnh_config_ini/wnh_config_ini.h"
#include "../wnh_inotify_use_sqlite/wnh_inotify_use_sqlite.h"
#include "../wnh_system_operation/wnh_system_operation.h"
#include "../wnh_openssl/wnh_openssl.h"

class wnh_filesync_client : public wnh_tcp_client
{
private:
    string ip; //服务端IP
    int port; //服务端使用的端口
    wnh_config_ini task_info;
    wnh_inotify_use_sqlite watch;
    wnh_system_operation sys_oper;
    wnh_openssl file_hash;
    bool singleton_core_thread_flag; //单例核心线程标志

public:
    bool live_sign;

public:
    wnh_filesync_client();
    wnh_filesync_client(const string & ip_address_and_port);
    wnh_filesync_client(const int argc, const char **argv);
    wnh_filesync_client(const string & ip, const int & port);
    ~wnh_filesync_client();

    void init(); //初始化
    void core(); //核心服务

    void sync_core(); //同步线程核心服务
    void sync_thread_core(); //同步线程核心服务
    void sync_thread_core_v1(); //同步线程核心服务
    bool sync_thread_core_son_core(bool & is_wait); //同步线程核心服务

    void status_core(); //发送客户端状态线程核心服务
    void status_thread_core(); //发送客户端状态线程核心服务
    void status_thread_core_v1(); //发送客户端状态线程核心服务

    bool send_if_allow_connect();  //向服务端请求是否允许链接
    bool send_online_signal(); //向服务端发送在线信号
    bool send_online_signal_v1(); //向服务端发送在线信号
    bool send_end_session_info(); //发送结束会话信息
    bool download_file(const string file_name, const string temp_file_name); //下载文件
    bool send_get_task_num(unsigned long & task_num); //向服务器请求获取任务数
    bool send_get_task_list(string  & task_list_path); //向服务器请求获取任务列表
    bool get_task_attr(wnh_inotify_use_sqlite::TASK_ATTR & task_attr, const int & i); //获取任务属性
    bool send_task_complete(const string & task_src_path, const string & event_id); //向服务器发送任务完成信息
    bool send_task_complete(const string & task_src_path, const string & task_dst_path, const string & event_id); //向服务器发送任务完成信息
    bool send_task_fail(const string & task_src_path, const string & event_id); //向服务器发送任务执行失败信息
    bool send_task_fail(const string & task_src_path, const string & task_dst_path, const string & event_id); //向服务器发送任务执行失败信息
    bool task_perform(wnh_inotify_use_sqlite::TASK_ATTR & task_attr); //执行一个任务
};

#endif
