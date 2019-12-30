#ifndef __wnh_config_ini_ex__
#define __wnh_config_ini_ex__

using namespace std;

#include "../wnh_base_class/wnh_base_class.h"

#define WNH_CONFIG_INI_EX_MAX_CONFIG_UNIT_NUM 100

class wnh_config_ini_ex : public wnh_base_class
{
public:
    struct CONFIG_INI_EX_UNIT{
        string name;
        vector<vector<string> > value; //配置存储
    };

    int config_unit_num; //节个数
    CONFIG_INI_EX_UNIT config_unit[WNH_CONFIG_INI_EX_MAX_CONFIG_UNIT_NUM];

public:
    wnh_config_ini_ex();
    ~wnh_config_ini_ex();

    void read_config_ini(const string & config_ini_path, const bool & space = false); //读取配置文件
    string unit_recognition(const string & str); //识别配置文件中的节点
    void show_configure_ini(); //显示读取到配置
    void clean_configure_ini(); //清除配置

    vector<string> get_conf(const string & config_unit_name, const string & config_unit_conf_name); //获取指定配置项
    vector<string> get_conf(const int & config_unit_num, const string & config_unit_conf_name);  //获取指定配置项
    string get_conf_one(const string & config_unit_name, const string & config_unit_conf_name); //获取指定配置项
    string get_conf_one(const int & config_unit_num, const string & config_unit_conf_name); //获取指定配置项
    vector<string> get_all_unit_name(); //获取所有节点的名称
};
#endif
