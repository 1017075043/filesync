#include "wnh_tcp_client.h"

wnh_tcp_client::wnh_tcp_client()
{

}

wnh_tcp_client::~wnh_tcp_client()
{

}

int wnh_tcp_client::set_non_blocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

bool wnh_tcp_client::create_socket() //创建一个socket,返回句柄数
{
    //AF_INET 使用IPv4协议
    //SOCK_STREAM 使用TCP来进行通行
    socket_num = socket( PF_INET, SOCK_STREAM, 0 );
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
    bzero( &teraccept_address, sizeof( teraccept_address ) );
    teraccept_address.sin_family = AF_INET;
    inet_pton( AF_INET, this->ip.c_str(), &teraccept_address.sin_addr );
    teraccept_address.sin_port = htons( this->portnum );
}

bool wnh_tcp_client::unblock_connect(int time) //非阻塞的连接
{
    int ret = 0;
    int fdopt = set_non_blocking( socket_num );
    ret = connect( socket_num, ( struct sockaddr* )&teraccept_address, sizeof( teraccept_address ) );
    WNHDEBUG("连接状态码, ret=" << ret);
    if ( ret == 0 )
    {
        WNHDEBUG("立即与服务器完成非阻塞连接, 连接成功");
        fcntl( socket_num, F_SETFL, fdopt );   //set old optional back
        return true;
    }
    //unblock mode --> connect return immediately! ret = -1 & errno=EINPROGRESS
    else if ( errno != EINPROGRESS )
    {
        WNHERROR("与服务器非阻塞连接失败了, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    else if (errno == EINPROGRESS)
    {
        WNHDEBUG("正在与服务器进行非阻塞连接, 请等待!");
    }

    //use select to check write event, if the socket is writable, then
    //connect is complete successfully!
    fd_set readfds;
    fd_set writefds;
    struct timeval timeout;

    FD_ZERO( &readfds );
    FD_SET( socket_num, &writefds );

    timeout.tv_sec = time; //timeout is 10 minutes
    timeout.tv_usec = 0;

    ret = select( socket_num + 1, nullptr, &writefds, nullptr, &timeout );
    if ( ret <= 0 )
    {
        WNHERROR("正在与服务器进行非阻塞连接, 连接超时了, 连接时间time=" << time << ", errno=" << errno << ", mesg=" << strerror(errno));
        close( socket_num );
        return false;
    }

    if ( ! FD_ISSET( socket_num, &writefds  ) )
    {
        WNHERROR("正在与服务器进行非阻塞连接, 连接失败了, 在socket_num上找不到事件, errno=" << errno << ", mesg=" << strerror(errno));
        close( socket_num );
        return false;
    }

    int error = 0;
    socklen_t length = sizeof( error );
    if( getsockopt( socket_num, SOL_SOCKET, SO_ERROR, &error, &length ) < 0 )
    {
        WNHERROR("正在与服务器进行非阻塞连接, 连接失败了, 获取套接字选项失败, errno=" << errno << ", mesg=" << strerror(errno));
        close( socket_num );
        return false;
    }

    if( error != 0 )
    {
        WNHERROR("正在与服务器进行非阻塞连接, 连接失败了, errno=" << errno << ", mesg=" << strerror(errno));
        close( socket_num );
        return false;
    }

    //connection successful!
    WNHDEBUG("与服务器完成非阻塞连接, 连接成功");
    fcntl( socket_num, F_SETFL, fdopt ); //set old optional back
    return true;
}

bool wnh_tcp_client::send_info(const string info) //发出一条信息
{
    if((unsigned int)info.length() != write(socket_num, info.c_str(), info.length()))
    {
        WNHERROR("信息发出失败了, 1.0, 内容:" << info << ", 长度:" << info.length() << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG("信息发出成功, 1.0, 内容:" << info << ", 长度:" << info.length());
    return true;
}

bool wnh_tcp_client::send_info(const char info[TCP_INFO_SZIE]) //发出一条信息
{
    if((unsigned int)strlen(info) != write(socket_num, info, strlen(info)))
    {
        WNHERROR("信息发出失败了, 2.0, 内容:" << info << ", 长度:" << strlen(info) << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG("信息发出成功, 2.0, 内容:" << info << ", 长度:" << strlen(info));
    return true;
}

bool wnh_tcp_client::send_info(const char info[TCP_INFO_SZIE], const int size) //发出一条信息
{
    if(size != write(socket_num, info, size))
    {
        WNHERROR("信息发出失败了, 2.0, 内容:" << info << ", 长度:" << size << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    WNHDEBUG("信息发出成功, 2.0, 内容:" << info << ", 长度:" << size);
    return true;
}

//  bool wnh_tcp_client::send_info_file(char * &info) //发出一条信息
//  {
//      if((unsigned int)strlen(info) != write(socket_num, info, strlen(info)))
//      {
//          WNHERROR("信息发出失败了, 3.0, 内容:" << info << ", 长度:" << strlen(info) << ", errno=" << errno << ", mesg=" << strerror(errno));
//          return false;
//      }
//      WNHDEBUG("信息发出成功, 3.0, 内容:" << info << ", 长度:" << strlen(info));
//      return true;
//  }

bool wnh_tcp_client::accept_info(string &info) //接收一条信息
{
    int recbytes;
    char buffer[TCP_INFO_SZIE]= {0};

    if(-1 == (recbytes = read(socket_num, buffer, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 1.0, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    buffer[recbytes]='\0';
    info = buffer;
    WNHDEBUG("信息接收成功, 1.0,内容:" << info << ", 长度:" << info.length());
    return true;
}

bool wnh_tcp_client::accept_info(char * &info) //接收一条信息
{
    int recbytes;
    if(-1 == (recbytes = read(socket_num, info, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 2.0, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    info[recbytes]='\0';
    WNHDEBUG("信息接收成功, 2.0, 内容:" << info << ", 长度:" << strlen(info));
    return true;
}

bool wnh_tcp_client::accept_info(string &info, int &size) //接收一条信息
{
    int recbytes;
    char buffer[TCP_INFO_SZIE]= {0};

    if(-1 == (recbytes = read(socket_num, buffer, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 1.0, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    buffer[recbytes]='\0';
    info = buffer;
    WNHDEBUG("信息接收成功, 1.0,内容:" << info << ", 长度:" << recbytes);
    size = recbytes;
    return true;
}

bool wnh_tcp_client::accept_info(char * &info, int &size) //接收一条信息
{
    int recbytes;
    if(-1 == (recbytes = read(socket_num, info, TCP_INFO_SZIE)))  //接收数据
    {
        WNHERROR("信息接收失败了, 2.0, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    info[recbytes]='\0';
    WNHDEBUG("信息接收成功, 2.0, 内容:" << info << ", 长度:" << recbytes);
    size = recbytes;
    return true;
}

bool wnh_tcp_client::send_start_session_info() //发送开始会话信息
{
    if(send_info(WNH_TCP_START_SESSION_INFO))
    {
        string info;
        accept_info(info);
        if(info == WNH_TCP_START_SESSION_INFO)
        {
            WNHDEBUG("成功发送开始会话信息,并得到的正常回复");
            return true;
        }
        else
        {
            WNHERROR("成功发送开始会话信息,但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR("发送开始会话信息失败了, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_tcp_client::send_end_session_info() //发送结束会话信息
{
    if(send_info(WNH_TCP_END_SESSION_INFO))
    {
        close(socket_num);
        WNHDEBUG("成功发出结束会话信息, 即将关闭会话句柄数socket_num=" << socket_num);
        return true;
    }
    close(socket_num);
    WNHDEBUG("发出结束会话信息失败了, 即将关闭会话句柄数socket_num=" << socket_num << ", errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_tcp_client::send_start_send_file_info() //发送开始发送文件信息
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

bool wnh_tcp_client::send_end_send_file_info() //发送结束发送文件信息
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

bool wnh_tcp_client::send_start_send_file_content_info() //发送开始发送文件内容信息
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

bool wnh_tcp_client::send_end_send_file_content_info() //发送结束发送文件内容信息
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

bool wnh_tcp_client::accept_send_file_content_result() //接收发送文件内容结果
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
        WNHERROR("文件打开失败, file_name:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }
    else
    {
        WNHDEBUG("文件打开成功, file_name:" << file_name);
    }
    file_info.seekg(0, ios::beg);
    char info_bin[TCP_INFO_SZIE];
    while(!file_info.eof())
    {
        memset(info_bin, '\0', TCP_INFO_SZIE);
        file_info.read(info_bin, TCP_INFO_SZIE - TCP_INFO_SZIE_RESERVE);
        WNHDEBUG("读取长度:" << file_info.gcount());
        send_info(info_bin, file_info.gcount());
        if(!accept_send_file_content_result())
        {
            break;
        }
    }
    file_info.close();

    if(!send_end_send_file_content_info())
    {
        return false;
    }
    return true;
}

//  bool wnh_tcp_client::send_file_content(const string file_name) //发送一个文件的内容
//  {
//      if(!send_start_send_file_content_info())
//      {
//          return false;
//      }
//
//      //发送文件内容
//      FILE *fq;
//      if((fq = fopen(file_name.c_str(),"rb") )== nullptr)
//      {
//          WNHERROR("文件打开失败, file_name:" << file_name << ", errno=" << errno << ", mesg=" << strerror(errno))
//          return false;
//      }
//      else
//      {
//          WNHDEBUG("文件打开成功, file_name:" << file_name);
//      }
//      char *info_bin = new char[TCP_INFO_SZIE];
//      int read_len;
//      while(!feof(fq)){
//           bzero(info_bin, sizeof(info_bin));
//          read_len = fread(info_bin, 1, sizeof(info_bin), fq);
//          WNHDEBUG("读取到文件内容为:" << info_bin << "read_len:" << read_len);
//          if(read_len == 0)
//          {
//              continue;
//          }
//          WNHDEBUG("读取到文件内容为:" << info_bin);
//          send_info_file(info_bin);
//          if(!accept_send_file_content_result())
//          {
//              break;
//          }
//      }
//      delete []info_bin;
//      fclose(fq);
//
//      if(!send_end_send_file_content_info())
//      {
//          return false;
//      }
//      return true;
//  }

bool wnh_tcp_client::send_file(const string file_name) //发送一个文件
{
    if(!send_start_send_file_info())
    {
        return false;
    }

    send_file_content(file_name);

    if(!send_end_send_file_info())
    {
        return false;
    }
    return true;
}

int wnh_tcp_client::test()
{
    create_socket();
    set_teraccept_address("127.0.0.1", 10051);
    unblock_connect(1);
    string info;
    send_start_session_info();
    //for(int i = 0; i < 2; i++)
    //{
    //    send_info(to_string(i));
    //    accept_info(info);
    //}
    sleep(3);
    send_file("/tmp/test/a.txt");
    sleep(3);
    //for(int i = 0; i < 2; i++)
    //{
    //    send_info(to_string(i));
    //    accept_info(info);
    //}
    //sleep(3);
    //send_file();
    //sleep(3);
    send_end_session_info();
    return 0;
}
