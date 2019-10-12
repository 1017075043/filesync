#include "wnh_system_operation.h"

//  S_ISREG(m) 是否为普通文件
//  S_ISDIR(m) 是否为目录
//  S_ISCHR(m) 是否为字符设备
//  S_ISBLK(m) 是否为块设备
//  S_ISFIFO(m) 是否为FIFO(命名管道文件,用于进程通信)
//  S_ISLNK(m) 是否为符号链接
//  S_ISSOCK(m) 是否为套接字
bool wnh_system_operation::is_dir(const string & file_path)//判断是否为目录
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    if(S_ISDIR(st.st_mode))
    {
        WNHDEBUG(file_path << " 是一个目录");
        return true;
    }
    WNHDEBUG(file_path << " 不是一个目录");
    return false;
}

bool wnh_system_operation::is_file(const string & file_path)//判断是否为普通文件
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return true;
    }
    if(S_ISREG(st.st_mode))
    {
        WNHDEBUG(file_path << " 是一个普通文件");
        return true;
    }
    WNHDEBUG(file_path << " 不是一个普通文件");
    return false;
}

bool wnh_system_operation::is_chr(const string & file_path)//判断是否为字符设备文件
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return true;
    }
    if(S_ISCHR(st.st_mode))
    {
        WNHDEBUG(file_path << " 是一个字符设备文件");
        return true;
    }
    WNHDEBUG(file_path << " 不是一个字符设备文件文件");
    return false;
}

bool wnh_system_operation::is_blk(const string & file_path)//判断是否为块设备文件
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return true;
    }
    if(S_ISBLK(st.st_mode))
    {
        WNHDEBUG(file_path << " 是一个块设备文件");
        return true;
    }
    WNHDEBUG(file_path << " 不是一个块设备文件");
    return false;
}

bool wnh_system_operation::is_fifo(const string & file_path)//判断是否为FIFO文件(命名管道文件,用于进程通信)
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return true;
    }
    if(S_ISFIFO(st.st_mode))
    {
        WNHDEBUG(file_path << " 是一个FIFO文件(命名管道文件,用于进程通信)");
        return true;
    }
    WNHDEBUG(file_path << " 不是一个FIFO文件(命名管道文件,用于进程通信)");
    return false;
}

bool wnh_system_operation::is_lnk(const string & file_path)//判断是否为符号链接文件
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return true;
    }
    if(S_ISLNK(st.st_mode))
    {
        WNHDEBUG(file_path << " 是一个符号链接文件");
        return true;
    }
    WNHDEBUG(file_path << " 不是一个符号链接文件");
    return false;
}

bool wnh_system_operation::is_sock(const string & file_path)//判断是否为套接字文件
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return true;
    }
    if(S_ISSOCK(st.st_mode))
    {
        WNHDEBUG(file_path << " 是一个套接字文件");
        return true;
    }
    WNHDEBUG(file_path << " 不是一个套接字文件");
    return false;
}


bool wnh_system_operation::get_file_power(const string & file_path, string & power)//获取文件的权限
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    power = get_file_power_s((int)st.st_mode);
    WNHDEBUG("获取文件" << file_path << "的权限为:" << power);
    return true;
}

bool wnh_system_operation::get_file_power_s(const string &file_path, string &power)
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    power = to_string(get_file_power((int)st.st_mode));
    WNHDEBUG("获取文件" << file_path << "的权限为:" << power);
    return true;
}

bool wnh_system_operation::get_file_power(const string & file_path, int & power)//获取文件的权限
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    power = get_file_power((int)st.st_mode);
    WNHDEBUG("获取文件" << file_path << "的权限为:" << power);
    return true;
}

string wnh_system_operation::get_file_type(int st_mode)//获取文件的类型
{
    if(S_ISDIR(st_mode))
    {
        return "dir" ;
    }
    if(S_ISREG(st_mode))
    {
        return "file";
    }
    if(S_ISCHR(st_mode))
    {
        return "chr";
    }
    if(S_ISBLK(st_mode))
    {
        return "blk";
    }
    if(S_ISFIFO(st_mode))
    {
        return "fifo";
    }
    if(S_ISLNK(st_mode))
    {
        return "lnk";
    }
    if(S_ISSOCK(st_mode))
    {
        return "sock";
    }
    return "";
}

