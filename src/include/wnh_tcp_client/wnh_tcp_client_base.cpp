 #include "wnh_tcp_client.h"

wnh_tcp_client::wnh_tcp_client()
{
    WNHDEBUG("wnh_tcp_client 构造");
    display_transfer_logs = DIS_TRAN_LOG_0;
}

wnh_tcp_client::~wnh_tcp_client()
{
    WNHDEBUG("~wnh_tcp_client 析构");
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
    WNHINFO("创建一个socket成功了,socket_num=" << socket_num);
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

bool wnh_tcp_client::unblock_connect(const string & ip, const string & port)
{
    addrinfo *result;
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    char addressString[INET6_ADDRSTRLEN];
    const char *retval = nullptr;
    if(0 != getaddrinfo(ip.c_str(), port.c_str(), &hints, &result))
    {
        return false;
    }
    for(addrinfo *addr = result; addr != nullptr; addr = addr->ai_next)
    {
        socket_num = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if(socket_num == -1)
        {
            WNHERROR("创建一个socket失败了, errno=" << errno << ", mesg=" << strerror(errno));
            continue;
        }
        if(connect(socket_num, addr->ai_addr, addr->ai_addrlen) != -1)
        {
            switch(addr->ai_family) {
                case AF_INET:
                {
                    retval = inet_ntop(addr->ai_family, &(reinterpret_cast<sockaddr_in *>(addr->ai_addr)->sin_addr), addressString, INET6_ADDRSTRLEN);
                    break;
                }
                case AF_INET6:
                {
                    retval = inet_ntop(addr->ai_family, &(reinterpret_cast<sockaddr_in6 *>(addr->ai_addr)->sin6_addr), addressString, INET6_ADDRSTRLEN);
                    break;
                }
                default:
                {
                    retval = nullptr;
                }
            }
            break;
        }
    }
    freeaddrinfo(result);
    if(retval == nullptr)
    {
        WNHERROR("与服务器完成非阻塞连接, 连接失败");
        return false;
    }
    else
    {
        WNHDEBUG("与服务器完成非阻塞连接, 连接成功");
        return true;
    }
}

bool wnh_tcp_client::block_connect() //阻塞的连接
{
    int ret = connect(socket_num,(struct sockaddr*)&teraccept_address, sizeof(teraccept_address));
    if(ret != -1)
    {
        WNHDEBUG("与服务器完成阻塞连接, 连接成功");
        return true;
    }
    else
    {
        WNHERROR("与服务器完成阻塞连接, 连接失败");
        return false;
    }
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

bool wnh_tcp_client::send_info(const string info) //发出一条信息
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

bool wnh_tcp_client::send_info(const char info[TCP_INFO_SZIE]) //发出一条信息
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

bool wnh_tcp_client::send_info(const string info, const int size) //发出一条信息
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

bool wnh_tcp_client::send_info(const char info[TCP_INFO_SZIE], const int size) //发出一条信息
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

bool wnh_tcp_client::accept_info(string &info) //接收一条信息
{
    if(!cheack_seesion_info_read())
    {
        info = WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID;
        WNHERROR("socket_num:" << socket_num << ", 等待超时或者会话异常, 接收信息错误" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
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

bool wnh_tcp_client::accept_info(char * &info) //接收一条信息
{
    if(!cheack_seesion_info_read())
    {
        strcpy(info, WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID);
        info[strlen(WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID)]='\0';
        WNHERROR("socket_num:" << socket_num << ", 等待超时或者会话异常, 接收信息错误" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
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

bool wnh_tcp_client::accept_info(string &info, int &size) //接收一条信息
{
    if(!cheack_seesion_info_read())
    {
        info = WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID;
        size = strlen(WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID);
        WNHERROR("socket_num:" << socket_num << ", 等待超时或者会话异常, 接收信息错误" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
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

bool wnh_tcp_client::accept_info(char * &info, int &size) //接收一条信息
{
    if(!cheack_seesion_info_read())
    {
        strcpy(info, WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID);
        size = strlen(WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID);
        info[size]='\0';
        WNHERROR("socket_num:" << socket_num << ", 等待超时或者会话异常, 接收信息错误" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
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

//  select函数简解：
//      selct 称之为多路复用IO，使用它可以让程序阻塞在select上，而非实际IO函数上.
//
//      int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
//               nfds: fd_set描述符集中 {最大描述符+1}
//            readfds: 读描述符集
//           writefds: 写描述符集
//          exceptfds: 异常描述符集
//            timeout: 超时时间，1)当timeout为NULL时，select将阻塞到有读或写或异常描述符就绪才返回。
//                              2)当timeout中tv_sec==0且tv_usec==0时，表示不等待，扫描一次马上返回。
//                              3)当timeout中tv_sec!=0且tv_usec!=0时，表示在指定时间内没有就绪描述符就返回。函数返回0
//
//  注意：
//  1）正常情况下返回就绪描述符个数！
//  2）同时会将未就绪的描述符置零，所以select每次返回后我们都应将需用监听的描述符重新添加到描述符集中。
//  3）为了可移植，当设置了超时时间时也应当从新赋值。
//  4）使用select函数尽量不要与非系统IO混用
//
//
//  以下是对描述符集操作的函数:
//      void FD_CLR(int fd, fd_set *set);
//              从描述符集set中清除描述符fd
//
//      int  FD_ISSET(int fd, fd_set *set);
//              判断描述符fd 是否在描述符集set中，是，返回非0；否，返回0
//
//      void FD_SET(int fd, fd_set *set);
//              将描述符fd 添加到描述符集set中
//
//      void FD_ZERO(fd_set *set);
//              对描述符集进行清零，当我们新定义一个描述集时，最好使用此函数进行清零，

bool wnh_tcp_client::cheack_seesion_info_read() //检查会话信息读取情况
{
    struct timeval st_timeout; //会话信息读取超时时间
    st_timeout.tv_sec = WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT; //秒
    st_timeout.tv_usec = 1; // 微秒
    int select_result = 0;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(socket_num, &readfds);//将监听套接字放到可读集合中
    select_result = select(FD_SETSIZE, &readfds, (fd_set*)0, (fd_set*)0, &st_timeout);
    if(select_result <= 0)
    {
        WNHERROR("socket_num:" << socket_num << ", 检查会话信息读取情况异常, 读就绪态描述符集个数, select_result:" << select_result);
        return false;
    }
    else
    {
        WNHDEBUG("socket_num:" << socket_num << ", 检查会话信息读取情况正常, 读就绪态描述符集个数, select_result:" << select_result);
        return true;
    }
}

bool wnh_tcp_client::cheack_seesion_info_read(const int & nfp) //检查会话信息读取情况
{
    struct timeval st_timeout; //会话信息读取超时时间
    st_timeout.tv_sec = WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT; //秒
    st_timeout.tv_usec = 1; // 微秒
    int select_result = 0;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(nfp, &readfds);//将监听套接字放到可读集合中
    select_result = select(FD_SETSIZE, &readfds, (fd_set*)0, (fd_set*)0, &st_timeout);
    if(select_result <= 0)
    {
        WNHERROR("nfp:" << nfp << ", 检查会话信息读取情况异常, 超时时间:" << WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT << ", 读就绪态描述符集个数, select_result:" << select_result);
        return false;
    }
    else
    {
        WNHDEBUG("nfp:" << nfp << ", 检查会话信息读取情况正常, 读就绪态描述符集个数, select_result:" << select_result);
        return true;
    }
}
