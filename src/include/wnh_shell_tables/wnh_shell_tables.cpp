#include "wnh_shell_tables.h"

wnh_shell_tables::wnh_shell_tables()
{
    WNHDEBUG("wnh_shell_tables 构造");
    line_num = 0;
    max_line_width = WNH_TABLES_MIN_WIDTH;
    max_row_num = 0;
}

wnh_shell_tables::~wnh_shell_tables()
{
    WNHDEBUG("~wnh_shell_tables 析构");
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<string>  & color, const vector<string>  & align) //添加成员数据
{
    if(value.size() != color.size() || value.size() != align.size())
    {
        WNHWARN("数据残缺, 成员值数量=" << value.size() << ", 颜色数量=" << color.size() << ", 对齐数量=" << align.size());
        return false;
    }
    tables_unit[line_num].value = value;
    tables_unit[line_num].color = color;
    tables_unit[line_num].align = align;
    tables_unit[line_num].num = value.size();
    tables_unit[line_num].length = tables_unit[line_num].num + 1;
    for(unsigned int i = 0 ; i < value.size(); i ++)
    {
        tables_unit[line_num].length = tables_unit[line_num].length + value[i].length();
    }
    if(max_row_num < tables_unit[line_num].num)
    {
        max_row_num = tables_unit[line_num].num;
    }
    line_num ++;
    return true;
}

void wnh_shell_tables::smart_line_width() //智能列宽
{
    for(unsigned int j = 0; j < tables_unit[0].value.size(); j ++)
    {
        unsigned int max_row_width = 0;
        for(int i = 0; i < line_num; i ++)
        {
            if(max_row_width < tables_unit[i].value[j].length())
            {
                max_row_width = tables_unit[i].value[j].length() - get_chinese_num(tables_unit[i].value[j]);
            }
        }
        max_row_width = max_row_width + 2;
        for(int i = 0; i < line_num; i ++)
        {
            tables_unit[i].value_width.push_back(max_row_width);
        }
    }
    if(max_line_width < tables_unit[line_num].length && max_line_width < WNH_TABLES_MAX_WIDTH)
    {
        max_line_width = tables_unit[line_num].length;
    }
}

void wnh_shell_tables::show_unit() //显示成员
{
    for(int i = 0; i < line_num; i ++)
    {
        for(unsigned int j = 0; j < tables_unit[i].value.size(); j++)
        {
            WNHINFO("tables_unit[" << i << "].unit[" << j << "]: value=" << tables_unit[i].value[j] << ", color=" << color_transform(tables_unit[i].color[j]) << ", align=" << tables_unit[i].align[j] << ", value_width=" << tables_unit[i].value_width[j]);
            //if(tables_unit[line_num].color.size() >= j && tables_unit[line_num].align.size() >= j)
            //{
            //    WNHINFO("tables_unit[" << i << "].unit[" << j << "]: value=" << tables_unit[i].value[j] << ", color=" << color_transform(tables_unit[i].color[j]) << ", align=" << tables_unit[i].align[j]);
            //}
            //if(tables_unit[line_num].color.size() < j && tables_unit[line_num].align.size() >= j)
            //{
            //    WNHINFO("tables_unit[" << i << "].unit[" << j << "]: value=" << tables_unit[i].value[j] << ", color=default" << ", align=" << tables_unit[i].align[j]);
            //}
            //if(tables_unit[line_num].color.size() >= j && tables_unit[line_num].align.size() < j)
            //{
            //    WNHINFO("tables_unit[" << i << "].unit[" << j << "]: value=" << tables_unit[i].value[j] << ", color=" << color_transform(tables_unit[i].color[j]) << ", align=default");
            //}
            //if(tables_unit[line_num].color.size() < j && tables_unit[line_num].align.size() < j)
            //{
            //    WNHINFO("tables_unit[" << i << "].unit[" << j << "]: value=" << tables_unit[i].value[j] << ", color=align, align=default");
            //}
        }
    }
}