int wnh_system_operation::get_file_power(int st_mode)//获取文件的权限
{
    int power = 0;
    (st_mode & S_IRUSR) ? power  = 400 : power = 0;
    (st_mode & S_IWUSR) ? power += 200 : power += 0;
    (st_mode & S_IXUSR) ? power += 100 : power += 0;
    (st_mode & S_IRGRP) ? power += 40  : power += 0;
    (st_mode & S_IWGRP) ? power += 20  : power += 0;
    (st_mode & S_IXUSR) ? power += 10  : power += 0;
    (st_mode & S_IROTH) ? power += 4   : power += 0;
    (st_mode & S_IWOTH) ? power += 2   : power += 0;
    (st_mode & S_IXOTH) ? power += 1   : power += 0;
    return power;
}

string wnh_system_operation::get_file_power_s(int st_mode)//获取文件的权限
{
    string power;
    (st_mode & S_IRUSR) ? power  = "r" : power = "-";
    (st_mode & S_IWUSR) ? power += "w" : power += "-";
    (st_mode & S_IXUSR) ? power += "x" : power += "-";
    (st_mode & S_IRGRP) ? power += "r" : power += "-";
    (st_mode & S_IWGRP) ? power += "w" : power += "-";
    (st_mode & S_IXUSR) ? power += "x" : power += "-";
    (st_mode & S_IROTH) ? power += "r" : power += "-";
    (st_mode & S_IWOTH) ? power += "w" : power += "-";
    (st_mode & S_IXOTH) ? power += "x" : power += "-";
    return power;
}

bool wnh_system_operation::get_file_size(const string & file_path, int & size)//获取文件的大小
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    size = (int)st.st_size;
    WNHDEBUG("获取文件" << file_path << "的大小为:" << size);
    return true;
}

bool wnh_system_operation::get_file_size(const string & file_path, long & size)//获取文件的大小
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    size = (long)st.st_size;
    WNHDEBUG("获取文件" << file_path << "的大小为:" << size);
    return true;
}

bool wnh_system_operation::get_file_size(const string & file_path, long long & size)//获取文件的大小
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    size = (long long)st.st_size;
    WNHDEBUG("获取文件" << file_path << "的大小为:" << size);
    return true;
}

bool wnh_system_operation::get_file_size(const string & file_path, unsigned int & size)//获取文件的大小
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    size = (unsigned int)st.st_size;
    WNHDEBUG("获取文件" << file_path << "的大小为:" << size);
    return true;
}

bool wnh_system_operation::get_file_size(const string & file_path, unsigned long & size)//获取文件的大小
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    size = (unsigned long)st.st_size;
    WNHDEBUG("获取文件" << file_path << "的大小为:" << size);
    return true;
}

bool wnh_system_operation::get_file_size(const string & file_path, unsigned long long & size)//获取文件的大小
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    size = (unsigned long long)st.st_size;
    WNHDEBUG("获取文件" << file_path << "的大小为:" << size);
    return true;
}

bool wnh_system_operation::get_file_uid(const string & file_path, int & uid)//获取文件的uid
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    uid = (int)st.st_uid;
    WNHDEBUG("获取文件" << file_path << "的uid为:" << uid);
    return true;
}

bool wnh_system_operation::get_file_gid(const string & file_path, int & gid)//获取文件的gid
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    gid = (int)st.st_gid;
    WNHDEBUG("获取文件" << file_path << "的gid为:" << gid);
    return true;
}

bool wnh_system_operation::get_file_uid(const string & file_path, unsigned int & uid)//获取文件的uid
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    uid = (unsigned int)st.st_uid;
    WNHDEBUG("获取文件" << file_path << "的uid为:" << uid);
    return true;
}

bool wnh_system_operation::get_file_gid(const string & file_path, unsigned int & gid)//获取文件的gid
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    gid = (unsigned int)st.st_gid;
    WNHDEBUG("获取文件" << file_path << "的gid为:" << gid);
    return true;
}

