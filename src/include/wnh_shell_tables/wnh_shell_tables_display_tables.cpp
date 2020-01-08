#include "wnh_shell_tables.h"

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
                    //WNHINFO("-1-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width << ", value_width=" << tables_unit[i].value_width[j]);
                }
                else
                {
                    //WNHINFO("-2-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width << ", value_width=" << tables_unit[i].value_width[j]);
                    break;
                }
                //WNHINFO("-3-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width << ", value_width=" << tables_unit[i].value_width[j]);
            }
            //WNHINFO("-4-smart_line_width:i=" << i << ", now_line_width=" << now_line_width << ", max_line_width=" << max_line_width);
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
            WNHINFO("tables_unit[" << i << "].unit[" << j << "]: value=" << tables_unit[i].value[j] << ", color=" << sytle_transform(tables_unit[i].color[j], false) << ", align=" << align_transform(tables_unit[i].align[j]) << ", value_width=" << tables_unit[i].value_width[j] << ", split_line_format=" << split_line_format_transform(tables_unit[i].split_line_format));
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
            if(tables_unit[0].separator_format[j])
            {
                cout << WNH_TABLES_CONTRO_UNDER;
            }
            else
            {
                cout << WNH_TABLES_CROSS;
            }
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
                //WNHDEBUG("0");
                if(tables_unit[i].separator_format[j] || j == tables_unit[i].num -1)
                {
                    //WNHDEBUG("1");
                    cout << sytle_transform(tables_unit[i].color[j], true) << format_string_left_fill(tables_unit[i].value[j], tables_unit[i].value_width[j], ' ') << WNH_TABLES_VERTICAL;
                }
                else
                {
                    //WNHDEBUG("2");
                    cout << sytle_transform(tables_unit[i].color[j], true) << format_string_left_fill(tables_unit[i].value[j], tables_unit[i].value_width[j], ' ') << " ";
                }
            }
            else if(tables_unit[i].align[j] == WNH_SHELL_TABLES_ALIGN_MODE::centro)
            {
                if(tables_unit[i].separator_format[j] || j == tables_unit[i].num -1)
                {
                    //WNHDEBUG("3");
                    cout << sytle_transform(tables_unit[i].color[j], true) << format_string_centro_fill(tables_unit[i].value[j], tables_unit[i].value_width[j], ' ') << WNH_TABLES_VERTICAL;
                    //WNHDEBUG("4");
                }
                else
                {
                    //WNHDEBUG("4");
                    cout << sytle_transform(tables_unit[i].color[j], true) << format_string_centro_fill(tables_unit[i].value[j], tables_unit[i].value_width[j], ' ') << " ";
                }
            }
            else if(tables_unit[i].align[j] == WNH_SHELL_TABLES_ALIGN_MODE::left)
            {
                if(tables_unit[i].separator_format[j] || j == tables_unit[i].num -1)
                {
                    //WNHDEBUG("5");
                    cout << sytle_transform(tables_unit[i].color[j], true) << format_string_right_fill(tables_unit[i].value[j], tables_unit[i].value_width[j], ' ') << WNH_TABLES_VERTICAL;
                }
                else
                {
                    //WNHDEBUG("6");
                    cout << sytle_transform(tables_unit[i].color[j], true) << format_string_right_fill(tables_unit[i].value[j], tables_unit[i].value_width[j], ' ') << " ";
                }
            }
        }
        cout << endl;
        //判断是否存在子行
        //WNHWARN(tables_unit[i].son_line_num.size());
        for(int k = 0; k < (int)tables_unit[i].son_line_num.size(); k++)
        {
            cout << WNH_TABLES_VERTICAL;
            for(int j = 0; j < tables_unit[i].num; j++)
            {
                if(is_son_line_align_left == true)
                {
                    if(tables_unit[i].separator_format[j] || j == tables_unit[i].num -1)
                    {
                        cout << sytle_transform(tables_unit[i].color[j], true) << format_string_right_fill(tables_unit_son[tables_unit[i].son_line_num[k]][j], tables_unit[i].value_width[j], ' ') << WNH_TABLES_VERTICAL;
                    }
                    else
                    {
                        cout << sytle_transform(tables_unit[i].color[j], true) << format_string_right_fill(tables_unit_son[tables_unit[i].son_line_num[k]][j], tables_unit[i].value_width[j], ' ') << " ";
                    }
                }
                else
                {
                    if(tables_unit[i].align[j] == WNH_SHELL_TABLES_ALIGN_MODE::right)
                    {
                        if(tables_unit[i].separator_format[j] || j == tables_unit[i].num -1)
                        {
                            cout << sytle_transform(tables_unit[i].color[j], true) << format_string_left_fill(tables_unit_son[tables_unit[i].son_line_num[k]][j], tables_unit[i].value_width[j], ' ') << WNH_TABLES_VERTICAL;
                        }
                        else
                        {
                            cout << sytle_transform(tables_unit[i].color[j], true) << format_string_left_fill(tables_unit_son[tables_unit[i].son_line_num[k]][j], tables_unit[i].value_width[j], ' ') << " ";
                        }
                    }
                    else if(tables_unit[i].align[j] == WNH_SHELL_TABLES_ALIGN_MODE::centro)
                    {
                        if(tables_unit[i].separator_format[j] || j == tables_unit[i].num -1)
                        {
                            cout << sytle_transform(tables_unit[i].color[j], true) << format_string_centro_fill(tables_unit_son[tables_unit[i].son_line_num[k]][j], tables_unit[i].value_width[j], ' ') << WNH_TABLES_VERTICAL;
                        }
                        else
                        {
                            cout << sytle_transform(tables_unit[i].color[j], true) << format_string_centro_fill(tables_unit_son[tables_unit[i].son_line_num[k]][j], tables_unit[i].value_width[j], ' ') << " ";
                        }
                    }
                    else if(tables_unit[i].align[j] == WNH_SHELL_TABLES_ALIGN_MODE::left)
                    {
                        if(tables_unit[i].separator_format[j] || j == tables_unit[i].num -1)
                        {
                            cout << sytle_transform(tables_unit[i].color[j], true) << format_string_right_fill(tables_unit_son[tables_unit[i].son_line_num[k]][j], tables_unit[i].value_width[j], ' ') << WNH_TABLES_VERTICAL;
                        }
                        else
                        {
                            cout << sytle_transform(tables_unit[i].color[j], true) << format_string_right_fill(tables_unit_son[tables_unit[i].son_line_num[k]][j], tables_unit[i].value_width[j], ' ') << " ";
                        }
                    }
                }
            }
            cout << endl;
        }
        //中间分隔行
        //根据重复次数来打印中间分隔行的行数
        for(int r = 0 ; r < get_repeat_num(tables_unit[i].split_line_format); r ++)
        {
            int temp_s = 0;
            if(i != line_num - 1)
            {
                cout << WNH_TABLES_FELT_CONTRO;
                for(int j = 0; j < max_line_width; j++)
                {
                    //计算出当前分隔行中列分隔符的模式
                    //temp_s: 0 = WNH_TABLES_CROSS, 1 = WNH_TABLES_CONTRO_ON, 2 = WNH_TABLES_CONTRO_UNDER, 3 = WNH_TABLES_CONTRO_CONTRO
                    int temp_b = -1;
                    for(int k = 0; k < tables_unit[i].num - 1; k ++)
                    {
                        temp_b = temp_b + tables_unit[i].value_width[k] + 1;
                        if(j == temp_b && tables_unit[i].separator_format[k])
                        {
                            temp_s = temp_s + 1;
                            break;
                        }
                    }
                    temp_b = -1;
                    for(int k = 0; k < tables_unit[i + 1].num - 1; k ++)
                    {
                        temp_b = temp_b + tables_unit[i + 1].value_width[k] + 1;
                        if(j == temp_b && tables_unit[i + 1].separator_format[k])
                        {
                            temp_s = temp_s + 2;
                            break;
                        }
                    }
                    if(temp_s == 0)
                    {
                        if(tables_unit[i].split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL)
                        {
                            cout << WNH_TABLES_CROSS;
                        }
                        else if(tables_unit[i].split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT)
                        {
                            if(r == 0)
                            {
                                cout << WNH_TABLES_CONTRO_UNDER;
                            }
                            else if(r == 1)
                            {
                                cout << WNH_TABLES_CONTRO_ON;
                            }
                        }
                    }
                    else if(temp_s == 1)
                    {
                        if(tables_unit[i].split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT && r == 0)
                        {
                            cout << WNH_TABLES_CONTRO_CONTRO;
                        }
                        else
                        {
                            cout << WNH_TABLES_CONTRO_ON;
                        }
                        temp_s = 0;
                    }
                    else if(temp_s == 2)
                    {
                        if(tables_unit[i].split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT && r == 1)
                        {
                            cout << WNH_TABLES_CONTRO_CONTRO;
                        }
                        else
                        {
                            cout << WNH_TABLES_CONTRO_UNDER;
                        }
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
            if(tables_unit[line_num-1].separator_format[j])
            {
                cout << WNH_TABLES_CONTRO_ON;
            }
            else
            {
                cout << WNH_TABLES_CROSS;
            }
        }
    }
    cout << WNH_TABLES_RIGHT_ON << endl;
}

int wnh_shell_tables::get_repeat_num(WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format) //获取重复次数
{
    if(split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL) return 1;
    if(split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY) return 0;
    if(split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT) return 2;
    return 0;
}
