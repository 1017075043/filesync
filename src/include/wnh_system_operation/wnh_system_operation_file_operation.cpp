#include "wnh_system_operation.h"


//unlink函数删除文件系统中的一个名字，如果这个名字是该文件的最后一个link并且该文件没有被任何进程打开，那么删除该文件。否则等到文件被关闭或最后一个link被删除后删除该文件并释放空间。
//由于rmdir只能删除空目录文件，所以在删除目录文件之前需要首先删除目录中的所有文件。
//实现rm_dir(const string& path)函数删除目录中的所有文件，在rm_dir()中遍历每一个文件，如果遇到目录文件，则递归删除该目录文件。
//https://www.cnblogs.com/StartoverX/p/4600866.html
bool wnh_system_operation::rm_dir(const string & dir_full_path)
{
    DIR* dirp = opendir(dir_full_path.c_str());
    if(!dirp)
    {
        return false;
    }
    struct dirent *dir;
    struct stat st;
    while((dir = readdir(dirp)) != nullptr)
    {
        if(strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0)
        {
            continue;
        }
        string sub_path = dir_full_path + '/' + dir->d_name;
        if(lstat(sub_path.c_str(),&st) == -1)
        {
            WNHERROR("获取文件属性失败, lstat, " << sub_path << ", errno=" << errno << ", mesg=" << strerror(errno));
            //Log("rm_dir:lstat ",sub_path," error");
            continue;
        }
        if(S_ISDIR(st.st_mode))
        {
            if(rm_dir(sub_path) == -1) // 如果是目录文件，递归删除
            {
                closedir(dirp);
                return false;
            }
            rmdir(sub_path.c_str());
        }
        else if(S_ISREG(st.st_mode))
        {
            WNHDEBUG("成功删除一个文件, sub_path:" << sub_path);
            unlink(sub_path.c_str());     // 如果是普通文件，则unlink
        }
        else
        {
            WNHERROR("删除文件失败, " << sub_path << ", errno=" << errno << ", mesg=" << strerror(errno));
            continue;
        }
    }
    if(rmdir(dir_full_path.c_str()) == -1)//删除dir本身
    {
        closedir(dirp);
        return false;
    }
    WNHDEBUG("成功删除一个目录, dir_full_path:" << dir_full_path);
    closedir(dirp);
    return true;
}

