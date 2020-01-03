#ifndef __wnh_filesync_server__
#define __wnh_filesync_server__

using namespace std;

#include "../wnh_define/wnh_filesync_tcp_define.h"
#include "wnh_filesync_server_init_define.h"
#include "../wnh_define/wnh_filesync_info_define.h"

#include "../wnh_config_ini/wnh_config_ini.h"
#include "../wnh_tcp_server/wnh_tcp_server.h"
#include "../wnh_inotify_use_sqlite/wnh_inotify_use_sqlite.h"
#include "../wnh_system_operation/wnh_system_operation.h"
#include "../wnh_openssl/wnh_openssl.h"
#include "../wnh_jwsmtp/jwsmtp.h"
#include "../wnh_license/wnh_license.h"

class wnh_filesync_server : public wnh_tcp_server
{
private:
    struct RULE //原始规则信息
    {
        string rule_name; //规则名称
        string src_dir; //源目录路径
        vector<string> dst_dir; //目标目录路径
        vector<string> dst_ip; //目标客户端IP
        vector<string> ignore_rule; //忽略同步规则
        vector<string> ignore_dir; //忽略同步目录
        bool rule_status; //状态
    };
    struct SYNC_RULE //有效的同步目录规则信息
    {
        string src_dir; //
        vector<string> dst_ip; //
        vector<string> dst_dir; //
        set<string> ignore_rule; //使用set容器实现对规则的去重
        set<string> ignore_dir; //使用set容器实现对规则的去重
    };
    struct CONNECT_INFO //连接信息
    {
        int client_nfp; //客户端连接句柄数
        string client_ip; //客户端连接IP
        int client_port; //客户端连接使用的临时端口
    };
    struct CLIENT_INFO //客户端信息
    {
        string client_ip; //客户端IP
        //string begin_connect_time;
        //string last_connect_time;
        unsigned long begin_connect_time; //客户端启动时间
        unsigned long last_connect_time; //客户端最后连接时间
        bool status; //状态
        unsigned long task_num; //任务数
        unsigned long fail_task_num; //失败任务数
        int is_email; //是否已经邮件告警，0:刚刚启动,1:在线，2:发送
    };
    string rule_identification; //规则识别标识
    struct EMAIL_INFO //邮件配置信息
    {
        bool status; //是否启用邮件报警
        string sender_email_address; //发件人邮箱地址
        vector<string> recipient_email_address; //收件人邮箱地址
        string email_server_address; //邮件服务器地址
        string email_server_user; //邮件服务器登录帐户
        string email_server_password; //邮件服务器登录帐户
    };

    struct LICENSE_INFO //许可信息
    {
        string file_path; //许可文件路径
        string begin_time; //开始时间
        string end_time; //结束时间
        unsigned long all_time; //有效期
        unsigned long remaining_time; //剩余有效期
        string serial_number; //序列号
    };


private:
    int pid; //进程PID
    string start_time; //启动时间

    int port; //使用端口号
    int network_timeout; //网络超时时间
    bool auto_restore_fail_task; //是否启动自动恢复失败任务
    bool persistence_task; //是否开启任务持久性
    //string license_file; //许可文件路径
    unsigned long license_remaining_effectiveness_time; //许可有效期剩余时间
    RULE *rule; //保存原始规则信息
    SYNC_RULE * sync_rule; //保存有效的同步目录规则信息
    int rule_num; //原始规则数量
    int sync_rule_num; //有效的同步目录规则数量
    wnh_config_ini conf; //配置信息
    wnh_inotify_use_sqlite watch; //事件监控
    unsigned int client_num; //客户端数量
    CLIENT_INFO *client_info; //客户端配置信息
    EMAIL_INFO email_info; //邮件配置信息
    string conf_path; //配置文件路径
    wnh_openssl file_hash; //获取文件hash值
    wnh_license license; //获取许可信息
    LICENSE_INFO lic; //许可信息

public:
    wnh_filesync_server();
    wnh_filesync_server(const string & conf_path);
    wnh_filesync_server(const int argc, const char **argv);
    ~wnh_filesync_server();
    void init(); //初始化

    void get_conf(const string &conf_path); //获取配置
    void get_rule_conf(); //获取规则配置
    void rectification_rule_conf(); //整理规则配置
    void show_rule_conf(); //显示配置

    void core(); //核心服务
    void tcp_core(); //tcp核心服务
    void watch_core(); //watch核心服务
    void watch_core_v1(); //使用wnh_inotify_use_sqlite进行目录监控,v1版本

