#include "wnh_inotify_ex.h"

wnh_inotify_ex::wnh_inotify_ex()
{
    WNHDEBUG("wnh_inotify_ex 构造");
}

wnh_inotify_ex::~wnh_inotify_ex()
{
    WNHDEBUG("~wnh_inotify_ex 析构");
}

void wnh_inotify_ex::init()
{
    this->mode = USE_MODE::back_record;
    this->set_max_user_watches();
}

void wnh_inotify_ex::init(USE_MODE mode)
{
    this->mode = mode;
    if(this->mode == USE_MODE::front_show)
    {
        WNHDEBUG("inotify创建成功,使用方式：前端显示");
    }
    if(this->mode == USE_MODE::back_record)
    {
        WNHDEBUG("inotify创建成功,使用方式：后台运行");
    }
    this->set_max_user_watches();
}

void wnh_inotify_ex::set_mode(USE_MODE mode)//修改启动模式
{
    this->mode = mode;
}

int wnh_inotify_ex::create_inotify()//创建监听inotify实例
{
    int fd = inotify_init();
    if(fd >= 0 && wathc_num.add_end_only(fd))
    {
        switch(mode)
        {
            case front_show:
            {
                thread start_watch_thread(&wnh_inotify_ex::start_watch_front_show, this, fd);
                start_watch_thread.detach();
                WNHDEBUG("创建inotify实例成功,且记录进wathc_num列表 fd=" << fd <<", 监控子线程启动完成");
                break;
            }
            case back_record:
            {
                thread start_watch_thread(&wnh_inotify_ex::start_watch_back_record, this, fd);
                start_watch_thread.detach();
                WNHDEBUG("创建inotify实例成功,且记录进wathc_num列表 fd=" << fd <<", 监控子线程启动完成");
                break;
            }
            default:
            {
                break;
            }
        }
        return fd;
    }
    else
    {
        WNHERROR("创建inotify实例失败" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return -1;
    }
}

int wnh_inotify_ex::distribution_inotify()//为监听分配inotify实例
{
    if(this->wathc_num.num == 0)
    {
        WNHDEBUG("当前还没有创建inotify实例,即将创建inotify实例");
        return create_inotify();
    }
    else
    {
        wathc_num.set_now_to_head();
        wnh_int_double_string_one_list::Node *node = new wnh_int_double_string_one_list::Node();
        while(wathc_num.get_now(node))
        {
            if(node->key1 < WATCH_MAX)
            {
                WNHDEBUG("分配inotify实例进行监听 fd=" << node->key << ", num=" << node->key1);
                int fd = node->key;
                delete node;
                node = nullptr;
                return fd;
            }
        }
        WNHDEBUG("当前创建的inotify实例的监控列表已经使用满了,需要创建新的inotify实例");
        delete node;
        node = nullptr;
        return create_inotify();
    }
}

bool wnh_inotify_ex::add_watch_unit(const string unit)//向inotify中添加一个监控
{
    int fd, wd;
    if(watch_list.find_list_exist(unit))
    {
        WNHWARN("inotify添加监听失败,监听列表中已经存在该监控项 unit=" << unit);
        return false;
    }

    fd = distribution_inotify();
    if(fd == -1)
    {
        WNHERROR("为监听分配inotify实例失败 unit=" << unit);
        return false;
    }
    else
    {
        WNHDEBUG("为监听分配inotify实例成功 fd=" << fd);
    }

    wd = inotify_add_watch(fd, unit.c_str(), WNH_INOTIFY_WATCH_EVENT);
    if (wd < 0)
    {
        WNHERROR("inotify添加监听失败 unit=" << unit << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    else
    {
        wnh_int_double_string_one_list::Node *node = new wnh_int_double_string_one_list::Node();
        if(!wathc_num.find_list_exist(fd, node))
        {
            WNHERROR("查找不到inotify实例 fd=" << fd);
            return false;
        }
        node->key1 = node->key1+1;
        if(!wathc_num.update_list(fd, node->key1-1, node))
        {
            WNHERROR("更新inotify实例监控数量值失败 fd=" << fd);
            return false;
        }
        if(watch_list.add_head_only(fd, wd, unit))
        {
            WNHDEBUG("inotify添加监听成功,且成功将数据记录进数据链表: unit=" << unit << ", wd=" << wd << ", fd=" << fd << ", fd实例监控数量=" << node->key1 << ", 总监控数量=" << watch_list.num << ", 总实例数=" << wathc_num.num);
            delete node;
            node = nullptr;
            return true;
        }
        else
        {
            WNHERROR("inotify添加监听成功,但是将数据记录进数据链失败: unit=" << unit << ", wd=" << wd << ", fd=" << fd);
            delete node;
            node = nullptr;
            return false;
        }
    }
}

bool wnh_inotify_ex::del_watch_unit(const string unit)//删除inotify监控列表中指定监控单元
{
    wnh_int_double_string_one_list::Node *node = new wnh_int_double_string_one_list::Node();
    if(watch_list.find_list_delete(unit, node))
    {
        int fd = node->key;
        int wd = node->key1;
        if(!wathc_num.find_list_exist(fd, node))
        {
            WNHERROR("查找不到inotify实例 fd=" << fd);
            return false;
        }
        inotify_rm_watch(fd, wd);
        node->key1 = node->key1-1;
        if(!wathc_num.update_list(fd, node->key1+1, node))
        {
            WNHERROR("更新inotify实例监控数量值失败 fd=" << fd);
            return false;
        }
        WNHDEBUG("inotify删除监听成功,且成功将数据从数据链表中删除: unit=" << unit << ", wd=" << wd << ", fd=" << fd << ", fd实例监控数量=" << node->key1 << ", 总监控数量=" << watch_list.num << ", 总实例数=" << wathc_num.num);
        return true;
    }
    WNHWARN("inotify删除监听失败,监控项在数据链表中不存在: unit=" << unit);
    return false;
}

int wnh_inotify_ex::add_watch_dir(const string dir_path)//向inotify中添加一个目录监控,会监控目录下（包括值目录）的所有动作,返回添加监控失败的数量
{
    int fail_watch_num = 0;//记录添加监控失败的数量
    wnh_system_operation dir_list;
    dir_list.get_dir(dir_path);
    if(!add_watch_unit(dir_path))
    {
        fail_watch_num++;
    }
    while(dir_list.dir_file_list.num > 0)
    {
        if(!add_watch_unit(dir_list.dir_file_list.del_head()))
        {
            fail_watch_num++;
        }
    }
    return fail_watch_num;
}

int wnh_inotify_ex::del_watch_dir(const string dir_path)//向inotify中删除一个目录监控,将目录下（包括子目录）的所有监控项删除,返回删除监控失败的数量
{
    int fail_watch_num = 0;//记录删除监控失败的数量
    wnh_system_operation dir_list;
    dir_list.get_dir(dir_path);
    if(!del_watch_unit(dir_path))
    {
        fail_watch_num++;
    }
    while(dir_list.dir_file_list.num > 0)
    {
        if(!del_watch_unit(dir_list.dir_file_list.del_head()))
        {
            fail_watch_num++;
        }
    }
    return fail_watch_num;
}

int wnh_inotify_ex::del_watch_dir_from_watch_list(const string dir_path)//从监控列表中获取数据删除一个目录下的所有监控,返回删除监控失败的数量
{
    int fail_watch_num = 0;//记录删除监控失败的数量
    if(!del_watch_unit(dir_path))
    {
        fail_watch_num++;
    }
    wnh_int_double_string_one_list::Node *node = new wnh_int_double_string_one_list::Node();
    watch_list.set_now_to_head();
    string path = dir_path + "/";
    int dir_path_length = path.length();
    while(watch_list.get_now(node))
    {
        if(node->value.substr(0, dir_path_length) == path)
        {
            if(!del_watch_unit(node->value))
            {
                fail_watch_num++;
            }
        }
    }
    delete node;
    node = nullptr;
    return fail_watch_num;
}

inline int wnh_inotify_ex::mask_transform(int mask)//事件转换
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

inline void wnh_inotify_ex::show_ignore_event(const string unit, int mask)//显示忽略事件的信息
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            WNHDEBUG("判定忽略事件 " << unit << " 属性被修改");
            break;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            WNHDEBUG("判定忽略事件 " << unit << " 被创建");
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            WNHDEBUG("判定忽略事件 " << unit << " 被删除");
            break;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            WNHDEBUG("判定忽略事件 " << unit << " 内容被修改");
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            WNHDEBUG("判定忽略事件 " << unit << " 被移除");
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            WNHDEBUG("判定忽略事件 " << unit << " 被移入");
            break;
        }
        default:
        {
            break;
        }
    }
}

