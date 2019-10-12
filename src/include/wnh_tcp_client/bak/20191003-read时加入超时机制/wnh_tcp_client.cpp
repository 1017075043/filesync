#include "wnh_tcp_client.h"
#include "wnh_tcp_client_base.cpp"
#include "wnh_tcp_client_download_file.cpp"
#include "wnh_tcp_client_send_file.cpp"
#include "wnh_tcp_client_telnet.cpp"

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

int wnh_tcp_client::test()
{
    return test("127.0.0.1");
}

int wnh_tcp_client::test(const string & ip)
{
    create_socket();
    set_teraccept_address(ip.c_str(), 10051);
    unblock_connect(1);
    string info;
    send_start_session_info();

    for(int i = 0; i < 5; i++)
    {
        for(int i = 0; i < 5; i++)
        {
            send_info(to_string(i));
            accept_info(info);
            WNHDEBUG("回复信息:" << info);
            sleep(1);
        }
        send_file("/tmp/test/a.txt");
        sleep(1);
        download_file("/tmp/test/v.tar.gz", "/tmp/test/temp_file_name.tar.gz");
        sleep(20);
    }

    for(int i = 1; i > 0; i--)
    {
        WNHDEBUG("等待此次会话结束剩余:" << i << "秒");
        sleep(1);
    }

    send_end_session_info();
    return 0;
}
