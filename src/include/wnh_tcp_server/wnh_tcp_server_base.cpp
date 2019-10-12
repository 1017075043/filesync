#include "wnh_tcp_server.h"

wnh_tcp_server::wnh_tcp_server()
{
    survival_id = true; //标志位存活状态
    tcp_listen_conturrent_now_num = 0;
    display_transfer_logs = DIS_TRAN_LOG_2;
}

wnh_tcp_server::wnh_tcp_server(bool inherit)
{

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

bool wnh_tcp_server::send_info(const int nfp, const string info) //发出一条信息
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

bool wnh_tcp_server::send_info(const int nfp,const char info[TCP_INFO_SZIE]) //发出一条信息
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

bool wnh_tcp_server::send_info(const int nfp, const string info, const int size) //发出一条信息
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

bool wnh_tcp_server::send_info(const int nfp,const char info[TCP_INFO_SZIE], const int size) //发出一条信息
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

bool wnh_tcp_server::accept_info(const int nfp, string & info) //接收一条信息
{
    if(!cheack_seesion_info_read(nfp))
    {
        info = WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID;
        WNHERROR("nfp:" << nfp << ", 等待超时或者会话异常, 接收信息错误" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
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
    //update_session_last_update_time(nfp);
    return true;
}

bool wnh_tcp_server::accept_info(const int nfp, char * & info) //接收一条信息
{
    if(!cheack_seesion_info_read(nfp))
    {
        strcpy(info, WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID);
        info[strlen(WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID)]='\0';
        WNHERROR("nfp:" << nfp << ", 等待超时或者会话异常, 接收信息错误" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
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
    //update_session_last_update_time(nfp);
    return true;
}

bool wnh_tcp_server::accept_info(const int nfp, string & info, int & size) //接收一条信息
{
    if(!cheack_seesion_info_read(nfp))
    {
        info = WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID;
        size = strlen(WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID);
        WNHERROR("nfp:" << nfp << ", 等待超时或者会话异常, 接收信息错误" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
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
    //update_session_last_update_time(nfp);
    return true;
}

bool wnh_tcp_server::accept_info(const int nfp, char * & info, int & size) //接收一条信息
{
    if(!cheack_seesion_info_read(nfp))
    {
        strcpy(info, WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID);
        size = strlen(WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID);
        info[size]='\0';
        WNHERROR("nfp:" << nfp << ", 等待超时或者会话异常, 接收信息错误" << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
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
    //update_session_last_update_time(nfp);
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

bool wnh_tcp_server::cheack_seesion_info_read(const int & nfp) //检查会话信息读取情况
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
