// 显示风格定义

#define WNH_FONT_COLOR_RESET         "\033[0m"               //恢复默认
#define WNH_FONT_COLOR_BLACK         "\033[30m"              //黑色
#define WNH_FONT_COLOR_RED           "\033[31m"              //红色
#define WNH_FONT_COLOR_GREEN         "\033[32m"              //绿色
#define WNH_FONT_COLOR_YELLOW        "\033[33m"              //黄色
#define WNH_FONT_COLOR_BLUE          "\033[34m"              //蓝色
#define WNH_FONT_COLOR_MAGENTA       "\033[35m"              //品红色
#define WNH_FONT_COLOR_CYAN          "\033[36m"              //青色
#define WNH_FONT_COLOR_WHITE         "\033[37m"              //白色
#define WNH_FONT_COLOR_BOLDBLACK     "\033[1m\033[30m"       //粗体黑色
#define WNH_FONT_COLOR_BOLDRED       "\033[1m\033[31m"       //粗体红色
#define WNH_FONT_COLOR_BOLDGREEN     "\033[1m\033[32m"       //粗体绿色
#define WNH_FONT_COLOR_BOLDYELLOW    "\033[1m\033[33m"       //粗体黄色
#define WNH_FONT_COLOR_BOLDBLUE      "\033[1m\033[34m"       //粗体蓝色
#define WNH_FONT_COLOR_BOLDMAGENTA   "\033[1m\033[35m"       //粗体品红色
#define WNH_FONT_COLOR_BOLDCYAN      "\033[1m\033[36m"       //粗体青色
#define WNH_FONT_COLOR_BOLDWHITE     "\033[1m\033[37m"       //粗体白色

#define WNH_FONT_STYLE_FLASHING      "\033[5m"               //闪烁
#define WNH_FONT_STYLE_UNDERLINE     "\033[4m"               //下划线

#define WNH_GROUPBECK_COLOR_BLACK         "\033[40m"              //黑色
#define WNH_GROUPBECK_COLOR_RED           "\033[41m"              //红色
#define WNH_GROUPBECK_COLOR_GREEN         "\033[42m"              //绿色
#define WNH_GROUPBECK_COLOR_YELLOW        "\033[43m"              //黄色
#define WNH_GROUPBECK_COLOR_BLUE          "\033[44m"              //蓝色
#define WNH_GROUPBECK_COLOR_MAGENTA       "\033[45m"              //品红色
#define WNH_GROUPBECK_COLOR_CYAN          "\033[46m"              //青色
#define WNH_GROUPBECK_COLOR_WHITE         "\033[47m"              //白色

#define WNH_DISPLAY_STYLE_CLEAR() printf("\033[2J") // 清除屏幕
#define WNH_DISPLAY_STYLE_MOVEUP(x) printf("\033[%dA", (x)) // 上移光标
#define WNH_DISPLAY_STYLE_MOVEDOWN(x) printf("\033[%dB", (x)) // 下移光标
#define WNH_DISPLAY_STYLE_MOVELEFT(y) printf("\033[%dD", (y)) // 左移光标
#define WNH_DISPLAY_STYLE_MOVERIGHT(y) printf("\033[%dC",(y)) // 右移光标
#define WNH_DISPLAY_STYLE_MOVETO(x,y) printf("\033[%d;%dH", (x), (y)) // 定位光标
#define WNH_DISPLAY_STYLE_RESET_CURSOR() printf("\033[H") // 光标复位
#define WNH_DISPLAY_STYLE_HIDE_CURSOR() printf("\033[?25l") // 隐藏光标
#define WNH_DISPLAY_STYLE_SHOW_CURSOR() printf("\033[?25h") // 显示光标
#define WNH_DISPLAY_STYLE_CLOSE_ALL_ATTRIBUTES() printf("\033[0m") //关闭所有属性
#define WNH_DISPLAY_STYLE_SET_HIGH_BRIGHTNESS() printf("\033[1m") //设置高亮度
#define WNH_DISPLAY_STYLE_THE_UNDERLINE() printf("\033[4m") //下划线
#define WNH_DISPLAY_STYLE_FLASHING() printf("\033[5m") //闪烁
#define WNH_DISPLAY_STYLE_REVERSE_VIDEO() printf("\033[7m") //反显
#define WNH_DISPLAY_STYLE_BLANKING() printf("\033[8m") //消隐
#define WNH_DISPLAY_STYLE_SHOW_CURSOR_S() system("echo -e '\033[?25h'") //显示光标

//反显
#define WNH_DISPLAY_STYLE_HIGHT_LIGHT() printf("\033[7m")
#define WNH_DISPLAY_STYLE_UN_HIGHT_LIGHT() printf("\033[27m")
