#include "wnh_base_class.h"

wnh_base_class::wnh_base_class()
{

}

wnh_base_class::~wnh_base_class()
{

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

string wnh_base_class::format_string_right_fill(const string & str, const unsigned int & length, const char & chr) //使用指定字符将字符串右填充到指定长度
{
    string str_temp = str;
    if(length > str.length())
    {
        unsigned int str_length = str.length();
        for(unsigned int i =0; i <= length - str_length; i ++)
        {
            str_temp = str_temp + chr;
        }
    }
    return str_temp;
}

string wnh_base_class::format_string_centre_fill(const string & str, const unsigned int & length, const char & chr) //使用指定字符将字符串左右填充到指定长度
{
    string str_temp = str;
    if(length > str_temp.length())
    {
        unsigned int str_length = str_temp.length();
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
        str_length = str_temp.length();
        for(unsigned int i =0; i <= length - str_length; i ++)
        {
            str_temp = str_temp + chr;
        }
    }
    return str_temp;
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
