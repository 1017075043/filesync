wnh_tcp_client::wnh_tcp_client()
{
    display_transfer_logs = DIS_TRAN_LOG_2;
}

wnh_tcp_client::~wnh_tcp_client()
{

}

int wnh_tcp_client::set_non_blocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

bool wnh_tcp_client::create_socket() //创建一个socket,返回句柄数
{
    //AF_INET 使用IPv4协议
    //SOCK_STREAM 使用TCP来进行通行
    socket_num = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == socket_num)
    {
        WNHERROR("创建一个socket失败了, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }

    int on = 1;
    setsockopt(socket_num, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));//允许地址的立即重用

    WNHDEBUG("创建一个socket成功了,socket_num=" << socket_num);
    return true;
}

void wnh_tcp_client::set_teraccept_address(string ip, int portnum) //设置目标服务器的地址信息
{
    this->ip = ip.c_str();
    this->portnum =(unsigned short)portnum;
    bzero(&teraccept_address, sizeof(teraccept_address));
    teraccept_address.sin_family = AF_INET;
    inet_pton(AF_INET, this->ip.c_str(), &teraccept_address.sin_addr);
    teraccept_address.sin_port = htons(this->portnum);
}

bool wnh_tcp_client::unblock_connect(int time) //非阻塞的连接
{
    int ret = 0;
    int fdopt = set_non_blocking(socket_num);
    ret = connect(socket_num,(struct sockaddr*)&teraccept_address, sizeof(teraccept_address));
    WNHDEBUG("连接状态码, ret=" << ret);
    if(ret == 0)
    {
        WNHDEBUG("立即与服务器完成非阻塞连接, 连接成功");
        fcntl(socket_num, F_SETFL, fdopt);   //set old optional back
        return true;
    }
    //unblock mode --> connect return immediately! ret = -1 & errno=EINPROGRESS
    else if(errno != EINPROGRESS)
    {
        WNHERROR("与服务器非阻塞连接失败了, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    else if(errno == EINPROGRESS)
    {
        WNHDEBUG("正在与服务器进行非阻塞连接, 请等待!");
    }

    //use select to check write event, if the socket is writable, then
    //connect is complete successfully!
    fd_set readfds;
    fd_set writefds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(socket_num, &writefds);

    timeout.tv_sec = time; //timeout is 10 minutes
    timeout.tv_usec = 0;

    ret = select(socket_num + 1, nullptr, &writefds, nullptr, &timeout);
    if(ret <= 0)
    {
        WNHERROR("正在与服务器进行非阻塞连接, 连接超时了, 连接时间time=" << time << ", errno=" << errno << ", mesg=" << strerror(errno));
        close(socket_num);
        return false;
    }

    if(! FD_ISSET(socket_num, &writefds ))
    {
        WNHERROR("正在与服务器进行非阻塞连接, 连接失败了, 在socket_num上找不到事件, errno=" << errno << ", mesg=" << strerror(errno));
        close(socket_num);
        return false;
    }

    int error = 0;
    socklen_t length = sizeof(error);
    if(getsockopt(socket_num, SOL_SOCKET, SO_ERROR, &error, &length) < 0)
    {
        WNHERROR("正在与服务器进行非阻塞连接, 连接失败了, 获取套接字选项失败, errno=" << errno << ", mesg=" << strerror(errno));
        close(socket_num);
        return false;
    }

    if(error != 0)
    {
        WNHERROR("正在与服务器进行非阻塞连接, 连接失败了, errno=" << errno << ", mesg=" << strerror(errno));
        close(socket_num);
        return false;
    }

    //connection successful!
    WNHDEBUG("与服务器完成非阻塞连接, 连接成功");
    fcntl(socket_num, F_SETFL, fdopt); //set old optional back
    return true;
}

inline bool wnh_tcp_client::send_info(const string info) //发出一条信息
{
    if((unsigned int)info.length() != write(socket_num, info.c_str(), info.length()))
    {
        if(display_transfer_logs == DIS_TRAN_LOG_2)
        {
            WNHERROR("信息发出失败了, 1.0, 内容:" << info << ", 长度:" << info.length() << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        else
        {
            WNHERROR("信息发出失败了, 1.0, 长度:" << info.length() << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("信息发出成功, 1.0, 长度:" << info.length());
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            WNHDEBUG("信息发出成功, 1.0, 内容:" << info << ", 长度:" << info.length());
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_client::send_info(const char info[TCP_INFO_SZIE]) //发出一条信息
{
    if((unsigned int)strlen(info) != write(socket_num, info, strlen(info)))
    {
        if(display_transfer_logs == DIS_TRAN_LOG_2)
        {
            WNHERROR("信息发出失败了, 2.0, 内容:" << info << ", 长度:" << strlen(info) << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        else
        {
            WNHERROR("信息发出失败了, 2.0, 长度:" << strlen(info) << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("信息发出成功, 2.0, 长度:" << strlen(info));
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            WNHDEBUG("信息发出成功, 2.0, 内容:" << info << ", 长度:" << strlen(info));
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_client::send_info(const string info, const int size) //发出一条信息
{
    if(size != write(socket_num, info.c_str(), size))
    {
        if(display_transfer_logs == DIS_TRAN_LOG_2)
        {
            WNHERROR("信息发出失败了, 1.0, 内容:" << info << ", 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        else
        {
            WNHERROR("信息发出失败了, 1.0, 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("信息发出成功, 1.0, 长度:" << size);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            if(size ==(int)info.length())
            {
                WNHDEBUG("信息发出成功, 1.0, 内容:" << info << ", 长度:" << size);
            }
            else
            {
                WNHDEBUG("信息发出成功, 1.0, 内容: 二进制内容-忽略显示, 长度:" << size);
            }
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_client::send_info(const char info[TCP_INFO_SZIE], const int size) //发出一条信息
{
    if(size != write(socket_num, info, size))
    {
        if(display_transfer_logs == DIS_TRAN_LOG_2)
        {
            WNHERROR("信息发出失败了, 2.0, 内容:" << info << ", 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        else
        {
            WNHERROR("信息发出失败了, 2.0, 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("信息发出成功, 2.0, 长度:" << size);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            if(size ==(int)strlen(info))
            {
                WNHDEBUG("信息发出成功, 2.0, 内容:" << info << ", 长度:" << size);
            }
            else
            {
                WNHDEBUG("信息发出成功, 2.0, 内容: 二进制内容-忽略显示, 长度:" << size);
            }
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_client::accept_info(string &info) //接收一条信息
{
    int recbytes;
    char buffer[TCP_INFO_SZIE]= {0};

    if(-1 ==(recbytes = read(socket_num, buffer, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 1.0, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    buffer[recbytes]='\0';
    info = buffer;
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("信息接收成功, 1.0, 长度:" << info.length());
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            WNHDEBUG("信息接收成功, 1.0,内容:" << info << ", 长度:" << info.length());
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_client::accept_info(char * &info) //接收一条信息
{
    int recbytes;
    if(-1 ==(recbytes = read(socket_num, info, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 2.0, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    info[recbytes]='\0';
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("信息接收成功, 2.0, 长度:" << strlen(info));
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            WNHDEBUG("信息接收成功, 2.0,内容:" << info << ", 长度:" << strlen(info));
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_client::accept_info(string &info, int &size) //接收一条信息
{
    int recbytes;
    char buffer[TCP_INFO_SZIE]= {0};

    if(-1 ==(recbytes = read(socket_num, buffer, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 1.0, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    buffer[recbytes]='\0';
    info = buffer;
    size = recbytes;
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("信息接收成功, 1.0, 长度:" << size);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            if(size ==(int)info.length())
            {
                WNHDEBUG("信息接收成功, 1.0,内容:" << info << ", 长度:" << size);
            }
            else
            {
                WNHDEBUG("信息接收成功, 1.0,内容:二进制内容-忽略显示, 长度:" << size);
            }
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_client::accept_info(char * &info, int &size) //接收一条信息
{
    int recbytes;
    if(-1 ==(recbytes = read(socket_num, info, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 2.0, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    info[recbytes]='\0';
    size = recbytes;
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("信息接收成功, 2.0, 长度:" << size);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            if(size ==(int)strlen(info))
            {
                WNHDEBUG("信息接收成功, 2.0,内容:" << info << ", 长度:" << size);
            }
            else
            {
                WNHDEBUG("信息接收成功, 2.0,内容:二进制内容-忽略显示, 长度:" << size);
            }
            break;
        }
    }
    return true;
}
