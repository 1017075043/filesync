#include "wnh_base_class.h"
#include "wnh_base_class_keyboard_input.cpp"

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
    unsigned long num = get_chinese_num(str);
    while(length > (str_temp.size() - num))
    {
        str_temp = chr + str_temp;
    }
    return str_temp;
}

string wnh_base_class::format_string_right_fill(const string & str, const unsigned int & length, const char & chr) //使用指定字符将字符串右填充到指定长度
{
    string str_temp = str;
    unsigned long num = get_chinese_num(str);
    while(length > (str_temp.size() - num))
    {
        str_temp = str_temp + chr;
    }
    return str_temp;
}

string wnh_base_class::format_string_centro_fill(const string & str, const unsigned int & length, const char & chr) //使用指定字符将字符串左右填充到指定长度
{
    string str_temp = str;
    unsigned long num = get_chinese_num(str);
    //WNHINFO("str:" << str << ", length:" << length << ", str_temp.size():" << str_temp.size() << ", num:" << num);
    bool status_temp = true;
    while(length > (str_temp.size() - num))
    {
        if(status_temp == true)
        {
            str_temp = str_temp + chr;
            status_temp = false;
        }
        else
        {
            str_temp = chr + str_temp;
            status_temp = true;
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

int wnh_base_class::transform_display_width(const string & str, const int & display_width) //转换显示宽度为字符串长度
{
    //WNHDEBUG("开始 int wnh_shell_tables::transform_display_width(const string & str, const int & display_width) //转换显示宽度为字符串长度");
    int str_size = 0;
    int i = 0;
    for(i = 0; i < (int)str.size(); i++)
    {
        //WNHDEBUG("i:" << i << ", display_width:" << display_width << ", str.size():" << str.size() << ", str_size:" << str_size);
        if(str_size >= display_width)
        {
            break;
        }
        if(str[i] & 0x80)
        {
            i = i + 2;
            str_size = str_size + 1;
        }
        str_size ++;
    }
    //WNHDEBUG("结束 int wnh_shell_tables::transform_display_width(const string & str, const int & display_width) //转换显示宽度为字符串长度");
    return i;
}

string wnh_base_class::safe_str_substr_left(string & str, const int & num) //安全的字符串切割(从左到右),处理切割到临界点是中文会乱码的问题
{
    int temp_chinese = 0;
    //WNHDEBUG("切割的临界点字符是中文");
    for(int i = 0; i < num; i++)
    {
        if(str[i] & 0x80)
        {
            temp_chinese ++;
        }
    }
    //WNHWARN("temp_chinese:" << temp_chinese << ", 多余中文字符:" << temp_chinese % 3);

    string str_temp = str.substr(num - temp_chinese % 3);
    str = str.substr(0, num - temp_chinese % 3);

    //WNHDEBUG("str_temp:" << str_temp << ", str:" << str);
    return str_temp;
}

string wnh_base_class::get_uuid() //获取uuid
{
    uuid_t uuid;
    char str[36];
    uuid_generate(uuid);
    uuid_unparse(uuid, str);
    string uuid_str_temp = str;
    trim(uuid_str_temp, "-");
    WNHDEBUG("uuid_str_temp=" << uuid_str_temp);
    return uuid_str_temp;
}
