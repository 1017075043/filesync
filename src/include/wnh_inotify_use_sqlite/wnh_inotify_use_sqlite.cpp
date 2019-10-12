#include "wnh_inotify_use_sqlite.h"

wnh_inotify_use_sqlite::wnh_inotify_use_sqlite()
{

}

wnh_inotify_use_sqlite::~wnh_inotify_use_sqlite()
{
    //delete register_watch_dir_path;
}

void wnh_inotify_use_sqlite::init()
{
    //register_wd = 0;
    //register_watch_dir_path = new string;
    start_watch_switch = false;
    repeated_event_neglect = true;
    fd = -1;
    this->set_max_user_watches();
    if(!watch_list_create_db() || !watch_list_drop_table() || !watch_list_create_table() || !event_list_drop_table() || !event_list_create_table() || !task_list_create_table() || !fail_task_list_create_table())
    {
        WNHERROR("数据表创建失败");
        exit(1);
    }
}

bool wnh_inotify_use_sqlite::create()//创建监听inotify实例
{
    if(fd != -1)
    {
        WNHERROR("初始化 inotify 失败, 该类已经创建了inotify实例");
        return false;
    }
    fd = inotify_init();
    if (fd < 0)
    {
        WNHERROR("初始化 inotify 失败");
        return false;
    }
    else
    {
        WNHINFO("初始化 inotify 成功, fd:" << fd);
    }
    return true;
}

