#ifndef __wnh_filesync_init__
#define __wnh_filesync_init__

#include <time.h>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <string>

using namespace std;

#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_define/wnh_filesync_info_define.h"

class wnh_filesync_init : public wnh_base_class
{
private:

public:
    wnh_filesync_init();
    ~wnh_filesync_init();
    void MY_PRAYER(); //佛祖保佑,永无BUG
    void version_control_and_copyright_start(); //版本控制和版权说明
    void version_control_and_copyright_stop(); //版本控制和版权说明
    void GETSYSTEMLOCALTIMESON();//获取当前时间,并存放LOCALTIME这个全局变量中
    void SETLOGLEVELSWITCH(); //设置日志输出等级
    void set_logs_mode(const string mode); //设置日志输出等级
    static int change_logs_lever(const string & mode); //转换日志等级
    bool check_process_pid(const char * pid_file); //检查进程号是否存在
    bool check_process_exist(const char * pid_file); //检查程序是否已经启动
    void INIT();//程序初始化函数
};

#endif
