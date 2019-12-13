#include "wnh_shell_tables.h"
#include "wnh_shell_tables_add_unit.cpp"
#include "wnh_shell_tables_display_tables.cpp"
#include "wnh_shell_tables_transform.cpp"
#include "wnh_shell_tables_set_unit.cpp"
#include "wnh_shell_tables_add_son_unit.cpp"

wnh_shell_tables::wnh_shell_tables()
{
    WNHDEBUG("wnh_shell_tables 构造");
    line_num = 0;
    max_line_width = 0;
    max_row_num = 0;
    max_line_num = 0;
    is_use_smart_line_width = false;
    local_son_line_num = 0;
}

wnh_shell_tables::~wnh_shell_tables()
{
    WNHDEBUG("~wnh_shell_tables 析构");
}

void wnh_shell_tables::clear() //清理数据
{
    TABLES_LINE tables_unit[WNH_TABLES_MAX_LINE_NUM]; //成员数据保存
    vector<string> tables_unit_son[WNH_TABLES_MAX_LINE_NUM]; //子成员数据保存
    for(int i = 0; i < line_num; i++)
    {
        tables_unit[i].value.clear();
        tables_unit[i].num = 0;
        tables_unit[i].color.clear();
        tables_unit[i].align.clear();
        tables_unit[i].value_width.clear();
        tables_unit[i].split_line_format = WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL;
        tables_unit[i].separator_format.clear();
        tables_unit[i].son_line_num.clear();
    }
    for(int i = 0; i < local_son_line_num; i++)
    {
        tables_unit_son[i].clear();
    }
    line_num = 0;
    max_line_width = 0;
    max_row_num = 0;
    max_line_num = 0;
    is_use_smart_line_width = false;
    local_son_line_num = 0;
}

template <typename Type, typename Types>
bool wnh_shell_tables::copy_vector_values(Type & vec_1, Types & vec_2)
{
    for(unsigned int i = 0; i < vec_2.size(); i++)
    {
        WNHINFO("i:" << i);
        vec_1.push_back(vec_2[i]);
    }
    return true;
}
