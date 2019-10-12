#ifndef __wnh_inotify_ex__
#define __wnh_inotify_ex__

using namespace std;

#include <sys/inotify.h>

#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_int_double_string_one_list/wnh_int_double_string_one_list.h"
#include "../wnh_string_rule_one_list/wnh_string_rule_one_list.h"
#include "../wnh_system_operation/wnh_system_operation.h"

//inotify监听的事件,代号
#define WNH_INOTIFY_IN_ATTRIB 1
#define WNH_INOTIFY_IN_CREATE 2
#define WNH_INOTIFY_IN_DELETE 3
#define WNH_INOTIFY_IN_MODIFY 4
#define WNH_INOTIFY_IN_MOVED_FROM 5
#define WNH_INOTIFY_IN_MOVED_TO 6

//inotify监听的事件
#define WNH_INOTIFY_WATCH_EVENT IN_ATTRIB|IN_CREATE|IN_DELETE|IN_MODIFY|IN_MOVED_FROM|IN_MOVED_TO

//单个线程inotify监听最大数量
#define WATCH_MAX 524288

class wnh_inotify_ex : public wnh_base_class
{
private:
    wnh_int_double_string_one_list wathc_num;//用于线程监听的数量
    wnh_int_double_string_one_list watch_list;//用于记录监听列表
    wnh_string_rule_one_list ignore_rule_list;//用户记录监听事件忽略规则
    wnh_int_double_string_one_list event_list;//用于记录发生事件的列表
    wnh_system_operation wnh_sys_op;

public:
    enum USE_MODE{front_show=1, back_record=2};
    USE_MODE mode;
    wnh_inotify_ex();
    ~wnh_inotify_ex();
    void init();
    void init(USE_MODE mode);
    void set_mode(USE_MODE mode);//修改启动模式
    int create_inotify();//创建监听inotify实例
    int distribution_inotify();//为监听分配inotify实例
    bool add_watch_unit(const string unit);//向inotify中添加一个监控
    bool del_watch_unit(const string unit);//删除inotify监控列表中指定监控单元
    int add_watch_dir(const string dir_path);//向inotify中添加一个目录监控,会监控目录下（包括值目录）的所有动作,返回添加监控失败的数量
    int del_watch_dir(const string dir_path);//向inotify中删除一个目录监控,将目录下（包括子目录）的所有监控项删除,返回删除监控失败的数量
    int del_watch_dir_from_watch_list(const string dir_path);//从监控列表中获取数据删除一个目录下的所有监控,返回删除监控失败的数量

    inline int mask_transform(int mask);//事件转换
    inline void show_ignore_event(const string unit, int mask);//显示忽略事件的信息

    inline bool auto_update_watch_unit(const string unit, int mask);//自动更新监控的单元

    inline void front_show_watch_event(const string unit, int mask);//前端显示监视监控事件
    void start_watch_front_show(int fd);//inotify监控子线程函数,前端显示使用方式

    inline void back_record_watch_event(const string unit, int mask);//后台记录监视监控事件
    void start_watch_back_record(int fd);//inotify监控子线程函数,后台记录使用方式

    bool add_ignore_rule(const string unit);//添加一个忽略规则
    bool del_ignore_rule(const string unit);//删除一个忽略规则
    bool check_ignore_rule_exist(const string unit);//判断一个忽略规则是否存在
    void show_ignore_rule_list();//显示忽略规则列表
    void clean_ignore_rule();//清空所有忽略规则
    bool is_ignore_event(const string event);//判断是否为忽略事件

    void set_max_user_watches();//设置max_user_watches
};
#endif
