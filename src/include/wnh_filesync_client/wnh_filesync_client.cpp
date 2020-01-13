#include "wnh_filesync_client.h"

#include "wnh_filesync_client_core.cpp"
#include "wnh_filesync_client_tcp_function.cpp"

wnh_filesync_client::wnh_filesync_client()
{
    WNHDEBUG("wnh_filesync_client 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:客户端");
    init();
    this->ip = IP;
    this->port = PORT;
    WNHINFO("服务端IP:" << this->ip << ", 端口:" << this->port);
}

wnh_filesync_client::wnh_filesync_client(const string &ip_address_and_port)
{
    WNHDEBUG("wnh_filesync_client 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:客户端");
    init();
    set_client_ip_port(ip_address_and_port);
}

void wnh_filesync_client::set_client_ip_port(const string &ip_address_and_port)
{
    this->ip = ip_address_and_port.substr(0, ip_address_and_port.find(":"));
    this->port = atoi(ip_address_and_port.substr(ip_address_and_port.find(":")+1).c_str());
    WNHINFO("服务端IP:" << this->ip << ", 端口:" << this->port);
}

wnh_filesync_client::wnh_filesync_client(const int argc, const char **argv)
{
    WNHDEBUG("wnh_filesync_client 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:客户端");
    init();
    set_client_ip_port(argc, argv);
}

void wnh_filesync_client::set_client_ip_port(const int argc, const char **argv)
{
    string ip_address_and_port = argv[2];
    this->ip = ip_address_and_port.substr(0, ip_address_and_port.find(":"));
    this->port = atoi(ip_address_and_port.substr(ip_address_and_port.find(":")+1).c_str());
    WNHINFO("服务端IP:" << this->ip << ", 端口:" << this->port);
}

wnh_filesync_client::wnh_filesync_client(const string &ip, const int &port)
{
    WNHDEBUG("wnh_filesync_client 构造");
    //WNHINFO(PROGRAM_NAME << "程序启动,启动方式:客户端");
    init();
    set_client_ip_port(ip, port);
}

void wnh_filesync_client::set_client_ip_port(const string &ip, const int &port)
{
    this->ip = ip;
    this->port = port;
    WNHINFO("服务端IP:" << this->ip << ", 端口:" << this->port);
}

wnh_filesync_client::~wnh_filesync_client()
{
    WNHDEBUG("~wnh_filesync_client 析构");
}

void wnh_filesync_client::init()
{
    ip = IP;
    port = PORT;
    live_sign = true;
    singleton_core_thread_flag = true;
}


