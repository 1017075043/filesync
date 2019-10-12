#include "wnh_tcp_server.h"

wnh_tcp_server::wnh_tcp_server()
{

}

wnh_tcp_server::~wnh_tcp_server()
{

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
        WNHERROR("信息发出失败了, 1.0, 内容:" << info << ", 长度:" << info.length() << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG("信息发出成功, 1.0, 内容:" << info << ", 长度:" << info.length());
    //close(nfp);
    return true;
}

bool wnh_tcp_server::send_info(const int nfp,const char info[TCP_INFO_SZIE]) //发出一条信息
{
    if((unsigned int)strlen(info) != write(nfp, info, strlen(info)))
    {
        WNHERROR("信息发出失败了, 2.0, 内容:" << info << ", 长度:" << strlen(info) << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG("信息发出成功, 2.0, 内容:" << info << ", 长度:" << strlen(info));
    return true;
}

bool wnh_tcp_server::send_info(const int nfp,const char info[TCP_INFO_SZIE], const int size) //发出一条信息
{
    if((unsigned int)strlen(info) != write(nfp, info, size))
    {
        WNHERROR("信息发出失败了, 2.0, 内容:" << info << ", 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG("信息发出成功, 2.0, 内容:" << info << ", 长度:" << size);
    return true;
}

//  bool wnh_tcp_server::send_info_file(const int nfp,char * &info) //发出一条信息
//  {
//      if((unsigned int)strlen(info) != write(nfp, info, strlen(info)))
//      {
//          WNHERROR("信息发出失败了, 3.0, 内容:" << info << ", 长度:" << strlen(info) << ", errno=" << errno << ", mesg=" << strerror(errno));
//          return false;
//      }
//      WNHDEBUG("信息发出成功, 3.0, 内容:" << info << ", 长度:" << strlen(info));
//      return true;
//  }

bool wnh_tcp_server::accept_info(const int nfp, string &info) //接收一条信息
{
    int recbytes;
    char buffer[TCP_INFO_SZIE]= {0};
    if(-1 == (recbytes = read(nfp, buffer, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 1.0, nfp=" << nfp << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    buffer[recbytes]='\0';
    info = buffer;
    WNHDEBUG("信息接收成功, 1.0, 内容:" << info << ", 长度:" << recbytes);
    return true;
}

bool wnh_tcp_server::accept_info(const int nfp, char * & info) //接收一条信息
{
    int recbytes;
    if(-1 == (recbytes = read(nfp, info, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 2.0, nfp=" << nfp << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    info[recbytes]='\0';
    WNHDEBUG("信息接收成功, 2.0, 内容:" << info << ", 长度:" << recbytes);
    return true;
}

bool wnh_tcp_server::accept_info(const int nfp, string &info, int & size) //接收一条信息
{
    int recbytes;
    char buffer[TCP_INFO_SZIE]= {0};
    if(-1 == (recbytes = read(nfp, buffer, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 1.0, nfp=" << nfp << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    buffer[recbytes]='\0';
    info = buffer;
    WNHDEBUG("信息接收成功, 1.0, 内容:" << info << ", 长度:" << recbytes);
    size = recbytes;
    return true;
}

bool wnh_tcp_server::accept_info(const int nfp, char * & info, int & size) //接收一条信息
{
    int recbytes;
    if(-1 == (recbytes = read(nfp, info, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 2.0, nfp=" << nfp << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    info[recbytes]='\0';
    WNHDEBUG("信息接收成功, 2.0, 内容:" << info << ", 长度:" << recbytes);
    size = recbytes;
    return true;
}

//  bool wnh_tcp_server::send_end_session_info(const int nfp) //发送结束会话信息
//  {
//      if(send_info(nfp, WNH_TCP_END_SESSION_INFO))
//      {
//          WNHDEBUG("成功发出结束会话信息, 即将关闭会话句柄数nfp=" << nfp);
//          close(nfp);
//          return true;
//      }
//      WNHDEBUG("发出结束会话信息失败了, 即将关闭会话句柄数nfp=" << nfp);
//      close(nfp);
//      return false;
//  }

//  bool wnh_tcp_server::send_start_session_info(const int nfp) //发送开始会话信息
//  {
//      if(send_info(nfp, WNH_TCP_START_SESSION_INFO))
//      {
//          WNHDEBUG("成功发送开始会话信息");
//          return true;
//      }
//      WNHDEBUG("发送开始会话信息失败了, errno=" << errno << ", mesg=" << strerror(errno));
//      return false;
//  }

bool wnh_tcp_server::accept_start_session_info(const int nfp, const string info) //接收开始会话信息
{
    if(info == WNH_TCP_START_SESSION_INFO)
    {
        if(send_info(nfp, WNH_TCP_START_SESSION_INFO))
        {
            WNHDEBUG("接收到开始会话信息,并正常回复");
            return true;
        }
        WNHERROR("接收到开始会话信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_end_session_info(const int nfp, const string info) //接收结束会话信息
{
    if(info == WNH_TCP_END_SESSION_INFO)
    {
        WNHDEBUG("接收到结束会话信息,即将关闭会话句柄数nfp=" << nfp);
        close(nfp);
        return true;
    }
    return false;
}

bool wnh_tcp_server::accept_start_send_file_info(const int nfp, const string info) //接收开始发送文件信息
{
    if(info == WNH_TCP_START_SEND_FILE_INFO)
    {
        if(send_info(nfp, WNH_TCP_START_SEND_FILE_INFO))
        {
            WNHDEBUG("接收到开始发送文件信息,并正常回复")
            return true;
        }
        WNHERROR("接收到开始发送文件信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_end_send_file_info(const int nfp, const string info) //接收结束发送文件信息
{
    if(info == WNH_TCP_END_SEND_FILE_INFO)
    {
        if(send_info(nfp, WNH_TCP_END_SEND_FILE_INFO))
        {
            WNHDEBUG("接收到结束发送文件信息,并正常回复")
            return true;
        }
        WNHERROR("接收到结束发送文件信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_start_send_file_content_info(const int nfp, const string info) //接收开始发送文件内容信息
{
    if(info == WNH_TCP_START_SEND_FILE_CONTENT_INFO)
    {
        if(send_info(nfp, WNH_TCP_START_SEND_FILE_CONTENT_INFO))
        {
            WNHDEBUG("接收到开始发送文件内容信息,并正常回复")
            return true;
        }
        WNHERROR("接收到开始发送文件内容信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_end_send_file_content_info(const int nfp, const string info) //接收结束发送文件内容信息
{
    if(info == WNH_TCP_END_SEND_FILE_CONTENT_INFO)
    {
        if(send_info(nfp, WNH_TCP_END_SEND_FILE_CONTENT_INFO))
        {
            WNHDEBUG("接收到结束发送文件内容信息,并正常回复")
            return true;
        }
        WNHERROR("接收到结束发送文件内容信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_file_content(const int nfp, const string info, const string file_name) //接收一个文件内容
{
    if(!accept_start_send_file_content_info(nfp, info))
    {
        return false;
    }
    ofstream file_info(file_name.c_str(), ios::out | ios::binary);
    if(!file_info.is_open())
    {
        WNHERROR("文件打开失败, file_name:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    else
    {
        WNHDEBUG("文件打开成功, file_name:" << file_name);
    }
    char *info_bin = new char[TCP_INFO_SZIE];
    int info_size;
    while(1)
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);
        accept_info(nfp, info_bin, info_size);//接收信息
        WNHDEBUG("接收到文件内容:" << TCP_INFO_SZIE << info_bin);
        if(accept_end_send_file_content_info(nfp, info_bin))
        {
            delete []info_bin;
            file_info.close();
            return true;
        }
        //WNHDEBUG("接收到文件内容:" << info_bin);
        file_info.write(info_bin, info_size);
        send_info(nfp, WNH_TCP_START_ACCEPT_FILE_CONTENT_INFO);
    }
    delete []info_bin;
    file_info.close();
    return true;
}

bool wnh_tcp_server::accept_file(const int nfp, const string info) //接收一个文件
{
    if(!accept_start_send_file_info(nfp, info))//判断是否为接收文件的标识语
    {
        return false;
    }
    //开始接收文件信息
    while(1)
    {
        string info;
        accept_info(nfp, info);//接收信息
        if(accept_end_send_file_info(nfp, info))//如果是接收到文件发送结束的标识语，就结束文件的接收
        {
            return true;
        }
        accept_file_content(nfp, info, "/tmp/test/b.txt");

        //send_info(nfp, info);
    }
    return false;
}

int wnh_tcp_server::test()
{
    create_socket();
    set_server_address(10051);
    server_bind();
    server_listen(5);

    while(1)
    {
        int nfp = server_accept();
        string info;
        while(nfp != -1)
        {
            if(accept_info(nfp, info))
            {
                if(accept_start_session_info(nfp, info))
                {
                    continue;
                }
                if(accept_file(nfp, info))
                {
                    continue;
                }
                if(accept_end_session_info(nfp, info))
                {
                    break;
                }
                send_info(nfp, info);
            }
            else
            {
                break;
            }
            usleep(1000);
        }
    }

    close(socket_num); //关闭套接字
    return 0;
}