#include "wnh_config_ini_ex.h"

wnh_config_ini_ex::wnh_config_ini_ex()
{
    WNHDEBUG("wnh_config_ini_ex 构造");
}

wnh_config_ini_ex::~wnh_config_ini_ex()
{
    WNHDEBUG("~wnh_config_ini_ex 析构");
}

void wnh_config_ini_ex::read_config_ini(const string & config_ini_path, const bool & space) //读取配置文件
{
    clean_configure_ini();

    ifstream fin(config_ini_path.c_str());
    if (!fin)
    {
        WNHERROR("无法打开" << config_ini_path << ", errno=" << errno << ", mesg=" << strerror(errno));
        return;
    }
    string temp;
    while(getline(fin,temp))
    {
        this->trim(temp,"\r");//去掉换行
        if(temp == "" || temp[0] == '#')
        {
            WNHDEBUG("读取到一个无效的数据, temp:" << temp << ", 长度:" << temp.length());
            continue;
        }
        WNHDEBUG("读取到一个数据, temp:" << temp << ", 长度:" << temp.length());
        if(space == true)
        {
            this->trim(temp, " ");//去掉空格
        }
        string unit_name = unit_recognition(temp);
        if(!unit_name.empty()) //如果读取到的配置是节点名
        {
            config_unit_num++;
            if(config_unit_num >= WNH_CONFIG_INI_EX_MAX_CONFIG_UNIT_NUM)
            {
                WNHWARN("配置单元数不得大于: " << WNH_CONFIG_INI_EX_MAX_CONFIG_UNIT_NUM);
                config_unit_num --;
                fin.close();
                return ;
            }
            config_unit[config_unit_num].name = unit_name;
            WNHDEBUG("读取到节点名: unit[" << config_unit_num << "]=" << config_unit[config_unit_num].name);
            continue;
        }
        string conf_name = temp.substr(0, temp.find("="));
        string conf_value = temp.substr(temp.find("=")+1);
        bool temp_ss = true;
        for(int i = 0; i < (int)config_unit[config_unit_num].value.size(); i++)
        {
            if(config_unit[config_unit_num].value[i][0] == conf_name)
            {
                config_unit[config_unit_num].value[i].push_back(conf_value);
                WNHDEBUG("填充已有配置: [" << config_unit[config_unit_num].name << "]." << conf_name << "=" << conf_value);
                temp_ss = false;
                break;
            }
        }
        if(temp_ss == true)
        {
            vector<string> temp_value;
            temp_value.push_back(conf_name);
            temp_value.push_back(conf_value);
            config_unit[config_unit_num].value.push_back(temp_value);
            WNHDEBUG("添加新的配置: [" << config_unit[config_unit_num].name << "]." << conf_name << "=" << conf_value);
        }
    }
    config_unit_num ++;
    fin.close();
    return;
}

void wnh_config_ini_ex::show_configure_ini() //显示读取到配置
{
    for(int i = 0; i < config_unit_num; i++)
    {
        for(int j = 0; j < (int)config_unit[i].value.size(); j++)
        {
            for(int k = 1; k < (int)config_unit[i].value[j].size(); k++)
            {
                WNHINFO("[" << config_unit[i].name << "]." << config_unit[i].value[j][0] << "=" << config_unit[i].value[j][k]);
            }
        }
    }
}

vector<string> wnh_config_ini_ex::get_conf(const string & config_unit_name, const string & config_unit_conf_name)
{
    for(int i = 0; i < config_unit_num; i++)
    {
        //WNHDEBUG("当前配置单元: " << config_unit[i].name << ", 查找目标配置单元: " << config_unit_name);
        if(config_unit[i].name == config_unit_name)
        {
            WNHDEBUG("当前配置单元: " << config_unit[i].name << ", 查找目标配置单元: " << config_unit_name << ", 查找目标配置单元");
            for(int j = 0; j < (int)config_unit[i].value.size(); j++)
            {
                //WNHDEBUG("当前配置项: " << config_unit[i].name << "." << config_unit[i].value[j][0] << ", 查找目标配置项: " << config_unit[i].name << "." << config_unit_conf_name);
                if(config_unit[i].value[j][0] == config_unit_conf_name)
                {
                    WNHDEBUG("当前配置项: " << config_unit[i].name << "." << config_unit[i].value[j][0] << ", 查找目标配置项: " << config_unit[i].name << "." << config_unit_conf_name << ", 查找目标配置项");
                    vector<string> all_value = config_unit[i].value[j];
                    vector<string>::iterator k = all_value.begin();
                    all_value.erase(k);
                    return all_value;
                }
            }
        }
    }
    WNHWARN("查找不到目标配置项: " << config_unit_name << "." << config_unit_conf_name);
    vector<string> all_value;
    return all_value;
}

