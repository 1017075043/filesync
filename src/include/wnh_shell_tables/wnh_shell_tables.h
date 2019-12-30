#ifndef __wnh_shell_tables__
#define __wnh_shell_tables__

using namespace std;

enum WNH_SHELL_TABLES_ALIGN_MODE
{
    left,right,centro
};
enum WNH_SHELL_TABLES_FONT_STYLE
{
    RESET,
                         BLACK,                      RED,                      GREEN,                      YELLOW,                      BLUE,                      MAGENTA,                      CYAN,                      WHITE,
                     BOLDBLACK,                  BOLDRED,                  BOLDGREEN,                  BOLDYELLOW,                  BOLDBLUE,                  BOLDMAGENTA,                  BOLDCYAN,                  BOLDWHITE,
                 FLASHINGBLACK,              FLASHINGRED,              FLASHINGGREEN,              FLASHINGYELLOW,              FLASHINGBLUE,              FLASHINGMAGENTA,              FLASHINGCYAN,              FLASHINGWHITE,
                UNDERLINEBLACK,             UNDERLINERED,             UNDERLINEGREEN,             UNDERLINEYELLOW,             UNDERLINEBLUE,             UNDERLINEMAGENTA,             UNDERLINECYAN,             UNDERLINEWHITE,
             FLASHINGBOLDBLACK,          FLASHINGBOLDRED,          FLASHINGBOLDGREEN,          FLASHINGBOLDYELLOW,          FLASHINGBOLDBLUE,          FLASHINGBOLDMAGENTA,          FLASHINGBOLDCYAN,          FLASHINGBOLDWHITE,
            UNDERLINEBOLDBLACK,         UNDERLINEBOLDRED,         UNDERLINEBOLDGREEN,         UNDERLINEBOLDYELLOW,         UNDERLINEBOLDBLUE,         UNDERLINEBOLDMAGENTA,         UNDERLINEBOLDCYAN,         UNDERLINEBOLDWHITE,
        UNDERLINEFLASHINGBLACK,     UNDERLINEFLASHINGRED,     UNDERLINEFLASHINGGREEN,     UNDERLINEFLASHINGYELLOW,     UNDERLINEFLASHINGBLUE,     UNDERLINEFLASHINGMAGENTA,     UNDERLINEFLASHINGCYAN,     UNDERLINEFLASHINGWHITE,
    UNDERLINEFLASHINGBOLDBLACK, UNDERLINEFLASHINGBOLDRED, UNDERLINEFLASHINGBOLDGREEN, UNDERLINEFLASHINGBOLDYELLOW, UNDERLINEFLASHINGBOLDBLUE, UNDERLINEFLASHINGBOLDMAGENTA, UNDERLINEFLASHINGBOLDCYAN, UNDERLINEFLASHINGBOLDWHITE


};
enum WNH_SHELL_TABLES_SPLIT_LINE_FORMAT
{
    NORMAL,EMPTY,REPEAT
};

#include "../wnh_base_class/wnh_base_class.h"
#include "wnh_shell_tables_define.h"

//┌───┬───┐
//│   │   │
//├───┼───┤
//│   │   │
//└───┴───┘

class wnh_shell_tables : public wnh_base_class
{
private:
    struct TABLES_LINE //表格成员
    {
        vector<string> value; //成员值
        int num;              //成员数量
        vector<WNH_SHELL_TABLES_FONT_STYLE> color; //每个成员渲染颜色
        vector<WNH_SHELL_TABLES_ALIGN_MODE> align; //每个成员对齐方式
        vector<unsigned int> value_width; //每个成员使用的宽度
        WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format;//分割线模式
        vector<bool> separator_format; //每个成员分隔符模式
        vector<unsigned int> son_line_num; //子行行号
    };

public:
    TABLES_LINE tables_unit[WNH_TABLES_MAX_LINE_NUM]; //成员数据保存
    vector<string> tables_unit_son[WNH_TABLES_MAX_LINE_NUM]; //子成员数据保存
    int local_son_line_num; //当前子行的数量
    int line_num; //行数
    int max_row_num;  //最大列数
    int max_line_width; //最大行宽度
    int max_line_num; //最大行数
    bool is_use_smart_line_width; //是否使用智能行宽
    wnh_shell_tables();
    ~wnh_shell_tables();

    bool add_unit(const vector<string> & value, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool set_unit(const int & num, const vector<WNH_SHELL_TABLES_FONT_STYLE> & color); //设置成员渲染颜色
    bool set_unit(const int & num, const vector<WNH_SHELL_TABLES_ALIGN_MODE> align); //设置成员对齐方式
    bool set_unit(const int & num, const vector<unsigned int> value_width); //设置成员使用的宽度
    bool set_unit(const int & num, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format); //设置分割线模式
    bool set_unit(const int & num, const vector<bool> separator_format); //设置成员分隔符模式

    void show_unit(); //显示成员
    string sytle_transform(WNH_SHELL_TABLES_FONT_STYLE color, bool mode); //颜色转换
    string align_transform(WNH_SHELL_TABLES_ALIGN_MODE align); //对齐方式转换
    string split_line_format_transform(WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format); //分隔行格式转换
    void show_tables(); //显示表格
    void smart_line_width(); //智能列宽
    int get_repeat_num(WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format); //获取重复次数

    bool add_son_unit(const int & num); //添加子行
    bool add_son_unit(const int & num, const int & son_num); //添加子行

    template <typename Type, typename Types>
    bool copy_vector_values(Type & vec_1, Types & vec_2);

    void clear(); //清理数据
};

#endif
