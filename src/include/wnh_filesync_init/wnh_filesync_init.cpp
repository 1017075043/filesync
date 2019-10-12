#include "wnh_filesync_init.h"

char LOCALTIME[LOCALTIMELENGTH];
int LOGLEVELSWITCH[4];
bool GETSYSTEMLOCALTIMESONID;
ofstream WNH_LOGS_FILE;    //创建日志文件操作对象
unsigned long LOCALTIMENUM; //记录当前时间的时间戳
mutex LOGS_MUTEX_LOCK;


//WNH_DEBUG_S, WNH_INFO_S, WNH_WARN_S, WNH_ERROR_S, WNH_DEBUG_XS, WNH_INFO_XS, WNH_WARN_XS, WNH_ERROR_XS
//WNH_DEBUG_W, WNH_INFO_W, WNH_WARN_W, WNH_ERROR_W, WNH_DEBUG_XW, WNH_INFO_XW, WNH_WARN_XW, WNH_ERROR_XW
//WNH_DEBUG_SW, WNH_INFO_SW, WNH_WARN_SW, WNH_ERROR_SW, WNH_DEBUG_XSW, WNH_INFO_XSW, WNH_WARN_XSW, WNH_ERROR_XSW
int LOGLEVEL = WNH_INFO_XS;


wnh_filesync_init::wnh_filesync_init()
{
    //INIT();
}

wnh_filesync_init::~wnh_filesync_init()
{
    GETSYSTEMLOCALTIMESONID = false;
    if(LOGLEVEL != WNH_DEBUG_S && LOGLEVEL != WNH_INFO_S && LOGLEVEL != WNH_WARN_S && LOGLEVEL != WNH_ERROR_S && LOGLEVEL != WNH_DEBUG_XS && LOGLEVEL != WNH_INFO_XS && LOGLEVEL != WNH_WARN_XS && LOGLEVEL != WNH_ERROR_XS)
    {
        WNH_LOGS_FILE.close();
    }
    usleep(GETSYSTEMLOCALTIMESONUSEINTERVAL+100);
    //将xhel打印字体颜色进行重置成白色
    //cout << WNH_COLOR_WHITE << endl;
}

