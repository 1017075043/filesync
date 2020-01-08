#include "wnh_shell_tables.h"

bool wnh_shell_tables::add_son_unit(const int & num) //添加子行
{
    bool is_repeat = false;
    vector<string> tables_unit_son_temp;
    for(int i = 0; i < tables_unit[num].num; i ++)
    {
        unsigned int values_display_width = tables_unit[num].value[i].size() - get_chinese_num(tables_unit[num].value[i]);
        if(values_display_width > tables_unit[num].value_width[i])
        {
            //WNHINFO(tables_unit[num].value[i] << ", 长度:" << tables_unit[num].value[i].size() << ", 中文个数:" << get_chinese_num(tables_unit[num].value[i]) << ", 非中文个数:" << tables_unit[num].value[i].size() - get_chinese_num(tables_unit[num].value[i]) * 3 << ", 在shell显示占用的宽度：" << tables_unit[num].value[i].size() - get_chinese_num(tables_unit[num].value[i]));
            string str_temp = tables_unit[num].value[i];
            string new_str_temp = safe_str_substr_left(str_temp, transform_display_width(str_temp, tables_unit[num].value_width[i] - 1));
            tables_unit_son_temp.push_back(new_str_temp);
            tables_unit[num].value[i] = str_temp;
            WNHDEBUG("str_temp:" << str_temp << ", new_str_temp:" << new_str_temp);
            if(new_str_temp.size() - get_chinese_num(new_str_temp) > tables_unit[num].value_width[i])
            {
                is_repeat = true;
            }
        }
        else
        {
            tables_unit_son_temp.push_back("");
        }
        WNHDEBUG(tables_unit[num].value[i] << ", 长度:" << tables_unit[line_num].value[i].size() << ", 中文个数:" << get_chinese_num(tables_unit[line_num].value[i]) << ", 非中文个数:" << tables_unit[line_num].value[i].size() - get_chinese_num(tables_unit[line_num].value[i]) * 3 << ", 在shell显示占用的宽度：" << tables_unit[line_num].value[i].size() - get_chinese_num(tables_unit[line_num].value[i]));
    }
    tables_unit_son[local_son_line_num] = tables_unit_son_temp;
    WNHDEBUG("数量:" << tables_unit_son[local_son_line_num].size());
    tables_unit[num].son_line_num.push_back(local_son_line_num);
    local_son_line_num = local_son_line_num + 1;
    if(is_repeat == true)
    {
        WNHDEBUG("需要再一次添加子行");
        add_son_unit(num, local_son_line_num - 1);
    }
    else
    {
        WNHDEBUG("一次添加子行就可以了");
    }
    return true;
}


bool wnh_shell_tables::add_son_unit(const int & num, const int & son_num) //添加子行
{
    bool is_repeat = false;
    vector<string> tables_unit_son_temp;
    for(int i = 0; i < (int)tables_unit_son[son_num].size(); i ++)
    {
        unsigned int values_display_width = tables_unit_son[son_num][i].size() - get_chinese_num(tables_unit_son[son_num][i]);
        if(values_display_width > tables_unit[num].value_width[i])
        {
            //WNHINFO(tables_unit[num].value[i] << ", 长度:" << tables_unit[num].value[i].size() << ", 中文个数:" << get_chinese_num(tables_unit[num].value[i]) << ", 非中文个数:" << tables_unit[num].value[i].size() - get_chinese_num(tables_unit[num].value[i]) * 3 << ", 在shell显示占用的宽度：" << tables_unit[num].value[i].size() - get_chinese_num(tables_unit[num].value[i]));
            string str_temp = tables_unit_son[son_num][i];
            string new_str_temp = safe_str_substr_left(str_temp, transform_display_width(str_temp, tables_unit[num].value_width[i] - 1));
            tables_unit_son_temp.push_back(new_str_temp);
            tables_unit_son[son_num][i] = str_temp;
            WNHDEBUG("str_temp:" << str_temp << ", new_str_temp:" << new_str_temp);
            if(new_str_temp.size() - get_chinese_num(new_str_temp) > tables_unit[num].value_width[i])
            {
                is_repeat = true;
            }
        }
        else
        {
            tables_unit_son_temp.push_back("");
        }
        WNHDEBUG(tables_unit[num].value[i] << ", 长度:" << tables_unit[line_num].value[i].size() << ", 中文个数:" << get_chinese_num(tables_unit[line_num].value[i]) << ", 非中文个数:" << tables_unit[line_num].value[i].size() - get_chinese_num(tables_unit[line_num].value[i]) * 3 << ", 在shell显示占用的宽度：" << tables_unit[line_num].value[i].size() - get_chinese_num(tables_unit[line_num].value[i]));

    }
    tables_unit_son[local_son_line_num] = tables_unit_son_temp;
    WNHDEBUG("数量:" << tables_unit_son[local_son_line_num].size());
    tables_unit[num].son_line_num.push_back(local_son_line_num);
    local_son_line_num = local_son_line_num + 1;
    if(is_repeat == true)
    {
        WNHDEBUG("需要再一次添加子行");
        add_son_unit(num, local_son_line_num - 1);
    }
    else
    {
        WNHDEBUG("一次添加子行就可以了");
    }
    return true;
}
