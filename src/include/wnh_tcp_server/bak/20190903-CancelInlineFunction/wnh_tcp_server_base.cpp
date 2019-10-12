wnh_tcp_server::wnh_tcp_server()
{
    survival_id = true; //标志位存活状态
    tcp_listen_conturrent_now_num = 0;
    thread start_manage_session_pthread(&wnh_tcp_server::manage_session_pthread, this);
    start_manage_session_pthread.detach();
    display_transfer_logs = DIS_TRAN_LOG_2;
}

wnh_tcp_server::~wnh_tcp_server()
{
    survival_id = false;  //标志位死亡状态
    close(socket_num); //关闭套接字
}

bool wnh_tcp_server::create_socket() //创建一个socket,返回句柄数
{
    //AF_INET 使用IPv4协议
    //SOCK_STREAM 使用TCP来进行通行
    socket_num = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == socket_num)
    {
        WNHERROR("创建一个socket失败了, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }

    int on = 1;
    setsockopt(socket_num, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));//允许地址的立即重用

    WNHDEBUG("创建一个socket成功,socket_num=" << socket_num);
    return true;
}

void wnh_tcp_server::set_server_address(int portnum) //设置服务器地址信息
{
    this->portnum =(unsigned short)portnum;
    bzero(&server_address,sizeof(struct sockaddr_in));
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=htonl(INADDR_ANY);
    server_address.sin_port=htons(portnum);
}

