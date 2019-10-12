#include "wnh_filesync_server.h"

void wnh_filesync_server::core()
{
    get_conf(conf_path);
    show_rule_conf();
    add_client_info();
    rectification_rule_conf();
    show_client_info();
    thread start_check_client_info_status_pthread(&wnh_filesync_server::check_client_info_status, this);
    start_check_client_info_status_pthread.detach();

    WNHINFO("启动核心服务");
    watch_core_v1();//watch核心服务
    clean_temp_dir_file();//清理临时目录
    tcp_core();//tcp核心服务
}
