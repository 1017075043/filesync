inline bool wnh_tcp_client::send_start_send_file_info() //发送开始发送文件信息
{
    if(send_info(WNH_TCP_START_SEND_FILE_INFO))
    {
        string info;
        accept_info(info);
        if(info == WNH_TCP_START_SEND_FILE_INFO)
        {
            WNHDEBUG("成功发送开始发送文件信息,并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送开始会话信息,但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送开始发送文件信息失败了, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_client::send_end_send_file_info() //发送结束发送文件信息
{
    if(send_info(WNH_TCP_END_SEND_FILE_INFO))
    {
        string info;
        accept_info(info);
        if(info == WNH_TCP_END_SEND_FILE_INFO)
        {
            WNHDEBUG("成功发送结束发送文件信息,并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送结束发送文件信息,但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送结束发送文件信息失败了, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_client::send_start_send_file_content_info() //发送开始发送文件内容信息
{
    if(send_info(WNH_TCP_START_SEND_FILE_CONTENT_INFO))
    {
        string info;
        accept_info(info);
        if(info == WNH_TCP_START_SEND_FILE_CONTENT_INFO)
        {
            WNHDEBUG("成功发送开始发送文件内容信息,并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送开始发送文件内容信息,但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送开始发送文件内容信息失败了, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_client::send_end_send_file_content_info() //发送结束发送文件内容信息
{
    if(send_info(WNH_TCP_END_SEND_FILE_CONTENT_INFO))
    {
        string info;
        accept_info(info);
        if(info == WNH_TCP_END_SEND_FILE_CONTENT_INFO)
        {
            WNHDEBUG("成功发送结束发送文件内容信息,并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送结束发送文件内容信息,但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送结束发送文件内容信息失败了, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_client::accept_send_file_content_result() //接收发送文件内容结果
{
    string info;
    accept_info(info);
    if(info == WNH_TCP_START_ACCEPT_FILE_CONTENT_INFO)
    {
        WNHDEBUG("成功接收发送文件内容结果,文件数据发送正常");
        return true;
    }
    else
    {
        WNHERROR("没有接收发送文件内容结果,文件数据发送错误");
        return false;
    }
}

inline bool wnh_tcp_client::send_file_size_info(unsigned long file_size) //发送文件大小信息
{
    string info;
    info = info + WNH_TCP_SEND_FILE_SIZE_INFO + to_string(file_size);
    if(send_info(info))
    {
        accept_info(info);
        if(info == WNH_TCP_SEND_FILE_SIZE_INFO)
        {
            WNHDEBUG("成功发送文件大小信息, 文件大小:" << file_size << ", 并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送文件大小信息, 文件大小:" << file_size << ", 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送文件大小信息失败了, 文件大小:" << file_size << ", errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

inline bool wnh_tcp_client::send_file_name_info(const string name) //发送文件名称信息
{
    string info;
    //info = info + WNH_TCP_SEND_FILE_NAME_INFO + name;
    info = info + WNH_TCP_SEND_FILE_NAME_INFO + name + ".bak";
    if(send_info(info))
    {
        accept_info(info);
        if(info == WNH_TCP_SEND_FILE_NAME_INFO)
        {
            WNHDEBUG("成功发送文件名称信息, 文件名称:" << name << ", 并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送文件名称信息, 文件名称:" << name << ", 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送文件名称信息失败了, name:" << name << ", errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_tcp_client::send_file_content(const string file_name) //发送一个文件的内容
{
    if(!send_start_send_file_content_info())
    {
        return false;
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
    file_info.seekg(0, ios::beg);
    char info_bin[TCP_INFO_SZIE];
    while(!file_info.eof())
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);
        file_info.read(info_bin, TCP_INFO_SZIE - TCP_INFO_SZIE_RESERVE);
        WNHDEBUG("发送文件内容长度:" << file_info.gcount());
        send_info(info_bin, file_info.gcount());
        if(!accept_send_file_content_result())
        {
            file_info.close();
            WNHERROR("会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
    }
    file_info.close();

    if(!send_end_send_file_content_info())
    {
        return false;
    }
    return true;
}

bool wnh_tcp_client::send_file_content(const string file_name, const unsigned long & file_size) //发送一个文件的内容
{
    if(!send_start_send_file_content_info())
    {
        return false;
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
        memset(info_bin, '\0', TCP_INFO_SZIE);//数组初始化
        file_info.read(info_bin, TCP_INFO_SZIE - TCP_INFO_SZIE_RESERVE);//从文件中读取一段内容
        temp_file_size -= file_info.gcount();//计算剩余尺寸
        WNHDEBUG("发送文件内容长度:" << file_info.gcount() << ", 文件大小:" << file_size << ", 剩余:" << temp_file_size);
        send_info(info_bin, file_info.gcount());//发送文件内容
        if(!accept_send_file_content_result())//接收发送文件内容后返回的结果
        {
            file_info.close();
            WNHERROR("会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
    }
    file_info.close();

    if(!send_end_send_file_content_info())
    {
        return false;
    }
    return true;
}

bool wnh_tcp_client::send_file_content_v1(const string file_name, const unsigned long & file_size) //发送一个文件的内容
{
    if(!send_start_send_file_content_info())
    {
        return false;
    }

    //发送文件内容
    ifstream file_info(file_name.c_str(), ios::in | ios::binary);
    if(!file_info.is_open())
    {
        WNHERROR("文件打开失败, file_name:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    else
    {
        WNHDEBUG("文件打开成功, file_name:" << file_name);
    }
    int temp_file_size = file_size;
    file_info.seekg(0, ios::beg);
    char info_bin[TCP_INFO_SZIE];
    while(!file_info.eof())
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);//数组初始化
        file_info.read(info_bin, TCP_INFO_SZIE - TCP_INFO_SZIE_RESERVE);//从文件中读取一段内容
        temp_file_size -= file_info.gcount();//计算剩余尺寸
        WNHDEBUG("发送文件内容长度:" << file_info.gcount() << ", 文件大小:" << file_size << ", 剩余:" << temp_file_size);
        send_info(info_bin, file_info.gcount());//发送文件内容
        //    if(!accept_send_file_content_result())//接收发送文件内容后返回的结果
        //    {
        //        break;
        //    }
    }
    file_info.close();

    if(!send_end_send_file_content_info())
    {
        return false;
    }
    return true;
}

inline bool wnh_tcp_client::send_file(const string file_name) //发送一个文件
{
    wnh_system_operation file_attr;
    unsigned long file_size;
    if(!file_attr.get_file_size(file_name, file_size))
    {
        return false;
    }
    WNHDEBUG("开始发送文件,文件名:" << file_name << ", 文件大小:" << file_size)
            if(!send_start_send_file_info())
    {
        return false;
    }
    if(!send_file_size_info(file_size))
    {
        return false;
    }
    if(!send_file_name_info(file_name))
    {
        return false;
    }
    //send_file_content(file_name);
    if(!send_file_content(file_name, file_size))
    {
        return false;
    }
    if(!send_end_send_file_info())
    {
        return false;
    }
    WNHDEBUG("发送文件成功,文件名:" << file_name << ", 文件大小:" << file_size);
    return true;
}
