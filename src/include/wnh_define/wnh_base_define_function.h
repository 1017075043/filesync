//  #ifndef __wnh_base_define_function__
//  #define __wnh_base_define_function__
//
//  #include <time.h>
//  #include <unistd.h>
//  #include <thread>
//  #include <fstream>
//  #include <iostream>
//  #include <errno.h>
//  #include <stdlib.h>
//  #include <stdio.h>
//  #include <sys/types.h>
//  #include <sys/stat.h>
//  #include <fcntl.h>
//  #include <string.h>
//  #include <signal.h>
//
//  #include "wnh_base_define.h"
//
//  char LOCALTIME[LOCALTIMELENGTH];
//  int LOGLEVELSWITCH[4];
//  ofstream WNH_LOGS_FILE;    //创建日志文件操作对象
//
//
//
//  void GETSYSTEMLOCALTIMESON()//获取当前时间,并存放LOCALTIME这个全局变量中
//  {
//      time_t t;
//      while(1)
//      {
//          t = time(0);
//          //strftime(LOCALTIME, LOCALTIMELENGTH, "%Y/%m/%d %X", localtime(&t));
//          strftime(LOCALTIME, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
//          usleep(GETSYSTEMLOCALTIMESONUSEINTERVAL);
//      }
//  }
//
//  void SETLOGLEVELSWITCH() //设置日志输出等级
//  {
//      LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_N;
//      if(LOGLEVEL == WNH_DEBUG_S)
//      {
//          LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_S;
//          WNHDEBUG("设置日志等级为 WNH_DEBUG_S");
//          return;
//      }
//      if(LOGLEVEL == WNH_INFO_S)
//      {
//          LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_S;
//          WNHDEBUG("设置日志等级为 WNH_INFO_S");
//          return;
//      }
//      if(LOGLEVEL == WNH_WARN_S)
//      {
//          LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_S;
//          WNHDEBUG("设置日志等级为 WNH_WARN_S");
//          return;
//      }
//      if(LOGLEVEL == WNH_ERROR_S)
//      {
//          LOGLEVELSWITCH[3] = WNH_LOGS_MODE_S;
//          WNHDEBUG("设置日志等级为 WNH_ERROR_S");
//          return;
//      }
//      if(LOGLEVEL == WNH_DEBUG_XS)
//      {
//          LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XS;
//          WNHDEBUG("设置日志等级为 WNH_DEBUG_XS");
//          return;
//      }
//      if(LOGLEVEL == WNH_INFO_XS)
//      {
//          LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XS;
//          WNHDEBUG("设置日志等级为 WNH_INFO_XS");
//          return;
//      }
//      if(LOGLEVEL == WNH_WARN_XS)
//      {
//          LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XS;
//          WNHDEBUG("设置日志等级为 WNH_WARN_XS");
//          return;
//      }
//      if(LOGLEVEL == WNH_ERROR_XS)
//      {
//          LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XS;
//          WNHDEBUG("设置日志等级为 WNH_ERROR_XS");
//          return;
//      }
//
//      if(LOGLEVEL == WNH_DEBUG_W)
//      {
//          LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_W;
//          WNHDEBUG("设置日志等级为 WNH_DEBUG_W");
//          return;
//      }
//      if(LOGLEVEL == WNH_INFO_W)
//      {
//          LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_W;
//          WNHDEBUG("设置日志等级为 WNH_INFO_W");
//          return;
//      }
//      if(LOGLEVEL == WNH_WARN_W)
//      {
//          LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_W;
//          WNHDEBUG("设置日志等级为 WNH_WARN_W");
//          return;
//      }
//      if(LOGLEVEL == WNH_ERROR_W)
//      {
//          LOGLEVELSWITCH[3] = WNH_LOGS_MODE_W;
//          WNHDEBUG("设置日志等级为 WNH_ERROR_W");
//      }
//      if(LOGLEVEL == WNH_DEBUG_XW)
//      {
//          LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XW;
//          WNHDEBUG("设置日志等级为 WNH_DEBUG_XW");
//          return;
//      }
//      if(LOGLEVEL == WNH_INFO_XW)
//      {
//          LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XW;
//          WNHDEBUG("设置日志等级为 WNH_INFO_XW");
//          return;
//      }
//      if(LOGLEVEL == WNH_WARN_XW)
//      {
//          LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XW;
//          WNHDEBUG("设置日志等级为 WNH_WARN_XW");
//          return;
//      }
//      if(LOGLEVEL == WNH_ERROR_XW)
//      {
//          LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XW;
//          WNHDEBUG("设置日志等级为 WNH_ERROR_XW");
//          return;
//      }
//
//      if(LOGLEVEL == WNH_DEBUG_SW)
//      {
//          LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_SW;
//          WNHDEBUG("设置日志等级为 debug_sw");
//          return;
//      }
//      if(LOGLEVEL == WNH_INFO_SW)
//      {
//          LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_SW;
//          WNHDEBUG("设置日志等级为 WNH_INFO_SW");
//          return;
//      }
//      if(LOGLEVEL == WNH_WARN_SW)
//      {
//          LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_SW;
//          WNHDEBUG("设置日志等级为 WNH_WARN_SW");
//          return;
//      }
//      if(LOGLEVEL == WNH_ERROR_SW)
//      {
//          LOGLEVELSWITCH[3] = WNH_LOGS_MODE_SW;
//          WNHDEBUG("设置日志等级为 WNH_ERROR_SW");
//          return;
//      }
//      if(LOGLEVEL == WNH_DEBUG_XSW)
//      {
//          LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XSW;
//          WNHDEBUG("设置日志等级为 WNH_DEBUG_XSW");
//          return;
//      }
//      if(LOGLEVEL == WNH_INFO_XSW)
//      {
//          LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XSW;
//          WNHDEBUG("设置日志等级为 WNH_INFO_XSW");
//          return;
//      }
//      if(LOGLEVEL == WNH_WARN_XSW)
//      {
//          LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XSW;
//          WNHDEBUG("设置日志等级为 WNH_WARN_XSW");
//          return;
//      }
//      if(LOGLEVEL == WNH_ERROR_XSW)
//      {
//          LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XSW;
//          WNHDEBUG("设置日志等级为 WNH_ERROR_XSW");
//          return;
//      }
//  }
//
//  void set_logs_mode(const string mode) //设置日志输出等级
//  {
//      if(mode == "WNH_DEBUG_S")
//      {
//          LOGLEVEL = WNH_DEBUG_S;
//      }
//      else if(mode == "WNH_INFO_S")
//      {
//          LOGLEVEL = WNH_INFO_S;
//      }
//      else if(mode == "WNH_WARN_S")
//      {
//          LOGLEVEL = WNH_WARN_S;
//      }
//      else if(mode == "WNH_ERROR_S")
//      {
//          LOGLEVEL = WNH_ERROR_S;
//      }
//      else if(mode == "WNH_DEBUG_XS")
//      {
//          LOGLEVEL = WNH_DEBUG_XS;
//      }
//      else if(mode == "WNH_INFO_XS")
//      {
//          LOGLEVEL = WNH_INFO_XS;
//      }
//      else if(mode == "WNH_WARN_XS")
//      {
//          LOGLEVEL = WNH_WARN_XS;
//      }
//      else if(mode == "WNH_ERROR_XS")
//      {
//          LOGLEVEL = WNH_ERROR_XS;
//      }
//      else if(mode == "WNH_DEBUG_W")
//      {
//          LOGLEVEL = WNH_DEBUG_W;
//      }
//      else if(mode == "WNH_INFO_W")
//      {
//          LOGLEVEL = WNH_INFO_W;
//      }
//      else if(mode == "WNH_WARN_W")
//      {
//          LOGLEVEL = WNH_WARN_W;
//      }
//      else if(mode == "WNH_ERROR_W")
//      {
//          LOGLEVEL = WNH_ERROR_W;
//      }
//      else if(mode == "WNH_DEBUG_XW")
//      {
//          LOGLEVEL = WNH_DEBUG_XW;
//      }
//      else if(mode == "WNH_INFO_XW")
//      {
//          LOGLEVEL = WNH_INFO_XW;
//      }
//      else if(mode == "WNH_WARN_XW")
//      {
//          LOGLEVEL = WNH_WARN_XW;
//      }
//      else if(mode == "WNH_ERROR_XW")
//      {
//          LOGLEVEL = WNH_ERROR_XW;
//      }
//      else if(mode == "WNH_DEBUG_SW")
//      {
//          LOGLEVEL = WNH_DEBUG_SW;
//      }
//      else if(mode == "WNH_INFO_SW")
//      {
//          LOGLEVEL = WNH_INFO_SW;
//      }
//      else if(mode == "WNH_WARN_SW")
//      {
//          LOGLEVEL = WNH_WARN_SW;
//      }
//      else if(mode == "WNH_ERROR_SW")
//      {
//          LOGLEVEL = WNH_ERROR_SW;
//      }
//      else if(mode == "WNH_DEBUG_XSW")
//      {
//          LOGLEVEL = WNH_DEBUG_XSW;
//      }
//      else if(mode == "WNH_INFO_XSW")
//      {
//          LOGLEVEL = WNH_INFO_XSW;
//      }
//      else if(mode == "WNH_WARN_XSW")
//      {
//          LOGLEVEL = WNH_WARN_XSW;
//      }
//      else if(mode == "WNH_ERROR_XSW")
//      {
//          LOGLEVEL = WNH_ERROR_XSW;
//      }
//      SETLOGLEVELSWITCH(); //设置日志输出等级
//  }
//
//  bool check_process_pid(const char * pid_file)
//  {
//      struct stat stb;
//      FILE *pidfile;
//      if (stat(pid_file, &stb) == 0)
//      {
//          pidfile = fopen(pid_file, "r");
//          if (pidfile)
//          {
//              char buf[64];
//              pid_t pid = 0;
//              memset(buf, 0, sizeof(buf));
//              if (fread(buf, 1, sizeof(buf), pidfile))
//              {
//                  buf[sizeof(buf) - 1] = '\0';
//                  pid = atoi(buf);
//              }
//              fclose(pidfile);
//              if (pid && kill(pid, 0) == 0)
//              {
//                  WNHDEBUG("程序正在运行中,pid:" << pid);
//                  return true;
//              }
//          }
//          WNHDEBUG("删除" << STARTER_PID_FILE_DEFAULT << ",程序没有在运行");
//          unlink(pid_file);
//      }
//      return false;
//  }
//
//  bool check_process_exist(const char * pid_file)
//  {
//      if(check_process_pid(pid_file))
//      {
//          return true;
//      }
//      FILE *fd = fopen(pid_file, "w");
//      if(fd)
//      {
//          fprintf(fd, "%u\n", getpid());
//          fclose(fd);
//          WNHDEBUG("程序启动,PID:" << getpid() << " 写入" << pid_file  << "文件完成");
//      }
//      return false;
//  }
//
//  void INIT()//程序初始化函数
//  {
//
//      time_t t;
//      t = time(0);
//      strftime(LOCALTIME, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
//
//      SETLOGLEVELSWITCH(); //设置日志输出等级
//
//      //当程序已经被启动过,则进入阻塞,一直到进程结束后,进程才正常启动
//      while(check_process_exist(STARTER_PID_FILE_DEFAULT))
//      {
//          sleep(1);
//      }
//
//      //日志追加输出
//      WNH_LOGS_FILE.open(WNH_LOGS_FILE_NAME, ios::out | ios::app);
//      //每一次启动都清空原先的日志
//      //WNH_LOGS_FILE.open(WNH_LOGS_FILE_NAME, ios::out | ios::app | ios::trunc);
//      if(!WNH_LOGS_FILE.is_open())
//      {
//          WNHERROR("打开日志文件" << WNH_LOGS_FILE_NAME <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
//          exit(1);
//      }
//
//      WNHDEBUG("┌────────────────────────────────────────────┐");
//      WNHDEBUG("│              欢迎使用filesync              │");
//      WNHDEBUG("└────────────────────────────────────────────┘");
//
//      std::thread get_local_time(GETSYSTEMLOCALTIMESON);
//      get_local_time.detach();
//      return;
//  }
//
//  #endif