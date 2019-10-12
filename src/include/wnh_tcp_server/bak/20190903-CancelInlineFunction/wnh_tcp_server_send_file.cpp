inline bool wnh_tcp_server::accept_apply_downinfo_file_info(const int nfp, const string info) //接收请求文件下载信息
{
    string file_name;
    if(!accept_apply_downinfo_file_name_info(nfp, info, file_name))
    {
        return false;
    }
    if(file_name.empty())
    {
        WNHERROR("nfp:" << nfp << ", 接收请求文件下载信息失败了, 文件名为空");
        return true;
    }
    unsigned long file_size;
    if(!reply_downinfo_file_size_info(nfp, file_name, file_size))
    {
        return true;
    }
    if(!send_reply_downinfo_file_content(nfp, file_name, file_size))
    {
        return true;
    }
    if(send_reply_downinfo_file_complete_info(nfp))
    {
        return true;
    }
    else
    {
        WNHERROR("nfp:" << nfp << ", 会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
        close_session(nfp, false);
    }
    return true;
}

inline bool wnh_tcp_server::send_reply_downinfo_file_content(const int nfp, const string file_name, const unsigned long file_size) //接收请求文件下载的文件内容信息
{
    if(!send_reply_downinfo_file_content_start(nfp))
    {
        return true;
    }

    //发送文件内容
    ifstream file_info(file_name.c_str(), ios::in | ios::binary);
    if(!file_info.is_open())
    {
        WNHERROR("文件打开失败, 文件名称:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    else
    {
        WNHDEBUG("文件打开成功, 文件名称:" << file_name);
    }
    int temp_file_size = file_size;
    file_info.seekg(0, ios::beg);
    char info_bin[TCP_INFO_SZIE];
    while(!file_info.eof())
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);
        file_info.read(info_bin, TCP_INFO_SZIE - TCP_INFO_SZIE_RESERVE);
        temp_file_size -= file_info.gcount();//计算剩余尺寸
        WNHDEBUG("发送文件内容长度:" << file_info.gcount() << ", 文件大小:" << file_size << ", 剩余:" << temp_file_size);
        send_info(nfp, info_bin, file_info.gcount());
        if(!accept_downinfo_file_content_result(nfp))
        {
            file_info.close();
            WNHERROR("会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
    }
    file_info.close();

    if(send_reply_downinfo_file_content_stop(nfp))
    {
        return true;
    }
    return true;
}

inline bool wnh_tcp_server::accept_downinfo_file_content_result(const int nfp) //接收下载文件成功接收一行文件内容信息结果
{
    string info;
    accept_info(nfp, info);
    if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_RESULT)
    {
        WNHDEBUG("成功接收下载文件成功接收一行文件内容信息结果,文件数据发送正常");
        return true;
    }
    else
    {
        WNHDEBUG("成功接收下载文件成功接收一行文件内容信息结果,文件数据发送正常");
        return false;
    }
}

inline bool wnh_tcp_server::send_reply_downinfo_file_content_stop(const int nfp) //发送回复下载文件结束发送文件内容信息
{
    string info;
    if(send_info(nfp, WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_STOP))
    {
        accept_info(nfp, info);
        if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_STOP)
        {
            WNHDEBUG("成功发送回复下载文件结束发送文件内容信息, 并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送回复下载文件结束发送文件内容信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送回复下载文件结束发送文件信息失败了, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_server::send_reply_downinfo_file_content_start(const int nfp) //发送回复下载文件开始发送文件内容信息
{
    string info;
    if(send_info(nfp, WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_START))
    {
        accept_info(nfp, info);
        if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_CONTENT_START)
        {
            WNHDEBUG("成功发送回复下载文件开始发送文件内容信息, 并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送回复下载文件开始发送文件内容信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送回复下载文件开始发送文件信息失败了, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_server::accept_apply_downinfo_file_name_info(const int nfp, const string info, string & file_name) //接收请求文件下载的文件名字信息
{
    if(info.substr(0, strlen(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO)) == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO)
    {
        file_name = info.substr(strlen(WNH_TCP_APPLY_DOWNLOAD_FILE_INFO));
        if(send_info(nfp, WNH_TCP_APPLY_DOWNLOAD_FILE_INFO))
        {
            string info_temp;
            accept_info(nfp, info_temp);
            if(info_temp == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO)
            {
                WNHDEBUG("nfp:" << nfp << ", 接收到请求文件下载的文件名字信息, 文件名称:" << file_name << ", 并正常回复, 同时得到正常答复");
                return true;
            }
            else
            {
                WNHDEBUG("nfp:" << nfp << ", 接收到请求文件下载的文件名字信息, 文件名称:" << file_name << ", 并正常回复,但是没有得到正常答复");
                return false;
            }
            return true;
        }
        WNHERROR("nfp:" << nfp << ", 接收到请求文件下载的文件名字信息, 文件名称:" << file_name << ", 但是回复时失败了");
    }
    return false;
}

inline bool wnh_tcp_server::reply_downinfo_file_size_info(const int nfp, const string file_name, unsigned long & file_size) //回复请求文件下载文件大小
{
    wnh_system_operation file_attr;
    if(!file_attr.get_file_size(file_name, file_size))
    {
        send_reply_downinfo_file_error_stop_info(nfp);
        return false;
    }
    if(!send_reply_downinfo_file_szie_info(nfp, file_size))
    {
        return false;
    }

    return true;
}

inline bool wnh_tcp_server::send_reply_downinfo_file_complete_info(const int nfp) //发送回复下载文件完成信息
{
    string info;
    if(send_info(nfp, WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_COMPLETE))
    {
        accept_info(nfp, info);
        if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_COMPLETE)
        {
            WNHDEBUG("成功发送回复下载文件完成信息, 并得到的正常回复, 下载文件完成");
            return true;
        }
        else
        {
            WNHERROR("成功发送回复下载文件完成信息, 但是并没得到得到的正常回复, 下载文件完成");
            return false;
        }
    }
    WNHERROR("发送回复下载文件完成信息失败了, 下载文件完成, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_server::send_reply_downinfo_file_szie_info(const int nfp, const unsigned long file_size) //发送回复下载文件大小信息
{
    string info;
    info = info + WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_SIZE + to_string(file_size);
    if(send_info(nfp, info))
    {
        accept_info(nfp, info);
        if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_SIZE)
        {
            WNHDEBUG("成功发送回复下载文件大小信息, 文件大小:" << file_size << ", 并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送回复下载文件大小信息, 文件大小:" << file_size << ", 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送发送回复下载文件大小信息失败了, 文件大小:" << file_size << ", errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_server::send_reply_downinfo_file_error_stop_info(const int nfp) //发送回复下载文件错误停止信息
{
    string info;
    if(send_info(nfp, WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_ERROR_END))
    {
        accept_info(nfp, info);
        if(info == WNH_TCP_APPLY_DOWNLOAD_FILE_INFO_ERROR_END)
        {
            WNHDEBUG("成功发送回复下载文件错误停止信息, 并得到的正常回复, 结束下载文件");
            return true;
        }
        else
        {
            WNHERROR("成功发送回复下载文件错误停止信息, 但是并没得到得到的正常回复, 结束下载文件");
            return false;
        }
    }
    WNHERROR("发送回复下载文件错误停止信息失败了, 结束下载文件, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}
