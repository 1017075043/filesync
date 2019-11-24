#include "wnh_shell_tables.h"

wnh_shell_tables::wnh_shell_tables()
{
    WNHDEBUG("wnh_shell_tables 构造");
    line_num = 0;
    max_line_width = 0;
    max_row_num = 0;
    max_line_num = 0;
    is_use_smart_line_width = false;
}

wnh_shell_tables::~wnh_shell_tables()
{
    WNHDEBUG("~wnh_shell_tables 析构");
}

bool wnh_shell_tables::add_unit(const vector<string> & value) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value)");
    vector<WNH_SHELL_TABLES_FONT_COLOR> color;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        color.push_back(WNH_SHELL_TABLES_FONT_COLOR::RESET);
    }
    return add_unit(value, color);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    vector<WNH_SHELL_TABLES_FONT_COLOR> color;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        color.push_back(WNH_SHELL_TABLES_FONT_COLOR::RESET);
    }
    return add_unit(value, color, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width)");
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        align.push_back(WNH_SHELL_TABLES_ALIGN_MODE::centro);
    }
    return add_unit(value, value_width, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        align.push_back(WNH_SHELL_TABLES_ALIGN_MODE::centro);
    }
    return add_unit(value, color, align);
}


bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    return add_unit(value, color, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    vector<unsigned int> value_width;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        value_width.push_back(value[i].length() - get_chinese_num(value[i]));
    }
    is_use_smart_line_width = true;
    return add_unit(value, value_width, color, align);
}


bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width)");
    return add_unit(value, value_width, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    vector<WNH_SHELL_TABLES_FONT_COLOR> color;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        color.push_back(WNH_SHELL_TABLES_FONT_COLOR::RESET);
    }
    return add_unit(value, value_width, color, align);
}


bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width)");
    return add_unit(value, value_width, color);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        align.push_back(WNH_SHELL_TABLES_ALIGN_MODE::centro);
    }
    return add_unit(value, value_width, color, align);
}


bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    return add_unit(value, value_width, color, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    return add_unit(value, value_width, color, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width)");
    return add_unit(value, value_width, color, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width)");
    return add_unit(value, value_width, color, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    return add_unit(value, value_width, color, align);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    if(value.size() != value_width.size() || value.size() != color.size() || value.size() != align.size())
    {
        WNHWARN("数据残缺, 成员值数量=" << value.size() << ", 颜色数量=" << color.size() << ", 对齐数量=" << align.size());
        return false;
    }
    tables_unit[line_num].value = value;
    tables_unit[line_num].color = color;
    tables_unit[line_num].align = align;
    tables_unit[line_num].value_width = value_width;
    tables_unit[line_num].num = value.size();

    if(max_row_num < tables_unit[line_num].num)
    {
        max_row_num = tables_unit[line_num].num;
    }
    int now_line_width = 0;
    for(int i = 0; i < tables_unit[line_num].num; i ++)
    {
        now_line_width = now_line_width + tables_unit[line_num].value_width[i] + 1;
        //tables_unit[line_num].value_width.push_back(tables_unit[line_num].value[i].length() - get_chinese_num(tables_unit[line_num].value[i]));
        //now_line_width = now_line_width + (tables_unit[line_num].value[i].length() - get_chinese_num(tables_unit[line_num].value[i])) + 1;
    }
    now_line_width --;
    if(now_line_width > max_line_width)
    {
        max_line_width = now_line_width;
        //WNHINFO("更新max_line_width=" << max_line_width);
        max_line_num = line_num;
    }
    line_num ++;
    return true;
}

void wnh_shell_tables::smart_line_width() //智能列宽
{
    for(int i = 0; i < line_num; i ++)
    {
        int now_line_width = 0;
        while(now_line_width < max_line_width)
        {
            now_line_width = 0;
            for(int j = 0; j < tables_unit[i].num; j ++)
            {
                now_line_width = now_line_width + tables_unit[i].value_width[j];
                //WNHINFO("-0-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width << ", value_width=" << tables_unit[i].value_width[j]);
                if(now_line_width < max_line_width)
                {
                    now_line_width = now_line_width + 1;
                    tables_unit[i].value_width[j] = tables_unit[i].value_width[j] + 1;
                    WNHINFO("-1-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width << ", value_width=" << tables_unit[i].value_width[j]);
                }
                else
                {
                    WNHINFO("-2-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width << ", value_width=" << tables_unit[i].value_width[j]);
                    break;
                }
                WNHINFO("-3-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width << ", value_width=" << tables_unit[i].value_width[j]);
            }
            WNHINFO("-4-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width);
        }
        now_line_width = 0;
        for(int j = 0; j < tables_unit[i].num; j ++)
        {
            //WNHINFO("smart_line_width:j=" << j);
            now_line_width = now_line_width + tables_unit[i].value_width[j];
        }
        if(now_line_width != max_line_width)
        {
            while(1)
            {
                if(now_line_width == max_line_width)
                {
                    break;
                }
                for(int j = 0; j < tables_unit[i].num; j ++)
                {
                    if(now_line_width == max_line_width)
                    {
                        break;
                    }
                    if(now_line_width > max_line_width)
                    {
                        tables_unit[i].value_width[j] --;
                        now_line_width --;
                    }
                    else if(now_line_width < max_line_width)
                    {
                        tables_unit[i].value_width[j] ++;
                        now_line_width ++;
                    }
                }
            }
        }
        for(int j = 0; j < tables_unit[i].num - 1; j ++)
        {
            tables_unit[i].value_width[j] --;
        }
    }
}

void wnh_shell_tables::show_unit() //显示成员
{
    for(int i = 0; i < line_num; i ++)
    {
        for(int j = 0; j < tables_unit[i].num; j++)
        {
            WNHINFO("tables_unit[" << i << "].unit[" << j << "]: value=" << tables_unit[i].value[j] << ", color=" << color_transform(tables_unit[i].color[j], false) << ", align=" << align_transform(tables_unit[i].align[j]) << ", value_width=" << tables_unit[i].value_width[j]);
        }
    }
}

void wnh_shell_tables::show_tables() //显示表格
{
    if(line_num == 0)
    {
        return;
    }
    if(is_use_smart_line_width == true)
    {
        smart_line_width();
    }
    //第一行
    cout << WNH_TABLES_FELT_UNDER;
    for(int j = 0; j < tables_unit[0].num; j++)
    {
        for(unsigned int k = 0; k < tables_unit[0].value_width[j]; k++)
        {
            cout << WNH_TABLES_CROSS;
        }
        if(j != tables_unit[0].num - 1)
        {
            cout << WNH_TABLES_CONTRO_UNDER;
        }
    }
    cout << WNH_TABLES_RIGHT_UNDER << endl;
    //中间行
    for(int i = 0; i < line_num; i ++)
    {
        cout << WNH_TABLES_VERTICAL;
        for(int j = 0; j < tables_unit[i].num; j++)
        {
            if(tables_unit[i].align[j] == WNH_SHELL_TABLES_ALIGN_MODE::right)
            {
                cout << color_transform(tables_unit[i].color[j], true) << format_string_left_fill(tables_unit[i].value[j], tables_unit[i].value_width[j] - 1, ' ') << WNH_TABLES_VERTICAL;
            }
            else if(tables_unit[i].align[j] == WNH_SHELL_TABLES_ALIGN_MODE::centro)
            {
                cout << color_transform(tables_unit[i].color[j], true) << format_string_centro_fill(tables_unit[i].value[j], tables_unit[i].value_width[j] - 1, ' ') << WNH_TABLES_VERTICAL;
            }
            else if(tables_unit[i].align[j] == WNH_SHELL_TABLES_ALIGN_MODE::left)
            {
                cout << color_transform(tables_unit[i].color[j], true) << format_string_right_fill(tables_unit[i].value[j], tables_unit[i].value_width[j] - 1, ' ') << WNH_TABLES_VERTICAL;
            }
        }
        cout << endl;
        int temp_s = 0;
        if(i != line_num - 1)
        {
            cout << WNH_TABLES_FELT_CONTRO;
            for(int j = 0; j < max_line_width; j++)
            {
                int temp_b = -1;
                for(int k = 0; k < tables_unit[i].num - 1; k ++)
                {
                    temp_b = temp_b + tables_unit[i].value_width[k] + 1;
                    if(j == temp_b)
                    {
                        temp_s = temp_s + 1;
                        break;
                    }
                }
                temp_b = -1;
                for(int k = 0; k < tables_unit[i + 1].num - 1; k ++)
                {
                    temp_b = temp_b + tables_unit[i + 1].value_width[k] + 1;
                    if(j == temp_b)
                    {
                        temp_s = temp_s + 2;
                        break;
                    }
                }
                if(temp_s == 0)
                {
                    cout << WNH_TABLES_CROSS;
                }
                else if(temp_s == 1)
                {
                    cout << WNH_TABLES_CONTRO_ON;
                    temp_s = 0;
                }
                else if(temp_s == 2)
                {
                    cout << WNH_TABLES_CONTRO_UNDER;
                    temp_s = 0;
                }
                else if(temp_s == 3)
                {
                    cout << WNH_TABLES_CONTRO_CONTRO;
                    temp_s = 0;
                }
            }
            cout << WNH_TABLES_RIGHT_CONTRO << endl;
        }
    }
    //最后一行
    cout << WNH_TABLES_FELT_ON;
    for(int j = 0; j < tables_unit[line_num-1].num; j++)
    {
        for(unsigned int k = 0; k < tables_unit[line_num-1].value_width[j]; k++)
        {
            cout << WNH_TABLES_CROSS;
        }
        if(j != tables_unit[line_num-1].num - 1)
        {
            cout << WNH_TABLES_CONTRO_ON;
        }
    }
    cout << WNH_TABLES_RIGHT_ON << endl;
}

string wnh_shell_tables::color_transform(WNH_SHELL_TABLES_FONT_COLOR color, bool mode) //颜色转换
{
    if(mode == true)
    {
        if(color == WNH_SHELL_TABLES_FONT_COLOR::RESET) return WNH_COLOR_RESET;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BLACK) return WNH_COLOR_BLACK;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::RED) return WNH_COLOR_RED;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::GREEN) return WNH_COLOR_GREEN;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::YELLOW) return WNH_COLOR_YELLOW;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BLUE) return WNH_COLOR_BLUE;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::MAGENTA) return WNH_COLOR_MAGENTA;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::CYAN) return WNH_COLOR_CYAN;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::WHITE) return WNH_COLOR_WHITE;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDBLACK) return WNH_COLOR_BOLDBLACK;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDRED) return WNH_COLOR_BOLDRED;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDGREEN) return WNH_COLOR_BOLDGREEN;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDYELLOW) return WNH_COLOR_BOLDYELLOW;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDBLUE) return WNH_COLOR_BOLDBLUE;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDMAGENTA) return WNH_COLOR_BOLDMAGENTA;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDCYAN) return WNH_COLOR_BOLDCYAN;
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDWHITE) return WNH_COLOR_BOLDWHITE;
        return "null";
    }
    else
    {
        if(color == WNH_SHELL_TABLES_FONT_COLOR::RESET) return "WNH_COLOR_RESET";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BLACK) return "WNH_COLOR_BLACK";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::RED) return "WNH_COLOR_RED";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::GREEN) return "WNH_COLOR_GREEN";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::YELLOW) return "WNH_COLOR_YELLOW";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BLUE) return "WNH_COLOR_BLUE";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::MAGENTA) return "WNH_COLOR_MAGENTA";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::CYAN) return "WNH_COLOR_CYAN";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::WHITE) return "WNH_COLOR_WHITE";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDBLACK) return "WNH_COLOR_BOLDBLACK";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDRED) return "WNH_COLOR_BOLDRED";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDGREEN) return "WNH_COLOR_BOLDGREEN";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDYELLOW) return "WNH_COLOR_BOLDYELLOW";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDBLUE) return "WNH_COLOR_BOLDBLUE";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDMAGENTA) return "WNH_COLOR_BOLDMAGENTA";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDCYAN) return "WNH_COLOR_BOLDCYAN";
        if(color == WNH_SHELL_TABLES_FONT_COLOR::BOLDWHITE) return "WNH_COLOR_BOLDWHITE";
        return "null";
    }
}

string wnh_shell_tables::align_transform(WNH_SHELL_TABLES_ALIGN_MODE align) //对齐方式转换
{
    if(align == WNH_SHELL_TABLES_ALIGN_MODE::right) return "right";
    if(align == WNH_SHELL_TABLES_ALIGN_MODE::centro) return "centro";
    if(align == WNH_SHELL_TABLES_ALIGN_MODE::left) return "left";
    return "null";
}
















