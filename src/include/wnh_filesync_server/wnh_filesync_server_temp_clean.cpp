#include "wnh_filesync_server.h"

void wnh_filesync_server::clean_temp_dir_file() //清理临时目录
{
    thread start_clean_temp_dir_file_son_pthread(&wnh_filesync_server::clean_temp_dir_file_son, this, WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH);
    start_clean_temp_dir_file_son_pthread.detach();
    WNHINFO("清理临时缓存文件线程启动成功");
}

void wnh_filesync_server::clean_temp_dir_file_son(const string & temp_dir_path) //清理临时目录
{
    wnh_system_operation sys_op;
    while(survival_id)
    {
        sleep(MAX_STORAGE_TIME_FOR_TEMP_FILES * 2);
        sys_op.rm_level_about_time_before(temp_dir_path, LOCALTIMENUM - MAX_STORAGE_TIME_FOR_TEMP_FILES);
    }
}
