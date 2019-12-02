#include "wnh_shell_tables.h"

bool wnh_shell_tables::add_unit(const vector<string> & value, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value)");
    vector<WNH_SHELL_TABLES_FONT_COLOR> color;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        color.push_back(WNH_SHELL_TABLES_FONT_COLOR::RESET);
    }
    return add_unit(value, color, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    vector<WNH_SHELL_TABLES_FONT_COLOR> color;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        color.push_back(WNH_SHELL_TABLES_FONT_COLOR::RESET);
    }
    return add_unit(value, color, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width)");
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        align.push_back(WNH_SHELL_TABLES_ALIGN_MODE::centro);
    }
    return add_unit(value, value_width, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        align.push_back(WNH_SHELL_TABLES_ALIGN_MODE::centro);
    }
    return add_unit(value, color, align, split_line_format);
}


bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    return add_unit(value, color, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    vector<unsigned int> value_width;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        value_width.push_back(value[i].length() - get_chinese_num(value[i]));
    }
    is_use_smart_line_width = true;
    return add_unit(value, value_width, color, align, split_line_format);
}


bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width)");
    return add_unit(value, value_width, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    vector<WNH_SHELL_TABLES_FONT_COLOR> color;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        color.push_back(WNH_SHELL_TABLES_FONT_COLOR::RESET);
    }
    return add_unit(value, value_width, color, align, split_line_format);
}


bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width)");
    return add_unit(value, value_width, color, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    for(unsigned int i = 0; i < value.size(); i ++)
    {
        align.push_back(WNH_SHELL_TABLES_ALIGN_MODE::centro);
    }
    return add_unit(value, value_width, color, align, split_line_format);
}


bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    return add_unit(value, value_width, color, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align)");
    return add_unit(value, value_width, color, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width)");
    return add_unit(value, value_width, color, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<unsigned int> & value_width)");
    return add_unit(value, value_width, color, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
{
    //WNHINFO("bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color)");
    return add_unit(value, value_width, color, align, split_line_format);
}

bool wnh_shell_tables::add_unit(const vector<string> & value, const vector<unsigned int> & value_width, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color, const vector<WNH_SHELL_TABLES_ALIGN_MODE> & align, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT & split_line_format) //添加成员数据
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
    tables_unit[line_num].split_line_format = split_line_format;

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
