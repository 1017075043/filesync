#ifndef __wnh_base_class__
#define __wnh_base_class__

using namespace std;

#include <vector>

#include "../wnh_define/wnh_base_define.h"
#include "../wnh_define/wnh_base_define_function.h"
#include "../wnh_define/wnh_tips_define.h"


#define LEFTSTRIP 0
#define RIGHTSTRIP 1
#define BOTHSTRIP 2

class wnh_base_class
{
public:
    wnh_base_class();
    ~wnh_base_class();
    void trim(string &s, const string &mark);//去掉首尾空格
    void delete_last_char(string &s, const char &mark);//删除最后一个字符

    string & replace_all(string & str, const string & old_value, const string & new_value); //字符串替换(循环)
    string & replace_all_distinct(string & str, const string & old_value, const string & new_value); //字符串替换
    string format_string_right_fill(const string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串右填充到指定长度
    void format_string_right_fill_v1(string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串右填充到指定长度
    string format_string_right_fill(const string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串右填充到指定长度
    void format_string_right_fill_v1(string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串右填充到指定长度
    string format_string_centre_fill(const string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串左右填充到指定长度
    void format_string_right_centre_v1(string & str, const unsigned int & length, const string & chr); //使用指定字符将字符串左右填充到指定长度
    string format_string_centre_fill(const string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串左右填充到指定长度
    void format_string_right_centre_v1(string & str, const unsigned int & length, const char & chr); //使用指定字符将字符串左右填充到指定长度


    //template <typename T> string to_binary(T value);//将任意进制的值转换为二进制

};

#endif