#ifndef __wnh_check_string__
#define __wnh_check_string__

using namespace std;

#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_filesync_init/wnh_filesync_init.h"

class wnh_check_string : public wnh_base_class
{
public:
    wnh_check_string();
    ~wnh_check_string();

    bool is_ip_address(const string & ip_address);//检查ip_address是否有效的IP地址
    bool is_num(const string & num);//检查num是否有效的数字
    bool is_ip_address_and_num(const string & ip_address_and_num);//检查ip_address_and_num是否有效的IP地址和PORT
    bool is_logs_level(const string & logs_level);//检查logs_level是否有效的日子等级
};
#endif
