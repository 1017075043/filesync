#ifndef __wnh_base_define__
#define __wnh_base_define__

#include <iostream>
#include <string.h>
#include <thread>
#include <errno.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <sstream>
#include <mutex>
#include <list>

#define PROGRAM_NAME "filesync v1.0.1"

#define LOCALTIMELENGTH 20    //记录实时的系统当前时间的数组的长度
#define GETSYSTEMLOCALTIMESONUSEINTERVAL 1000*100*5   //记录实时的系统当前时间的运行间隔,执行间隔1000*100*5=0.5秒
#define TIMEDISPLAYFORMAT "%Y/%m/%d %H:%M:%S"   //时间显示格式

#define WNH_LOGS_FILE_NAME "filesync.log"    //日志文件名称

extern int LOGLEVEL;  //记录日志等级
extern char LOCALTIME[LOCALTIMELENGTH];    //记录实时的系统当前时间
extern ofstream WNH_LOGS_FILE;    //创建日志文件操作对象
extern int LOGLEVELSWITCH[4];  //调试日志的输出--20190523
extern bool GETSYSTEMLOCALTIMESONID; //记录实时的系统当前时间线程运行标志
extern unsigned long LOCALTIMENUM; //记录当前时间的时间戳
extern mutex LOGS_MUTEX_LOCK; //日志输出线程互斥锁

#include "wnh_display_style_define.h" //可以控制控shell输出时的颜色
#include "wnh_base_logs_define.h" //日志输出定义

#endif
