#include "wnh_config_ini.h"

wnh_config_ini::wnh_config_ini()
{
    WNHDEBUG("wnh_config_ini 构造");
    unit_num = 0;
    use_temp = false;
}

wnh_config_ini::~wnh_config_ini()
{
    WNHDEBUG("~wnh_config_ini 析构");
    clean_configure_ini();
}

void wnh_config_ini::read_config_ini(const string & config_ini_path)
{
    WNHDEBUG(config_ini_path);
    use_temp = true;
    ifstream fin(config_ini_path.c_str());
    if (!fin)
    {
        WNHERROR("无法打开" << config_ini_path << ", errno=" << errno << ", mesg=" << strerror(errno));
    }
    string temp;
    string unit_name;
    unit_num = -1;
    while(getline(fin,temp))
    {
        WNHDEBUG("读取到一个数据, temp:" << temp << ", 长度:" << temp.length());
        if(temp.empty())
        {
            continue;
        }
        this->trim(temp, " ");//去掉空格
        this->trim(temp,"\r");//去掉换行
        unit_name = "";
        unit_name = unit_recognition(temp);
        if(!unit_name.empty()) //如果读取到的配置是节点名
        {
            unit_num++;
            unit[unit_num] = new Unit;
            unit[unit_num]->name = unit_name;
            WNHDEBUG("unit[" << unit_num << "]->name=" << unit_name);
            continue;
        }
        if(unit[unit_num]->conf.check_config(temp))
        {
            unit[unit_num]->conf.add_config(temp.substr(0, temp.find("=")), temp.substr(temp.find("=")+1));
            WNHDEBUG("unit[" << unit_num << "]->conf=" << temp.substr(0, temp.find("=")) << ", " << temp.substr(temp.find("=")+1));
        }
    }
    fin.close();
    return;
}

void wnh_config_ini::read_config_ini(const string & config_ini_path, const bool & space) //读取配置文件
{
    WNHDEBUG(config_ini_path);
    use_temp = true;
    ifstream fin(config_ini_path.c_str());
    if (!fin)
    {
        WNHERROR("无法打开" << config_ini_path << ", errno=" << errno << ", mesg=" << strerror(errno));
    }
    string temp;
    string unit_name;
    unit_num = -1;
    while(getline(fin,temp))
    {
        WNHDEBUG("读取到一个数据, temp:" << temp << ", 长度:" << temp.length());
        if(temp.empty())
        {
            continue;
        }
        if(space)
        {
            this->trim(temp, " ");//去掉空格
        }
        this->trim(temp,"\r");//去掉换行
        unit_name = "";
        unit_name = unit_recognition(temp);
        if(!unit_name.empty()) //如果读取到的配置是节点名
        {
            unit_num++;
            unit[unit_num] = new Unit;
            unit[unit_num]->name = unit_name;
            WNHDEBUG("unit[" << unit_num << "]->name=" << unit_name);
            continue;
        }
        if(unit[unit_num]->conf.check_config(temp))
        {
            unit[unit_num]->conf.add_config(temp.substr(0, temp.find("=")), temp.substr(temp.find("=")+1));
            WNHDEBUG("unit[" << unit_num << "]->conf=" << temp.substr(0, temp.find("=")) << ", " << temp.substr(temp.find("=")+1));
        }
    }
    fin.close();
    return;
}

string wnh_config_ini::unit_recognition(const string & str)
{
    if(str[0] == '[' && str[str.length()-1] == ']')
    {
        return str.substr(1, str.length()-2);
    }
    return "";
}

void wnh_config_ini::show_configure_ini()
{
    for(int i = 0; i <= unit_num; i++)
    {
        WNHDEBUG("节点名：" << unit[i]->name);
        unit[i]->conf.show_config();
    }
}

void wnh_config_ini::clean_configure_ini()
{
    if(unit_num == 0 && use_temp == false)
    {
        //unit[0]->conf.delete_list();
        //delete unit[0];
        //unit[0] = nullptr;
        return;
    }
    for(int i = 0; i <= unit_num; i++)
    {
        unit[i]->conf.delete_list();
        delete unit[i];
        unit[i] = nullptr;
    }
    unit_num = 0;
    use_temp = false;
}

vector<string> wnh_config_ini::get_conf(const string & unit_name, const string & conf_name)
{
    WNHDEBUG("unit_num:" << unit_num);
    for(int i = 0; i <= unit_num; i++)
    {
        WNHDEBUG("查找配置段, 现在的配置段name, unit[" << i << "]->name" << ":" << unit[i]->name << ", 目标配置段:" << unit_name);
        if(unit[i]->name == unit_name)
        {
            WNHDEBUG("查找到配置段:unit_name:" << unit_name);
            return unit[i]->conf.get_config(conf_name);
        }
    }
    vector<string> all_value;
    return all_value;
}

vector<string> wnh_config_ini::get_all_unit_name()
{
    vector<string> all_unit_name;
    for(int i = 0; i <= unit_num; i++)
    {
        all_unit_name.push_back(unit[i]->name);
    }
    return all_unit_name;
}

//  vector<string> getStrings() {
//      vector<string> strings;
//      strings.push_back("hello");
//      strings.push_back("world");
//  }
//  vector<string> strings = getStrings();