inline bool wnh_inotify_ex::auto_update_watch_unit(const string unit, int mask)//自动更新监控的单元
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_CREATE:
        {
            wnh_system_operation file_open;
            if(file_open.is_dir(unit))
            {
                int temp = add_watch_dir(unit);
                if(temp == 0)
                {
                    WNHDEBUG("检测到监控目录下（创建）了一个目录:" << unit <<" ,且成功的将该目录加入监控列表");
                }
                else
                {
                    WNHWARN("检测到监控目录下（创建）了一个目录:" << unit <<" ,但是将该目录加入监控列表的过程中有" << temp << "个目录添加失败了");
                    return false;
                }
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            wnh_system_operation file_open;
            if(file_open.is_dir(unit))
            {
                int temp = add_watch_dir(unit);
                if(temp == 0)
                {
                    WNHDEBUG("检测到监控目录下（移入）了一个目录:" << unit <<" ,且成功的将该目录加入监控列表");
                }
                else
                {
                    WNHWARN("检测到监控目录下（移入）了一个目录:" << unit <<" ,但是将该目录加入监控列表的过程中有" << temp << "个目录添加失败了");
                    return false;
                }
            }
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            if(watch_list.find_list_exist(unit))
            {

                int temp = del_watch_dir_from_watch_list(unit);
                if(temp == 0)
                {
                    WNHDEBUG("检测到监控目录下（删除）了一个目录:" << unit <<" ,且成功的将该目录从监控列表删除");
                }
                else
                {
                    WNHWARN("检测到监控目录下（删除）了一个目录:" << unit <<" ,但是将该目录从监控列表删除的过程中有" << temp << "个目录删除失败了");
                    return false;
                }
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            if(watch_list.find_list_exist(unit))
            {
                int temp = del_watch_dir_from_watch_list(unit);
                if(temp == 0)
                {
                    WNHDEBUG("检测到监控目录下（移出）了一个目录:" << unit <<" ,且成功的将该目录从监控列表删除");
                }
                else
                {
                    WNHWARN("检测到监控目录下（移出）了一个目录:" << unit <<" ,但是将该目录从监控列表删除的过程中有" << temp << "个目录删除失败了");
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

inline void wnh_inotify_ex::front_show_watch_event(const string unit, int mask)//前端显示监视监控事件
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            WNHDEBUG(unit << " 属性被修改");
            this->wnh_sys_op.show_file_all_info(unit);
            break;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            WNHDEBUG(unit << " 被创建");
            this->wnh_sys_op.show_file_all_info(unit);
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            WNHDEBUG(unit << " 被删除");
            break;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            WNHDEBUG(unit << " 内容被修改");
            this->wnh_sys_op.show_file_all_info(unit);
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            WNHDEBUG(unit << " 被移除");
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            WNHDEBUG(unit << " 被移入");
            this->wnh_sys_op.show_file_all_info(unit);
            break;
        }
        default:
        {
            break;
        }
    }
}

void wnh_inotify_ex::start_watch_front_show(int fd)//inotify监控子线程函数,前端显示使用方式
{
    int len, nread, mask;
    char buf[1024];
    struct inotify_event *event;
    string path;
    buf[sizeof(buf) - 1] = 0;
    wnh_int_double_string_one_list::Node *node = new wnh_int_double_string_one_list::Node();
    while ((len = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        nread = 0;
        while (len > 0)
        {
            event = (struct inotify_event *)&buf[nread];
            if (event->len > 0)
            {
                if(!watch_list.find_list_exist(fd, (double)event->wd, node))
                {
                    WNHWARN("查找失败,监控列表中不存在节点 fd=" << fd << ", wd=" << event->wd);
                    break;
                }
                path = node->value + "/" + event->name;
                mask = mask_transform(event->mask);
                if(!ignore_rule_list.is_match_rule(path))
                {
                    front_show_watch_event(path, mask);
                }
                else
                {
                    show_ignore_event(path, mask);
                }
                auto_update_watch_unit(path, mask);
            }
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }
}

inline void wnh_inotify_ex::back_record_watch_event(const string unit, int mask)//后台记录监视监控事件
{
    switch(mask)
    {
        case WNH_INOTIFY_IN_ATTRIB:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_ATTRIB, unit))
            {
                WNHDEBUG(unit << " 属性被修改,成功记录到缓存列表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_ATTRIB, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 属性被修改,记录到缓存列表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_CREATE:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_CREATE, unit))
            {
                WNHDEBUG(unit << " 被创建,成功记录到缓存列表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_CREATE, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被创建,记录到缓存列表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_DELETE:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_DELETE, unit))
            {
                WNHDEBUG(unit << " 被删除,成功记录到缓存列表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_DELETE, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被删除,记录到缓存列表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MODIFY:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_MODIFY, unit))
            {
                WNHDEBUG(unit << " 内容被修改,成功记录到缓存列表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MODIFY, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 内容被修改,记录到缓存列表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_FROM:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_MOVED_FROM, unit))
            {
                WNHDEBUG(unit << " 被移除,成功记录到缓存列表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MOVED_FROM, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被移除,记录到缓存列表中 失败");
            }
            break;
        }
        case WNH_INOTIFY_IN_MOVED_TO:
        {
            if(event_list.add_head_only(WNH_INOTIFY_IN_MOVED_TO, unit))
            {
                WNHDEBUG(unit << " 被移入,成功记录到缓存列表中,unit=" << unit << ", mask=WNH_INOTIFY_IN_MOVED_TO, 缓存事件数量 num=" << event_list.num);
            }
            else
            {
                WNHWARN(unit << " 被移入,记录到缓存列表中 失败");
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void wnh_inotify_ex::start_watch_back_record(int fd)//inotify监控子线程函数,后台记录使用方式
{
    int len, nread, mask;
    char buf[1024];
    struct inotify_event *event;
    string path;
    buf[sizeof(buf) - 1] = 0;
    wnh_int_double_string_one_list::Node *node = new wnh_int_double_string_one_list::Node();
    while ((len = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        nread = 0;
        while (len > 0)
        {
            event = (struct inotify_event *)&buf[nread];
            if (event->len > 0)
            {
                if(!watch_list.find_list_exist(fd, (double)event->wd, node))
                {
                    WNHWARN("查找失败,监控列表中不存在节点 fd=" << fd << ", wd=" << event->wd);
                    break;
                }
                path = node->value + "/" + event->name;
                mask = mask_transform(event->mask);
                if(!ignore_rule_list.is_match_rule(path))
                {
                    back_record_watch_event(path, mask);
                }
                else
                {
                    show_ignore_event(path, mask);
                }
                auto_update_watch_unit(path, mask);
            }
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }
}

bool wnh_inotify_ex::add_ignore_rule(const string unit)//添加一个忽略规则
{
    if(ignore_rule_list.add_end_only(unit))
    {
        WNHDEBUG("添加一个忽略规则 unit=" << unit << " 成功");
        return true;
    }
    else
    {
        WNHDEBUG("添加一个忽略规则 unit=" << unit << " 失败");
        return false;
    }
}

bool wnh_inotify_ex::del_ignore_rule(const string unit)//删除一个忽略规则
{
    if(ignore_rule_list.find_list_delete(unit))
    {
        WNHDEBUG("删除一个忽略规则 unit=" << unit << " 成功");
        return true;
    }
    else
    {
        WNHDEBUG("删除一个忽略规则 unit=" << unit << " 失败");
        return false;
    }
}

bool wnh_inotify_ex::check_ignore_rule_exist(const string unit)//判断一个忽略规则是否存在
{
    return ignore_rule_list.find_list_exist(unit);
}

void wnh_inotify_ex::show_ignore_rule_list()//显示忽略规则列表
{
    return ignore_rule_list.show_list();
}

void wnh_inotify_ex::clean_ignore_rule()//清空所有忽略规则
{
    return ignore_rule_list.delete_list();
}

bool wnh_inotify_ex::is_ignore_event(const string event)//判断是否为忽略事件
{
    return ignore_rule_list.is_match_rule(event);
}

void wnh_inotify_ex::set_max_user_watches()//设置max_user_watches
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
        WNHDEBUG("将fs.inotify.max_user_watches设置为524288");
    }
}
