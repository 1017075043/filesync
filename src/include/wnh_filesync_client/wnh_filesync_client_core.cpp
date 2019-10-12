#include "wnh_filesync_client.h"


void wnh_filesync_client::core()
{
    //WNHINFO("启动核心服务");
    ////thread start_online_core_pthread(&wnh_filesync_client::online_core, this);
    ////start_online_core_pthread.detach();
    //work_core();
}

void wnh_filesync_client::status_core() //发送客户端状态线程核心服务
{
    if(singleton_core_thread_flag)
    {
        singleton_core_thread_flag = false;
    }
    else
    {
        WNHWARN("该对象已经创建了其他的核心线程服务,无法再创建发送客户端状态线程核心服务");
        return ;
    }
    thread start_status_thread_core_pthread(&wnh_filesync_client::status_thread_core_v1, this);
    start_status_thread_core_pthread.detach();
    WNHINFO("发送客户端状态线程成功!");
}

void wnh_filesync_client::status_thread_core_v1() //发送客户端状态线程核心服务
{
    while(live_sign)
    {
        if(!unblock_connect(ip, to_string(port)))
        {
            WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
            close(socket_num);
            sleep(SERVER_LINK_INTERVAL);
            continue;
        }
        if(!send_start_session_info())
        {
            close(socket_num);
            sleep(SERVER_LINK_INTERVAL);
            continue;
        }
        if(!send_if_allow_connect())
        {
            send_end_session_info();
            live_sign = false;
            return;
        }
        if(!send_online_signal_v1())
        {
            close(socket_num);
            sleep(SERVER_LINK_INTERVAL);
            continue;
        }
        send_end_session_info();
        sleep(ONLINE_MESSAGE_SENDING_INTERVAL);
    }
}

//void wnh_filesync_client::status_thread_core() //发送客户端状态线程核心服务
//{
//    while(live_sign)
//    {
//        if(!unblock_connect(ip, to_string(port)))
//        {
//            WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
//            close(socket_num);
//            sleep(SERVER_LINK_INTERVAL);
//            continue;
//        }
//        if(!send_start_session_info())
//        {
//            live_sign = false;
//            return;
//        }
//        if(!send_if_allow_connect())
//        {
//            send_end_session_info();
//            live_sign = false;
//            return;
//        }
//        if(!send_online_signal_v1())
//        {
//            live_sign = false;
//            return;
//        }
//        send_end_session_info();
//        sleep(ONLINE_MESSAGE_SENDING_INTERVAL);
//    }
//}

void wnh_filesync_client::sync_core() //同步线程核心服务
{
    if(singleton_core_thread_flag)
    {
        singleton_core_thread_flag = false;
    }
    else
    {
        WNHWARN("该对象已经创建了其他的核心线程服务,无法再创建同步线程核心服务!");
        return ;
    }
    thread start_sync_thread_core_pthread(&wnh_filesync_client::sync_thread_core_v1, this);
    start_sync_thread_core_pthread.detach();
    WNHINFO("启动同步线程成功!");
}

void wnh_filesync_client::sync_thread_core_v1() //同步线程核心服务
{
    if(!sys_oper.is_dir(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH))
    {
        if(!sys_oper.create_dirs(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH))
        {
            WNHERROR("任务列表存放目录创建失败:" << WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH);
            exit(1);
        }
    }
    while(live_sign)
    {
        if(!unblock_connect(ip, to_string(port)))
        {
            WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
            close(socket_num);
            sleep(SERVER_LINK_INTERVAL);
            continue;
        }
        if(!send_start_session_info())
        {
            close(socket_num);
            sleep(SERVER_LINK_INTERVAL);
            continue;
        }
        if(!send_if_allow_connect())
        {
            send_end_session_info();
            live_sign = false;
            return;
        }
        bool is_wait = true;
        if(!sync_thread_core_son_core(is_wait))
        {
            close(socket_num);
            sleep(SERVER_LINK_INTERVAL);
            continue;
        }
        send_end_session_info();
        if(is_wait)
        {
            sleep(INTERVAL_BETWEEN_WORKER_THREADS);
        }
        else
        {
            usleep(100);
        }
    }
}

