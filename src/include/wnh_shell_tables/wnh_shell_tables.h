#ifndef __wnh_shell_tables__
#define __wnh_shell_tables__

using namespace std;

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
        long length;          //成员值总长度
        int num;              //成员数量
        vector<string> color; //每个成员渲染颜色
        vector<string> align; //每个成员对齐方式
        vector<unsigned int> value_width; //每个成员使用的宽度
    };

public:
    enum ALIGN_MODE{left=1, right=2, centre=3};
    TABLES_LINE tables_unit[WNH_TABLES_MAX_LINE_NUM]; //成员数据保存
    int line_num; //行数
    int max_row_num;  //最大列数
    int max_line_width; //最大行宽度
    wnh_shell_tables();
    ~wnh_shell_tables();

    bool add_unit(const vector<string> & value, const vector<string>  & color, const vector<string>  & align); //添加成员数据
    void show_unit(); //显示成员
    string color_transform(string color); //颜色转换
    void show_tables(); //显示表格
    void smart_line_width(); //智能列宽
};

#endif