bool wnh_inotify_use_sqlite::add_watch_unit(const string unit)//向inotify中添加一个监控
{
    int wd = inotify_add_watch(fd, unit.c_str(), WNH_INOTIFY_WATCH_EVENT);
    if (wd < 0)
    {
        if(fd == -1)
        {
            WNHERROR("inotify 添加监听失败,未初始化inotify,请先使用wnh_inotify_use_sqlite_create()方法进行初始化: " << unit);
        }
        else
        {
            WNHERROR("inotify 添加监听失败: " << unit << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    else
    {
        this->watch_list_add_one_record(wd, unit);
        WNHINFO("inotify 添加监听成功,且成功将数据记录进数据表: unit=" << unit << ", wd=" << wd);
        return true;
    }
}

bool wnh_inotify_use_sqlite::del_watch_unit(const string unit)//删除inotify监控数据表中指定监控单元
{
    int wd = this->watch_list_get_record(unit);
    if(wd == 0)
    {
        WNHWARN("inotify 删除监听失败,监控项在数据表中不存在: unit=" << unit);
        return false;
    }
    WNHDEBUG("获取" << unit << "对应的wd=" << wd);
    inotify_rm_watch(fd, wd);
    if(this->watch_list_delete_record(wd, unit))
    {
        WNHINFO("inotify 删除监听成功,且成功将数据从数据表中删除: unit=" << unit << ", wd=" << wd);
        return true;
    }
    else
    {
        WNHWARN("inotify 删除监听失败,数据从数据表中删除失败了: unit=" << unit);
        return false;
    }
}

bool wnh_inotify_use_sqlite::del_watch_unit(const int key)//删除inotify监控数据表中指定监控单元
{
    int wd = key;
    inotify_rm_watch(fd, wd);
    if(this->watch_list_delete_record(wd))
    {
        WNHDEBUG("inotify 删除监听成功,且成功将数据从数据表中删除: wd=" << wd);
        return true;
    }
    else
    {
        WNHWARN("inotify 删除监听失败,数据从数据表中删除失败了: wd=" << wd);
        return false;
    }
}

int wnh_inotify_use_sqlite::add_watch_dir(const string dir_path)//向inotify中添加一个目录监控,会监控目录下（包括子目录）的所有动作
{
    int fail_watch_num = 0;//记录添加监控失败的数量
    wnh_system_operation dir_list;
    if(!add_watch_unit(dir_path))
    {
        fail_watch_num++;
    }
    dir_list.get_dir(dir_path);
    while(dir_list.dir_file_list.num > 0)
    {
        if(!add_watch_unit(dir_list.dir_file_list.del_head()))
        {
            fail_watch_num++;
        }
    }
    return fail_watch_num;
}

int wnh_inotify_use_sqlite::del_watch_dir(const string dir_path)//向inotify中删除一个目录监控,将目录下（包括子目录）的所有监控项删除
{
    int fail_watch_num = 0;//记录删除监控失败的数量
    wnh_system_operation dir_list;
    dir_list.get_dir(dir_path);
    if(!del_watch_unit(dir_path))
    {
        WNHDEBUG("从监控数据表中获取数据删除一个监控失败 value=" << dir_path);
        fail_watch_num++;
    }
    else
    {
        WNHDEBUG("从监控数据表中获取数据删除一个监控成功 value=" << dir_path);
    }
    wnh_int_string_one_list::Node *node = new wnh_int_string_one_list::Node();
    while(dir_list.dir_file_list.del_head(node))
    {
        if(!del_watch_unit(node->value))
        {
            WNHDEBUG("从监控数据表中获取数据删除一个监控失败 value=" << node->value);
            fail_watch_num++;
        }
        else
        {
            WNHDEBUG("从监控数据表中获取数据删除一个监控成功 value=" << node->value);
        }
    }
    return fail_watch_num;
}

int wnh_inotify_use_sqlite::del_watch_dir_from_watch_list(const string dir_path)//从监控数据表中获取数据删除一个目录下的所有监控
{
    int fail_watch_num = 0;//记录删除监控失败的数量
    int row, column;
    string **result;
    this->watch_list_get_record(dir_path + "/", result, row, column);
    for(int i=0; i < row; i++)
    {
        inotify_rm_watch(fd, stoi(result[i][0].c_str()));
    }
    if(!this->watch_list_delete_record_like(dir_path + "/"))
    {
        WNHDEBUG("从监控数据表中获取数据删除一个监控失败");
        fail_watch_num++;
    }

    if(!del_watch_unit(dir_path))
    {
        WNHDEBUG("从监控数据表中获取数据删除一个监控失败 value=" << dir_path);
        fail_watch_num++;
    }
    else
    {
        WNHDEBUG("从监控数据表中获取数据删除一个监控成功 value=" << dir_path);
    }
    for( int i=0; i<row; i++ )
    {
        delete [] result[i];
    }
    delete result;
    return fail_watch_num;
}

bool wnh_inotify_use_sqlite::start_watch(USE_MODE mode)//开始inotify监控
{
    if(start_watch_switch)
    {
        WNHWARN("inotify监控 已经是开启状态");
        return false;
    }
    start_watch_switch = true;
    switch(mode)
    {
        case front_show:
        {
            thread start_watch_thread(&wnh_inotify_use_sqlite::start_watch_front_show, this);
            start_watch_thread.detach();
            WNHDEBUG("监控子线程启动完成,启动方式:前端显示 mode=front_show");
            break;
        }
        case back_record:
        {
            thread start_watch_thread(&wnh_inotify_use_sqlite::start_watch_back_record, this);
            start_watch_thread.detach();
            WNHDEBUG("监控子线程启动完成,启动方式:后台记录 mode=back_record");
            break;
        }
        default:
        {
            break;
        }
    }
    return true;
}

void wnh_inotify_use_sqlite::start_watch_front_show()//inotify监控子线程函数,前端显示使用方式
{
    int len, nread, mask;
    char buf[1024];
    struct inotify_event *event;
    string path;
    buf[sizeof(buf) - 1] = 0;
    int mask_temp = -1;
    string path_temp = "";
    unsigned long time_temp = LOCALTIMENUM;
    unsigned long time_temp_s = LOCALTIMENUM;
    while ((len = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        nread = 0;
        while (len > 0)
        {
            event = (struct inotify_event *)&buf[nread];
            if (event->len > 0)
            {
                string name = this->watch_list_get_record(event->wd);
                if(name == "")
                {
                    WNHWARN("查找失败,监控数据表中不存在节点 wd=" << event->wd);
                    break;
                }
                path = name + "/" + event->name;
                mask = mask_transform(event->mask);
                if(repeated_event_neglect) //重复事件忽略
                {
                    if(mask_temp == mask && LOCALTIMENUM-time_temp <= 1 && path_temp == path)
                    {
                        time_temp = LOCALTIMENUM;
                        if(LOCALTIMENUM-time_temp_s >= 2)
                        {
                            time_temp_s = LOCALTIMENUM;
                        }
                        else
                        {
                            nread = nread + sizeof(struct inotify_event) + event->len;
                            len = len - sizeof(struct inotify_event) - event->len;
                            continue;
                        }
                    }
                    else
                    {
                        mask_temp = mask;
                        path_temp = path;
                        time_temp = LOCALTIMENUM;
                        time_temp_s = LOCALTIMENUM;
                    }
                }
                if(!ignore_rule_list.is_match_rule(path))
                {
                    front_show_watch_event(path, mask);
                    auto_update_watch_unit(path, mask);
                }
                else
                {
                    show_ignore_event(path, mask);
                }
            }
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }
}

void wnh_inotify_use_sqlite::start_watch_back_record()//inotify监控子线程函数,后台记录使用方式
{
    int len, nread, mask;
    char buf[1024];
    struct inotify_event *event;
    string path;
    buf[sizeof(buf) - 1] = 0;
    int mask_temp = -1;
    string path_temp = "";
    unsigned long time_temp = LOCALTIMENUM;
    unsigned long time_temp_s = LOCALTIMENUM;
    while ((len = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        nread = 0;
        while (len > 0)
        {
            event = (struct inotify_event *)&buf[nread];
            if (event->len > 0)
            {
                string name = this->watch_list_get_record(event->wd);
                if(name == "")
                {
                    WNHWARN("查找失败,监控数据表中不存在节点 wd=" << event->wd);
                    break;
                }
                path = name + "/" + event->name;
                mask = mask_transform(event->mask);
                if(repeated_event_neglect) //重复事件忽略
                {
                    if(mask_temp == mask && LOCALTIMENUM-time_temp <= 1 && path_temp == path)
                    {
                        time_temp = LOCALTIMENUM;
                        if(LOCALTIMENUM-time_temp_s >= 2)
                        {
                            time_temp_s = LOCALTIMENUM;
                        }
                        else
                        {
                            nread = nread + sizeof(struct inotify_event) + event->len;
                            len = len - sizeof(struct inotify_event) - event->len;
                            continue;
                        }
                    }
                    else
                    {
                        mask_temp = mask;
                        path_temp = path;
                        time_temp = LOCALTIMENUM;
                        time_temp_s = LOCALTIMENUM;
                    }
                }
                if(!ignore_rule_list.is_match_rule(path))
                {
                    //back_record_watch_event(path, mask);
                    back_record_watch_event_sqlite(path, mask);
                    auto_update_watch_unit(path, mask);
                }
                else
                {
                    show_ignore_event(path, mask);
                }
            }
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }
}

inline int wnh_inotify_use_sqlite::mask_transform(int mask)//事件转换
{
    if(mask & IN_ATTRIB)
    {
        return WNH_INOTIFY_IN_ATTRIB;
    }
    else if(mask & IN_CREATE)
    {
        return WNH_INOTIFY_IN_CREATE;
    }
    else if(mask & IN_DELETE)
    {
        return WNH_INOTIFY_IN_DELETE;
    }
    else if(mask & IN_MODIFY)
    {
        return WNH_INOTIFY_IN_MODIFY;
    }
    else if(mask & IN_MOVED_FROM)
    {
        return WNH_INOTIFY_IN_MOVED_FROM;
    }
    else if(mask & IN_MOVED_TO)
    {
        return WNH_INOTIFY_IN_MOVED_TO;
    }
    return -1;
}

string wnh_inotify_use_sqlite::event_transform(const int & event_id)//事件转换
{
    string result;
    switch(event_id)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            result = "属性修改";
            return result;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            result = "创建";
            return result;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            result = "删除";
            return result;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            result = "内容修改";
            return result;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            result = "移除";
            return result;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            result = "移入";
            return result;
        }
        default:
        {
            result = "未知";
            return result;
        }
    }
}

string wnh_inotify_use_sqlite::event_transform(const string & event_id)//事件转换
{
    int event_id_temp = atoi(event_id.c_str());
    return event_transform(event_id_temp);
}

inline void wnh_inotify_use_sqlite::show_ignore_event(const string unit, int mask)//显示忽略事件的信息
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            WNHINFO("忽略事件 " << unit << " 属性被修改");
            break;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            WNHINFO("忽略事件 " << unit << " 被创建");
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            WNHINFO("忽略事件 " << unit << " 被删除");
            break;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            WNHINFO("忽略事件 " << unit << " 内容被修改");
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            WNHINFO("忽略事件 " << unit << " 被移除");
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            WNHINFO("忽略事件 " << unit << " 被移入");
            break;
        }
        default:
        {
            break;
        }
    }
}

inline void wnh_inotify_use_sqlite::front_show_watch_event(const string unit, int mask)//前端显示监视监控事件
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            WNHINFO(unit << " 属性被修改");
            //this->wnh_sys_op.show_file_all_info(unit);
            break;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            WNHINFO(unit << " 被创建");
            //this->wnh_sys_op.show_file_all_info(unit);
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            WNHINFO(unit << " 被删除");
            break;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            WNHINFO(unit << " 内容被修改");
            //this->wnh_sys_op.show_file_all_info(unit);
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            WNHINFO(unit << " 被移除");
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            WNHINFO(unit << " 被移入");
            //this->wnh_sys_op.show_file_all_info(unit);
            break;
        }
        default:
        {
            break;
        }
    }
}

