#ifndef __wnh_system_operation__
#define __wnh_system_operation__

using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_int_string_one_list/wnh_int_string_one_list.h"
#include "../wnh_openssl/wnh_openssl.h"

class wnh_system_operation : public wnh_base_class
{
private:
    wnh_openssl md5;

public:
    struct WNH_FILE_STAT{
        int uid;
        int gid;
        string user;
        string group;
        long size;
        int power;
        string power_s;
        string type;
        string atime;
        string mtime;
        string ctime;
        string md5;
    };

    wnh_system_operation();
    ~wnh_system_operation();

    bool file_or_dir_exist(const string & file_path); //判断文件或者目录是否存在
    bool file_is_exist(const string & file_path);//判断文件是否存在
    inline bool get_file_handle(struct stat &st, const string & file_path);//获取一个文件的句柄
    inline bool get_dir_handle(DIR * &dir, const string & dir_path);//获取一个目录的句柄
    inline bool get_open_file_handle(FILE * &stream, const string & file_path, const string & use_method);//获取一个文件的操作句柄

    wnh_int_string_one_list dir_file_list;
    bool get_all(const string & dir_path);//获取目录下的所有文件(文件+目录)
    bool get_file(const string & dir_path);//获取目录下的所有文件(文件)
    bool get_dir(const string & dir_path);//获取目录下的所有文件(目录)

    bool get_all(const string & dir_path, vector<string> & result);//获取目录下的所有文件(文件+目录)
    bool get_file(const string & dir_path, vector<string> & result);//获取目录下的所有文件(文件)
    bool get_dir(const string & dir_path, vector<string> & result);//获取目录下的所有文件(目录)

    bool show_all(const string & dir_path);//显示目录下的所有文件(文件+目录)
    bool show_file(const string & dir_path);//显示目录下的所有文件(文件)
    bool show_dir(const string & dir_path);//显示目录下的所有文件(目录)

    bool get_level_all(const string & dir_path);//获取目录下的所有文件(文件+目录)-单层目录
    bool get_level_file(const string & dir_path);//获取目录下的所有文件(文件)-单层目录
    bool get_level_dir(const string & dir_path);//获取目录下的所有文件(目录)-单层目录

    bool get_level_all(const string & dir_path, vector<string> & result);//获取目录下的所有文件(文件+目录)-单层目录
    bool get_level_file(const string & dir_path, vector<string> & result);//获取目录下的所有文件(文件)-单层目录
    bool get_level_dir(const string & dir_path, vector<string> & result);//获取目录下的所有文件(目录)-单层目录

    bool show_level_all(const string & dir_path);//显示目录下的所有文件(文件+目录)-单层目录
    bool show_level_file(const string & dir_path);//显示目录下的所有文件(文件)-单层目录
    bool show_level_dir(const string & dir_path);//显示目录下的所有文件(目录)-单层目录

    vector<string> get_level_dir_quick(const string & dir_path);//获取目录下的所有文件(目录)-单层目录
    bool show_level_dir_quick(const string & dir_path);//显示目录下的所有文件(目录)-单层目录

    bool is_dir(const string & file_path);//判断是否为目录
    bool is_file(const string & file_path);//判断是否为普通文件
    bool is_chr(const string & file_path);//判断是否为字符设备文件
    bool is_blk(const string & file_path);//判断是否为块设备文件
    bool is_fifo(const string & file_path);//判断是否为FIFO文件(命名管道文件,用于进程通信)
    bool is_lnk(const string & file_path);//判断是否为符号链接文件
    bool is_sock(const string & file_path);//判断是否为套接字文件
    string get_file_type(int st_mode);//获取文件的类型

    bool get_file_power(const string & file_path, string & power);//获取文件的权限
    bool get_file_power_s(const string & file_path, string & power);//获取文件的权限
    bool get_file_power(const string & file_path, int & power);//获取文件的权限
    int get_file_power(int st_mode);//获取文件的权限
    string get_file_power_s(int st_mode);//获取文件的权限

    bool get_file_size(const string & file_path, int & size);//获取文件的大小
    bool get_file_size(const string & file_path, long & size);//获取文件的大小
    bool get_file_size(const string & file_path, long long & size);//获取文件的大小
    bool get_file_size(const string & file_path, unsigned int & size);//获取文件的大小
    bool get_file_size(const string & file_path, unsigned long & size);//获取文件的大小
    bool get_file_size(const string & file_path, unsigned long long & size);//获取文件的大小

    bool get_file_uid(const string & file_path, int & uid);//获取文件的uid
    bool get_file_gid(const string & file_path, int & gid);//获取文件的gid
    bool get_file_uid(const string & file_path, unsigned int & uid);//获取文件的uid
    bool get_file_gid(const string & file_path, unsigned int & gid);//获取文件的gid
    bool get_file_uid(const string & file_path, string & user_name);//获取文件的user
    bool get_file_gid(const string & file_path, string & group_name);//获取文件的group

    unsigned long get_file_last_update_time(const string & file_path); //获取文件最后更新时间戳
    unsigned long get_file_last_access_time(const string & file_path); //获取文件最后访问时间戳
    unsigned long get_file_last_i_update_time(const string & file_path); //获取文件i节点最后更新时间戳
    string get_file_last_update_time_s(const string & file_path); //获取文件最后更新时间
    string get_file_last_access_time_s(const string & file_path); //获取文件最后访问时间
    string get_file_last_i_update_time_s(const string & file_path); //获取文件i节点最后更新时间

    wnh_int_string_one_list uid_user_relation_list;//uid和user的关系列表
    wnh_int_string_one_list gid_group_relation_list;//gid和group的关系列表
    bool show_user_info(const int &uid);//根据uid显示user信息
    bool show_system_all_user_info();//显示系统所有用户信息
    bool show_system_all_group_info();//显示系统所有用户组信息
    bool get_system_all_user_info();//获取系统所有用户信息，并存入uid_user_relation_list
    bool get_system_all_group_info();//获取系统所有用户组信息，并存入gid_group_relation_list
    string get_user(const int & uid);//根据uid获取用户名
    string get_group(const int & gid);//根据gid获取用户组
    int get_uid(const string & user);//根据用户名获取uid
    int get_gid(const string & group);//根据用户组获取gid
    bool show_file_all_info(const string & file_path);//显示文件的所有信息
    bool get_file_all_info(const string & file_path, WNH_FILE_STAT & info);//获取文件的所有信息

    bool rm_dir(const string & dir_full_path); //删除目录中的所有文件
    bool rm(const string & file_name); //删除文件或者目录中的所有文件
    bool rm_level_about_time_before(const string & file_name, const unsigned long & time); //删除一个单层目录下指定时间戳之前的文件
    bool create_dirs(const string & dir_name); //创建目录，支持创建多级目录，相当于命令mkdir -p
    bool chmod_wnh(const string & file_name, const int & power); //修改文件或目录的权限
    bool chmod_wnh(const string & file_name, const string & power); //修改文件或目录的权限
    bool chown_wnh(const string & file_name, const int & user_id, const int & group_id); //修改文件或目录的权限
    bool chown_wnh(const string & file_name, const string & user_name, const string & group_name); //修改文件或目录的权限
};

#endif
