#ifndef __wnh_base_class__
#define __wnh_base_class__

using namespace std;

#include <vector>
#include <cctype>
#include <string>
#include <algorithm>

#include "../wnh_define/wnh_base_define.h"
#include "../wnh_define/wnh_base_define_function.h"
#include "../wnh_define/wnh_tips_define.h"

//#define LEFTSTRIP 0 //左填充
//#define RIGHTSTRIP 1 //右填充
//#define BOTHSTRIP 2 //左右填充

class wnh_base_class
{
public:
    wnh_base_class();
    ~wnh_base_class();
    void trim(string &s, const string &mark);//去掉首尾空格
    void delete_last_char(string &s, const char &mark);//删除最后一个字符

    string & replace_all(string & str, const string & old_value, const string & new_value); //字符串替换(循环)
    string & replace_all_distinct(string & str, const string & old_value, const string & new_value); //字符串替换

    string format_string_left_fill(const string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串左填充到指定长度
    void format_string_left_fill_v1(string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串左填充到指定长度
    string format_string_left_fill(const string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串左填充到指定长度
    void format_string_left_fill_v1(string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串左填充到指定长度

    string format_string_right_fill(const string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串右填充到指定长度
    void format_string_right_fill_v1(string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串右填充到指定长度
    string format_string_right_fill(const string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串右填充到指定长度
    void format_string_right_fill_v1(string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串右填充到指定长度

    string format_string_centro_fill(const string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串左右填充到指定长度
    void format_string_right_centro_v1(string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串左右填充到指定长度
    string format_string_centro_fill(const string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串左右填充到指定长度
    void format_string_right_centro_v1(string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串左右填充到指定长度

    unsigned long get_capital_letters_num(const string & str); //获取大写字母的数量
    unsigned long get_lower_letters_num(const string & str); //获取小写字母的数量
    unsigned long get_digital_num(const string & str); //获取数字的数量
    unsigned long get_chinese_num(const string & str); //获取中文的数量
    string to_upper_string(const string & strs); //将str中的字母转为大写字母
    string to_lower_string(const string & strs); //将str中的字母转为小写字母

    string safe_str_substr_left(string & str, const int & num); //安全的字符串切割(从左到右),处理切割到临界点是中文会乱码的问题
    int transform_display_width(const string & str, const int & display_width); //转换显示宽度为字符串长度

    //template <typename Type_v, typename Type>
    //void set_vector_values(Type_v & values, const Type & arg); //设置vector变量值

    //template <typename Type_v, typename Type, typename ... Types>
    //void set_vector_values(Type_v & values, const Type & arg,const Types & ... args); //设置vector变量值

    //template <typename Type>
    //void print(const Type & arg);

    //template <typename Type, typename ... Types>
    //void print(const Type & arg,const Types & ... args);

    //template <typename T> string to_binary(T value);//将任意进制的值转换为二进制

};

#endif