//void wnh_filesync_client::sync_thread_core() //同步线程核心服务
//{
//    if(!sys_oper.is_dir(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH))
//    {
//        if(!sys_oper.create_dirs(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH))
//        {
//            WNHERROR("任务列表存放目录创建失败:" << WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH);
//            exit(1);
//        }
//    }
//    while(live_sign)
//    {
//        if(!unblock_connect(ip, to_string(port)))
//        {
//            WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
//            close(socket_num);
//            sleep(SERVER_LINK_INTERVAL);
//            continue;
//        }
//        if(!send_start_session_info())
//        {
//            live_sign = false;
//            return;
//        }
//        if(!send_if_allow_connect())
//        {
//            send_end_session_info();
//            live_sign = false;
//            return;
//        }
//        bool is_wait = true;
//        if(!sync_thread_core_son_core(is_wait))
//        {
//            live_sign = false;
//            return;
//        }
//        send_end_session_info();
//        if(is_wait)
//        {
//            sleep(INTERVAL_BETWEEN_WORKER_THREADS);
//        }
//        else
//        {
//            usleep(100);
//        }
//    }
//}

bool wnh_filesync_client::sync_thread_core_son_core(bool & is_wait) //工作核心服务
{
    unsigned long task_num = 0;
    for(int get_task_num = 0; get_task_num < SIGNAL_SESSION_MAX_GET_TASK_NUM; get_task_num++)
    {
        if(!send_get_task_num(task_num))
        {
            return false;
        }
        if(task_num == 0)
        {
            return true;
        }
        string task_list_path;
        if(!send_get_task_list(task_list_path))
        {
            return false;
        }
        if(task_list_path.empty())
        {
            return false;
        }
        if(!download_file(task_list_path, task_list_path + TASK_LIST_FILE_SUFFIX))
        {
            return false;
        }

        task_info.read_config_ini(task_list_path + TASK_LIST_FILE_SUFFIX, false);
        for(int i = 0 ; i <= task_info.unit_num; i++)
        {
            wnh_inotify_use_sqlite::TASK_ATTR task_attr;
            if(!get_task_attr(task_attr, i))
            {
                //continue;
                return false;
            }
            if(task_perform(task_attr))
            {
                if(!send_task_complete(task_attr.src_path, task_attr.dst_path, task_attr.event_id))
                {
                    //continue;
                    return false;
                }
            }
            else
            {
                if(!send_task_fail(task_attr.src_path, task_attr.dst_path, task_attr.event_id))
                {
                    //continue;
                    return false;
                }
            }
        }
        task_info.clean_configure_ini();
        if(unlink((task_list_path + TASK_LIST_FILE_SUFFIX).c_str()) != 0)
        {
            WNHWARN("临时文件," << task_list_path + TASK_LIST_FILE_SUFFIX << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
        }
        if(task_num == (unsigned long)0)
        {
            break;
        }
    }

    if(task_num != (unsigned long)0)
    {
        is_wait = false;
    }
    else
    {
        task_num = true;
    }
    return true;
}

bool wnh_filesync_client::task_perform(wnh_inotify_use_sqlite::TASK_ATTR & task_attr) //执行一个任务
{
    int temp_event_id = atoi(task_attr.event_id.c_str());
    if(temp_event_id == WNH_INOTIFY_IN_ATTRIB)
    {
        string power; //文件的权限
        if(sys_oper.get_file_power_s(task_attr.dst_path, power)) //获取文件的权限
        {
            if(power != task_attr.file_power) //获取比较用户权限是否相同
            {
                if(!sys_oper.chmod_wnh(task_attr.dst_path, task_attr.file_power)) //不同就修改用户权限
                {
                    return false;
                }
            }
            else
            {
                WNHINFO("文件" << task_attr.dst_path << "权限相同, 无需修改");
            }
        }
        else
        {
            WNHERROR("文件" << task_attr.dst_path << "不存在");
            return false;
        }
        string user, group; //文件所属的用户和用户组
        if(sys_oper.get_file_uid(task_attr.dst_path, user) && sys_oper.get_file_gid(task_attr.dst_path, group)) //获取文件的权限
        {
            if(user != task_attr.file_user || group != task_attr.file_group) //获取比较用户权限是否相同
            {
                if(!sys_oper.chown_wnh(task_attr.dst_path, task_attr.file_user, task_attr.file_group))
                {
                    return false;
                }
            }
            else
            {
                WNHINFO("文件" << task_attr.dst_path << "文件所属的用户和用户组相同, 无需修改");
            }
        }
        else
        {
            WNHERROR("文件" << task_attr.dst_path << "不存在");
            return false;
        }
    }
    else if(temp_event_id == WNH_INOTIFY_IN_CREATE || temp_event_id == WNH_INOTIFY_IN_MOVED_TO || temp_event_id == WNH_INOTIFY_IN_MODIFY)
    {
        if(task_attr.file_type == "file")
        {
            string dir_temp = task_attr.dst_path.substr(0, task_attr.dst_path.rfind("/"));
            //检查文件存放的目录时候存在,如果不存在就创建目录,然后在下载文件,如果文件存在，就判断hash值来决定是否下载
            if(!sys_oper.is_dir(dir_temp))
            {
                if(!sys_oper.create_dirs(dir_temp))
                {
                    return false;
                }
                if(!download_file(task_attr.src_path, task_attr.dst_path))
                {
                    return false;
                }
                if(file_hash.get_file_md5(task_attr.dst_path) != task_attr.file_hash)
                {
                    WNHERROR("文件" << task_attr.dst_path << "下载后的hash值检验不匹配, 文件下载失败");
                    return false;
                }
            }
            else
            {
                if(!sys_oper.file_is_exist(task_attr.dst_path) || file_hash.get_file_md5(task_attr.dst_path) != task_attr.file_hash)
                {
                    if(!download_file(task_attr.src_path, task_attr.dst_path))
                    {
                        return false;
                    }
                    if(file_hash.get_file_md5(task_attr.dst_path) != task_attr.file_hash)
                    {
                        WNHERROR("文件" << task_attr.dst_path << "下载后的hash值检验不匹配, 文件下载失败");
                        return false;
                    }
                }
                else
                {
                    WNHINFO("文件" << task_attr.dst_path << "文件内容相同, 无需下载文件");
                }
            }
        }
        else if(task_attr.file_type == "dir")
        {
            if(!sys_oper.is_dir(task_attr.dst_path))
            {
                if(!sys_oper.create_dirs(task_attr.dst_path))
                {
                    return false;
                }
            }
        }
        string power; //文件的权限
        if(sys_oper.get_file_power_s(task_attr.dst_path, power)) //获取文件的权限
        {
            if(power != task_attr.file_power) //获取比较用户权限是否相同
            {
                if(!sys_oper.chmod_wnh(task_attr.dst_path, task_attr.file_power)) //不同就修改用户权限
                {
                    return false;
                }
            }
            else
            {
                WNHDEBUG("文件" << task_attr.dst_path << "权限相同, 无需修改");
            }
        }
        else
        {
            WNHERROR("文件" << task_attr.dst_path << "不存在");
            return false;
        }
        string user, group; //文件所属的用户和用户组
        if(sys_oper.get_file_uid(task_attr.dst_path, user) && sys_oper.get_file_gid(task_attr.dst_path, group)) //获取文件的权限
        {
            if(user != task_attr.file_user || group != task_attr.file_group) //获取比较用户权限是否相同
            {
                if(!sys_oper.chown_wnh(task_attr.dst_path, task_attr.file_user, task_attr.file_group))
                {
                    return false;
                }
            }
            else
            {
                WNHDEBUG("文件" << task_attr.dst_path << "文件所属的用户和用户组相同, 无需修改");
            }
        }
        else
        {
            WNHERROR("文件" << task_attr.dst_path << "不存在");
            return false;
        }
    }
    else if(temp_event_id == WNH_INOTIFY_IN_MOVED_FROM || temp_event_id == WNH_INOTIFY_IN_DELETE)
    {
        if(!sys_oper.file_or_dir_exist(task_attr.dst_path))
        {
            WNHINFO("文件" << task_attr.dst_path << "不存在, 忽略删除");
            return true;
        }
        if(!sys_oper.rm(task_attr.dst_path))
        {
            return false;
        }
    }
    return true;
}

bool wnh_filesync_client::get_task_attr(wnh_inotify_use_sqlite::TASK_ATTR & task_attr, const int & i) //获取任务属性
{
    //string task_name;
    //string event_id;
    //string src_path;
    //string dst_path;
    //string file_type;
    //string file_user;
    //string file_group;
    //string file_power;
    //inotify监听的事件,代号
    //#define WNH_INOTIFY_IN_ATTRIB 1
    //#define WNH_INOTIFY_IN_CREATE 2
    //#define WNH_INOTIFY_IN_MOVED_TO 3
    //#define WNH_INOTIFY_IN_MODIFY 4
    //#define WNH_INOTIFY_IN_MOVED_FROM 5
    //#define WNH_INOTIFY_IN_DELETE 6
    task_attr.task_name = task_info.unit[i]->name;
    task_attr.event_id = task_info.unit[i]->conf.get_one_config("event_id");
    task_attr.src_path = task_info.unit[i]->conf.get_one_config("src_path");
    task_attr.dst_path = task_info.unit[i]->conf.get_one_config("dst_path");
    if(task_attr.task_name.empty() || task_attr.event_id.empty() || task_attr.src_path.empty() || task_attr.dst_path.empty())
    {
        WNHWARN(SERVER_INFO_LOGS << "任务信息残缺,忽略该任务, 任务名:" << task_attr.task_name << ", 动作:" << watch.event_transform(task_attr.event_id) << ", 源路径:" << task_attr.src_path << ", 目标路径:" << task_attr.dst_path);
        return false;
    }
    int temp_event_id = atoi(task_attr.event_id.c_str());
    if(temp_event_id != WNH_INOTIFY_IN_MOVED_FROM && temp_event_id != WNH_INOTIFY_IN_DELETE)
    {
        task_attr.file_user = task_info.unit[i]->conf.get_one_config("file_user");
        task_attr.file_group = task_info.unit[i]->conf.get_one_config("file_group");
        task_attr.file_power = task_info.unit[i]->conf.get_one_config("file_power");
        if(task_attr.file_user.empty() || task_attr.file_group.empty() || task_attr.file_power.empty())
        {
            WNHWARN(SERVER_INFO_LOGS << "任务信息残缺,忽略该任务, 任务名:" << task_attr.task_name << ", 动作:" << watch.event_transform(task_attr.event_id) << ", 源路径:" << task_attr.src_path << ", 目标路径:" << task_attr.dst_path << ", 所属用户:" << task_attr.file_user << ", 所属用户组:" << task_attr.file_group << ", 权限:" << task_attr.file_power);
            return false;
        }
        if(temp_event_id == WNH_INOTIFY_IN_CREATE || temp_event_id == WNH_INOTIFY_IN_MOVED_TO || temp_event_id == WNH_INOTIFY_IN_MODIFY)
        {
            task_attr.file_type = task_info.unit[i]->conf.get_one_config("file_type");
            task_attr.file_hash = task_info.unit[i]->conf.get_one_config("file_hash");
            if(task_attr.file_type.empty() && task_attr.file_hash.empty() && task_attr.file_hash == "NULL")
            {
                WNHWARN(SERVER_INFO_LOGS << "任务信息残缺,忽略该任务, 任务名:" << task_attr.task_name << ", 动作:" << watch.event_transform(task_attr.event_id) << ", 源路径:" << task_attr.src_path << ", 目标路径:" << task_attr.dst_path << ", 所属用户:" << task_attr.file_user << ", 所属用户组:" << task_attr.file_group << ", 权限:" << task_attr.file_power << ", 文件类型:" << task_attr.file_type << ", 文件hash值:" << task_attr.file_hash);
                return false;
            }
        }
    }
    if(temp_event_id == WNH_INOTIFY_IN_ATTRIB)
    {
        WNHINFO(SERVER_INFO_LOGS << "任务信息:任务名:" << task_attr.task_name << ", 动作:" << watch.event_transform(task_attr.event_id) << ", 源路径:" << task_attr.src_path << ", 目标路径:" << task_attr.dst_path << ", 所属用户:" << task_attr.file_user << ", 所属用户组:" << task_attr.file_group << ", 权限:" << task_attr.file_power);
    }
    else if(temp_event_id == WNH_INOTIFY_IN_CREATE || temp_event_id == WNH_INOTIFY_IN_MOVED_TO || temp_event_id == WNH_INOTIFY_IN_MODIFY)
    {
        if(task_attr.file_type == "file")
        {
            WNHINFO(SERVER_INFO_LOGS << "任务信息:任务名:" << task_attr.task_name << ", 动作:" << watch.event_transform(task_attr.event_id) << ", 源路径:" << task_attr.src_path << ", 目标路径:" << task_attr.dst_path << ", 所属用户:" << task_attr.file_user << ", 所属用户组:" << task_attr.file_group << ", 权限:" << task_attr.file_power << ", 文件类型:" << task_attr.file_type << ", 文件hash值:" << task_attr.file_hash);
        }
        else
        {
            WNHINFO(SERVER_INFO_LOGS << "任务信息:任务名:" << task_attr.task_name << ", 动作:" << watch.event_transform(task_attr.event_id) << ", 源路径:" << task_attr.src_path << ", 目标路径:" << task_attr.dst_path << ", 所属用户:" << task_attr.file_user << ", 所属用户组:" << task_attr.file_group << ", 权限:" << task_attr.file_power << ", 文件类型:" << task_attr.file_type);
        }
    }
    else if(temp_event_id == WNH_INOTIFY_IN_MOVED_FROM || temp_event_id == WNH_INOTIFY_IN_DELETE)
    {
        WNHINFO(SERVER_INFO_LOGS << "任务信息:任务名:" << task_attr.task_name << ", 动作:" << watch.event_transform(task_attr.event_id) << ", 源路径:" << task_attr.src_path << ", 目标路径:" << task_attr.dst_path);
    }
    return true;
}
