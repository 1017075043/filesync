#ifndef __wnh_inotify_use_sqlite__
#define __wnh_inotify_use_sqlite__

using namespace std;

#include <sys/inotify.h>
#include <list>
#include <algorithm>

#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_int_string_one_list/wnh_int_string_one_list.h"
#include "../wnh_unsigned_long_string_one_list/wnh_unsigned_long_string_one_list.h"
#include "../wnh_string_rule_one_list/wnh_string_rule_one_list.h"
#include "../wnh_system_operation/wnh_system_operation.h"
#include "../wnh_sqlite/wnh_sqlite.h"
#include "../wnh_openssl/wnh_openssl.h"
#include "../wnh_license/wnh_license.h"


//inotify监听的事件,代号
#define WNH_INOTIFY_IN_ATTRIB 1
#define WNH_INOTIFY_IN_CREATE 2
#define WNH_INOTIFY_IN_MOVED_TO 3
#define WNH_INOTIFY_IN_MODIFY 4
#define WNH_INOTIFY_IN_MOVED_FROM 5
#define WNH_INOTIFY_IN_DELETE 6

//inotify监听的事件
#define WNH_INOTIFY_WATCH_EVENT IN_ATTRIB|IN_CREATE|IN_DELETE|IN_MODIFY|IN_MOVED_FROM|IN_MOVED_TO
#define DB_NAME "filesync.db"
#define WATCH_LIST_TABLE_NAME "watch_list_table"
#define EVENT_LIST_TABLE_NAME "event_list_table"
#define TASK_LIST_TABLE_NAME "task_list_table"
#define TAIL_TASK_LIST_TABLE_NAME "fail_task_list_table"
#define COMPLETE_TASK_LIST_TABLE_NAME "complete_task_list_table"

#define TASK_ATTR_DEFAULT_FILE_USER "root"
#define TASK_ATTR_DEFAULT_FILE_GROUP "root"
#define TASK_ATTR_DEFAULT_FILE_POWER "755"

class wnh_inotify_use_sqlite : public wnh_base_class
{
public:
    struct TASK_ATTR{
        string task_name; //任务名
        string event_id; //事件ID
        string src_path; //源文件路径
        string dst_path; //目标文件路径
        string file_type; //文件类型
        string file_user; //所属用户
        string file_group; //所属用户组
        string file_power; //权限
        string file_hash; //hash值
    };

public:
    int fd;//inotify_init返回的文件描述符
    //wnh_int_string_one_list watch_list;//用于记录监听列表
    wnh_sqlite sqlite_op;//用于记录监听数据库句柄
    wnh_string_rule_one_list ignore_rule_list;//用于记录监听事件忽略规则
    vector<string> ignore_watch_dir_list;//用于记录忽略目录监听列表
    wnh_int_string_one_list event_list;//用于记录发生事件的列表
    bool start_watch_switch;//确保void start_watch(USE_MODE mode);不会被重复调用
    //wnh_system_operation wnh_sys_op;
    bool repeated_event_neglect; //重复事件忽略

public:
    enum USE_MODE{front_show=1, back_record=2};
    wnh_inotify_use_sqlite();
    ~wnh_inotify_use_sqlite();

    void init();
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
    string event_transform(const int & event_id);//事件转换
    string event_transform(const string & event_id);//事件转换
    inline bool auto_update_watch_unit(const string unit, int mask);//自动更新监控的单元
    inline void front_show_watch_event(const string unit, int mask);//前端实现监视监控事件
    inline void back_record_watch_event(const string unit, int mask);//后台记录监视监控事件
    inline void back_record_watch_event_sqlite_agent(const string unit, int mask);//后台记录监视监控事件-再次添加事件
    inline void back_record_watch_event_sqlite(const string unit, int mask);//后台记录监视监控事件
    inline void show_ignore_event(const string unit, int mask);//显示忽略事件的信息
    void start_event_list_show(); //事件表数据显示
    void start_event_list(); //事件表数据显示进程创建

    wnh_unsigned_long_string_one_list agent_event_list;
    void again_add_event(const int & mask, const string & dir_path); //再次添加事件
    void again_created_event(); //再次创建事件

    bool add_ignore_rule(const string unit);//添加一个忽略规则
    bool del_ignore_rule(const string unit);//删除一个忽略规则
    bool check_ignore_rule_exist(const string unit);//判断一个忽略规则是否存在
    void show_ignore_rule_list();//显示忽略规则列表
    void clean_ignore_rule();//清空所有忽略规则
    bool is_ignore_event(const string event);//判断是否为忽略事件