bool wnh_system_operation::get_file_uid(const string & file_path, string & user_name)//获取文件的user
{
    int uid;
    if(get_file_uid(file_path, uid))
    {
        user_name = get_user(uid);
        WNHDEBUG("获取文件" << file_path << "的user_name为:" << user_name);
        return true;
    }
    else
    {
        return false;
    }
}

bool wnh_system_operation::get_file_gid(const string & file_path, string & group_name)//获取文件的group
{
    int gid;
    if(get_file_gid(file_path, gid))
    {
        group_name = get_group(gid);
        WNHDEBUG("获取文件" << file_path << "的group_name为:" << group_name);
        return true;
    }
    else
    {
        return false;
    }
}

//getpw, fgetpwent, getpwent, getpwnam
//函数说明： fgetgrent()会从参数stream 指定的文件读取一行数据, 然后以group 结构将该数据返回. 参数stream 所指定的文件必须和、etc/group 相同的格式. group 结构定义请参考getgrent().
//函数说明： fgetpwent()会从参数stream 指定的文件读取一行数据, 然后以passwd 结构将该数据返回. 参数stream 所指定的文件必须和/etc/passwd 相同的格式. passwd 结构定义请参考getpwent().
//返回值：返回 passwd 结构数据, 如果返回nullptr 则表示已无数据, 或有错误发生.
//  获取linux系统的用户名:通过 struct passwd *getpwuid(uid_t uid)函数;
//  该函数返回passwd结构体,此结构体中包含用户名字段
//  struct passwd {
//      char *pw_name;         /*user name */
//      char *pw_passwd;     /*user password */
//      uid_t pw_uid;        /*user id */
//      gid_t pw_gid;         /*group id */
//      char *pw_gecos;     /*user real name */
//      char *pw_dir;         /*home directory */
//      char *pw_shell;     /*shell program */
//  };
bool wnh_system_operation::show_user_info(const int &uid)//根据uid显示user信息
{
    struct passwd * user;
    user = getpwuid((uid_t)uid);
    if(user == nullptr)
    {
        WNHERROR("获取用户信息错误 " << uid << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG(user->pw_name << ":" << user->pw_uid << ":" << user->pw_gid << ":" << user->pw_gecos << ":" << user->pw_dir << ":" << user->pw_shell);
    return true;
}

bool wnh_system_operation::show_system_all_user_info()//显示系统所有用户信息
{
    struct passwd *user;
    FILE *stream;
    if(!get_open_file_handle(stream, "/etc/passwd", "r"))
    {
        return false;
    }
    while((user = fgetpwent(stream)) != 0)
    {
        WNHDEBUG(user->pw_name << ":" << user->pw_uid << ":" << user->pw_gid << ":" << user->pw_gecos << ":" << user->pw_dir << ":" << user->pw_shell);
    }
    fclose(stream);
    return true;
}

bool wnh_system_operation::show_system_all_group_info()//显示系统所有用户组信息
{
    struct group *data;
    FILE *stream;
    int i;
    if(!get_open_file_handle(stream, "/etc/group", "r"))
    {
        return false;
    }
    while((data = fgetgrent(stream)) != 0)
    {
        i = 0;
        string user;
        while(data->gr_mem[i])
        {
            user += data->gr_mem[i++];
            user += ",";
        }
        WNHDEBUG(data->gr_name << ":" << data->gr_passwd << ":" << data->gr_gid << ":" << user);
    }
    fclose(stream);
    return true;
}

bool wnh_system_operation::get_system_all_user_info()//获取系统所有用户信息，并存入uid_user_relation_list
{
    struct passwd *user;
    FILE *stream;
    if(!get_open_file_handle(stream, "/etc/passwd", "r"))
    {
        return false;
    }
    while((user = fgetpwent(stream)) != 0)
    {
        uid_user_relation_list.add_end((int)user->pw_uid, user->pw_name);
    }
    fclose(stream);
    return true;
}

bool wnh_system_operation::get_system_all_group_info()//获取系统所有用户组信息，并存入gid_group_relation_list
{
    struct group *data;
    FILE *stream;
    if(!get_open_file_handle(stream, "/etc/group", "r"))
    {
        return false;
    }
    while((data = fgetgrent(stream)) != 0)
    {
        gid_group_relation_list.add_end((int)data->gr_gid, data->gr_name);
    }
    fclose(stream);
    return true;
}

string wnh_system_operation::get_user(const int &uid)//根据uid获取用户名
{
    static string user_temp_s = "";
    static int user_temp_i = -1;
    if(uid == user_temp_i)
    {
        WNHDEBUG("根据uid:" << uid << ",从寄存器中获取到用户名user:" << user_temp_s);
        return user_temp_s;
    }
    if(uid_user_relation_list.num == 0)
    {
        WNHDEBUG("初始化用户信息，获取系统所有用户信息，并存入uid_user_relation_list");
        if(!get_system_all_user_info())
        {
            return "";
        }
    }
    string user;
    if(uid_user_relation_list.find_list(uid, user))
    {
        WNHDEBUG("根据uid:" << uid << ",获取到用户名user:" << user);
        user_temp_s = user;
        user_temp_i = uid;
        return user;
    }
    WNHDEBUG("根据uid:" << uid << ",获取不到用户名");
    return "";
}

string wnh_system_operation::get_group(const int & gid)//根据gid获取用户组
{
    static string group_temp_s = "";
    static int group_temp_i = -1;
    if(gid == group_temp_i)
    {
        WNHDEBUG("根据gid:" << gid << ",从寄存器中获取到用户组group:" << group_temp_s);
        return group_temp_s;
    }
    if(gid_group_relation_list.num == 0)
    {
        WNHDEBUG("初始化用户组信息，获取系统所有用户组信息，并存入gid_group_relation_list");
        if(!get_system_all_group_info())
        {
            return "";
        }
    }
    string group;
    if(gid_group_relation_list.find_list(gid, group))
    {
        WNHDEBUG("根据gid:" << gid << ",获取到用户组group:" << group);
        group_temp_s = group;
        group_temp_i = gid;
        return group;
    }
    WNHDEBUG("根据gid:" << gid << ",获取不到用户组");
    return "";
}

int wnh_system_operation::get_uid(const string & user)//根据用户名获取uid
{
    static string user_temp_s = "";
    static int user_temp_i = -1;
    if(user == user_temp_s)
    {
        WNHDEBUG("根据用户名user:" << user << ",从寄存器中获取到uid:" << user_temp_i);
        return user_temp_i;
    }
    if(uid_user_relation_list.num == 0)
    {
        WNHDEBUG("初始化用户信息，获取系统所有用户信息，并存入uid_user_relation_list");
        if(!get_system_all_user_info())
        {
            return -1;
        }
    }
    int uid;
    if(uid_user_relation_list.find_list(user, uid))
    {
        WNHDEBUG("根据用户名user:" << user << ",获取到uid:" << uid);
        user_temp_s = user;
        user_temp_i = uid;
        return uid;
    }
    WNHDEBUG("根据用户名user:" << user << ",获取不到uid");
    return -1;
}

int wnh_system_operation::get_gid(const string & group)//根据用户组获取gid
{
    static string group_temp_s = "";
    static int group_temp_i = -1;
    if(group == group_temp_s)
    {
        WNHDEBUG("根据用户名组group:" << group << ",从寄存器中获取到gid:" << group_temp_i);
        return group_temp_i;
    }
    if(gid_group_relation_list.num == 0)
    {
        WNHDEBUG("初始化用户组信息，获取系统所有用户组信息，并存入gid_group_relation_list");
        if(!get_system_all_group_info())
        {
            return -1;
        }
    }
    int gid;
    if(gid_group_relation_list.find_list(group, gid))
    {
        WNHDEBUG("根据用户名组group:" << group << ",获取到gid:" << gid);
        group_temp_s = group;
        group_temp_i = gid;
        return gid;
    }
    WNHDEBUG("根据用户名组group:" << group << ",获取不到gid");
    return -1;
}

unsigned long wnh_system_operation::get_file_last_update_time(const string & file_path) //获取文件最后更新时间戳
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return 0;
    }
    else
    {
        return st.st_mtime;
    }
}

