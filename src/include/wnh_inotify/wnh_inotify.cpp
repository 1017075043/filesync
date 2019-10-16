#include "wnh_inotify.h"

wnh_inotify::wnh_inotify()
{
    WNHDEBUG("wnh_inotify 构造");
}

wnh_inotify::~wnh_inotify()
{
    WNHDEBUG("~wnh_inotify 析构");
}

void wnh_inotify::init()
{
    start_watch_switch = false;
    fd = -1;
    this->set_max_user_watches();
}

bool wnh_inotify::create()//创建监听inotify实例
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
        WNHDEBUG("初始化 inotify 成功, fd:" << fd);
    }
    return true;
}

bool wnh_inotify::add_watch_unit(const string unit)//向inotify中添加一个监控
{
    if(watch_list.find_list_exist(unit))
    {
        WNHWARN("inotify 添加监听失败,监听列表中已经存在该监控项 unit=" << unit);
        return false;
    }
    int wd = inotify_add_watch(fd, unit.c_str(), WNH_INOTIFY_WATCH_EVENT);
    if (wd < 0)
    {
        if(fd == -1)
        {
            WNHERROR("inotify 添加监听失败,未初始化inotify,请先使用wnh_inotify_create()方法进行初始化: " << unit);
        }
        else
        {
            WNHERROR("inotify 添加监听失败: " << unit);
        }
        return false;
    }
    else
    {
        watch_list.add_head(wd, unit);
        WNHDEBUG("inotify 添加监听成功,且成功将数据记录进数据链表: unit=" << unit << ", wd=" << wd << ", 当前监控数量=" << watch_list.num);
        return true;
    }
}

bool wnh_inotify::del_watch_unit(const string unit)//删除inotify监控列表中指定监控单元
{
    wnh_int_string_one_list::Node *node = new wnh_int_string_one_list::Node();
    if(watch_list.find_list_delete(unit, node))
    {
        inotify_rm_watch(fd, node->key);
        WNHDEBUG("inotify 删除监听成功,且成功将数据从数据链表中删除: unit=" << unit << ", wd=" << node->key << ", 当前监控数量=" << watch_list.num);
        return true;
    }
    WNHWARN("inotify 删除监听失败,监控项在数据链表中不存在: unit=" << unit);
    return false;
}

int wnh_inotify::add_watch_dir(const string dir_path)//向inotify中添加一个目录监控,会监控目录下（包括子目录）的所有动作
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

int wnh_inotify::del_watch_dir(const string dir_path)//向inotify中删除一个目录监控,将目录下（包括子目录）的所有监控项删除
{
    int fail_watch_num = 0;//记录删除监控失败的数量
    wnh_system_operation dir_list;
    dir_list.get_dir(dir_path);
    if(!del_watch_unit(dir_path))
    {
        WNHDEBUG("从监控列表中获取数据删除一个监控失败 value=" << dir_path);
        fail_watch_num++;
    }
    else
    {
        WNHDEBUG("从监控列表中获取数据删除一个监控成功 value=" << dir_path);
    }
    wnh_int_string_one_list::Node *node = new wnh_int_string_one_list::Node();
    while(dir_list.dir_file_list.del_head(node))
    {
        if(!del_watch_unit(node->value))
        {
            WNHDEBUG("从监控列表中获取数据删除一个监控失败 value=" << node->value);
            fail_watch_num++;
        }
        else
        {
            WNHDEBUG("从监控列表中获取数据删除一个监控成功 value=" << node->value);
        }
    }
    return fail_watch_num;
}

