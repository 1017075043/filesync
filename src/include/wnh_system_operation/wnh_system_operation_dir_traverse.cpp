#include "wnh_system_operation.h"

//  struct dirent
//  {
//      long d_ino;                 /* inode number 索引节点号 */
//      off_t d_off;                /* offset to this dirent 在目录文件中的偏移 */
//      unsigned short d_reclen;    /* length of this d_name 文件名长 */
//      unsigned char d_type;        /* the type of d_name 文件类型 */
//      char d_name [NAME_MAX+1];   /* file name (null-terminated) 文件名,最长255字符 */
//  }
//  struct dirent中的几个成员：
//  d_type：4表示为目录,8表示为文件
//  d_reclen：16表示子目录或文件,24表示非子目录
//  经试验发现：d_reclen：16表示子目录或以.开头的隐藏文件,24表示普通文本文件,28为二进制文件,等等
//  d_name：目录或文件的名称
bool wnh_system_operation::get_all(const string & dir_path)//获取目录下的所有文件(文件+目录)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            if(dir_file_list.add_end_only(temp))
            {
                WNHDEBUG("获取目录名 path=" << temp << ", 已经添加进入dir_file_list列表");
            }
            else
            {
                WNHDEBUG("获取目录名 path=" << temp << ", 添加失败,已经存在于dir_file_list列表");
            }
            get_all(temp);
        }
        else
        {
            if(dir_file_list.add_end_only(temp))
            {
                WNHDEBUG("获取文件名 path=" << temp << ", 已经添加进入dir_file_list列表");
            }
            else
            {
                WNHDEBUG("获取文件名 path=" << temp << ", 添加失败,已经存在于dir_file_list列表");
            }
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_level_all(const string & dir_path)//获取目录下的所有文件(文件+目录)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            if(dir_file_list.add_end_only(temp))
            {
                WNHDEBUG("获取目录名 path=" << temp << ", 已经添加进入dir_file_list列表");
            }
            else
            {
                WNHDEBUG("获取目录名 path=" << temp << ", 添加失败,已经存在于dir_file_list列表");
            }
        }
        else
        {
            if(dir_file_list.add_end_only(temp))
            {
                WNHDEBUG("获取文件名 path=" << temp << ", 已经添加进入dir_file_list列表");
            }
            else
            {
                WNHDEBUG("获取文件名 path=" << temp << ", 添加失败,已经存在于dir_file_list列表");
            }
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_file(const string & dir_path)//获取目录下的所有文件(文件)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            get_file(temp);
        }
        else
        {
            if(dir_file_list.add_end_only(temp))
            {
                WNHDEBUG("获取文件名 path=" << temp << ", 已经添加进入dir_file_list列表");
            }
            else
            {
                WNHDEBUG("获取文件名 path=" << temp << ", 添加失败,已经存在于dir_file_list列表");
            }
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_level_file(const string & dir_path)//获取目录下的所有文件(文件)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(!this->is_dir(temp))
        {
            if(dir_file_list.add_end_only(temp))
            {
                WNHDEBUG("获取文件名 path=" << temp << ", 已经添加进入dir_file_list列表");
            }
            else
            {
                WNHDEBUG("获取文件名 path=" << temp << ", 添加失败,已经存在于dir_file_list列表");
            }
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_dir(const string & dir_path)//获取目录下的所有文件(目录)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            if(dir_file_list.add_end_only(temp))
            {
                WNHDEBUG("获取目录名 path=" << temp << ", 已经添加进入dir_file_list列表");
            }
            else
            {
                WNHDEBUG("获取目录名 path=" << temp << ", 添加失败,已经存在于dir_file_list列表");
            }
            get_dir(temp);
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_level_dir(const string & dir_path)//获取目录下的所有文件(目录)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            if(dir_file_list.add_end_only(temp))
            {
                WNHDEBUG("获取目录名 path=" << temp << ", 已经添加进入dir_file_list列表");
            }
            else
            {
                WNHDEBUG("获取目录名 path=" << temp << ", 添加失败,已经存在于dir_file_list列表");
            }
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_all(const string & dir_path, vector<string> & result)//获取目录下的所有文件(文件+目录)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            result.push_back(temp);
            WNHDEBUG("获取目录名 path=" << temp << ", 已经添加进入result容器");
            get_all(temp);
        }
        else
        {
            result.push_back(temp);
            WNHDEBUG("获取文件名 path=" << temp << ", 已经添加进入result容器");
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_level_all(const string & dir_path, vector<string> & result)//获取目录下的所有文件(文件+目录)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            result.push_back(temp);
            WNHDEBUG("获取目录名 path=" << temp << ", 已经添加进入result容器");
        }
        else
        {
            result.push_back(temp);
            WNHDEBUG("获取文件名 path=" << temp << ", 已经添加进入result容器");
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_file(const string & dir_path, vector<string> & result)//获取目录下的所有文件(文件)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            get_file(temp);
        }
        else
        {
            result.push_back(temp);
            WNHDEBUG("获取文件名 path=" << temp << ", 已经添加进入result容器");
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_level_file(const string & dir_path, vector<string> & result)//获取目录下的所有文件(文件)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(!this->is_dir(temp))
        {
            result.push_back(temp);
            WNHDEBUG("获取文件名 path=" << temp << ", 已经添加进入result容器");
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_dir(const string & dir_path, vector<string> & result)//获取目录下的所有文件(目录)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            result.push_back(temp);
            WNHDEBUG("获取目录名 path=" << temp << ", 已经添加进入result容器");
            get_dir(temp);
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::get_level_dir(const string & dir_path, vector<string> & result)//获取目录下的所有文件(目录)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            result.push_back(temp);
            WNHDEBUG("获取目录名 path=" << temp << ", 已经添加进入result容器");
        }
    }
    closedir(dir);
    return true;
}

