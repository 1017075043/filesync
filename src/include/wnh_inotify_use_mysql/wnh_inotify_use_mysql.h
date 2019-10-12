#ifndef __wnh_inotify_use_mysql__
#define __wnh_inotify_use_mysql__

using namespace std;

#include <sys/inotify.h>

#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_int_string_one_list/wnh_int_string_one_list.h"
#include "../wnh_string_rule_one_list/wnh_string_rule_one_list.h"
#include "../wnh_system_operation/wnh_system_operation.h"
#include "../wnh_mysql/wnh_mysql.h"

//inotify监听的事件,代号
#define WNH_INOTIFY_IN_ATTRIB 1
#define WNH_INOTIFY_IN_CREATE 2
#define WNH_INOTIFY_IN_DELETE 3
#define WNH_INOTIFY_IN_MODIFY 4
#define WNH_INOTIFY_IN_MOVED_FROM 5
#define WNH_INOTIFY_IN_MOVED_TO 6

//inotify监听的事件
#define WNH_INOTIFY_WATCH_EVENT IN_ATTRIB|IN_CREATE|IN_DELETE|IN_MODIFY|IN_MOVED_FROM|IN_MOVED_TO

class wnh_inotify_use_mysql : public wnh_base_class
{
    //private:
public:
    int fd;//inotify_init返回的文件描述符
    //wnh_int_string_one_list watch_list;//用于记录监听列表
    wnh_mysql watch_list;//用于记录监听数据库句柄
    string table_name;//用来记录数据的表
    wnh_string_rule_one_list ignore_rule_list;//用户记录监听事件忽略规则
    wnh_int_string_one_list event_list;//用于记录发生事件的列表
    bool start_watch_switch;//确保void start_watch(USE_MODE mode);不会被重复调用
    wnh_system_operation wnh_sys_op;

public:
    enum USE_MODE{front_show=1, back_record=2};
    wnh_inotify_use_mysql();
    ~wnh_inotify_use_mysql();

    void init();
    void init(const string & ip, const string & user, const string & passwd, const string & db);
    bool create();//创建监听inotify实例
    bool add_watch_unit(const string unit);//向inotify中添加一个监控单元
    bool del_watch_unit(const int key);//删除inotify监控列表中指定监控单元
    bool del_watch_unit(const string unit);//删除inotify监控列表中指定监控单元
    int add_watch_dir(const string dir_path);//向inotify中添加一个目录监控,会监控目录下（包括值目录）的所有动作
    int del_watch_dir_from_watch_list(const string dir_path);//从监控列表中获取数据删除一个目录下的所有监控
    int del_watch_dir(const string dir_path);//向inotify中删除一个目录监控,将目录下（包括子目录）的所有监控项删除
    bool start_watch(USE_MODE mode);//开始inotify监控
    void start_watch_front_show();//inotify监控子线程函数,前端显示使用方式
    void start_watch_back_record();//inotify监控子线程函数,后台记录使用方式
    inline int mask_transform(int mask);//事件转换
    inline bool auto_update_watch_unit(const string unit, int mask);//自动更新监控的单元
    inline void front_show_watch_event(const string unit, int mask);//前端实现监视监控事件
    inline void back_record_watch_event(const string unit, int mask);//后台记录监视监控事件
    inline void show_ignore_event(const string unit, int mask);//显示忽略事件的信息

    bool add_ignore_rule(const string unit);//添加一个忽略规则
    bool del_ignore_rule(const string unit);//删除一个忽略规则
    bool check_ignore_rule_exist(const string unit);//判断一个忽略规则是否存在
    void show_ignore_rule_list();//显示忽略规则列表
    void clean_ignore_rule();//清空所有忽略规则
    bool is_ignore_event(const string event);//判断是否为忽略事件

    void set_max_user_watches();//设置max_user_watches

    MYSQL_ROW row;
    string wnh_mysql_sql;
    int rows;
    int register_key;
    string register_value;
    bool connont_mysql(string host,string user,string pwd,string db_name);//与数据进行链接
    bool create_table();//创建一张数据表
    bool add_one_record(int key, string value);//添加一行数据
    bool check_unit_exist(int key);//查找指定一行记录是否存在
    bool check_unit_exist(string value);//查找指定一行记录是否存在
    bool check_unit_exist(int key, string value);//查找指定一行记录是否存在
    bool delete_record(int key);//删除记录
    bool delete_record(string value);//删除记录
    bool delete_record(int key, string value);//删除记录
    bool delete_record(string value, int &rows);//删除记录
    int get_record(string value);//使用value获取key
    string get_record(int key);//使用key获取value
    MYSQL_RES * get_record(string value, int &list, int &rows);//使用value模糊查询获取key
};
#endif