unsigned long wnh_system_operation::get_file_last_access_time(const string & file_path) //获取文件最后访问时间戳
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return 0;
    }
    else
    {
        return st.st_atime;
    }
}

unsigned long wnh_system_operation::get_file_last_i_update_time(const string & file_path) //获取文件i节点最后更新时间戳
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return 0;
    }
    else
    {
        return st.st_ctime;
    }
}

string wnh_system_operation::get_file_last_update_time_s(const string & file_path) //获取文件最后更新时间
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return "0000/00/00 00:00:00";
    }
    else
    {
        string time;
        char time_temp[20];
        memset(time_temp, '\0', sizeof(time_temp));
        strftime(time_temp, 20, "%Y/%m/%d %H:%M:%S", localtime(&st.st_mtime));
        time = time_temp;
        return time;
    }
}

string wnh_system_operation::get_file_last_access_time_s(const string & file_path) //获取文件最后访问时间
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return "0000/00/00 00:00:00";
    }
    else
    {
        string time;
        char time_temp[20];
        memset(time_temp, '\0', sizeof(time_temp));
        strftime(time_temp, 20, "%Y/%m/%d %H:%M:%S", localtime(&st.st_atime));
        time = time_temp;
        return time;
    }
}

string wnh_system_operation::get_file_last_i_update_time_s(const string & file_path) //获取文件i节点最后更新时间
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return "0000/00/00 00:00:00";
    }
    else
    {
        string time;
        char time_temp[20];
        memset(time_temp, '\0', sizeof(time_temp));
        strftime(time_temp, 20, "%Y/%m/%d %H:%M:%S", localtime(&st.st_ctime));
        time = time_temp;
        return time;
    }
}

