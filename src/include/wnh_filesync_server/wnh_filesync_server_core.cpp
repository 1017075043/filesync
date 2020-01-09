#include "wnh_filesync_server.h"

void wnh_filesync_server::core()
{
    get_conf(conf_path);
    if(license.check_license_file_effectiveness(lic.file_path) == (unsigned long)0) //许可检查
    {
        exit(1);
    }
    add_client_info();
    rectification_rule_conf();
    show_client_info();
    thread start_check_client_info_status_pthread(&wnh_filesync_server::check_client_info_status, this);
    start_check_client_info_status_pthread.detach();

    WNHINFO("启动核心服务");
    watch_core_v1();//watch核心服务
    timer_task();//定时任务
    update_client_task_num_and_fail_task_num(); //更新客户端任务数和失败任务数
    tcp_core();//tcp核心服务
}