vector<string> wnh_system_operation::get_level_dir_quick(const string & dir_path)//获取目录下的所有文件(目录)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    vector<string> file_path;
    if(!get_dir_handle(dir, dir_path))
    {
        return file_path;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        file_path.push_back(temp);
    }
    closedir(dir);
    return file_path;
}

bool wnh_system_operation::show_all(const string & dir_path)//显示目录下的所有文件(文件+目录)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            WNHDEBUG("目录名 path=" << temp);
            show_all(temp);
        }
        else
        {
            WNHDEBUG("文件名 path=" << temp);
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::show_level_all(const string & dir_path)//显示目录下的所有文件(文件+目录)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            WNHDEBUG("目录名 path=" << temp);
        }
        else
        {
            WNHDEBUG("文件名 path=" << temp);
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::show_file(const string & dir_path)//显示目录下的所有文件(文件)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            show_file(temp);
        }
        else
        {
            WNHDEBUG("文件名 path=" << temp);
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::show_level_file(const string & dir_path)//显示目录下的所有文件(文件)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(!this->is_dir(temp))
        {
            WNHDEBUG("文件名 path=" << temp);
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::show_dir(const string & dir_path)//显示目录下的所有文件(目录)
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            WNHDEBUG("目录名 path=" << temp);
            show_dir(temp);
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::show_level_dir(const string & dir_path)//显示目录下的所有文件(目录)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        if(this->is_dir(temp))
        {
            WNHDEBUG("目录名 path=" << temp);
        }
    }
    closedir(dir);
    return true;
}

bool wnh_system_operation::show_level_dir_quick(const string & dir_path)//显示目录下的所有文件(目录)-单层目录
{
    DIR *dir;
    struct dirent *ptr;
    if(!get_dir_handle(dir, dir_path))
    {
        return false;
    }
    while((ptr = readdir(dir)) != nullptr)
    {
        string temp  = ptr->d_name;
        if(temp == "." || temp == "..")
        {
            continue;
        }
        temp = dir_path + "/" + ptr->d_name;
        WNHDEBUG("文件或目录名 path=" << temp);
    }
    closedir(dir);
    return true;
}
