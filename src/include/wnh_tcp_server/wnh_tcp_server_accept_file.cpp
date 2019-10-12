#include "wnh_tcp_server.h"

bool wnh_tcp_server::accept_start_send_file_info(const int nfp, const string info) //接收开始发送文件信息
{
    if(info == WNH_TCP_START_SEND_FILE_INFO)
    {
        if(send_info(nfp, WNH_TCP_START_SEND_FILE_INFO))
        {
            WNHDEBUG("nfp:" << nfp << ", 接收到开始发送文件信息,并正常回复");
            return true;
        }
        WNHERROR("nfp:" << nfp << ", 接收到开始发送文件信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_end_send_file_info(const int nfp, const string info) //接收结束发送文件信息
{
    if(info == WNH_TCP_END_SEND_FILE_INFO)
    {
        if(send_info(nfp, WNH_TCP_END_SEND_FILE_INFO))
        {
            WNHDEBUG("nfp:" << nfp << ", 接收到结束发送文件信息,并正常回复");
            return true;
        }
        WNHERROR("nfp:" << nfp << ", 接收到结束发送文件信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_start_send_file_content_info(const int nfp, const string info) //接收开始发送文件内容信息
{
    if(info == WNH_TCP_START_SEND_FILE_CONTENT_INFO)
    {
        if(send_info(nfp, WNH_TCP_START_SEND_FILE_CONTENT_INFO))
        {
            WNHDEBUG("nfp:" << nfp << ", 接收到开始发送文件内容信息,并正常回复");
            return true;
        }
        WNHERROR("nfp:" << nfp << ", 接收到开始发送文件内容信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_end_send_file_content_info(const int nfp, const string info) //接收结束发送文件内容信息
{
    if(info == WNH_TCP_END_SEND_FILE_CONTENT_INFO)
    {
        if(send_info(nfp, WNH_TCP_END_SEND_FILE_CONTENT_INFO))
        {
            WNHDEBUG("nfp:" << nfp << ", 接收到结束发送文件内容信息,并正常回复");
            return true;
        }
        WNHERROR("nfp:" << nfp << ", 接收到结束发送文件内容信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_file_size_info(const int nfp, const string info, long long & file_size) //接收文件大小信息
{
    if(info.substr(0, strlen(WNH_TCP_SEND_FILE_SIZE_INFO)) == WNH_TCP_SEND_FILE_SIZE_INFO)
    {
        file_size = strtoull(info.substr(strlen(WNH_TCP_SEND_FILE_SIZE_INFO)).c_str(), nullptr, 10);
        if(send_info(nfp, WNH_TCP_SEND_FILE_SIZE_INFO))
        {
            WNHDEBUG("nfp:" << nfp << ", 接收到文件大小信息, 文件大小:" << file_size << ", 并正常回复");
            return true;
        }
        WNHERROR("nfp:" << nfp << ", 接收到文件大小信息, 文件大小:" << file_size << ", 但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_file_name_info(const int nfp, const string info, string & name) //接收文件名字信息
{
    if(info.substr(0, strlen(WNH_TCP_SEND_FILE_NAME_INFO)) == WNH_TCP_SEND_FILE_NAME_INFO)
    {
        name = info.substr(strlen(WNH_TCP_SEND_FILE_NAME_INFO));
        if(send_info(nfp, WNH_TCP_SEND_FILE_NAME_INFO))
        {
            WNHDEBUG("nfp:" << nfp << ", 接收到文件文件信息, 文件名字:" << name << ", 并正常回复");
            return true;
        }
        WNHERROR("nfp:" << nfp << ", 接收到文件文件信息, 文件名字:" << name << ", 但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_file_content(const int nfp, const string info, const string file_name) //接收一个文件内容
{
    if(!accept_start_send_file_content_info(nfp, info))
    {
        return false;
    }
    if(file_name.empty())
    {
        WNHERROR("nfp:" << nfp << ", 接收一个文件内容失败了, 文件名为空");
        return true;
    }
    ofstream file_info(file_name.c_str(), ios::out | ios::binary);
    if(!file_info.is_open())
    {
        WNHERROR("nfp:" << nfp << ", 文件打开失败, 文件名称:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
        return true;
    }
    else
    {
        WNHDEBUG("nfp:" << nfp << ", 文件打开成功, 文件名称:" << file_name);
    }
    char *info_bin = new char[TCP_INFO_SZIE];
    int info_size = 0;
    while(survival_id)
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);
        if(!accept_info(nfp, info_bin, info_size))
        {
            WNHERROR("nfp:" << nfp << ", 接收一个文件内容失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            break;
        }
        if(accept_end_send_file_content_info(nfp, info_bin))
        {
            delete []info_bin;
            file_info.close();
            return true;
        }
        WNHDEBUG("nfp:" << nfp << ", 接收到文件内容,长度:" << info_size);
        file_info.write(info_bin, info_size);
        if(!send_info(nfp, WNH_TCP_START_ACCEPT_FILE_CONTENT_INFO))
        {
            delete []info_bin;
            file_info.close();
            return true;
        }
    }
    delete []info_bin;
    file_info.close();
    return true;
}

bool wnh_tcp_server::accept_file_content(const int nfp, const string info, const string file_name, const long long & file_size) //接收一个文件内容
{
    if(!accept_start_send_file_content_info(nfp, info))
    {
        return false;
    }
    if(file_name.empty())
    {
        WNHERROR("nfp:" << nfp << ", 接收一个文件内容失败了, 文件名不存在");
        return true;
    }
    if(file_size == -1)
    {
        WNHERROR("nfp:" << nfp << ", 接收一个文件内容失败了, 文件大小不存在");
        return true;
    }
    WNHDEBUG("开始接收文件信息, 文件名:" << file_name << ", 文件大小:" << file_size);
    ofstream file_info(file_name.c_str(), ios::out | ios::binary);
    if(!file_info.is_open())
    {
        WNHERROR("nfp:" << nfp << ", 文件打开失败, 文件名称:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
        return true;
    }
    else
    {
        WNHDEBUG("nfp:" << nfp << ", 文件打开成功, 文件名称:" << file_name);
    }
    char *info_bin = new char[TCP_INFO_SZIE];
    int info_size = 0;
    unsigned long temp_file_size = file_size;
    while(survival_id)
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);
        if(!accept_info(nfp, info_bin, info_size))
        {
            WNHERROR("nfp:" << nfp << ", 接收一个文件内容失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            break;
        }
        if(accept_end_send_file_content_info(nfp, info_bin))
        {
            delete []info_bin;
            file_info.close();
            return true;
        }
        temp_file_size -= info_size;//计算剩余尺寸
        WNHDEBUG("nfp:" << nfp << ", 接收到文件内容,长度:" << info_size << ", 文件大小:" << file_size << ", 剩余:" << temp_file_size);
        file_info.write(info_bin, info_size);
        if(!send_info(nfp, WNH_TCP_START_ACCEPT_FILE_CONTENT_INFO))
        {
            delete []info_bin;
            file_info.close();
            return true;
        }
    }
    delete []info_bin;
    file_info.close();
    return true;
}

bool wnh_tcp_server::accept_file_content_v1(const int nfp, const string info, const string file_name, const long long & file_size) //接收一个文件内容
{
    if(!accept_start_send_file_content_info(nfp, info))
    {
        return false;
    }
    if(file_name.empty())
    {
        WNHERROR("nfp:" << nfp << ", 接收一个文件内容失败了, 文件名为空");
        return true;
    }
    if(file_size == -1)
    {
        WNHERROR("nfp:" << nfp << ", 接收一个文件内容失败了, 文件大小不存在");
        return true;
    }

    WNHDEBUG("开始接收文件信息, 文件名:" << file_name << ", 文件大小:" << file_size);
    ofstream file_info(file_name.c_str(), ios::out | ios::binary);
    if(!file_info.is_open())
    {
        WNHERROR("nfp:" << nfp << ", 文件打开失败, 文件名称:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
        return true;
    }
    else
    {
        WNHDEBUG("nfp:" << nfp << ", 文件打开成功, 文件名称:" << file_name);
    }
    char *info_bin = new char[TCP_INFO_SZIE];
    int info_size = 0;
    unsigned long temp_file_size = file_size;
    while(temp_file_size != 0)
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);
        if(!accept_info(nfp, info_bin, info_size))
        {
            WNHERROR("nfp:" << nfp << ", 接收一个文件内容失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            break;
        }
        if(info_size == 0)
        {
            delete []info_bin;
            file_info.close();
            return true;
        }
        temp_file_size -= info_size;//计算剩余尺寸
        WNHDEBUG("接收到文件内容,长度:" << info_size << ", 文件大小:" << file_size << ", 剩余:" << temp_file_size);
        file_info.write(info_bin, info_size);
    }
    delete []info_bin;
    file_info.close();

    if(accept_end_send_file_content_info(nfp, info_bin))
    {
        WNHDEBUG("nfp:" << nfp << ", 成功接收文件信息, 文件名:" << file_name << ", 文件大小:" << file_size);
        return true;
    }
    return true;
}

int wnh_tcp_server::accept_file(const int nfp, const string info) //接收一个文件
{
    if(!accept_start_send_file_info(nfp, info))//判断是否为接收文件的标识语
    {
        return WNH_TCP_IGNORE_RESULTS;
    }
    //开始接收文件信息
    string name = "";
    long long file_size = -1;
    while(survival_id)
    {
        string info;
        if(accept_info(nfp, info))//接收信息
        {
            if(accept_end_send_file_info(nfp, info))//如果是接收到文件发送结束的标识语，就结束文件的接收
            {
                return WNH_TCP_SUCCESS_RESULTS;
            }
            if(accept_file_size_info(nfp, info, file_size))
            {
                continue;
            }
            if(accept_file_name_info(nfp, info, name))
            {
                continue;
            }
            if(accept_file_content(nfp, info, name, file_size))
            {
                name = "";
                file_size = -1;
                continue;
            }
            if(info.empty())
            {
                WNHERROR("nfp:" << nfp << ", 会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
                return WNH_TCP_FAIL_RESULTS;
            }
            if(info == WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID)
            {
                WNHERROR("nfp:" << nfp << ", 等待超时或者会话异常, 接收到信息错误, 会话异常结束" << ", errno=" << errno << ", mesg=" << strerror(errno));
                close_session(nfp, false);
                return WNH_TCP_FAIL_RESULTS;
            }
            WNHDEBUG("nfp:" << nfp << ", 接收到无法识别的信息:" << info);
            if(!send_info(nfp, info))
            {
                return WNH_TCP_FAIL_RESULTS;
            }
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
            return WNH_TCP_FAIL_RESULTS;
        }
    }
    return WNH_TCP_FAIL_RESULTS;
}
