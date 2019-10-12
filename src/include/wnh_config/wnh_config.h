#ifndef __wnh_config__
#define __wnh_config__

//#include <iostream>
//#include <fstream>

using namespace std;

#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_int_string_one_list/wnh_int_string_one_list.h"

class wnh_config : public wnh_base_class
{
private:
    struct Node{
        string name;
        wnh_int_string_one_list value;
        Node * next;
    };
    Node *head;
    Node *end;
    Node *target;

public:
    wnh_config();
    wnh_config(string config_path);
    ~wnh_config();

    bool check_config(string unit);//检查配置是否合格
    bool find_config(string name, Node *&unit);//查找一个配置是否存在

    void read_config(string config_path);//读取配置
    void read_config(string config_path, const bool & space);//读取配置
    void add_config_son(Node *&unit);//添加一个配置
    void add_config(string name, string data);//添加一个配置
    void show_config();//显示配置

    int find_config(string name);//查找一个配置
    vector<string> get_config(const string & name);//获取配置
    string get_one_config(const string & name);//获取配置
    void delete_list();//删除列表
};
#endif
