#ifndef __wnh_license__
#define __wnh_license__

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

#include "wnh_license_define.h"
#include "../wnh_base_class/wnh_base_class.h"

class wnh_license : public wnh_base_class
{
public:
    wnh_license();
    ~wnh_license();

    string get_interfaces_info(); //获取网卡信息
    string get_cpu_id_by_asm(); //获取cpu信息
};
#endif