void wnh_filesync_init::GETSYSTEMLOCALTIMESON()//获取当前时间,并存放LOCALTIME这个全局变量中
{
    time_t t;
    WNHDEBUG("记录实时的系统当前时间线程开始运行");
    while(GETSYSTEMLOCALTIMESONID)
    {
        t = time(0);
        LOCALTIMENUM = (unsigned long)t;
        strftime(LOCALTIME, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
        usleep(GETSYSTEMLOCALTIMESONUSEINTERVAL);
    }
    WNHDEBUG("记录实时的系统当前时间线程即将结束运行");
}

void wnh_filesync_init::SETLOGLEVELSWITCH() //设置日志输出等级
{
    LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_N;
    if(LOGLEVEL == WNH_DEBUG_S)
    {
        LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_S;
        WNHDEBUG("设置日志等级为 WNH_DEBUG_S");
        return;
    }
    if(LOGLEVEL == WNH_INFO_S)
    {
        LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_S;
        WNHDEBUG("设置日志等级为 WNH_INFO_S");
        return;
    }
    if(LOGLEVEL == WNH_WARN_S)
    {
        LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_S;
        WNHDEBUG("设置日志等级为 WNH_WARN_S");
        return;
    }
    if(LOGLEVEL == WNH_ERROR_S)
    {
        LOGLEVELSWITCH[3] = WNH_LOGS_MODE_S;
        WNHDEBUG("设置日志等级为 WNH_ERROR_S");
        return;
    }
    if(LOGLEVEL == WNH_DEBUG_XS)
    {
        LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XS;
        WNHDEBUG("设置日志等级为 WNH_DEBUG_XS");
        return;
    }
    if(LOGLEVEL == WNH_INFO_XS)
    {
        LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XS;
        WNHDEBUG("设置日志等级为 WNH_INFO_XS");
        return;
    }
    if(LOGLEVEL == WNH_WARN_XS)
    {
        LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XS;
        WNHDEBUG("设置日志等级为 WNH_WARN_XS");
        return;
    }
    if(LOGLEVEL == WNH_ERROR_XS)
    {
        LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XS;
        WNHDEBUG("设置日志等级为 WNH_ERROR_XS");
        return;
    }
    if(LOGLEVEL == WNH_DEBUG_W)
    {
        LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_W;
        WNHDEBUG("设置日志等级为 WNH_DEBUG_W");
        return;
    }
    if(LOGLEVEL == WNH_INFO_W)
    {
        LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_W;
        WNHDEBUG("设置日志等级为 WNH_INFO_W");
        return;
    }
    if(LOGLEVEL == WNH_WARN_W)
    {
        LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_W;
        WNHDEBUG("设置日志等级为 WNH_WARN_W");
        return;
    }
    if(LOGLEVEL == WNH_ERROR_W)
    {
        LOGLEVELSWITCH[3] = WNH_LOGS_MODE_W;
        WNHDEBUG("设置日志等级为 WNH_ERROR_W");
    }
    if(LOGLEVEL == WNH_DEBUG_XW)
    {
        LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XW;
        WNHDEBUG("设置日志等级为 WNH_DEBUG_XW");
        return;
    }
    if(LOGLEVEL == WNH_INFO_XW)
    {
        LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XW;
        WNHDEBUG("设置日志等级为 WNH_INFO_XW");
        return;
    }
    if(LOGLEVEL == WNH_WARN_XW)
    {
        LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XW;
        WNHDEBUG("设置日志等级为 WNH_WARN_XW");
        return;
    }
    if(LOGLEVEL == WNH_ERROR_XW)
    {
        LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XW;
        WNHDEBUG("设置日志等级为 WNH_ERROR_XW");
        return;
    }

    if(LOGLEVEL == WNH_DEBUG_SW)
    {
        LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_SW;
        WNHDEBUG("设置日志等级为 debug_sw");
        return;
    }
    if(LOGLEVEL == WNH_INFO_SW)
    {
        LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_SW;
        WNHDEBUG("设置日志等级为 WNH_INFO_SW");
        return;
    }
    if(LOGLEVEL == WNH_WARN_SW)
    {
        LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_SW;
        WNHDEBUG("设置日志等级为 WNH_WARN_SW");
        return;
    }
    if(LOGLEVEL == WNH_ERROR_SW)
    {
        LOGLEVELSWITCH[3] = WNH_LOGS_MODE_SW;
        WNHDEBUG("设置日志等级为 WNH_ERROR_SW");
        return;
    }
    if(LOGLEVEL == WNH_DEBUG_XSW)
    {
        LOGLEVELSWITCH[0] = LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XSW;
        WNHDEBUG("设置日志等级为 WNH_DEBUG_XSW");
        return;
    }
    if(LOGLEVEL == WNH_INFO_XSW)
    {
        LOGLEVELSWITCH[1] = LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XSW;
        WNHDEBUG("设置日志等级为 WNH_INFO_XSW");
        return;
    }
    if(LOGLEVEL == WNH_WARN_XSW)
    {
        LOGLEVELSWITCH[2] = LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XSW;
        WNHDEBUG("设置日志等级为 WNH_WARN_XSW");
        return;
    }
    if(LOGLEVEL == WNH_ERROR_XSW)
    {
        LOGLEVELSWITCH[3] = WNH_LOGS_MODE_XSW;
        WNHDEBUG("设置日志等级为 WNH_ERROR_XSW");
        return;
    }
}

void wnh_filesync_init::set_logs_mode(const string mode) //设置日志输出等级
{
    if(mode == "WNH_DEBUG_S")
    {
        LOGLEVEL = WNH_DEBUG_S;
    }
    else if(mode == "WNH_INFO_S")
    {
        LOGLEVEL = WNH_INFO_S;
    }
    else if(mode == "WNH_WARN_S")
    {
        LOGLEVEL = WNH_WARN_S;
    }
    else if(mode == "WNH_ERROR_S")
    {
        LOGLEVEL = WNH_ERROR_S;
    }
    else if(mode == "WNH_DEBUG_XS")
    {
        LOGLEVEL = WNH_DEBUG_XS;
    }
    else if(mode == "WNH_INFO_XS")
    {
        LOGLEVEL = WNH_INFO_XS;
    }
    else if(mode == "WNH_WARN_XS")
    {
        LOGLEVEL = WNH_WARN_XS;
    }
    else if(mode == "WNH_ERROR_XS")
    {
        LOGLEVEL = WNH_ERROR_XS;
    }
    else if(mode == "WNH_DEBUG_W")
    {
        LOGLEVEL = WNH_DEBUG_W;
    }
    else if(mode == "WNH_INFO_W")
    {
        LOGLEVEL = WNH_INFO_W;
    }
    else if(mode == "WNH_WARN_W")
    {
        LOGLEVEL = WNH_WARN_W;
    }
    else if(mode == "WNH_ERROR_W")
    {
        LOGLEVEL = WNH_ERROR_W;
    }
    else if(mode == "WNH_DEBUG_XW")
    {
        LOGLEVEL = WNH_DEBUG_XW;
    }
    else if(mode == "WNH_INFO_XW")
    {
        LOGLEVEL = WNH_INFO_XW;
    }
    else if(mode == "WNH_WARN_XW")
    {
        LOGLEVEL = WNH_WARN_XW;
    }
    else if(mode == "WNH_ERROR_XW")
    {
        LOGLEVEL = WNH_ERROR_XW;
    }
    else if(mode == "WNH_DEBUG_SW")
    {
        LOGLEVEL = WNH_DEBUG_SW;
    }
    else if(mode == "WNH_INFO_SW")
    {
        LOGLEVEL = WNH_INFO_SW;
    }
    else if(mode == "WNH_WARN_SW")
    {
        LOGLEVEL = WNH_WARN_SW;
    }
    else if(mode == "WNH_ERROR_SW")
    {
        LOGLEVEL = WNH_ERROR_SW;
    }
    else if(mode == "WNH_DEBUG_XSW")
    {
        LOGLEVEL = WNH_DEBUG_XSW;
    }
    else if(mode == "WNH_INFO_XSW")
    {
        LOGLEVEL = WNH_INFO_XSW;
    }
    else if(mode == "WNH_WARN_XSW")
    {
        LOGLEVEL = WNH_WARN_XSW;
    }
    else if(mode == "WNH_ERROR_XSW")
    {
        LOGLEVEL = WNH_ERROR_XSW;
    }
    SETLOGLEVELSWITCH(); //设置日志输出等级
}

int wnh_filesync_init::change_logs_lever(const string &mode)
{
    if(mode == "WNH_DEBUG_S")
    {
        return WNH_DEBUG_S;
    }
    else if(mode == "WNH_INFO_S")
    {
        return WNH_INFO_S;
    }
    else if(mode == "WNH_WARN_S")
    {
        return WNH_WARN_S;
    }
    else if(mode == "WNH_ERROR_S")
    {
        return WNH_ERROR_S;
    }
    else if(mode == "WNH_DEBUG_XS")
    {
        return WNH_DEBUG_XS;
    }
    else if(mode == "WNH_INFO_XS")
    {
        return WNH_INFO_XS;
    }
    else if(mode == "WNH_WARN_XS")
    {
        return WNH_WARN_XS;
    }
    else if(mode == "WNH_ERROR_XS")
    {
        return WNH_ERROR_XS;
    }
    else if(mode == "WNH_DEBUG_W")
    {
        return WNH_DEBUG_W;
    }
    else if(mode == "WNH_INFO_W")
    {
        return WNH_INFO_W;
    }
    else if(mode == "WNH_WARN_W")
    {
        return WNH_WARN_W;
    }
    else if(mode == "WNH_ERROR_W")
    {
        return WNH_ERROR_W;
    }
    else if(mode == "WNH_DEBUG_XW")
    {
        return WNH_DEBUG_XW;
    }
    else if(mode == "WNH_INFO_XW")
    {
        return WNH_INFO_XW;
    }
    else if(mode == "WNH_WARN_XW")
    {
        return WNH_WARN_XW;
    }
    else if(mode == "WNH_ERROR_XW")
    {
        return WNH_ERROR_XW;
    }
    else if(mode == "WNH_DEBUG_SW")
    {
        return WNH_DEBUG_SW;
    }
    else if(mode == "WNH_INFO_SW")
    {
        return WNH_INFO_SW;
    }
    else if(mode == "WNH_WARN_SW")
    {
        return WNH_WARN_SW;
    }
    else if(mode == "WNH_ERROR_SW")
    {
        return WNH_ERROR_SW;
    }
    else if(mode == "WNH_DEBUG_XSW")
    {
        return WNH_DEBUG_XSW;
    }
    else if(mode == "WNH_INFO_XSW")
    {
        return WNH_INFO_XSW;
    }
    else if(mode == "WNH_WARN_XSW")
    {
        return WNH_WARN_XSW;
    }
    else if(mode == "WNH_ERROR_XSW")
    {
        return WNH_ERROR_XSW;
    }
    return -1;
}

bool wnh_filesync_init::check_process_pid(const char *pid_file) //检查进程号是否存在
{
    struct stat stb;
    FILE *pidfile;
    if (stat(pid_file, &stb) == 0)
    {
        pidfile = fopen(pid_file, "r");
        if (pidfile)
        {
            char buf[64];
            pid_t pid = 0;
            memset(buf, 0, sizeof(buf));
            if (fread(buf, 1, sizeof(buf), pidfile))
            {
                buf[sizeof(buf) - 1] = '\0';
                pid = atoi(buf);
            }
            fclose(pidfile);
            if (pid && kill(pid, 0) == 0)
            {
                WNHWARN(PROGRAM_NAME << "程序正在运行中, 进程号:" << pid);
                return true;
            }
        }
        WNHDEBUG("删除" << pid_file << ", " PROGRAM_NAME << " 程序没有在运行");
        unlink(pid_file);
    }
    return false;
}


bool wnh_filesync_init::check_process_exist(const char * pid_file) //检查程序是否已经启动
{
    if(check_process_pid(pid_file))
    {
        return true;
    }
    FILE *fd = fopen(pid_file, "w");
    if(fd != nullptr)
    {
        fprintf(fd, "%u\n", getpid());
        fclose(fd);
        WNHDEBUG(PROGRAM_NAME << "程序启动,进程号:" << getpid() << " 写入" << pid_file  << "文件完成");
    }
    else
    {
        WNHERROR("无法打开" << pid_file << ", errno=" << errno << ", mesg=" << strerror(errno) << ",程序异常退出");
        exit(1);
    }
    return false;
}

void wnh_filesync_init::MY_PRAYER() //佛祖保佑,永无BUG
{
    WNHINFO("┌─────────────────────────────────────────────┐"     );
    WNHINFO("│                   _ooOoo_                   │"     );
    WNHINFO("│                  o8888888o                  │"     );
    WNHINFO("│                  88\" . \"88                  │"   );
    WNHINFO("│                  (| -_- |)                  │"     );
    WNHINFO("│                  O\\  =  /O                  │"    );
    WNHINFO("│               ____/`---'\\____               │"    );
    WNHINFO("│             .'  \\\\|     |//  `.             │"   );
    WNHINFO("│            /  \\\\|||  :  |||//  \\            │"  );
    WNHINFO("│           /  _||||| -:- |||||-  \\           │"    );
    WNHINFO("│           |   | \\\\\\  -  /// |   |           │"  );
    WNHINFO("│           | \\_|  ''\\---/''  |   |           │"   );
    WNHINFO("│           \\  .-\\__  `-`  ___/-. /           │"   );
    WNHINFO("│         ___`. .'  /--.--\\  `. . __          │"    );
    WNHINFO("│      .\"\" '<  `.___\\_<|>_/___.'  >'\"\".       │");
    WNHINFO("│     | | :  `- \\`.;`\\ _ /`;.`/ - ` : | |     │"   );
    WNHINFO("│     \\  \\ `-.   \\_ __\\ /__ _/   .-` /  /     │" );
    WNHINFO("│======`-.____`-.___\\_____/___.-`____.-'======│"    );
    WNHINFO("│                   `=---='                   │"     );
    WNHINFO("│^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^│"     );
    WNHINFO("│           佛祖保佑        永无BUG           │"       );
    WNHINFO("└─────────────────────────────────────────────┘"     );
}

void wnh_filesync_init::version_control_and_copyright_start() //版本控制和版权说明
{
    cout << WNH_COLOR_RED << "--------------------WELCOME TO USE " << PROGRAM_NAME << "---------------------" <<  WNH_COLOR_WHITE << endl;
    cout << WNH_COLOR_RED << WNH_FILESYNC_USE_HELP <<  WNH_COLOR_WHITE << endl;
    cout << WNH_COLOR_RED << WNH_FILESYNC_COPYRIGHT <<  WNH_COLOR_WHITE << endl;
    //sleep(3);
}

void wnh_filesync_init::version_control_and_copyright_stop() //版本控制和版权说明
{
    cout << WNH_COLOR_RED << "-----------------THANK YOU FOR USING " << PROGRAM_NAME << "-------------------" << WNH_COLOR_WHITE << endl;
    cout << WNH_COLOR_RED << WNH_FILESYNC_USE_HELP <<  WNH_COLOR_WHITE << endl;
    cout << WNH_COLOR_RED << WNH_FILESYNC_COPYRIGHT <<  WNH_COLOR_WHITE << endl;
    //sleep(3);
}

void wnh_filesync_init::INIT()//程序初始化函数
{
    version_control_and_copyright_start(); //版本控制和版权说明
    time_t t;
    t = time(0);
    LOCALTIMENUM = (unsigned long)t;
    strftime(LOCALTIME, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
    SETLOGLEVELSWITCH(); //设置日志输出等级

    //当程序已经被启动过,则进入阻塞,一直到进程结束后,进程才正常启动
    //while(check_process_exist(STARTER_PID_FILE_DEFAULT))
    //{
    //    sleep(1);
    //}
    if(LOGLEVEL != WNH_DEBUG_S && LOGLEVEL != WNH_INFO_S && LOGLEVEL != WNH_WARN_S && LOGLEVEL != WNH_ERROR_S && LOGLEVEL != WNH_DEBUG_XS && LOGLEVEL != WNH_INFO_XS && LOGLEVEL != WNH_WARN_XS && LOGLEVEL != WNH_ERROR_XS)
    {
        //日志追加输出
        WNH_LOGS_FILE.open(WNH_LOGS_FILE_NAME, ios::out | ios::app);
        //每一次启动都清空原先的日志
        //WNH_LOGS_FILE.open(WNH_LOGS_FILE_NAME, ios::out | ios::app | ios::trunc);
        if(!WNH_LOGS_FILE.is_open())
        {
            WNHERROR("打开日志文件" << WNH_LOGS_FILE_NAME <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
            exit(1);
        }
    }
    //MY_PRAYER();

    GETSYSTEMLOCALTIMESONID = true;
    std::thread get_local_time(&wnh_filesync_init::GETSYSTEMLOCALTIMESON, this);
    get_local_time.detach();
}
