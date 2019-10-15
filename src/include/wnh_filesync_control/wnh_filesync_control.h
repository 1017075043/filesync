#ifndef __wnh_filesync_control__
#define __wnh_filesync_control__

using namespace std;

#include "../../filesync_define.h"
#include "wnh_filesync_control_define.h"
#include "../wnh_define/wnh_filesync_tcp_define.h"
#include "../wnh_tcp_client/wnh_tcp_client.h"
#include "../wnh_config_ini/wnh_config_ini.h"
#include "../wnh_system_operation/wnh_system_operation.h"

class wnh_filesync_control : public wnh_tcp_client
{
private:
    string ip; //服务端IP
    int port; //服务端使用的端口

public:
    wnh_filesync_control();
    wnh_filesync_control(const string &conf_parameter);
    wnh_filesync_control(const int argc, const char **argv);
    wnh_filesync_control(const string &ip, const int &port);
    ~wnh_filesync_control();

    wnh_config_ini status_info;
    wnh_config_ini sync_rule_info;

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

    void get_server_and_client_status_info(); //获取服务端和客户端状态信息
    void get_server_and_client_status_info_while(); //获取服务端和客户端状态信息(循环)

    void ues_instructions(); //使用说明
    void control_use_instructions(); //控制端使用说明
    void show_system_var(); //显示系统变量

    void get_synv_rule_info(); //获取客户端状态信息
    bool send_get_sync_rule_info(string & sync_rule_info_file_path); //向服务器发送获取同步规则信息信号, 且获取同步规则信息文件路径
    bool show_sync_info_info(const string & sync_info_info_file_path); //显示同步规则信息

};

#endif