    void set_max_user_watches();//设置max_user_watches

    void add_ignore_watch_dir(const string & ignore_dir); //添加忽略目录监听
    bool find_ignore_watch_dir(const string & ignore_dir); //查找忽略目录监听
    bool matching_ignore_watch_dir(const string & unit); //匹配忽略目录监听
    void start_ignore_watch_dir_action(); //执行忽略目录监听

    int register_wd;
    string register_watch_dir_path;
    bool watch_list_create_db(); //创建一个数据进行数据存储-监控目录
    bool watch_list_create_table(); //创建一张数据表-监控目录
    bool watch_list_drop_table(); //删除数据表-监控目录
    bool watch_list_add_one_record(const int wd, const string watch_dir_path);//添加一行数据-监控目录
    bool watch_list_check_unit_exist(const int wd);//查找指定一行记录是否存在-监控目录
    bool watch_list_check_unit_exist(const string watch_dir_path);//查找指定一行记录是否存在-监控目录
    bool watch_list_check_unit_exist(const int wd, const string watch_dir_path);//查找指定一行记录是否存在-监控目录
    bool watch_list_delete_record(const int wd);//删除记录-监控目录
    bool watch_list_delete_record(const string watch_dir_path);//删除记录-监控目录
    bool watch_list_delete_record(const int wd, const string watch_dir_path);//删除记录-监控目录
    bool watch_list_delete_record_like(const string watch_dir_path);//删除记录-监控目录
    int watch_list_get_record(const string watch_dir_path);//使用value获取key-监控目录
    string watch_list_get_record(const int wd);//使用key获取value-监控目录
    bool watch_list_get_record(const string watch_dir_path, string **& result, int &list, int &rows);//使用value模糊查询获取key-监控目录

    bool event_list_create_table(); //创建一张数据表-事件列表
    bool event_list_drop_table(); //删除数据表-事件列表
    bool event_list_add_one_record(const int & event_id, const string & event_path); //添加一行数据-事件列表
    bool event_list_add_one_record(const string & event_id, const string & event_path); //添加一行数据-事件列表
    bool event_list_show(); //查询事件表里面的所有数据
    bool task_list_create_table(); //创建一张数据表-任务列表
    bool event_into_task(const string & src_dir, const string & dst_dir, const vector<string> & client_ip); //将事件转为任务,多IP
    bool event_into_task(const string & src_dir, const vector<string> & dst_dir, const vector<string> & client_ip); //将事件转为任务,多IP，多目标目录
    bool query_task_num(const string & client_ip, unsigned long & task_num); //根据客户端IP查询任务数量
    bool create_task_list_file(const string & client_ip, const string & task_list_path, const int & max_task_num); //根据客户端IP生成任务列表文件
    bool delete_one_task(const string & client_ip, const string & event_id, const string & src_path); //根据客户端IP、事件ID、源路径删除一个任务
    bool delete_one_task(const string & client_ip, const string & event_id, const string & src_path, const string & dst_path); //根据客户端IP、事件ID、源路径、目标路径删除一个任务

    bool fail_task_list_create_table(); //创建一张数据表-失败任务列表
    bool add_fail_task_info(const string & client_ip, const string & event_id, const string & src_path); //添加一行失败任务信息
    bool add_fail_task_info(const string & client_ip, const string & event_id, const string & src_path, const string & dst_path); //添加一行失败任务信息

    bool complete_task_list_create_table(); //创建一张数据表-成功任务列表
    bool add_complete_task_info(const string & client_ip, const string & event_id, const string & src_path); //添加一行失败任务信息
    bool add_complete_task_info(const string & client_ip, const string & event_id, const string & src_path, const string & dst_path); //添加一行失败任务信息

    unsigned long get_event_list_num(); //获取失败任务数量
    unsigned long get_task_list_num(); //获取失败任务数量
    unsigned long get_fail_task_list_num(); //获取失败任务数量
    unsigned long get_fail_task_list_num(const string & client_ip); //根据客户端IP,获取失败任务数量
    unsigned long get_task_list_num(const string & client_ip); //根据客户端IP,获取任务数量
    vector<vector<string> > get_real_time_complete_task_list(const int & real_time, const int & num); //获取同步完成实时数据

    vector<vector<string> > get_fail_task_list(const string & line, const string & num); //获取同步失败任务数据

};
#endif
