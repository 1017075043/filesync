#ifndef __wnh_config_ini__
#define __wnh_config_ini__

using namespace std;

#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_config/wnh_config.h"

class wnh_config_ini : public wnh_base_class
{
private:
    struct Unit{
        string name;
        wnh_config conf; //配置存储
    };
    bool use_temp;

public:
    int unit_num; //节个数
    Unit *unit[];

    wnh_config_ini();
    ~wnh_config_ini();

    void read_config_ini(const string & config_ini_path); //读取配置文件
    void read_config_ini(const string & config_ini_path, const bool & space); //读取配置文件
    string unit_recognition(const string & str); //是识别配置文件中的节点
    void show_configure_ini(); //显示读取到配置
    void clean_configure_ini(); //清除配置

    vector<string> get_conf(const string & unit_name, const string & conf_name); //获取指定配置项
    vector<string> get_all_unit_name(); //获取所有节点的名称
};
#endif
