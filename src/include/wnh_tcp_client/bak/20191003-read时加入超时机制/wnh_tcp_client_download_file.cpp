#include "wnh_tcp_client.h"

bool wnh_tcp_client::accept_download_file_error_stop_info(const string info) //接收下载文件错误结束信息
{
    if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_ERROR_END)
    {
        if(send_info(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_ERROR_END))
        {
            WNHDEBUG("接收到下载文件错误结束信息, 并正常回复, 结束下载文件");
        }
        else
        {
            WNHERROR("接收到下载文件错误结束信息, 但是回复时失败了, 结束下载文件");
        }
        return true;
    }
    return false;
}

bool wnh_tcp_client::accept_download_file_size_info(const string info, unsigned long & file_size) //接收下载文件大小信息
{
    if(info.substr(0, strlen(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_SIZE)) == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_SIZE)
    {
        file_size = strtoull(info.substr(strlen(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_SIZE)).c_str(), nullptr, 10);
        if(send_info(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_SIZE))
        {
            WNHDEBUG("接收到下载文件大小信息, 文件大小:" << file_size << ", 并正常回复");
        }
        else
        {
            WNHERROR("接收到下载文件大小信息, 文件大小:" << file_size << ", 但是回复时失败了");
        }
        return true;
    }
    return false;
}

bool wnh_tcp_client::accept_download_file_complete_info(const string info) //接收下载文件完成信息
{
    if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_COMPLETE)
    {
        if(send_info(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_COMPLETE))
        {
            WNHDEBUG("接收到下载文件完成信息, 并正常回复, 结束下载文件");
        }
        else
        {
            WNHERROR("接收到下载文件完成信息, 但是回复时失败了, 结束下载文件");
        }
        return true;
    }
    return false;
}

bool wnh_tcp_client::accept_download_file_content_start_info(const string info) //接收开始下载文件内容信息
{
    if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_START)
    {
        if(send_info(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_START))
        {
            WNHDEBUG("接收到下载文件内容信息, 并正常回复, 结束下载文件");
        }
        else
        {
            WNHERROR("接收到下载文件内容信息, 但是回复时失败了, 结束下载文件");
        }
        return true;
    }
    return false;
}

bool wnh_tcp_client::accept_download_file_content_stop_info(const string info) //接收结束下载文件内容信息
{
    if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_STOP)
    {
        if(send_info(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_STOP))
        {
            WNHDEBUG("接收到结束下载文件内容信息, 并正常回复, 结束下载文件");
        }
        else
        {
            WNHERROR("接收到结束下载文件内容信息, 但是回复时失败了, 结束下载文件");
        }
        return true;
    }
    return false;
}

bool wnh_tcp_client::accept_download_file_content_info(const string info, const unsigned long & file_size, const string & temp_file_name) //接收下载文件内容信息
{
    if(!accept_download_file_content_start_info(info))
    {
        return false;
    }
    if(file_size == (unsigned long)-1)
    {
        WNHERROR("接收下载文件内容信息失败了, 文件大小不存在");
        return true;
    }
    string file_name = temp_file_name;
    WNHDEBUG("开始接收下载文件, 文件名:" << file_name << ", 文件大小:" << file_size);
    ofstream file_info(file_name.c_str(), ios::out | ios::binary);
    if(!file_info.is_open())
    {
        WNHERROR("文件打开失败, 文件名称:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
        return true;
    }
    else
    {
        WNHDEBUG("文件打开成功, 文件名称:" << file_name);
    }
    char *info_bin = new char[TCP_INFO_SZIE];
    int info_size = 0;
    unsigned long temp_file_size = file_size;
    unsigned long temp_time = LOCALTIMENUM;
    while(1)
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);
        accept_info(info_bin, info_size);
        //  if(info_size == 0)
        //  {
        //      delete []info_bin;
        //      file_info.close();
        //      return true;
        //  }
        if(accept_download_file_content_stop_info(info_bin))
        {
            delete []info_bin;
            file_info.close();
            return true;
        }
        temp_file_size -= info_size;//计算剩余尺寸
        WNHDEBUG("接收到下载文件内容,长度:" << info_size << ", 文件大小:" << file_size << ", 剩余:" << temp_file_size);
        file_info.write(info_bin, info_size);
        if(!send_info(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_RESULT))
        {
            delete []info_bin;
            file_info.close();
            return true;
        }
        //显示进度
        if(LOCALTIMENUM - temp_time > 3)
        {
            WNHINFO("下载文件:" << file_name << ", 进度:" << ((float)(((float)file_size - (float)temp_file_size)/(float)file_size))*100 << "%, 总大小:" << file_size << ", 剩余:" << temp_file_size);
            temp_time = LOCALTIMENUM;
        }
    }
    delete []info_bin;
    file_info.close();
    return true;
}

bool wnh_tcp_client::download_file(const string file_name, const string temp_file_name) //下载文件
{
    if(!send_apply_download_file_info(file_name))
    {
        return false;
    }

    string info;
    unsigned long file_size;
    while(1)
    {
        if(accept_info(info))
        {
            if(accept_download_file_error_stop_info(info))
            {
                return false;
            }
            if(accept_download_file_size_info(info, file_size))
            {
                if(file_size == (unsigned long)0)
                {
                    ofstream file_info(temp_file_name.c_str(), ios::out | ios::binary);
                    if(!file_info.is_open())
                    {
                        WNHERROR("文件创建失败, 文件名称:" << temp_file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
                    }
                    else
                    {
                        WNHDEBUG("文件创建成功, 文件名称:" << temp_file_name);
                    }
                    file_info.close();
                }
                continue;
            }
            if(accept_download_file_content_info(info, file_size, temp_file_name))
            {
                continue;
            }
            if(accept_download_file_complete_info(info))
            {
                return true;
            }
        }
    }
    return true;
}

bool wnh_tcp_client::send_apply_download_file_info(const string file_name) //发送请求文件下载信息
{
    string info;
    info = info + WNH_TCP_APPLY_DOWNLOAD_FILE_INFO + file_name;
    if(send_info(info))
    {
        accept_info(info);
        if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO)
        {
            if(send_info(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO))
            {
                WNHDEBUG("成功发送请求文件下载信息, 文件名称:" << file_name << ", 并得到的正常回复");
            }
            else
            {
                WNHDEBUG("成功发送请求文件下载信息, 文件名称:" << file_name << ", 并没有得到的正常回复");
            }
            return true;
        }
        else
        {
            WNHERROR("成功发送请求文件下载信息, 文件名称:" << file_name << ", 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送请求文件下载信息失败了, 文件名称:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}
