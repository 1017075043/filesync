#ifndef __wnh_filesync_control__
#define __wnh_filesync_control__

using namespace std;

#include "../../filesync_define.h"
#include "wnh_filesync_control_define.h"
#include "../wnh_define/wnh_filesync_tcp_define.h"
#include "../wnh_tcp_client/wnh_tcp_client.h"
//#include "../wnh_config_ini/wnh_config_ini.h"
#include "../wnh_config_ini_ex/wnh_config_ini_ex.h"
#include "../wnh_system_operation/wnh_system_operation.h"
#include "../wnh_shell_tables/wnh_shell_tables.h"

class wnh_filesync_control : public wnh_tcp_client
{
private:
    string ip; //服务端IP
    int port; //服务端使用的端口
    template <typename Type_v, typename Type>
    void set_vector_values(Type_v & values, const Type & arg); //设置vector变量值

    template <typename Type_v, typename Type, typename ... Types>
    void set_vector_values(Type_v & values, const Type & arg,const Types & ... args); //设置vector变量值

    template <typename Type_v, typename Type>
    void set_vector_values(const bool & status, Type_v & values, const Type & arg); //设置vector变量值

    template <typename Type_v, typename Type, typename ... Types>
    void set_vector_values(const bool & status, Type_v & values, const Type & arg,const Types & ... args); //设置vector变量值

    int fail_task_list_info_page; //失败页码数

public:
    wnh_filesync_control();
    wnh_filesync_control(const string &conf_parameter);
    wnh_filesync_control(const int argc, const char **argv);
    wnh_filesync_control(const string &ip, const int &port);
    ~wnh_filesync_control();

    wnh_config_ini_ex status_info;
    wnh_config_ini_ex sync_rule_info;
    wnh_config_ini_ex sync_transfer_info;
    wnh_config_ini_ex sync_fail_task_list_info;

    wnh_shell_tables shell_tables;

    void create_temp_list_dir();
    void get_server_status_info(); //获取服务端状态信息
    void get_server_status_info_while(); //获取服务端状态信息(循环)
    bool send_get_server_status_info(string & server_status_info_file_path); //向服务器发送获取服务端状态信息信号, 且获取服务端状态信息文件路径
    bool show_server_status_info(const string & server_status_info_file_path); //显示服务端状态
    int show_server_status_info(const string & server_status_info_file_path, const int & offset); //显示服务端状态

    void get_server_status_info_v1(); //获取服务端状态信息
    void get_server_status_info_while_v1(); //获取服务端状态信息(循环)
    bool send_get_server_status_info_v1(string & server_status_info); //向服务器发送获取服务端状态信息信号, 且获取服务端状态信息
    bool show_server_status_info_v1(const string & server_status_info); //显示服务端状态
    int show_server_status_info_v1(const string & server_status_info, const int & offset); //显示服务端状态

    bool show_server_status_info_son(string & pid, string & start_time, string & client_num, string & online_client_num, string & offline_client_num, string & task_num, string & complete_task_num, string & unfinished_task_num, string & fail_task_num, string & event_num); //显示服务端状态

    void get_client_status_info(); //获取客户端状态信息
    void get_client_status_info_while(); //获取客户端状态信息(循环)
    bool send_get_client_status_info(string & client_status_info_file_path); //向服务器发送获取客户端状态信息信号, 且获取客户端状态信息文件路径
    bool show_client_status_info(const string & client_status_info_file_path); //显示客户端状态
    int show_client_status_info(const string & client_status_info_file_path, const int & offset); //显示客户端状态
    vector<string> get_client_status_info(const string & client_status_info_file_path); //获取客户端状态信息
    bool show_client_status_info_son(const vector<string> & values_ss_temp);  //显示客户端状态

    void get_server_and_client_status_info(); //获取服务端和客户端状态信息
    void get_server_and_client_status_info_while(); //获取服务端和客户端状态信息(循环)

    void ues_instructions(); //使用说明
    void control_use_instructions(); //控制端使用说明
    void show_system_var(); //显示系统变量

    void get_synv_rule_info(); //获取客户端状态信息
    bool send_get_sync_rule_info(string & sync_rule_info_file_path); //向服务器发送获取同步规则信息信号, 且获取同步规则信息文件路径
    bool show_sync_info_info(const string & sync_info_info_file_path); //显示同步规则信息
    vector<string> get_sync_info_info(const string & sync_info_info_file_path); //获取同步规则信息

    void show_server_license();//显示许可信息

    bool send_get_server_license_info(string & license_info); //向服务器发送获许可信息信号, 且获取许可
    bool show_server_license_info(const string & license_info); //显示许可信息

    void get_sync_transfer_info(); //获取同步传输过程信息
    bool send_get_sync_transfer_info(string & sync_transfer_file_path); //向服务器发送获取同步传输过程信息信号, 且获取同步传输过程信息文件路径
    vector<string> get_sync_transfer_data_info(const string & sync_transfer_file_path); //获取同步传输过程数据信息
    bool show_sync_transfer_info(const string & sync_transfer_file_path); //显示同步传输过程数据信息

    void get_sync_fail_task_list_info(); //获取同步失败任务列表信息
    bool send_get_fail_task_list_info(string & sync_fail_task_list_file_path); //向服务器发送获取同步失败任务列表信号, 且获取同步失败任务列表文件路径
    vector<string> get_sync_fail_task_list_info(const string & sync_fail_task_list_file_path); //获取同步失败任务列表信息
    bool show_sync_fail_task_list_info(const string & sync_fail_task_list_file_path); //显示同步失败任务列表信息
    bool show_sync_fail_task_list_info_son(const vector<string> & values_ss_temp); //显示同步失败任务列表信息
    bool get_fail_task_list_info_page(); //同步失败任务列表信号换页选择
};

#endif
