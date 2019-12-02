#include "wnh_shell_tables.h"

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

string wnh_shell_tables::split_line_format_transform(WNH_SHELL_TABLES_SPLIT_LINE_FORMAT split_line_format) //分隔行格式转换
{
    if(split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::NORMAL) return "NORMAL";
    if(split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::EMPTY) return "EMPTY";
    if(split_line_format == WNH_SHELL_TABLES_SPLIT_LINE_FORMAT::REPEAT) return "REPEAT";
    return "null";
}
















