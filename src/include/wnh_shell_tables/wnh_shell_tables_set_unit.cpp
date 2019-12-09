#include "wnh_shell_tables.h"

bool wnh_shell_tables::set_unit(const int & num, const vector<WNH_SHELL_TABLES_FONT_COLOR> & color) //设置成员渲染颜色
{
    if(num < line_num)
    {
        if(color.size() == (unsigned int)tables_unit[num].num)
        {
            tables_unit[num].color = color;
            WNHDEBUG("成功设置行颜色, num=" << num );
            return true;
        }
        else
        {
            WNHWARN("设置行颜色异常, 数据残缺, num=" << num << ", 目标成员值数量=" << tables_unit[num].num << ", 颜色数量=" << color.size());
        }
    }
    else
    {
        WNHWARN("设置行颜色异常, 下标溢出, num=" << num << ", line_num=" << line_num);
    }
    return false;
}

bool wnh_shell_tables::set_unit(const int & num, const vector<WNH_SHELL_TABLES_ALIGN_MODE> align) //设置成员对齐方式
{
    if(num < line_num)
    {
        if(align.size() == (unsigned int)tables_unit[num].num)
        {
            tables_unit[num].align = align;
            WNHDEBUG("成功设置行对齐方式, num=" << num );
            return true;
        }
        else
        {
            WNHWARN("设置行对齐方式异常, 数据残缺, num=" << num << ", 目标成员值数量=" << tables_unit[num].num << ", 对齐方式数量=" << align.size());
        }
    }
    else
    {
        WNHWARN("设置行行对齐方式异常, 下标溢出, num=" << num << ", line_num=" << line_num);
    }
    return false;
}

bool wnh_shell_tables::set_unit(const int & num, const vector<unsigned int> value_width) //设置成员使用的宽度
{
    if(num < line_num)
    {
        if(value_width.size() == (unsigned int)tables_unit[num].num)
        {
            tables_unit[num].value_width = value_width;
            WNHDEBUG("成功设置行使用的宽度, num=" << num );
            return true;
        }
        else
        {
            WNHWARN("设置行使用的宽度异常, 数据残缺, num=" << num << ", 目标成员值数量=" << tables_unit[num].num << ", 使用的宽度数量=" << value_width.size());
        }
    }
    else
    {
        WNHWARN("设置行使用的宽度异常, 下标溢出, num=" << num << ", line_num=" << line_num);
    }
    return false;
}

bool wnh_shell_tables::set_unit(const int & num, const WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format) //设置分割线模式
{
    if(num < line_num)
    {
        tables_unit[num].split_line_format = split_line_format;
        WNHDEBUG("成功设置分割线模式, num=" << num );
    }
    else
    {
        WNHWARN("设置分割线模式异常, 下标溢出, num=" << num << ", line_num=" << line_num);
    }
    return false;
}

bool wnh_shell_tables::set_unit(const int & num, const vector<bool> separator_format) //设置成员分隔符模式
{
    if(num < line_num)
    {
        if(separator_format.size() == (unsigned int)tables_unit[num].num)
        {
            tables_unit[num].separator_format = separator_format;
            WNHDEBUG("成功设置分隔符模式, num=" << num );
            return true;
        }
        else
        {
            WNHWARN("设置行分隔符模式异常, 数据残缺, num=" << num << ", 目标成员值数量=" << tables_unit[num].num << ", 分隔符模式数量=" << separator_format.size());
        }
    }
    else
    {
        WNHWARN("设置分隔符模式异常, 下标溢出, num=" << num << ", line_num=" << line_num);
    }
    return false;
}