void wnh_shell_tables::show_tables() //显示表格
{
    smart_line_width();
    show_unit();
    //第一行
    cout << WNH_TABLES_FELT_UNDER;
    for(unsigned int j = 0; j < tables_unit[0].value.size(); j++)
    {
        for(unsigned int k = 0; k < tables_unit[0].value_width[j]; k++)
        {
            cout << WNH_TABLES_CROSS;
        }
        if(j != tables_unit[0].value.size() - 1)
        {
            cout << WNH_TABLES_CONTRO_UNDER;
        }
    }
    cout << WNH_TABLES_RIGHT_UNDER << endl;
    //中间行
    for(int i = 0; i < line_num; i ++)
    {
        cout << WNH_TABLES_VERTICAL;
        for(unsigned int j = 0; j < tables_unit[i].value.size(); j++)
        {
            if(tables_unit[i].align[j] == "left")
            {
                cout << tables_unit[i].color[j] << format_string_left_fill(tables_unit[i].value[j], tables_unit[i].value_width[j] - 1, ' ') << WNH_TABLES_VERTICAL;
            }
            else if(tables_unit[i].align[j] == "centro")
            {
                cout << tables_unit[i].color[j] << format_string_centro_fill(tables_unit[i].value[j], tables_unit[i].value_width[j] - 1, ' ') << WNH_TABLES_VERTICAL;
            }
            else if(tables_unit[i].align[j] == "right")
            {
                cout << tables_unit[i].color[j] << format_string_right_fill(tables_unit[i].value[j], tables_unit[i].value_width[j] - 1, ' ') << WNH_TABLES_VERTICAL;
            }
        }
        cout << endl;
        if(i != line_num - 1)
        {
            cout << WNH_TABLES_FELT_CONTRO;
            for(unsigned int j = 0; j < tables_unit[i].value.size(); j++)
            {
                for(unsigned int k = 0; k < tables_unit[i].value_width[j]; k++)
                {
                    cout << WNH_TABLES_CROSS;
                }
                if(j != tables_unit[i].value.size() - 1)
                {
                    cout << WNH_TABLES_CONTRO_CONTRO;
                }
            }
            cout << WNH_TABLES_RIGHT_CONTRO << endl;
        }
    }
    //最后一行
    cout << WNH_TABLES_FELT_ON;
    for(unsigned int j = 0; j < tables_unit[line_num-1].value.size(); j++)
    {
        for(unsigned int k = 0; k < tables_unit[line_num-1].value_width[j]; k++)
        {
            cout << WNH_TABLES_CROSS;
        }
        if(j != tables_unit[line_num-1].value.size() - 1)
        {
            cout << WNH_TABLES_CONTRO_ON;
        }
    }
    cout << WNH_TABLES_RIGHT_ON << endl;
}

string wnh_shell_tables::color_transform(string color) //颜色转换
{
    if(color == WNH_COLOR_RESET) return "WNH_COLOR_RESET";
    if(color == WNH_COLOR_BLACK) return "WNH_COLOR_BLACK";
    if(color == WNH_COLOR_RED) return "WNH_COLOR_RED";
    if(color == WNH_COLOR_GREEN) return "WNH_COLOR_GREEN";
    if(color == WNH_COLOR_YELLOW) return "WNH_COLOR_YELLOW";
    if(color == WNH_COLOR_BLUE) return "WNH_COLOR_BLUE";
    if(color == WNH_COLOR_MAGENTA) return "WNH_COLOR_MAGENTA";
    if(color == WNH_COLOR_CYAN) return "WNH_COLOR_CYAN";
    if(color == WNH_COLOR_WHITE) return "WNH_COLOR_WHITE";
    if(color == WNH_COLOR_BOLDBLACK) return "WNH_COLOR_BOLDBLACK";
    if(color == WNH_COLOR_BOLDRED) return "WNH_COLOR_BOLDRED";
    if(color == WNH_COLOR_BOLDGREEN) return "WNH_COLOR_BOLDGREEN";
    if(color == WNH_COLOR_BOLDYELLOW) return "WNH_COLOR_BOLDYELLOW";
    if(color == WNH_COLOR_BOLDBLUE) return "WNH_COLOR_BOLDBLUE";
    if(color == WNH_COLOR_BOLDMAGENTA) return "WNH_COLOR_BOLDMAGENTA";
    if(color == WNH_COLOR_BOLDCYAN) return "WNH_COLOR_BOLDCYAN";
    if(color == WNH_COLOR_BOLDWHITE) return "WNH_COLOR_BOLDWHITE";
    return "null";
}