inline void wnh_inotify_use_sqlite::back_record_watch_event(const string unit, int mask)//后台记录监视监控事件
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_ATTRIB, unit))
            {
                WNHINFO(unit << " 属性被修改");
                //WNHINFO(unit << " 属性被修改,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_ATTRIB, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 属性被修改,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_CREATE, unit))
            {
                WNHINFO(unit << " 被创建");
                //WNHINFO(unit << " 被创建,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_CREATE, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被创建,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_DELETE, unit))
            {
                WNHINFO(unit << " 被删除");
                //WNHINFO(unit << " 被删除,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_DELETE, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被删除,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_MODIFY, unit))
            {
                WNHINFO(unit << " 内容被修改");
                //WNHINFO(unit << " 内容被修改,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MODIFY, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 内容被修改,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_MOVED_FROM, unit))
            {
                WNHINFO(unit << " 被移除");
                //WNHINFO(unit << " 被移除,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MOVED_FROM, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被移除,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_MOVED_TO, unit))
            {
                WNHINFO(unit << " 被移入");
                //WNHINFO(unit << " 被移入,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MOVED_TO, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被移入,记录到缓存数据表中 失败");
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

inline void wnh_inotify_use_sqlite::back_record_watch_event_sqlite(const string unit, int mask)//后台记录监视监控事件
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_ATTRIB, unit))
            {
                WNHINFO(unit << " 属性被修改");
                //WNHINFO(unit << " 属性被修改,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_ATTRIB, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 属性被修改,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_CREATE, unit))
            {
                WNHINFO(unit << " 被创建");
                //WNHINFO(unit << " 被创建,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_CREATE, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被创建,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_DELETE, unit))
            {
                WNHINFO(unit << " 被删除");
                //WNHINFO(unit << " 被删除,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_DELETE, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被删除,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_MODIFY, unit))
            {
                WNHINFO(unit << " 内容被修改");
                //WNHINFO(unit << " 内容被修改,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MODIFY, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 内容被修改,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_MOVED_FROM, unit))
            {
                WNHINFO(unit << " 被移除");
                //WNHINFO(unit << " 被移除,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MOVED_FROM, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被移除,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_MOVED_TO, unit))
            {
                WNHINFO(unit << " 被移入");
                //WNHINFO(unit << " 被移入,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MOVED_TO, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被移入,记录到缓存数据表中 失败");
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

inline void wnh_inotify_use_sqlite::back_record_watch_event_sqlite_agent(const string unit, int mask)//后台记录监视监控事件-再次添加事件
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_ATTRIB, unit))
            {
                WNHINFO("再次添加, "<< unit << " 属性被修改");
                //WNHINFO(unit << " 属性被修改,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_ATTRIB, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN("再次添加, "<< unit << " 属性被修改,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_CREATE, unit))
            {
                WNHINFO("再次添加, "<< unit << " 被创建");
                //WNHINFO(unit << " 被创建,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_CREATE, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN("再次添加, "<< unit << " 被创建,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_DELETE, unit))
            {
                WNHINFO("再次添加, "<< unit << " 被删除");
                //WNHINFO(unit << " 被删除,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_DELETE, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN("再次添加, "<< unit << " 被删除,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_MODIFY, unit))
            {
                WNHINFO("再次添加, "<< unit << " 内容被修改");
                //WNHINFO(unit << " 内容被修改,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MODIFY, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN("再次添加, "<< unit << " 内容被修改,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_MOVED_FROM, unit))
            {
                WNHINFO("再次添加, "<< unit << " 被移除");
                //WNHINFO(unit << " 被移除,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MOVED_FROM, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN("再次添加, "<< unit << " 被移除,记录到缓存数据表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            if(this->event_list_add_one_record(WNH_INOTIFY_IN_MOVED_TO, unit))
            {
                WNHINFO("再次添加, "<< unit << " 被移入");
                //WNHINFO(unit << " 被移入,成功记录到缓存数据表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MOVED_TO, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN("再次添加, "<< unit << " 被移入,记录到缓存数据表中 失败");
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

inline bool wnh_inotify_use_sqlite::auto_update_watch_unit(const string unit, int mask)//自动更新监控的单元
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_CREATE:
        {
            wnh_system_operation file_open;
            //if(file_open.is_dir(unit) && !find_ignore_watch_dir(unit))
            if(file_open.is_dir(unit))
            {
                int temp = add_watch_dir(unit);
                again_add_event(mask, unit);
                if(temp == 0)
                {
                    WNHINFO("检测到监控目录下（创建）了一个目录:" << unit <<" ,且成功的将该目录加入监控数据表");
                }
                else
                {
                    WNHWARN("检测到监控目录下（创建）了一个目录:" << unit <<" ,但是将该目录加入监控数据表的过程中有" << temp << "个目录添加失败了");
                    return false;
                }
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            wnh_system_operation file_open;
            //if(file_open.is_dir(unit)  && !find_ignore_watch_dir(unit))
            if(file_open.is_dir(unit))
            {
                int temp = add_watch_dir(unit);
                again_add_event(mask, unit);
                if(temp == 0)
                {
                    WNHINFO("检测到监控目录下（移入）了一个目录:" << unit <<" ,且成功的将该目录加入监控数据表");
                }
                else
                {
                    WNHWARN("检测到监控目录下（移入）了一个目录:" << unit <<" ,但是将该目录加入监控数据表的过程中有" << temp << "个目录添加失败了");
                    return false;
                }
            }
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            if(this->watch_list_check_unit_exist(unit))
            {
                int temp = del_watch_dir_from_watch_list(unit);
                if(temp == 0)
                {
                    WNHINFO("检测到监控目录下（删除）了一个目录:" << unit <<" ,且成功的将该目录从监控数据表删除");
                }
                else
                {
                    WNHWARN("检测到监控目录下（删除）了一个目录:" << unit <<" ,但是将该目录从监控数据表删除的过程中有" << temp << "个目录删除失败了");
                    return false;
                }
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            if(this->watch_list_check_unit_exist(unit))
            {
                int temp = del_watch_dir_from_watch_list(unit);
                if(temp == 0)
                {
                    WNHINFO("检测到监控目录下（移出）了一个目录:" << unit <<" ,且成功的将该目录从监控数据表删除");
                }
                else
                {
                    WNHWARN("检测到监控目录下（移出）了一个目录:" << unit <<" ,但是将该目录从监控数据表删除的过程中有" << temp << "个目录删除失败了");
                    return false;
                }
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return true;
}

bool wnh_inotify_use_sqlite::add_ignore_rule(const string unit)//添加一个忽略规则
{
    if(ignore_rule_list.add_end_only(unit))
    {
        WNHINFO("添加一个忽略规则 unit=" << unit << " 成功");
        return true;
    }
    else
    {
        WNHWARN("添加一个忽略规则 unit=" << unit << " 失败");
        return false;
    }
}

bool wnh_inotify_use_sqlite::del_ignore_rule(const string unit)//删除一个忽略规则
{
    if(ignore_rule_list.find_list_delete(unit))
    {
        WNHINFO("删除一个忽略规则 unit=" << unit << " 成功");
        return true;
    }
    else
    {
        WNHERROR("删除一个忽略规则 unit=" << unit << " 失败");
        return false;
    }
}

bool wnh_inotify_use_sqlite::check_ignore_rule_exist(const string unit)//判断一个忽略规则是否存在
{
    return ignore_rule_list.find_list_exist(unit);
}

void wnh_inotify_use_sqlite::show_ignore_rule_list()//显示忽略规则数据表
{
    return ignore_rule_list.show_list();
}

void wnh_inotify_use_sqlite::clean_ignore_rule()//清空所有忽略规则
{
    return ignore_rule_list.delete_list();
}

bool wnh_inotify_use_sqlite::is_ignore_event(const string event)//判断是否为忽略事件
{
    return ignore_rule_list.is_match_rule(event);
}

void wnh_inotify_use_sqlite::set_max_user_watches()//设置max_user_watches
{
    pid_t pc;
    pc = fork();
    if(pc < 0) //子进程创建失败了
    {
        WNHERROR("子进程创建失败");
        exit(1);
    }
    else if(pc == 0) //在子进程中执行
    {
        WNHDEBUG("用子进程将fs.inotify.max_user_watches设置为524288");
        execl("/usr/sbin/sysctl", "sysctl", "fs.inotify.max_user_watches=524288", nullptr);
        exit(1);
    }
    else //在父进程中执行
    {
        int status;
        wait(&status);
        WNHINFO("将fs.inotify.max_user_watches设置为524288");
    }
}

void wnh_inotify_use_sqlite::start_event_list_show() //事件表数据显示
{
    while(1)
    {
        usleep(100);
        event_list_show();
    }
}

void wnh_inotify_use_sqlite::start_event_list() //事件表数据显示进程创建
{
    thread start_event_list_show_thread(&wnh_inotify_use_sqlite::start_event_list_show, this);
    start_event_list_show_thread.detach();
    WNHDEBUG("事件表数据显示进程创建完成,start_event_list_show_thread");
}

void wnh_inotify_use_sqlite::add_ignore_watch_dir(const string & ignore_dir) //添加忽略目录监听
{
    if(!find_ignore_watch_dir(ignore_dir))
    {
        ignore_watch_dir_list.push_back(ignore_dir);
        del_watch_dir_from_watch_list(ignore_dir);
        add_ignore_rule(ignore_dir);
    }
}

bool wnh_inotify_use_sqlite::find_ignore_watch_dir(const string & ignore_dir) //查找忽略目录监听
{
    static string cache_register = "";
    if(cache_register == ignore_dir)
    {
        WNHDEBUG("寄存器匹配到" << ignore_dir << "为忽略监听目录");
        return true;
    }
    vector<string>::iterator ret;
    ret = find(ignore_watch_dir_list.begin(), ignore_watch_dir_list.end(), ignore_dir);
    if(ret == ignore_watch_dir_list.end())
    {
        WNHDEBUG("忽略监听目录列表没有匹配到" << ignore_dir);
        return false;
    }
    else
    {
        WNHDEBUG("忽略监听目录列表匹配到" << ignore_dir);
        cache_register = ignore_dir;
        return true;
    }
}

void wnh_inotify_use_sqlite::again_add_event(const int & mask, const string & dir_path) //再次添加事件
{
    WNHINFO("将动作:" << event_transform(mask) << ", dir_path:" << dir_path << ", 时间:" << LOCALTIMENUM <<", 添加进入再次遍历列表");
    agent_event_list.add_end_only(LOCALTIMENUM, to_string(mask)+dir_path);
}

void wnh_inotify_use_sqlite::again_created_event() //再次创建事件
{
    string temp_mask_dir_path;
    int mask;
    string dir_path;
    wnh_system_operation sys_open;
    vector<string> file_path;
    while(agent_event_list.num > 0 && LOCALTIMENUM-agent_event_list.head->key > 1)
    {
        temp_mask_dir_path = agent_event_list.del_head();
        mask = atoi(temp_mask_dir_path.substr(0, 1).c_str());
        dir_path = temp_mask_dir_path.substr(1);
        file_path = sys_open.get_level_dir_quick(dir_path);
        for(int i = 0; i < (int)file_path.size(); i++)
        {
            if(sys_open.is_dir(file_path[i]))
            {
                again_add_event(mask, file_path[i]);
            }
            if(!ignore_rule_list.is_match_rule(file_path[i]))
            {
                back_record_watch_event_sqlite_agent(file_path[i], mask);
            }
        }
    }
}
