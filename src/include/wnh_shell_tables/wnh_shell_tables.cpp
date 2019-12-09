#include "wnh_shell_tables.h"
#include "wnh_shell_tables_add_unit.cpp"
#include "wnh_shell_tables_display_tables.cpp"
#include "wnh_shell_tables_transform.cpp"
#include "wnh_shell_tables_set_unit.cpp"

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
