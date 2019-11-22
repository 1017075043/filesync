#include "wnh_base_class.h"

wnh_base_class::wnh_base_class()
{
    WNHDEBUG("wnh_base_class 构造");
}

wnh_base_class::~wnh_base_class()
{
    WNHDEBUG("~wnh_base_class 析构");
}

void wnh_base_class::trim(string &s, const string &mark)//删除指定字符
{
    size_t nSize = mark.size();
    while(1)
    {
        size_t pos = s.find(mark);
        if(pos == string::npos)
        {
            return;
        }
        s.erase(pos, nSize);
    }
}

void wnh_base_class::delete_last_char(string &s, const char &mark)
{
    if(s[s.length()-1] == mark)
    {
        s = s.substr(0, s.length()-1);
    }
}

string & wnh_base_class::replace_all(string & str, const string & old_value, const string & new_value)
{
    while(true)
    {
        string::size_type  pos(0);
        if((pos=str.find(old_value))!=string::npos)
        {
            str.replace(pos,old_value.length(),new_value);
        }
        else
        {
            break;
        }
    }
    return str;
}
string & wnh_base_class::replace_all_distinct(string & str, const string & old_value, const string & new_value)
{
    for(string::size_type pos(0);pos!=string::npos;pos+=new_value.length())
    {
        if((pos=str.find(old_value,pos))!=string::npos)
        {
            str.replace(pos,old_value.length(),new_value);
        }
        else
        {
            break;
        }
    }
    return str;
}

string wnh_base_class::format_string_left_fill(const string & str, const unsigned int & length, const char & chr) //使用指定字符将字符串左填充到指定长度
{
    string str_temp = str;
    string chr_temp = "";
    chr_temp = chr_temp + chr;
    unsigned long num = get_chinese_num(str);
    if(length > str.length() - num)
    {
        unsigned int str_length = str.length() - num;
        for(unsigned int i =0; i <= length - str_length; i ++)
        {
            str_temp = chr_temp + str_temp;
        }
    }
    return str_temp;
}

string wnh_base_class::format_string_right_fill(const string & str, const unsigned int & length, const char & chr) //使用指定字符将字符串右填充到指定长度
{
    string str_temp = str;
    unsigned long num = get_chinese_num(str);
    if(length > str.length() - num)
    {
        unsigned int str_length = str.length() - num;
        for(unsigned int i =0; i <= length - str_length; i ++)
        {
            str_temp = str_temp + chr;
        }
    }
    return str_temp;
}

string wnh_base_class::format_string_centro_fill(const string & str, const unsigned int & length, const char & chr) //使用指定字符将字符串左右填充到指定长度
{
    string str_temp = str;
    unsigned long num = get_chinese_num(str);
    if(length > str_temp.length() - num)
    {
        unsigned int str_length = str_temp.length() - num;
        if((length - str_length) % 2 != 0)
        {
            for(unsigned int i =0; i <= (length - str_length)/2; i ++)
            {
                str_temp = chr + str_temp;
            }
        }
        else
        {
            for(unsigned int i =0; i <= (length - str_length)/2-1; i ++)
            {
                str_temp = chr + str_temp;
            }
        }
        str_length = str_temp.length() - num;
        for(unsigned int i =0; i <= length - str_length; i ++)
        {
            str_temp = str_temp + chr;
        }
    }
    return str_temp;
}

unsigned long wnh_base_class::get_capital_letters_num(const string & str) //获取大写字母的数量
{
    unsigned long num = 0;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        // 大写字母
        if(str[i] >= 'A' && str[i] <= 'Z')
        {
            num ++;
        }
    }
    WNHDEBUG("统计到大写字母的个数=" << num);
    return num;
}

unsigned long wnh_base_class::get_lower_letters_num(const string & str) //获取小写字母的数量
{
    unsigned long num = 0;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        // 小写字母
        if(str[i] >= 'a' && str[i] <= 'z')
        {
            num ++;
        }
    }
    WNHDEBUG("统计到小写字母的个数=" << num);
    return num;
}

unsigned long wnh_base_class::get_digital_num(const string & str) //获取数字的数量
{
    unsigned long num = 0;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            num ++;
        }
    }
    WNHDEBUG("统计到数字的个数=" << num);
    return num;
}

unsigned long wnh_base_class::get_chinese_num(const string & str) //获取中文的数量
{
    unsigned long num = 0;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if (str[i]& 0x80)
        {
            num ++;
        }
    }
    //在string中一个中文占了3个字节
    WNHDEBUG("统计到中文的个数=" << num / 3);
    return num / 3;
}

string wnh_base_class::to_upper_string(const string & strs) //将str中的字母转为大写字母
{
    string str = strs;
    transform(str.begin(), str.end(), str.begin(), (int (*)(int))toupper);
    return str;
}
string wnh_base_class::to_lower_string(const string & strs) //将str中的字母转为小写字母
{
    string str = strs;
    transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
    return str;
}


//template <typename T> string wnh_base_class::to_binary(T value)//将任意进制的值转换为二进制
//{
//    //switch(type)
//    //{
//    //    case 10://如果是十进制转二进制
//    //    {
//    //        WNHDEBUG("如果是十进制转二进制");
//    //    }
//    //    case 2://如果是二进制转二进制
//    //    {
//    //        WNHDEBUG("如果是二进制转二进制");
//    //    }
//    //    case 8://如果是八进制转二进制
//    //    {
//    //        WNHDEBUG("如果是八进制转二进制");
//    //    }
//    //    case 16://如果是十六进制转二进制
//    //    {
//    //        WNHDEBUG("如果是十六进制转二进制");
//    //    }
//    //}
//    return "";
//}
