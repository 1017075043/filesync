#ifndef __wnh_shell_tables__
#define __wnh_shell_tables__

using namespace std;

enum WNH_SHELL_TABLES_ALIGN_MODE
{
    left=1,
    right=2,
    centro=3
};
enum WNH_SHELL_TABLES_FONT_COLOR
{
    RESET=1,
    BLACK=2,
    RED=3,
    GREEN=4,
    YELLOW=5,
    BLUE=6,
    MAGENTA=7,
    CYAN=8,
    WHITE=9,
    BOLDBLACK=10,
    BOLDRED=11,
    BOLDGREEN=12,
    BOLDYELLOW=13,
    BOLDBLUE=14,
    BOLDMAGENTA=15,
    BOLDCYAN=16,
    BOLDWHITE=17
};
enum WNH_SHELL_TABLES_SPLIT_LINE_FORMAT
{
    NORMAL=1,
    EMPTY=2,
    REPEAT=3
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
        vector<WNH_SHELL_TABLES_FONT_COLOR> color; //每个成员渲染颜色
        vector<WNH_SHELL_TABLES_ALIGN_MODE> align; //每个成员对齐方式
        vector<unsigned int> value_width; //每个成员使用的宽度
        WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format;//分割线模式
    };

public:
    TABLES_LINE tables_unit[WNH_TABLES_MAX_LINE_NUM]; //成员数据保存
    int line_num; //行数
    int max_row_num;  //最大列数
    int max_line_width; //最大行宽度
    int max_line_num; //最大行数
    bool is_use_smart_line_width;
    wnh_shell_tables();
    ~wnh_shell_tables();

    bool add_unit(const vector<string> & value, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据
    bool add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL); //添加成员数据

    void show_unit(); //显示成员
    string color_transform(WNH_SHELL_TABLES_FONT_COLOR color, bool mode); //颜色转换
    string align_transform(WNH_SHELL_TABLES_ALIGN_MODE align); //对齐方式转换
    string split_line_format_transform(WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format); //分隔行格式转换
    void show_tables(); //显示表格
    void smart_line_width(); //智能列宽
    int get_repeat_num(WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format); //获取重复次数
};

#endif
