#include "filesync.h"

#include "filesync_init_parameter.cpp"
#include "filesync_server_mode.cpp"
#include "filesync_client_mode.cpp"
#include "filesync_control_mode.cpp"

void filesync_deamon_Process(int argc, char **argv);

int main(int argc, char **argv)
{
    filesync program; //定义一个程序类
    program.init.INIT(); //初始化
    program.startup_mode((const int)argc, (const char**)argv);
    wnh_license li;
    li.get_server_serial_number();
    return 0;
}

filesync::filesync()
{

}

filesync::~filesync()
{
    init.version_control_and_copyright_stop();
}

void filesync::startup_mode(const int argc, const char **argv)
{
    init_parameter(argc, argv); //初始化参数
    if(filesync_start_mode == "server")
    {
        server_mode();
    }
    else if(filesync_start_mode == "client")
    {
        client_mode();
    }
    else if(filesync_start_mode == "control")
    {
        control_mode();
    }
}

void filesync_deamon_Process()
{
    WNHDEBUG("开始创建守护进程");

    //只是为了可以正常输出日志而操作的。
    time_t t;
    t = time(0);
    strftime(LOCALTIME, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
    wnh_filesync_init init;
    init.SETLOGLEVELSWITCH();
    LOGLEVEL = WNH_DEBUG_S;

    pid_t pc;
    pc = fork(); //第一步,创建子进程，父进程退出
    if(pc < 0) //子进程创建失败了
    {
        WNHERROR("子进程创建失败,程序异常退出" << ", errno=" << errno << ", mesg=" << strerror(errno));
        exit(1);
    }
    else if(pc > 0) //父进程退出
    {
        WNHDEBUG("子进程创建成功,父进程即将退出");
        exit(0);
    }
    setsid(); //第二步,在子进程中创建新的对话,使子进程摆脱控制
    //cout << "子进程创建新的对话,子进程摆脱控制完成" << endl;
    //chdir("/root/wnh/c/filesync/src"); //第三步,将子进程的工作目录更改为 根目录,可以根据自己需要修改
    //cout << "子进程工作目录更改完成" << endl;
    umask(0); //第四步,子进程重新设置文件权限掩码
    //cout << "子进程重新设置文件权限掩码完成" << endl;
    WNHINFO("守护进程创建成功");
}