    // 对wnh_tcp_server继承过来的方法进行重写
    bool creat_session_pthread(const int & nfp, const CONNECT_INFO & CONNECT_INFO); //创建会话线程
    bool build_session(const int & nfp, const CONNECT_INFO & CONNECT_INFO); //建立一个会话
    bool accept_start_session_info(const int nfp, const string info); //接收开始会话信息
    bool accept_end_session_info(const int nfp, const string info); //接收结束会话信息
    int server_accept(); //等待客户端的连接
    wnh_filesync_server::CONNECT_INFO server_accept_v1(); //等待客户端的连接
    int accept_file(const int nfp, const string info, string & accept_file_name, const CONNECT_INFO & CONNECT_INFO); //接收一个文件
    int accept_apply_downinfo_file_info(const int nfp, const string info, string & accept_file_name, const CONNECT_INFO & CONNECT_INFO); //接收请求文件下载信息
    bool add_session(thread *session, const int nfp, const CONNECT_INFO & CONNECT_INFO); //将一个会话添加进入会话记录列表
    bool close_session(const int nfp, const bool status); //关闭一个会话
    bool sub_session(const int nfp); //将一个会话从会话记录列表中删除
    bool manage_session_pthread(); //管理会话线程
    bool check_target_ip(const string & client_ip); //检查客户端IP是否为允许连接

    void event_into_task(); //将事件转换成任务
    void again_created_event(); //再次创建事件

    void add_client_info(); //添加客户端信息
    void show_client_info(); //显示客户端信息
    void update_client_info_status(const int & nfp, const CONNECT_INFO & CONNECT_INFO); //更新客户端状态信息
    void check_client_info_status(); //检查更新客户端状态信息
    void add_task_num_for_client_info(const int & nfp, const CONNECT_INFO & CONNECT_INFO);//更新客户端状态信息
    void add_fail_task_num_for_client_info(const int & nfp, const CONNECT_INFO & CONNECT_INFO);//更新客户端状态信息

    bool accept_if_allow_connect(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收检查客户端IP是否为允许连接信息
    bool accept_online_signal(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收在线信号
    bool accept_get_task_num(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收请求获取任务数
    bool accept_get_task_list(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收请求获取任务列表
    bool accept_task_complete(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收任务完成信息
    bool accept_task_fail(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收任务执行失败信息
    bool accept_task_complete_v1(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收任务完成信息
    bool accept_task_fail_v1(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收任务执行失败信息

    bool accept_get_server_status_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收获取服务端状态信息
    bool accept_get_server_status_info_v1(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收获取服务端状态信息
    bool create_server_status_info(const string & server_status_info_file_path); //创建服务端状态文件
    string create_server_status_info(); //创建服务端状态信息

    bool accept_get_client_status_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收获取客户端状态信息
    bool create_client_status_info(const string & server_status_info_file_path); //创建客户端状态文件

    bool email_client_offline_alert_info(const vector<string> & offline_client_ip, const vector<string> & begin_connect_time, const vector<string> & last_connect_time, const vector<string> & complete_task_num, const vector<string> & unfinished_task_num, const vector<string> & fail_task_num); //邮件发送告警信息
    string create_email_client_offline_content_html(const vector<string> & offline_client_ip, const vector<string> & begin_connect_time, const vector<string> & last_connect_time, const vector<string> & complete_task_num, const vector<string> & unfinished_task_num, const vector<string> & fail_task_num); //创建邮件告警信息内容

    void timer_task(); //定时任务
    void timer_task_son(const string & temp_dir_path); //定时任务

    bool accept_get_sync_rule_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收获取同步规则信息信息
    bool create_sync_rule_info(const string & client_status_info_file_path); //创建同步规则信息文件

    unsigned long get_license_info(); //获取许可信息
    bool accept_get_license_info(const int & nfp, const string & info, const CONNECT_INFO & CONNECT_INFO); //接收获取许可信息

    bool accept_get_sync_transfer_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收获取同步传输过程信息
    bool create_sync_transfer_info(const string & sync_transfer_file_path); //创建同步传输过程文件

    bool accept_get_sync_fail_task_list_info(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO); //接收获取同步失败任务列表信息
    bool create_sync_fail_task_list_info(const string & sync_fail_task_list_file_path, const string & line, const string & num); //创建同步失败任务列表信息文件
};

#endif
