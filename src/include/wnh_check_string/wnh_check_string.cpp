#include "wnh_check_string.h"

wnh_check_string::wnh_check_string()
{

}

wnh_check_string::~wnh_check_string()
{

}

bool wnh_check_string::is_ip_address(const string & ip_address)
{
    const char* point = ".";
    const string ip_addresstemp = ip_address.c_str();
    char * token = strtok((char*)(ip_address.c_str()),point);
    int i = 0,tem = 0;//i表示有几个字段，tem表示每个字段的数字大小
    bool flag = 1;//标志位
    while(token != 0)
    {
        i++;
        tem = atoi(token);
        if(tem > 255 || tem < 0)//合法的ip的每个字段在0~255之间
        {
            WNHDEBUG(ip_addresstemp << "不是有效的IP地址");
            return false;
        }
        token = strtok(0,point);
        if(i >= 5)//合法的ip应该是有四个字段
        {
            WNHDEBUG(ip_addresstemp << "不是有效的IP地址");
            return false;
        }
    }
    if(i < 4 && flag)//每个字段都在0~255之间，但是字段不是四个
    {
        WNHDEBUG(ip_addresstemp << "不是有效的IP地址");
        return false;
    }
    if(flag)//合法的ip
    {
        WNHDEBUG(ip_addresstemp << "是有效的IP地址");
        return true;
    }
    return false;
}

bool wnh_check_string::is_num(const string &num)
{
    stringstream sin(num);
    double t;
    char p;
    if(!(sin >> t))
    {
        WNHDEBUG(num << "不是有效的数字");
        return false;
    }
    if(sin >> p)
    {
        WNHDEBUG(num << "不是有效的数字");
        return false;
    }
    else
    {
        WNHDEBUG(num << "是有效的数字");
        return true;
    }
}

bool wnh_check_string::is_ip_address_and_num(const string &ip_address_and_num)
{
    if(ip_address_and_num.find(":") == string::npos)
    {
        WNHDEBUG(ip_address_and_num << "不是有效的IP地址和端口");
        return false;
    }
    wnh_check_string chk_str;
    if(is_ip_address(ip_address_and_num.substr(0, ip_address_and_num.find(":"))) && is_num(ip_address_and_num.substr(ip_address_and_num.find(":")+1)))
    {
        WNHDEBUG(ip_address_and_num << "是有效的IP地址和端口");
        return true;
    }
    else
    {
        WNHDEBUG(ip_address_and_num << "不是有效的IP地址和端口");
        return false;
    }
}

bool wnh_check_string::is_logs_level(const string &logs_level)
{
    if(wnh_filesync_init::change_logs_lever(logs_level) != -1)
    {
        WNHDEBUG(logs_level << "是有效的日志等级");
        return true;
    }
    WNHDEBUG(logs_level << "不是有效的日志等级");
    return false;
}
