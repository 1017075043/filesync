#include "wnh_filesync_control.h"


void wnh_filesync_control::ues_instructions() //使用说明
{
    vector<string> values;
    vector<WNH_SHELL_TABLES_FONT_STYLE> color;
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    vector<unsigned int> values_width;
    vector<bool> separator_format;

    string str_temp;
    str_temp = str_temp + PROGRAM_NAME + " 服务端使用说明";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro);
    set_vector_values(true, values_width, 132);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "启动参数", " filesync server --conf=配置文件路径 --pid=PID文件路径 --limit=是否root限定 --log=日志等级");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 19, 112);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "范例 1 (缺省方式)", " filesync server filesync.conf");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY);

    set_vector_values(true, values, "", " filesync server --conf=filesync.conf");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "范例 2 (完整方式)", " filesync server filesync.conf filesync_server.pid \"limit root\" WNH_INFO_XS");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY);

    set_vector_values(true, values, "", " filesync server --conf=filesync.conf --pid=filesync_server.pid --limit=\"limit root\" --log=WNH_INFO_XS");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT);

    str_temp = "";
    str_temp = str_temp + PROGRAM_NAME + " 控制端使用说明";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro);
    set_vector_values(true, values_width, 132);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "启动参数", " filesync client --ip=服务端IP --port=服务端PORT --pid=PID文件路径 --limit=是否root限定 --log=日志等级");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 19, 112);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "范例 1 (缺省方式)", " filesync client 127.0.0.1 10086", "(只连接单个服务端)");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::RESET);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::right);
    set_vector_values(true, values_width, 19, 93, 18);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY);

    set_vector_values(true, values, "", " filesync client --ip=127.0.0.1 --port=10086");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 19, 112);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "范例 2 (完整方式)", " filesync client 127.0.0.1 10086 filesync_client.pid \"limit root\" WNH_INFO_XS", "(只连接单个服务端)");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::RESET);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::right);
    set_vector_values(true, values_width, 19, 93, 18);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY);

    set_vector_values(true, values, "", " filesync client --ip=127.0.0.1 --port=10086 --pid=filesync_client.pid --limit=\"limit root\" --log=WNH_INFO_XS");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 19, 112);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "范例 3 (缺省方式)", " filesync client filesync.conf", "(可连接多个服务端)");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::RESET);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::right);
    set_vector_values(true, values_width, 19, 93, 18);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY);

    set_vector_values(true, values, "", " filesync client --conf=filesync.conf");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 19, 112);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "范例 4 (完整方式)", " filesync client filesync.conf \"limit root\" WNH_INFO_XS", "(可连接多个服务端)");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::RESET);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::right);
    set_vector_values(true, values_width, 19, 93, 18);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY);

    set_vector_values(true, values, "", " filesync client --conf=filesync.conf --limit=\"limit root\" --log=WNH_INFO_XS");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 19, 112);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT);

    str_temp = "";
    str_temp = str_temp + PROGRAM_NAME + " 客户端使用说明";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro);
    set_vector_values(true, values_width, 132);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "启动参数", " filesync control 使用参数 --ip=服务端IP --port=服务端PORT --log=日志等级");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 19, 112);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "范例 1 (缺省方式)", " filesync", "(只连接单个服务端)", " filesync 1", "(显示控制端使用列表)");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::RESET, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::RESET);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::right, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::right);
    set_vector_values(true, values_width, 19, 35, 18, 36, 20);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, "范例 2 (完整方式)", " filesync control \"show list\" 127.0.0.1 10086 WNH_INFO_XS");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::centro, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 19, 112);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY);

    set_vector_values(true, values, "", " filesync control \"show list\" --ip=127.0.0.1 --port=10086 --log=WNH_INFO_XS");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, values, " 说明: 如果系统参数配置足够完整的话, 可以缺省至直接执行", "filesync", "就能以你期望的模式运行程序.");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values_width, 55, 8, 67);
    shell_tables.add_unit(values, color, align, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY);

    set_vector_values(true, values, "       缺省的参数从系统变量中获取,若系统变量也不存在将使用程序默认值,使用命令", "filesync 9", "查看系统变量配置方式.");
    set_vector_values(true, values_width, 77, 10, 43);
    shell_tables.add_unit(values, color, align, values_width);

    set_vector_values(true, separator_format, true, false, true);
    shell_tables.set_unit(8, separator_format);
    shell_tables.set_unit(10, separator_format);
    shell_tables.set_unit(12, separator_format);
    shell_tables.set_unit(14, separator_format);

    set_vector_values(true, separator_format, true, false, true, false, true);
    shell_tables.set_unit(18, separator_format);

    set_vector_values(true, separator_format, false, false, true);
    shell_tables.set_unit(21, separator_format);
    shell_tables.set_unit(22, separator_format);

    shell_tables.show_tables();
    shell_tables.clear();
}