bool wnh_tcp_server::server_bind() //将进程与端口进行绑定
{
    if(-1 == bind(socket_num,(struct sockaddr *)(&server_address), sizeof(struct sockaddr)))
    {
        WNHERROR("将进程与" << portnum << "端口进行绑定绑定失败了, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG("将进程与" << portnum << "端口进行绑定绑定成功");
    return true;
}

bool wnh_tcp_server::server_listen(int concurrent_num) //开始监听端口
{
    if(-1 == listen(socket_num,concurrent_num)) //在套接字上监听
    {
        WNHERROR("监听" << portnum << "端口失败了, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG("监听" << portnum << "端口成功, 并发监听数concurrent_num=" << concurrent_num);
    return true;
}

int wnh_tcp_server::server_accept() //等待客户端的连接
{
    struct sockaddr_in client_address;
    sin_size = sizeof(struct sockaddr_in);
    int nfp = accept(socket_num, (struct sockaddr *)(&client_address), &sin_size);
    if(-1 == nfp)
    {
        WNHERROR("等待客户端的连接失败了, errno=" << errno << ", mesg=" << strerror(errno));
        return -1;
    }
    WNHDEBUG("确定接收客户端的连接,获得新的临时句柄数nfp=" << nfp << ", 客户端的IP:" << inet_ntoa(client_address.sin_addr) << ", 使用的临时端口:" << ntohs(client_address.sin_port));
    return nfp;
}

inline bool wnh_tcp_server::send_info(const int nfp, const string info) //发出一条信息
{
    if((unsigned int)info.length() != write(nfp, info.c_str(), info.length()))
    {
        if(display_transfer_logs == DIS_TRAN_LOG_2)
        {
            WNHERROR("nfp:" << nfp << ", 信息发出失败了, 1.0, 内容:" << info << ", 长度:" << info.length() << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 信息发出失败了, 1.0, 长度:" << info.length() << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 1.0, 长度:" << info.length());
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 1.0, 内容:" << info << ", 长度:" << info.length());
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_server::send_info(const int nfp,const char info[TCP_INFO_SZIE]) //发出一条信息
{
    if((unsigned int)strlen(info) != write(nfp, info, strlen(info)))
    {
        if(display_transfer_logs == DIS_TRAN_LOG_2)
        {
            WNHERROR("nfp:" << nfp << ", 信息发出失败了, 2.0, 内容:" << info << ", 长度:" << strlen(info) << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 信息发出失败了, 2.0, 长度:" << strlen(info) << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    switch(display_transfer_logs)
    {
    case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 长度:" << strlen(info));
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 2.0, 内容:" << info << ", 长度:" << strlen(info));
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_server::send_info(const int nfp, const string info, const int size) //发出一条信息
{
    if(size != write(nfp, info.c_str(), size))
    {
        if(display_transfer_logs == DIS_TRAN_LOG_2)
        {
            WNHERROR("nfp:" << nfp << ", 信息发出失败了, 1.0, 内容:" << info << ", 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 信息发出失败了, 1.0, 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 长度:" << size);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            if(size == (int)info.length())
            {
                WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 1.0, 内容:" << info << ", 长度:" << size);
            }
            else
            {
                WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 1.0, 内容:二进制内容-忽略显示, 长度:" << size);
            }
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_server::send_info(const int nfp,const char info[TCP_INFO_SZIE], const int size) //发出一条信息
{
    if(size != write(nfp, info, size))
    {
        if(display_transfer_logs == DIS_TRAN_LOG_2)
        {
            WNHERROR("nfp:" << nfp << ", 信息发出失败了, 2.0, 内容:" << info << ", 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 信息发出失败了, 2.0, 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        }
        return false;
    }
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 2.0, 长度:" << size);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            if(size == (int)strlen(info))
            {
                WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 2.0, 内容:" << info << ", 长度:" << size);
            }
            else
            {
                WNHDEBUG("nfp:" << nfp << ", 信息发出成功, 2.0, 内容:二进制内容-忽略显示, 长度:" << size);
            }
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_server::accept_info(const int nfp, string & info) //接收一条信息
{
    int recbytes;
    char buffer[TCP_INFO_SZIE]= {0};
    if(-1 == (recbytes = read(nfp, buffer, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("nfp:" << nfp << ", 信息接收失败了, 1.0, nfp=" << nfp << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    buffer[recbytes]='\0';
    info = buffer;
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 1.0, 长度:" << recbytes);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 1.0, 内容:" << info << ", 长度:" << recbytes);
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_server::accept_info(const int nfp, char * & info) //接收一条信息
{
    int recbytes;
    if(-1 == (recbytes = read(nfp, info, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("nfp:" << nfp << ", 信息接收失败了, 2.0, nfp=" << nfp << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    info[recbytes]='\0';
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 2.0, 长度:" << recbytes);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 2.0, 内容:" << info << ", 长度:" << recbytes);
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_server::accept_info(const int nfp, string & info, int & size) //接收一条信息
{
    int recbytes;
    char buffer[TCP_INFO_SZIE]= {0};
    if(-1 == (recbytes = read(nfp, buffer, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("nfp:" << nfp << ", 信息接收失败了, 1.0, nfp=" << nfp << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    buffer[recbytes]='\0';
    info = buffer;
    size = recbytes;
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 1.0, 长度:" << size);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            if(size == (int)info.length())
            {
                WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 1.0, 内容:" << info << ", 长度:" << size);
            }
            else
            {
                WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 1.0, 内容:二进制内容-忽略显示, 长度:" << size);
            }
            break;
        }
    }
    return true;
}

inline bool wnh_tcp_server::accept_info(const int nfp, char * & info, int & size) //接收一条信息
{
    int recbytes;
    if(-1 == (recbytes = read(nfp, info, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("nfp:" << nfp << ", 信息接收失败了, 2.0, nfp=" << nfp << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    info[recbytes]='\0';
    size = recbytes;
    switch(display_transfer_logs)
    {
        case DIS_TRAN_LOG_1:
        {
            WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 2.0, 长度:" << size);
            break;
        }
        case DIS_TRAN_LOG_2:
        {
            if(size == (int)strlen(info))
            {
                WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 2.0, 内容:" << info << ", 长度:" << size);
            }
            else
            {
                WNHDEBUG("nfp:" << nfp << ", 信息接收成功, 2.0, 内容:二进制内容-忽略显示, 长度:" << size);
            }
            break;
        }
    }
    return true;
}
