#include "wnh_config.h"

wnh_config::wnh_config()
{
    WNHDEBUG("wnh_config 构造");
    head = nullptr;
    end = nullptr;
    target = nullptr;
}

wnh_config::wnh_config(string config_path)
{
    WNHDEBUG("wnh_config 构造");
    head = nullptr;
    end = nullptr;
    target = nullptr;
    this->read_config(config_path);
}

wnh_config::~wnh_config()
{
    WNHDEBUG("~wnh_config 析构");
    delete_list();
}

void wnh_config::read_config(string config_path)//读取配置
{
    ifstream fin(config_path.c_str());
    if (!fin)
    {
        WNHERROR("无法打开" << config_path << ", errno=" << errno << ", mesg=" << strerror(errno) << ",程序异常退出");
        exit(1);
    }
    string temp;
    while(getline(fin,temp))
    {
        this->trim(temp, " ");//去掉空格
        this->trim(temp,"\r");//去掉换行
        if(check_config(temp))
        {
            this->add_config(temp.substr(0, temp.find("=")), temp.substr(temp.find("=")+1));
        }
    }
}

void wnh_config::read_config(string config_path, const bool & space)//读取配置
{
    ifstream fin(config_path.c_str());
    if (!fin)
    {
        WNHERROR("无法打开" << config_path << ", errno=" << errno << ", mesg=" << strerror(errno) << ",程序异常退出");
        exit(1);
    }
    string temp;
    while(getline(fin,temp))
    {
        if(space)
        {
            this->trim(temp, " ");//去掉空格
        }
        this->trim(temp,"\r");//去掉换行
        if(check_config(temp))
        {
            this->add_config(temp.substr(0, temp.find("=")), temp.substr(temp.find("=")+1));
        }
    }
}

bool wnh_config::check_config(string unit)//检查配置是否合格
{
    //判断是否为注释
    if(unit.length() == 0)
    {
        return false;
    }
    //判断是否为注释
    if(unit[0] == '#')
    {
        WNHDEBUG("检测 注释性的配置,直接忽略：" << unit);
        return false;
    }
    //判断是否为没有等号的无效事项
    if(unit.find("=") == unit.npos || unit[0] == '=' || unit[unit.length()-1] == '=')
    {
        WNHWARN("检测 无效的配置,直接忽略：" << unit);
        return false;
    }
    WNHDEBUG("检测 正常的配置：" << unit);
    return true;
}

void wnh_config::add_config_son(Node *&unit)//添加一个配置
{
    unit->next = nullptr;
    if(head == nullptr)
    {
        head = unit;
        end = unit;
    }
    else
    {
        end->next = unit;
        end = unit;
    }
}

void wnh_config::add_config(string name, string data)//添加一个配置
{
    Node *node;
    if(this->find_config(name, node))
    {
        node->value.add_end_only(data);
        WNHDEBUG("向一个已经存在的配置项中添加一个值 name=" << name << ", data=" << data << ", 完成");
    }
    else
    {
        node = new Node;
        node->name = name;
        node->value.add_end_only(data);
        this->add_config_son(node);
        WNHDEBUG("添加一个配置项 name=" << name << ", data=" << data << ", 完成");
    }
}

bool wnh_config::find_config(string name, Node *&unit)//查找一个配置是否存在
{
    Node *t = head;
    while(t != nullptr)
    {
        if(t->name == name)
        {
            unit = t;
            return true;
        }
        if(t->next != nullptr)
        {
            t = t->next;
        }
        else
        {
            t = nullptr;
        }
    }
    return false;
}

int wnh_config::find_config(string name)//查找一个配置
{
    Node *t = head;
    while(t != nullptr)
    {
        if(t->name == name)
        {
            target = t;
            target->value.set_now_to_head();
            WNHDEBUG("查询到 存在配置 name=" << name << ", 且已经设置好,已经提供get_config使用");
            return target->value.num;
        }
        if(t->next != nullptr)
        {
            t = t->next;
        }
        else
        {
            t = nullptr;
        }
    }
    WNHDEBUG("查询到 不存在配置 name=" << name);
    return 0;
}

vector<string> wnh_config::get_config(const string & name)//获取配置
{
    Node *t = head;
    while(t != nullptr)
    {
        if(t->name == name)
        {
            target = t;
            return target->value.get_value();
        }
        if(t->next != nullptr)
        {
            t = t->next;
        }
        else
        {
            t = nullptr;
        }
    }
    WNHDEBUG("查询到 不存在配置 name=" << name);
    vector<string> all_value;
    return all_value;
}

string wnh_config::get_one_config(const string & name)//获取配置
{
    Node *t = head;
    while(t != nullptr)
    {
        if(t->name == name)
        {
            target = t;
            return target->value.get_head_value();
        }
        if(t->next != nullptr)
        {
            t = t->next;
        }
        else
        {
            t = nullptr;
        }
    }
    WNHDEBUG("查询到 不存在配置 name=" << name);
    string value;
    return value;
}

void wnh_config::show_config()//显示配置
{
    Node *t = head;
    string temp;
    while(t != nullptr)
    {
        t->value.set_now_to_head();
        while(t->value.get_now(temp))
        {
            WNHDEBUG("显示配置列表内容,配置项 name=" << t->name << ", 配置值 value=" << temp);
        }
        if(t->next != nullptr)
        {
            t = t->next;
        }
        else
        {
            t = nullptr;
        }
    }
}

void wnh_config::delete_list()//删除列表
{
    Node *t = head;
    Node *now;
    while(t != nullptr)
    {
        if(t->next != nullptr)
        {
            now = t;
            t = t->next;
            now->value.delete_list();
            WNHDEBUG("销毁链表,删除节点 name=" << now->name);
            delete now;
            now = nullptr;
        }
        else
        {
            WNHDEBUG("销毁链表,删除节点 name=" << t->name);
            t->value.delete_list();
            delete t;
            head  = nullptr;
            t = nullptr;
        }
    }
    head = nullptr;
    end = nullptr;
}