bool wnh_system_operation::get_file_all_info(const string & file_path, WNH_FILE_STAT & info)//获取文件的所有信息
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    info.uid = (int)st.st_uid;
    info.gid = (int)st.st_gid;
    info.user = get_user(info.uid);
    info.group = get_group(info.gid);
    info.size = st.st_size;
    info.power = get_file_power((int)st.st_mode);
    info.power_s = get_file_power_s((int)st.st_mode);
    info.type = get_file_type((int)st.st_mode);
    char time_temp[20];
    memset(time_temp, '\0', sizeof(time_temp));
    strftime(time_temp, 20, "%Y/%m/%d %H:%M:%S", localtime(&st.st_atime));
    info.atime = time_temp;
    memset(time_temp, '\0', sizeof(time_temp));
    strftime(time_temp, 20, "%Y/%m/%d %H:%M:%S", localtime(&st.st_mtime));
    info.mtime = time_temp;
    memset(time_temp, '\0', sizeof(time_temp));
    strftime(time_temp, 20, "%Y/%m/%d %H:%M:%S", localtime(&st.st_ctime));
    info.ctime = time_temp;
    string file_md5;
    md5.get_file_md5(file_path, file_md5);
    WNHDEBUG("获取文件" << file_path << "的信息为, uid:" << info.uid << ", gid:" << info.gid << ", user:" << info.user << ", group:" << info.group << ", size:" << info.size << ", power:" << info.power << ", power_s:" << info.power_s << ", type:" << info.type << ", atime:" << info.atime << ", mtime:" << info.mtime << ", ctime:" << info.ctime << ", md5:" << info.md5);
    return true;
}

bool wnh_system_operation::show_file_all_info(const string & file_path)//显示文件的所有信息
{
    struct stat st;
    if(!get_file_handle(st, file_path))
    {
        return false;
    }
    string file_md5;
    md5.get_file_md5(file_path, file_md5);
    WNHDEBUG("获取文件" << file_path << "的信息为, uid:" << (int)st.st_uid << ", gid:" << (int)st.st_gid << ", user:" << get_user((int)st.st_uid) << ", group:" << get_group((int)st.st_uid) << ", size:" << st.st_size << ", power:" << get_file_power((int)st.st_mode) << ", power_s:" << get_file_power_s((int)st.st_mode) << ", type:" << get_file_type((int)st.st_mode) << ", md5:" << file_md5);
    return true;
}