vector<string> wnh_config_ini_ex::get_conf(const int & config_unit_num, const string & config_unit_conf_name)
{
    if(config_unit_num >= this->config_unit_num)
    {
        WNHERROR("查找配置单元下标溢出, 最大下标: " << this->config_unit_num << ", 查找下标: " << config_unit_num);
        vector<string> all_value;
        return all_value;
    }
    for(int j = 0; j < (int)config_unit[config_unit_num].value.size(); j++)
    {
        //WNHDEBUG("当前配置项: " << config_unit[i].name << "." << config_unit[i].value[j][0] << ", 查找目标配置项: " << config_unit[i].name << "." << config_unit_conf_name);
        if(config_unit[config_unit_num].value[j][0] == config_unit_conf_name)
        {
            WNHDEBUG("当前配置项: " << config_unit[config_unit_num].name << "." << config_unit[config_unit_num].value[j][0] << ", 查找目标配置项: " << config_unit[config_unit_num].name << "." << config_unit_conf_name << ", 查找目标配置项");
            vector<string> all_value = config_unit[config_unit_num].value[j];
            vector<string>::iterator k = all_value.begin();
            all_value.erase(k);
            return all_value;
        }
    }
    WNHWARN("查找不到目标配置项: " << config_unit_num << "." << config_unit_conf_name);
    vector<string> all_value;
    return all_value;
}

string wnh_config_ini_ex::get_conf_one(const string & config_unit_name, const string & config_unit_conf_name)
{
    for(int i = 0; i < config_unit_num; i++)
    {
        //WNHDEBUG("当前配置单元: " << config_unit[i].name << ", 查找目标配置单元: " << config_unit_name);
        if(config_unit[i].name == config_unit_name)
        {
            WNHDEBUG("当前配置单元: " << config_unit[i].name << ", 查找目标配置单元: " << config_unit_name << ", 查找目标配置单元");
            for(int j = 0; j < (int)config_unit[i].value.size(); j++)
            {
                //WNHDEBUG("当前配置项: " << config_unit[i].name << "." << config_unit[i].value[j][0] << ", 查找目标配置项: " << config_unit[i].name << "." << config_unit_conf_name);
                if(config_unit[i].value[j][0] == config_unit_conf_name)
                {
                    WNHDEBUG("当前配置项: " << config_unit[i].name << "." << config_unit[i].value[j][0] << ", 查找目标配置项: " << config_unit[i].name << "." << config_unit_conf_name << ", 查找目标配置项");
                    return config_unit[i].value[j][config_unit[i].value[j].size() - 1];
                }
            }
        }
    }
    WNHWARN("查找不到目标配置项: " << config_unit_name << "." << config_unit_conf_name);
    return "";
}

string wnh_config_ini_ex::get_conf_one(const int & config_unit_num, const string & config_unit_conf_name)
{
    if(config_unit_num >= this->config_unit_num)
    {
        WNHERROR("查找配置单元下标溢出, 最大下标: " << this->config_unit_num << ", 查找下标: " << config_unit_num);
        return "";
    }
    for(int j = 0; j < (int)config_unit[config_unit_num].value.size(); j++)
    {
        //WNHDEBUG("当前配置项: " << config_unit[i].name << "." << config_unit[i].value[j][0] << ", 查找目标配置项: " << config_unit[i].name << "." << config_unit_conf_name);
        if(config_unit[config_unit_num].value[j][0] == config_unit_conf_name)
        {
            WNHDEBUG("当前配置项: " << config_unit[config_unit_num].name << "." << config_unit[config_unit_num].value[j][0] << ", 查找目标配置项: " << config_unit[config_unit_num].name << "." << config_unit_conf_name << ", 查找目标配置项");
            return config_unit[config_unit_num].value[j][config_unit[config_unit_num].value[j].size() - 1];
        }
    }
    WNHWARN("查找不到目标配置项: " << config_unit_num << "." << config_unit_conf_name);
    return "";
}

vector<string> wnh_config_ini_ex::get_all_unit_name()
{
    vector<string> all_unit_name;
    for(int i = 0; i < config_unit_num; i++)
    {
        all_unit_name.push_back(config_unit[i].name);
    }
    return all_unit_name;
}

string wnh_config_ini_ex::unit_recognition(const string & str)
{
    if(str[0] == '[' && str[str.length()-1] == ']')
    {
        return str.substr(1, str.length()-2);
    }
    return "";
}

void wnh_config_ini_ex::clean_configure_ini() //清除配置
{
    for(int i = 0; i < config_unit_num; i ++)
    {
        config_unit[i].name.clear();
        for(int j = 0; j < (int)config_unit[i].value.size(); j ++)
        {
            config_unit[i].value[j].clear();
        }
        config_unit[i].value.clear();
    }
    config_unit_num = -1;
}
