#include "wnh_system_operation.h"
#include "wnh_system_operation_dir_traverse.cpp"
#include "wnh_system_operation_file_attribute.cpp"
#include "wnh_system_operation_file_operation.cpp"

wnh_system_operation::wnh_system_operation()
{

}

wnh_system_operation::~wnh_system_operation()
{
    dir_file_list.delete_list();//清除dir_file_list类中的数据
}

bool wnh_system_operation::file_or_dir_exist(const string & file_path) //判断文件或者目录是否存在
{
    fstream file;
    file.open(file_path, ios::in);
    if(!file)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool wnh_system_operation::file_is_exist(const string & file_path)//判断文件是否存在
{
    struct stat st;
    return get_file_handle(st, file_path);
}

inline bool wnh_system_operation::get_file_handle(struct stat &st, const string & file_path)//获取一个文件的句柄
{
    if(stat(file_path.c_str(), &st) == -1)
    {
        WNHDEBUG("获取文件状态失败 " << file_path << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    return true;
}

inline bool wnh_system_operation::get_dir_handle(DIR * &dir, const string & file_path)//获取一个目录的句柄
{
    dir = opendir(file_path.c_str());
    if(dir == nullptr)
    {
        WNHDEBUG("打开目录失败 " << file_path << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    return true;
}

inline bool wnh_system_operation::get_open_file_handle(FILE * &stream, const string & file_path, const string & use_method)//获取一个文件的操作句柄
{
    stream = fopen(file_path.c_str(), use_method.c_str());
    if(stream == nullptr)
    {
        WNHDEBUG("获取文件" << file_path << "的操作句柄失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    return true;
}