//实现rm()函数，判断文件类型，如果是目录文件则rm_dir，普通文件则unlink.
bool wnh_system_operation::rm(const string & file_name)
{
    string file_path = file_name;
    struct stat st;
    if(lstat(file_path.c_str(),&st) == -1)
    {
        WNHERROR("删除文件失败, " << file_path << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    if(S_ISREG(st.st_mode))
    {
        if(unlink(file_path.c_str()) == -1)
        {
            WNHERROR("删除文件失败, " << file_path << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        else
        {
            WNHINFO("成功删除一个文件, file_path:" << file_path);
        }
    }
    else if(S_ISDIR(st.st_mode))
    {
        if(file_name == "." || file_name == "..")
        {
            WNHERROR("删除文件失败, 不能删除隐藏目录, " << file_path << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(rm_dir(file_path) == -1)
        {
            return false;
        }
        else
        {
            WNHINFO("成功删除一个目录, file_path:" << file_path);
        }
    }
    return true;
}

bool wnh_system_operation::create_dirs(const string & dir_name) //创建目录，支持创建多级目录，相当于命令mkdir -p
{
    uint32_t begin_cmp_path = 0;
    uint32_t end_cmp_path = 0;

    string full_path = "";

    WNHDEBUG("创建目录, full_path:" << full_path);
    if('/' != dir_name[0]) //如果使用的是相对路径，则获得当前路径
    {
        full_path = getcwd(nullptr, 0);
        begin_cmp_path = full_path.size();
        WNHDEBUG("使用的是相对路径, 获得当前路径, full_path:" << full_path);
        full_path = full_path + "/" + dir_name;
    }
    else
    {
        //使用的是绝对路径
        full_path = dir_name;
        begin_cmp_path = 1;
    }
    //使用'/'结尾
    if (full_path[full_path.size() - 1] != '/')
    {
        full_path += "/";
    }
    end_cmp_path = full_path.size();
    //创建目录
    for(uint32_t i = begin_cmp_path; i < end_cmp_path ; i++ )
    {
        if('/' == full_path[i])
        {
            string cur_path = full_path.substr(0, i);
            if(access(cur_path.c_str(), F_OK) != 0)
            {
                if(mkdir(cur_path.c_str(), S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH) == -1)
                {
                    WNHERROR("创建目录失败 " << cur_path << ", errno=" << errno << ", mesg=" << strerror(errno));
                    return false;
                }
            }
        }
    }
    return true;
}

bool wnh_system_operation::chmod_wnh(const string & file_name, const int & power) //修改文件或目录的权限
{
    //chmod("/etc/passwd",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    //更改文件权限函数
    //int chmod(const char * path,mode_t mode);
    //依参数mode权限来更改参数path指定文件的权限
    //更改成功返回0，失败返回-1，错误原因存于errno
    //mode参数表
    //S_IRUSR 拥有者读
    //S_IWUSR 拥有者写
    //S_IXUSR 拥有者执行
    //S_IRGRP 组读
    //S_IWGRP 组写
    //S_IXGRP 组执行
    //S_IROTH 其他用户读
    //S_IWOTH 其他用户写
    //S_IXOTH 其他用户执行

    int mode = power;     //权限
    if(mode > 777 || mode < 0)
    {
        WNHERROR("修改" << file_name << "的权限失败, 参数错误:" << mode << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    mode = ((mode / 100) * 8 * 8) + ((mode / 10 % 10) * 8) + (mode % 10);   //八进制转换

    //int chmod(const char * path, mode_t mode)
    //函数说明：chmod()会依参数mode权限来更改参数path指定文件的权限。
    //更改失败返回-1
    if(chmod(file_name.c_str(), mode) == -1)
    {
        WNHERROR("修改" << file_name << "的权限失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHINFO("修改" << file_name << "的权限成功");
    return true;
}

bool wnh_system_operation::chmod_wnh(const string & file_name, const string & power) //修改文件或目录的权限
{
    return chmod_wnh(file_name, atoi(power.c_str()));
}

bool wnh_system_operation::chown_wnh(const string & file_name, const int & user_id, const int & group_id) //修改文件或目录的权限
{
    if(chown(file_name.c_str(), (uid_t)user_id, (uid_t)group_id) == -1)
    {
        WNHERROR("修改" << file_name << "的所属的用户和用户组失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHINFO("修改" << file_name << "的所属的用户和用户组成功");
    return true;
}

bool wnh_system_operation::chown_wnh(const string & file_name, const string & user_name, const string & group_name) //修改文件或目录的权限
{
    int user_id = get_uid(user_name);
    int group_id = get_gid(group_name);
    if(user_id == -1 && group_id == -1)
    {
        WNHERROR("修改" << file_name << "的所属的用户和用户组失败, 不存在的用户和用户组:" << user_name << ":" << group_name);
        return false;
    }
    else if(user_id == -1)
    {
        WNHERROR("修改" << file_name << "的所属的用户和用户组失败, 不存在的用户:" << user_name);
        return false;
    }
    else if(group_id == -1)
    {
        WNHERROR("修改" << file_name << "的所属的用户和用户组失败, 不存在的用户组:" << group_name);
        return false;
    }
    else
    {
        return chown_wnh(file_name, user_id, group_id);
    }
}

bool wnh_system_operation::rm_level_about_time_before(const string & file_name, const unsigned long & time) //删除一个单层目录下指定时间戳之前的文件
{
    vector<string> result;
    if(get_level_all(file_name, result) == false)
    {
        return false;
    }
    for(unsigned int i = 0; i < result.size(); i++)
    {
        if(get_file_last_update_time(result[i]) <= time)
        {
            rm(result[i]);
        }
    }
    return true;
}
