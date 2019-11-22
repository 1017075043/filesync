#include "wnh_filesync_control.h"


void wnh_filesync_control::ues_instructions() //使用说明
{
    cout << WNH_COLOR_BOLDWHITE << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│                                                    " << WNH_COLOR_BOLDMAGENTA << PROGRAM_NAME << " 服务端使用说明" << WNH_COLOR_BOLDWHITE << "                                                  " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┬───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "      启动参数      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << " filesync server --conf=配置文件路径 --pid=PID文件路径 --limit=是否root限定 --log=日志等级                     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  范例 1 (缺省方式) " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync server filesync.conf " << WNH_COLOR_RESET << "                                                                                " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
	cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << " filesync server --conf=filesync.conf " << WNH_COLOR_RESET << "                                                                         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  范例 2 (完整方式) " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync server filesync.conf filesync_server.pid \"limit root\" WNH_INFO_XS                                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << " filesync server --conf=filesync.conf --pid=filesync_server.pid --limit=\"limit root\" --log=WNH_INFO_XS         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
	cout << WNH_COLOR_BOLDWHITE << "├┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│                                                    " << WNH_COLOR_BOLDMAGENTA << PROGRAM_NAME << " 客户端使用说明" << WNH_COLOR_BOLDWHITE << "                                                  " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┬───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "      启动参数      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << " filesync client --ip=服务端IP --port=服务端PORT --pid=PID文件路径 --limit=是否root限定 --log=日志等级         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  范例 1 (缺省方式) " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync client 127.0.0.1 10086                                                             " << WNH_COLOR_RESET << "(只连接单个服务端)" << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << " filesync client --ip=127.0.0.1 --port=10086" << WNH_COLOR_RESET << "                                                                   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  范例 2 (完整方式) " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync client 127.0.0.1 10086 filesync_client.pid \"limit root\" WNH_INFO_XS                " << WNH_COLOR_RESET << "(只连接单个服务端)" << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << " filesync client --ip=127.0.0.1 --port=10086 --pid=filesync_client.pid --limit=\"limit root\" --log=WNH_INFO_XS" << WNH_COLOR_RESET << "  " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  范例 3 (缺省方式) " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync client filesync.conf                                                               " << WNH_COLOR_RESET << "(可连接多个服务端)" << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << " filesync client --conf=filesync.conf" << WNH_COLOR_RESET << "                                                                          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  范例 4 (完整方式) " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync client filesync.conf \"limit root\" WNH_INFO_XS                                      " << WNH_COLOR_RESET << "(可连接多个服务端)" << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << " filesync client --conf=filesync.conf --limit=\"limit root\" --log=WNH_INFO_XS" << WNH_COLOR_RESET << "                                   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│                                                    " << WNH_COLOR_BOLDMAGENTA << PROGRAM_NAME << " 控制端使用说明" << WNH_COLOR_BOLDWHITE << "                                                  " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┬───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;   
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "      启动参数      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << " filesync control 使用参数 --ip=服务端IP --port=服务端PORT --log=日志等级                                      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┼───────────────────────────────────────────────────────┬───────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  范例 1 (缺省方式) " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync" << "                                " << WNH_COLOR_RESET << "(显示使用帮助)" << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync 1" << "                        " << WNH_COLOR_RESET << "(显示控制端使用列表)" << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┼───────────────────────────────────────────────────────┴───────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "  范例 2 (完整方式) " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << " filesync control \"show list\" 127.0.0.1 10086 WNH_INFO_XS                                                      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDBLUE << " filesync control \"show list\" --ip=127.0.0.1 --port=10086 --log=WNH_INFO_XS                                    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────┴───────────────────────────────────────────────────────────────────────────────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN << "  说明: 如果系统参数配置足够完整的话, 可以缺省至直接执行 " << WNH_COLOR_BOLDRED << "filesync" << WNH_COLOR_BOLDGREEN << " 就能以你期望的模式运行程序.                                       " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN << "        缺省的参数从系统变量中获取,若系统变量也不存在将使用程序默认值,使用命令 " << WNH_COLOR_BOLDRED << "filesync 9" << WNH_COLOR_BOLDGREEN << " 查看系统变量配置方式                      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "└────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << WNH_COLOR_RESET << endl;
}