void wnh_filesync_control::control_use_instructions() //控制端使用说明
{
    vector<string> values;
    vector<WNH_SHELL_TABLES_FONT_STYLE> color;
    vector<unsigned int> values_width;

    string str_temp;
    str_temp = str_temp + PROGRAM_NAME + " 控制端使用说明";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA);
    set_vector_values(true, values_width, 114);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "序号", "参数", "说明", "使用范例");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN);
    set_vector_values(true, values_width, 6, 24, 30, 51);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "0", "show use", "显示使用帮助", "filesync 0", "filesync \"show use\"");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW);
    set_vector_values(true, values_width, 6, 24, 30, 15, 35);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "1", "show list", "显示使用命令列表", "filesync 1", "filesync \"show list\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "2", "show server client", "显示服务端和客户端状态", "filesync 2", "filesync \"show server client\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "3", "show server client s", "实时显示服务端和客户端状态", "filesync 3", "filesync \"show server client s\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "4", "show server", "显示服务端列表", "filesync 4", "filesync \"show server\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "5", "show server s", "实时显示服务端列表", "filesync 5", "filesync \"show server s\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "6", "show client", "显示客户端列表", "filesync 6", "filesync \"show client\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "7", "show client s", "实时显示客户端列表", "filesync 7", "filesync \"show client s\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "8", "show sync rule", "显示同步规则列表", "filesync 8", "filesync \"show sync rule\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "9", "show system var", "显示系统环境变量说明", "filesync 9", "filesync \"show system var\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "10", "show license", "显示服务端许可信息", "filesync 10", "filesync \"show license\"");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "11", "show transfer", "显示同步传输过程信息", "filesync 11", "filesync \"show transfer\"");
    shell_tables.add_unit(values, color, values_width);

    shell_tables.show_tables();
    shell_tables.clear();
}


void wnh_filesync_control::show_system_var() //显示系统变量
{
    vector<string> values;
    vector<WNH_SHELL_TABLES_FONT_STYLE> color;
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    vector<unsigned int> values_width;

    string str_temp;
    str_temp = str_temp + PROGRAM_NAME + " 系统变量使用说明";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA);
    set_vector_values(true, values_width, 117);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "系统变量名", "用途说明", "使用范围", "默认值");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN);
    set_vector_values(true, values_width, 32, 24, 26, 32);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_START_MODE, "程序启动模式", "服务端|客户端|控制端", "control");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA, WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_SERVER_IP, "服务端服务器IP", "客户端|控制端", "127.0.0.1");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_SERVER_PORT, "服务端服务器端口", "客户端|控制端", "10086");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_SERVER_CONFIG_PATH, "配置文件路径", "服务端", "filesync.conf");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_SERVER_PID_PATH, "PID文件路径", "服务端", "/var/run/filesync_server.pid");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_SERVER_LOGS_LEVEL, "日志等级", "服务端", "WNH_INFO_S");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_SERVER_ROOT_LIMIT, "root用户限制", "服务端", "limit root");
    shell_tables.add_unit(values, color, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT);

    set_vector_values(true, values, FILESYNC_CLIENT_CONFIG_PATH, "配置文件路径", "客户端", "filesync.conf");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_CLIENT_PID_PATH, "PID文件路径", "客户端", "/var/run/filesync_client.pid");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_CLIENT_LOGS_LEVEL, "日志等级", "客户端", "WNH_INFO_S");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_CLIENT_ROOT_LIMIT, "root用户限制", "客户端", "limit root");
    shell_tables.add_unit(values, color, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT);

    set_vector_values(true, values, FILESYNC_CONTROL_USE_PARAMETER, "客户端默认使用参数", "控制端", "0");
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, FILESYNC_CONTROL_LOGS_LEVEL, "日志等级", "控制端", "WNH_INFO_S");
    shell_tables.add_unit(values, color, values_width, WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT);

    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::left);
    set_vector_values(true, values, "  注释: linux配置系统变量可以使用命令 export , 例如 export FILESYNC_START_MODE=control");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN);
    set_vector_values(true, values_width, 32 + 24 + 26 + 32 + 3);
    shell_tables.add_unit(values, color, values_width, align);
    shell_tables.show_tables();
    shell_tables.clear();
}
