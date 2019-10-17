#include "wnh_filesync_server.h"

void wnh_filesync_server::timer_task() //定时任务
{
    thread start_timer_task_son_pthread(&wnh_filesync_server::timer_task_son, this, WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH);
    start_timer_task_son_pthread.detach();
    WNHINFO("定时任务线程启动成功");
}

void wnh_filesync_server::timer_task_son(const string & temp_dir_path) //定时任务
{
    wnh_system_operation sys_op;
    unsigned long long time = 0;
    while(survival_id)
    {
        time ++ ;
        if(time >= MAX_STORAGE_TIME_FOR_TEMP_FILES && time % MAX_STORAGE_TIME_FOR_TEMP_FILES == 0)
        {
            sys_op.rm_level_about_time_before(temp_dir_path, LOCALTIMENUM - MAX_STORAGE_TIME_FOR_TEMP_FILES); //清理临时目录
        }
        if(time >= CLEARANCE_INSPECTION_INTERVAL && time % CLEARANCE_INSPECTION_INTERVAL == 0)
        {
            get_license_info(); //检查许可
        }
        sleep(1);
    }
}