void wnh_filesync_control::control_use_instructions() //控制端使用说明
{
    cout << WNH_COLOR_BOLDWHITE << "┌──────┬───────────────────────────┬──────────────────────────────────────────┬──────────────────────────────────────────────────────┐" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN<< " 序号 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN  << "           参数            " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN<< "                   说明                   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                      使用范例                        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┬──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  0   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "         show use          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "               显示使用帮助               " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 0   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "        filesync \"show use\"           " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  1   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "         show list         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "             显示使用命令列表             " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 1   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "        filesync \"show list\"          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  2   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "    show server client     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "          显示服务端和客户端状态          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 2   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "    filesync \"show server client\"     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  3   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "   show server client s    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "        实时显示服务端和客户端状态        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 3   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "   filesync \"show server client s\"    " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  4   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "        show server        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "              显示服务端列表              " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 4   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "       filesync \"show server\"         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  5   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "       show server s       " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "            实时显示服务端列表            " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 5   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "      filesync \"show server s\"        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  6   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "        show client        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "              显示客户端列表              " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 6   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "       filesync \"show client\"         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  7   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "       show client s       " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "            实时显示客户端列表            " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 7   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "      filesync \"show client s\"        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  8   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "      show sync rule       " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "             显示同步规则列表             " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 8   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "     filesync \"show sync rule\"        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  9   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "      show system var      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "           显示系统环境变量说明           " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 9   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "     filesync \"show system var\"       " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├──────┼───────────────────────────┼──────────────────────────────────────────┼───────────────┼──────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  10  " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "       show license        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "            显示服务端许可信息            " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "  filesync 10  " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "      filesync \"show license\"         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "└──────┴───────────────────────────┴──────────────────────────────────────────┴───────────────┴──────────────────────────────────────┘" << WNH_COLOR_RESET << endl;
}


void wnh_filesync_control::show_system_var() //显示系统变量
{
    cout << WNH_COLOR_BOLDWHITE << "┌────────────────────────────────────┬────────────────────────────────┬──────────────────────┬───────────────────────────────────────┐" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN   << "             系统变量名             " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN<< "            用途说明            " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "       使用范围       " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDCYAN << "                默认值                 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "        " << FILESYNC_START_MODE << "         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "          程序启动模式          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << " 服务端|客户端|控制端 " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_START_MODE_DEFAUL, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "         " << FILESYNC_SERVER_IP << "         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "         服务端服务器IP         " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "    客户端|控制端     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_SERVER_IP_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "        " << FILESYNC_SERVER_PORT << "        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "        服务端服务器端口        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "    客户端|控制端     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_SERVER_PORT_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "    " << FILESYNC_SERVER_CONFIG_PATH << "     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "          配置文件路径          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        服务端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_SERVER_CONFIG_PATH_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "      " << FILESYNC_SERVER_PID_PATH << "      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "          PID文件路径           " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        服务端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_SERVER_PID_PATH_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "     " << FILESYNC_SERVER_LOGS_LEVEL << "     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "            日志等级            " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        服务端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_SERVER_LOGS_LEVEL_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "     " << FILESYNC_SERVER_ROOT_LIMIT << "     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "          root用户限制          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        服务端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_SERVER_ROOT_LIMIT_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "    " << FILESYNC_CLIENT_CONFIG_PATH << "     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "          配置文件路径          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        客户端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_CLIENT_CONFIG_PATH_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "      " << FILESYNC_CLIENT_PID_PATH << "      " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "          PID文件路径           " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        客户端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_CLIENT_PID_PATH_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "     " << FILESYNC_CLIENT_LOGS_LEVEL << "     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "            日志等级            " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        客户端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_CLIENT_LOGS_LEVEL_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "     " << FILESYNC_CLIENT_ROOT_LIMIT << "     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "          root用户限制          " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        客户端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_CLIENT_ROOT_LIMIT_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┼┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "   " << FILESYNC_CONTROL_USE_PARAMETER << "   " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "       客户端默认使用参数       " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        控制端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_CONTROL_USE_PARAMETER_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┼────────────────────────────────┼──────────────────────┼───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << "    " << FILESYNC_CONTROL_LOGS_LEVEL << "     " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDRED << "            日志等级            " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDMAGENTA << "        控制端        " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDYELLOW << format_string_centro_fill(FILESYNC_CONTROL_LOGS_LEVEL_DEFAULT, 38, ' ') << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "├────────────────────────────────────┴────────────────────────────────┴──────────────────────┴───────────────────────────────────────┤" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_BOLDGREEN << " 注释: linux配置系统变量可以使用命令 export , 例如 export FILESYNC_START_MODE=control                                               " << WNH_COLOR_BOLDWHITE << "│" << WNH_COLOR_RESET << endl;
    cout << WNH_COLOR_BOLDWHITE << "└────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << WNH_COLOR_RESET << endl;

}
