#ifndef __wnh_license__
#define __wnh_license__

//  需要先在linux环境下安装libuuid-1.0.3,步骤如下
//  tar -zxvf libuuid-1.0.3.tar.gz
//  ./configure && make && make install
//  在编译连接时需要加上-luuid, 例如$(CC) -o $(EXEC) $(OBJS) $(LIB) -lcrypto -lsqlite3 -luuid

using namespace std;

#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <string>
#include <fstream>
#include <cpuid.h>
#include <map>
#include <unistd.h>
#include <sys/utsname.h>
#include <uuid/uuid.h>

#include "wnh_license_define.h"
#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_openssl/wnh_openssl.h"

class wnh_license : public wnh_base_class
{
public:
    wnh_license();
    ~wnh_license();

    //wnh_license_interfaces_info
    string get_interfaces_info(); //获取网卡信息

    //wnh_license_cpu_info
    bool get_cpu_id_by_asm(string & cpu_id); //从asm中获取cpu信息
    void parse_cpu_id(const char * file_name, const char * match_words, string & cpu_id); //解析cpu信息
    bool get_cpu_id_by_system(string & cpu_id); //从系统中获取cpu信息
    bool get_cpu_id(string & cpu_id); //获取cpu信息
    string get_cpu_id(); //获取cpu信息

    string get_sysntem_core_info(); //获取linux操作系统内核信息

    string get_uuid(); //获取uuid
    string get_server_serial_number(); //获取服务器序列号
    string create_license_file(const string & server_serial_number,const unsigned long & validity_time); //创建许可文件
    unsigned long check_license_file_effectiveness(const string & license_file); //检查许可的有效性,返回许可的有效期时间
    bool get_license_file_effectiveness(const string & license_file, string & begin_time, string & end_time, unsigned long & all_time, unsigned long & remaining_time); //获取许可的信息
};
#endif
