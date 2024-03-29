#include "wnh_shell_tables.h"

string wnh_shell_tables::sytle_transform(WNH_SHELL_TABLES_FONT_STYLE color, bool mode) //颜色转换
{
    string temp_ss = "";
    if(mode == true)
    {
        switch (color) {
        case WNH_SHELL_TABLES_FONT_STYLE::RESET:                        return temp_ss = temp_ss + WNH_FONT_COLOR_RESET;

        case WNH_SHELL_TABLES_FONT_STYLE::BLACK:                        return temp_ss = temp_ss + WNH_FONT_COLOR_BLACK;
        case WNH_SHELL_TABLES_FONT_STYLE::RED:                          return temp_ss = temp_ss + WNH_FONT_COLOR_RED;
        case WNH_SHELL_TABLES_FONT_STYLE::GREEN:                        return temp_ss = temp_ss + WNH_FONT_COLOR_GREEN;
        case WNH_SHELL_TABLES_FONT_STYLE::YELLOW:                       return temp_ss = temp_ss + WNH_FONT_COLOR_YELLOW;
        case WNH_SHELL_TABLES_FONT_STYLE::BLUE:                         return temp_ss = temp_ss + WNH_FONT_COLOR_BLUE;
        case WNH_SHELL_TABLES_FONT_STYLE::MAGENTA:                      return temp_ss = temp_ss + WNH_FONT_COLOR_MAGENTA;
        case WNH_SHELL_TABLES_FONT_STYLE::CYAN:                         return temp_ss = temp_ss + WNH_FONT_COLOR_CYAN;
        case WNH_SHELL_TABLES_FONT_STYLE::WHITE:                        return temp_ss = temp_ss + WNH_FONT_COLOR_WHITE;

        case WNH_SHELL_TABLES_FONT_STYLE::BOLDBLACK:                    return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDBLACK;
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDRED:                      return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDRED;
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN:                    return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDGREEN;
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW:                   return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDYELLOW;
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE:                     return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDBLUE;
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA:                  return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDMAGENTA;
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN:                     return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDCYAN;
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDWHITE:                    return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDWHITE;

        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBLACK:                return temp_ss = temp_ss + WNH_FONT_COLOR_BLACK + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGRED:                  return temp_ss = temp_ss + WNH_FONT_COLOR_RED + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGGREEN:                return temp_ss = temp_ss + WNH_FONT_COLOR_GREEN + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGYELLOW:               return temp_ss = temp_ss + WNH_FONT_COLOR_YELLOW + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBLUE:                 return temp_ss = temp_ss + WNH_FONT_COLOR_BLUE + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGMAGENTA:              return temp_ss = temp_ss + WNH_FONT_COLOR_MAGENTA + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGCYAN:                 return temp_ss = temp_ss + WNH_FONT_COLOR_CYAN + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGWHITE:                return temp_ss = temp_ss + WNH_FONT_COLOR_WHITE + WNH_FONT_STYLE_FLASHING;

        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBLACK:               return temp_ss = temp_ss + WNH_FONT_COLOR_BLACK + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINERED:                 return temp_ss = temp_ss + WNH_FONT_COLOR_RED + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEGREEN:               return temp_ss = temp_ss + WNH_FONT_COLOR_GREEN + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEYELLOW:              return temp_ss = temp_ss + WNH_FONT_COLOR_YELLOW + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBLUE:                return temp_ss = temp_ss + WNH_FONT_COLOR_BLUE + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEMAGENTA:             return temp_ss = temp_ss + WNH_FONT_COLOR_MAGENTA + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINECYAN:                return temp_ss = temp_ss + WNH_FONT_COLOR_CYAN + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEWHITE:               return temp_ss = temp_ss + WNH_FONT_COLOR_WHITE + WNH_FONT_STYLE_UNDERLINE;

        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDBLACK:            return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDBLACK + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDRED:              return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDRED + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDGREEN:            return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDGREEN + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDYELLOW:           return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDYELLOW + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDBLUE:             return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDBLUE + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDMAGENTA:          return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDMAGENTA + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDCYAN:             return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDCYAN + WNH_FONT_STYLE_FLASHING;
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDWHITE:            return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDWHITE + WNH_FONT_STYLE_FLASHING;

        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDBLACK:           return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDBLACK + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDRED:             return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDRED + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDGREEN:           return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDGREEN + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDYELLOW:          return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDYELLOW + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDBLUE:            return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDBLUE + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDMAGENTA:         return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDMAGENTA + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDCYAN:            return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDCYAN + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDWHITE:           return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDWHITE + WNH_FONT_STYLE_UNDERLINE;

        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBLACK:       return temp_ss = temp_ss + WNH_FONT_COLOR_BLACK + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGRED:         return temp_ss = temp_ss + WNH_FONT_COLOR_RED + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGGREEN:       return temp_ss = temp_ss + WNH_FONT_COLOR_GREEN + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGYELLOW:      return temp_ss = temp_ss + WNH_FONT_COLOR_YELLOW + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBLUE:        return temp_ss = temp_ss + WNH_FONT_COLOR_BLUE + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGMAGENTA:     return temp_ss = temp_ss + WNH_FONT_COLOR_MAGENTA + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGCYAN:        return temp_ss = temp_ss + WNH_FONT_COLOR_CYAN + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGWHITE:       return temp_ss = temp_ss + WNH_FONT_COLOR_WHITE + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;

        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDBLACK:   return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDBLACK + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDRED:     return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDRED + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDGREEN:   return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDGREEN + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDYELLOW:  return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDYELLOW + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDBLUE:    return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDBLUE + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDMAGENTA: return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDMAGENTA + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDCYAN:    return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDCYAN + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDWHITE:   return temp_ss = temp_ss + WNH_FONT_COLOR_BOLDWHITE + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE;

        default: return temp_ss = "";
        }
    }
    else
    {
        switch (color) {
        case WNH_SHELL_TABLES_FONT_STYLE::RESET:                        return temp_ss = temp_ss + "WNH_FONT_COLOR_RESET";

        case WNH_SHELL_TABLES_FONT_STYLE::BLACK:                        return temp_ss = temp_ss + "WNH_FONT_COLOR_BLACK";
        case WNH_SHELL_TABLES_FONT_STYLE::RED:                          return temp_ss = temp_ss + "WNH_FONT_COLOR_RED";
        case WNH_SHELL_TABLES_FONT_STYLE::GREEN:                        return temp_ss = temp_ss + "WNH_FONT_COLOR_GREEN";
        case WNH_SHELL_TABLES_FONT_STYLE::YELLOW:                       return temp_ss = temp_ss + "WNH_FONT_COLOR_YELLOW";
        case WNH_SHELL_TABLES_FONT_STYLE::BLUE:                         return temp_ss = temp_ss + "WNH_FONT_COLOR_BLUE";
        case WNH_SHELL_TABLES_FONT_STYLE::MAGENTA:                      return temp_ss = temp_ss + "WNH_FONT_COLOR_MAGENTA";
        case WNH_SHELL_TABLES_FONT_STYLE::CYAN:                         return temp_ss = temp_ss + "WNH_FONT_COLOR_CYAN";
        case WNH_SHELL_TABLES_FONT_STYLE::WHITE:                        return temp_ss = temp_ss + "WNH_FONT_COLOR_WHITE";

        case WNH_SHELL_TABLES_FONT_STYLE::BOLDBLACK:                    return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDBLACK";
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDRED:                      return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDRED";
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN:                    return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDGREEN";
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDYELLOW:                   return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDYELLOW";
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE:                     return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDBLUE";
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA:                  return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDMAGENTA";
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN:                     return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDCYAN";
        case WNH_SHELL_TABLES_FONT_STYLE::BOLDWHITE:                    return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDWHITE";

        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBLACK:                return temp_ss = temp_ss + "WNH_FONT_COLOR_BLACK + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGRED:                  return temp_ss = temp_ss + "WNH_FONT_COLOR_RED + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGGREEN:                return temp_ss = temp_ss + "WNH_FONT_COLOR_GREEN + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGYELLOW:               return temp_ss = temp_ss + "WNH_FONT_COLOR_YELLOW + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBLUE:                 return temp_ss = temp_ss + "WNH_FONT_COLOR_BLUE + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGMAGENTA:              return temp_ss = temp_ss + "WNH_FONT_COLOR_MAGENTA + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGCYAN:                 return temp_ss = temp_ss + "WNH_FONT_COLOR_CYAN + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGWHITE:                return temp_ss = temp_ss + "WNH_FONT_COLOR_WHITE + WNH_FONT_STYLE_FLASHING";

        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBLACK:               return temp_ss = temp_ss + "WNH_FONT_COLOR_BLACK + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINERED:                 return temp_ss = temp_ss + "WNH_FONT_COLOR_RED + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEGREEN:               return temp_ss = temp_ss + "WNH_FONT_COLOR_GREEN + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEYELLOW:              return temp_ss = temp_ss + "WNH_FONT_COLOR_YELLOW + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBLUE:                return temp_ss = temp_ss + "WNH_FONT_COLOR_BLUE + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEMAGENTA:             return temp_ss = temp_ss + "WNH_FONT_COLOR_MAGENTA + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINECYAN:                return temp_ss = temp_ss + "WNH_FONT_COLOR_CYAN + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEWHITE:               return temp_ss = temp_ss + "WNH_FONT_COLOR_WHITE + WNH_FONT_STYLE_UNDERLINE";

        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDBLACK:            return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDBLACK + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDRED:              return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDRED + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDGREEN:            return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDGREEN + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDYELLOW:           return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDYELLOW + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDBLUE:             return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDBLUE + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDMAGENTA:          return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDMAGENTA + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDCYAN:             return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDCYAN + WNH_FONT_STYLE_FLASHING";
        case WNH_SHELL_TABLES_FONT_STYLE::FLASHINGBOLDWHITE:            return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDWHITE + WNH_FONT_STYLE_FLASHING";

        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDBLACK:           return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDBLACK + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDRED:             return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDRED + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDGREEN:           return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDGREEN + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDYELLOW:          return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDYELLOW + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDBLUE:            return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDBLUE + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDMAGENTA:         return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDMAGENTA + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDCYAN:            return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDCYAN + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEBOLDWHITE:           return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDWHITE + WNH_FONT_STYLE_UNDERLINE";

        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBLACK:       return temp_ss = temp_ss + "WNH_FONT_COLOR_BLACK + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGRED:         return temp_ss = temp_ss + "WNH_FONT_COLOR_RED + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGGREEN:       return temp_ss = temp_ss + "WNH_FONT_COLOR_GREEN + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGYELLOW:      return temp_ss = temp_ss + "WNH_FONT_COLOR_YELLOW + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBLUE:        return temp_ss = temp_ss + "WNH_FONT_COLOR_BLUE + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGMAGENTA:     return temp_ss = temp_ss + "WNH_FONT_COLOR_MAGENTA + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGCYAN:        return temp_ss = temp_ss + "WNH_FONT_COLOR_CYAN + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGWHITE:       return temp_ss = temp_ss + "WNH_FONT_COLOR_WHITE + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";

        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDBLACK:   return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDBLACK + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDRED:     return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDRED + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDGREEN:   return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDGREEN + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDYELLOW:  return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDYELLOW + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDBLUE:    return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDBLUE + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDMAGENTA: return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDMAGENTA + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDCYAN:    return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDCYAN + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        case WNH_SHELL_TABLES_FONT_STYLE::UNDERLINEFLASHINGBOLDWHITE:   return temp_ss = temp_ss + "WNH_FONT_COLOR_BOLDWHITE + WNH_FONT_STYLE_FLASHING + WNH_FONT_STYLE_UNDERLINE";
        default: return temp_ss = "";
        }
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
















