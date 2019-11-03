#ifndef __wnh_filesync_client_concurrent__
#define __wnh_filesync_client_concurrent__

using namespace std;

#include "../wnh_config_ini/wnh_config_ini.h"
#include "../wnh_filesync_client/wnh_filesync_client.h"
#include "../wnh_check_string/wnh_check_string.h"

class wnh_filesync_client_concurrent : public wnh_base_class
{
public:
    wnh_config_ini client_conf;
    string conf_parameter;

public:
    wnh_filesync_client_concurrent();
    wnh_filesync_client_concurrent(const string & conf_parameter);
    wnh_filesync_client_concurrent(const int argc, const char **argv);
    wnh_filesync_client_concurrent(const string & ip, const int & port);
    ~wnh_filesync_client_concurrent();

    void core();
    void core(const string &ip, const int &port);
    void core(const string &conf_parameter);
    void start_client(const string &ip, const int &port); //启动客户端线程
    void start_client_s(const string &ip_address_and_port); //启动客户端线程
};

#endif
