#include "wnh_filesync_client_concurrent.h"

wnh_filesync_client_concurrent::wnh_filesync_client_concurrent()
{
    WNHDEBUG("wnh_filesync_client_concurrent 构造");
}

wnh_filesync_client_concurrent::wnh_filesync_client_concurrent(const string &conf_parameter)
{
    WNHDEBUG("wnh_filesync_client_concurrent 构造");
    this->conf_parameter = conf_parameter;
}

wnh_filesync_client_concurrent::wnh_filesync_client_concurrent(const int argc, const char **argv)
{
    WNHDEBUG("wnh_filesync_client_concurrent 构造");
}

wnh_filesync_client_concurrent::wnh_filesync_client_concurrent(const string &ip, const int &port)
{
    WNHDEBUG("wnh_filesync_client_concurrent 构造");
}

wnh_filesync_client_concurrent::~wnh_filesync_client_concurrent()
{
    WNHDEBUG("wnh_filesync_client_concurrent 析构");
}

void wnh_filesync_client_concurrent::core()
{
    core(this->conf_parameter);
}

void wnh_filesync_client_concurrent::core(const string &conf_parameter)
{
    client_conf.read_config_ini(conf_parameter);
    client_conf.show_configure_ini();
    vector<string> client_ip_and_port;
    wnh_check_string chk_str;
    client_ip_and_port = client_conf.get_conf("client_configure", "server_ip_port");
    for(unsigned int i = 0; i < client_ip_and_port.size(); i++)
    {
        string temp_client_ip_and_port;
        if(chk_str.is_ip_address_and_num(client_ip_and_port[i]))
        {
            thread start_start_client_pthread(&wnh_filesync_client_concurrent::start_client_s, this, client_ip_and_port[i]);
            start_start_client_pthread.detach();
            WNHINFO("成功启动连接的服务端ip:part=" << client_ip_and_port[i] << "的线程");
            sleep(1);
        }
        else
        {
            WNHINFO("无效的服务端ip:part=" << temp_client_ip_and_port << ", 忽略该配置");
        }
    }
    while(1)
    {
        sleep(1000);
    }
}

void wnh_filesync_client_concurrent::core(const string &ip, const int &port)
{
    start_client(ip, port);
}

void wnh_filesync_client_concurrent::start_client(const string &ip, const int &port)
{
    wnh_filesync_client client_status_core(ip, port);
    client_status_core.status_core();

    wnh_filesync_client client_sync_core(ip, port);
    client_sync_core.sync_core();
    //检查状态线程和同步线程
    while(client_sync_core.live_sign && client_status_core.live_sign)
    {
        sleep(1);
    }
    //当更新状态线程或者同步线程出现异常时,将这两个线程的存活标志设置为false,并使用5秒的时间等待线程结束。
    client_sync_core.live_sign = false;
    client_status_core.live_sign = false;
    sleep(5);
}

void wnh_filesync_client_concurrent::start_client_s(const string &ip_address_and_port)
{
    wnh_filesync_client client_status_core(ip_address_and_port);
    client_status_core.status_core();

    wnh_filesync_client client_sync_core(ip_address_and_port);
    client_sync_core.sync_core();
    //检查状态线程和同步线程
    while(client_sync_core.live_sign && client_status_core.live_sign)
    {
        sleep(1);
    }
    //当更新状态线程或者同步线程出现异常时,将这两个线程的存活标志设置为false,并使用5秒的时间等待线程结束。
    client_sync_core.live_sign = false;
    client_status_core.live_sign = false;
    sleep(5);
}