int wnh_inotify::del_watch_dir_from_watch_list(const string dir_path)//从监控列表中获取数据删除一个目录下的所有监控
{
    int fail_watch_num = 0;//记录删除监控失败的数量
    if(!del_watch_unit(dir_path))
    {
        WNHDEBUG("从监控列表中获取数据删除一个监控失败 value=" << dir_path);
        fail_watch_num++;
    }
    else
    {
        WNHDEBUG("从监控列表中获取数据删除一个监控成功 value=" << dir_path);
    }
    wnh_int_string_one_list::Node *node = new wnh_int_string_one_list::Node();
    watch_list.set_now_to_head();
    string path = dir_path + "/";
    int dir_path_length = path.length();
    while(watch_list.get_now(node))
    {
        if(node->value.substr(0, dir_path_length) == path)
        {
            if(!del_watch_unit(node->value))
            {
                WNHDEBUG("从监控列表中获取数据删除一个监控失败 value=" << node->value);
                fail_watch_num++;
            }
            else
            {
                WNHDEBUG("从监控列表中获取数据删除一个监控成功 value=" << node->value);
            }
        }
    }
    delete node;
    node = nullptr;
    return fail_watch_num;
}

bool wnh_inotify::start_watch(USE_MODE mode)//开始inotify监控
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
        thread start_watch_thread(&wnh_inotify::start_watch_front_show, this);
        start_watch_thread.detach();
        WNHDEBUG("监控子线程启动完成,启动方式:前端显示 mode=front_show");
        break;
    }
    case back_record:
    {
        thread start_watch_thread(&wnh_inotify::start_watch_back_record, this);
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

void wnh_inotify::start_watch_front_show()//inotify监控子线程函数,前端显示使用方式
{
    int len, nread, mask;
    char buf[1024];
    struct inotify_event *event;
    string path;
    buf[sizeof(buf) - 1] = 0;
    wnh_int_string_one_list::Node *node = new wnh_int_string_one_list::Node();
    while ((len = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        nread = 0;
        while (len > 0)
        {
            event = (struct inotify_event *)&buf[nread];
            if (event->len > 0)
            {
                if(!watch_list.find_list_exist(event->wd, node))
                {
                    WNHWARN("查找失败,监控列表中不存在节点 wd=" << event->wd);
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

void wnh_inotify::start_watch_back_record()//inotify监控子线程函数,后台记录使用方式
{
    int len, nread, mask;
    char buf[1024];
    struct inotify_event *event;
    string path;
    buf[sizeof(buf) - 1] = 0;
    wnh_int_string_one_list::Node *node = new wnh_int_string_one_list::Node();
    while ((len = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        nread = 0;
        while (len > 0)
        {
            event = (struct inotify_event *)&buf[nread];
            if (event->len > 0)
            {
                if(!watch_list.find_list_exist(event->wd, node))
                {
                    WNHWARN("查找失败,监控列表中不存在节点 wd=" << event->wd);
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

inline int wnh_inotify::mask_transform(int mask)//事件转换
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

inline void wnh_inotify::show_ignore_event(const string unit, int mask)//显示忽略事件的信息
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

inline void wnh_inotify::front_show_watch_event(const string unit, int mask)//前端显示监视监控事件
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

inline void wnh_inotify::back_record_watch_event(const string unit, int mask)//后台记录监视监控事件
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

inline bool wnh_inotify::auto_update_watch_unit(const string unit, int mask)//自动更新监控的单元
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

bool wnh_inotify::add_ignore_rule(const string unit)//添加一个忽略规则
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

bool wnh_inotify::del_ignore_rule(const string unit)//删除一个忽略规则
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

bool wnh_inotify::check_ignore_rule_exist(const string unit)//判断一个忽略规则是否存在
{
    return ignore_rule_list.find_list_exist(unit);
}

void wnh_inotify::show_ignore_rule_list()//显示忽略规则列表
{
    return ignore_rule_list.show_list();
}

void wnh_inotify::clean_ignore_rule()//清空所有忽略规则
{
    return ignore_rule_list.delete_list();
}

bool wnh_inotify::is_ignore_event(const string event)//判断是否为忽略事件
{
    return ignore_rule_list.is_match_rule(event);
}

void wnh_inotify::set_max_user_watches()//设置max_user_watches
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
