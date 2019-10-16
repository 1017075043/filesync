#include "wnh_string_rule_one_list.h"

wnh_string_rule_one_list::wnh_string_rule_one_list()
{
    WNHDEBUG("wnh_string_rule_one_list 构造");
}
wnh_string_rule_one_list::~wnh_string_rule_one_list()
{
    WNHDEBUG("~wnh_string_rule_one_list 析构");
}

void wnh_string_rule_one_list::analyse_rule(string rule, Node *&unit)//分析一个rule,将结果存放在Node中
{
    if(rule.find("*") == rule.npos)//rule没有*的情况,全路径匹配
    {
        unit->value = rule;
        WNHDEBUG("rule没有*的情况,全路径匹配 rule=" << rule << ", value=" << unit->value);
    }
    else
    {
        //分析rule
        string value = rule.substr(0, rule.find("*"));
        string value1 = rule.substr(rule.find("*")+1);
        if(value.empty())
        {
            value = "*";
        }
        if(value1.empty())
        {
            value1 = "*";
        }
        unit->value = value;
        unit->value1 = value1;
        WNHDEBUG("rule分析结果为 rule=" << rule << ", value=" << value << ", value1=" << value1);
    }
}

void wnh_string_rule_one_list::add_head(string rule)//向头节点添加一个子节点
{
    Node *node = new Node;
    this->analyse_rule(rule, node);
    WNHDEBUG("node->value:" << node->value << ", node->value1:" << node->value1);
    return list.add_head(node->value, node->value1);
}

void wnh_string_rule_one_list::add_end(string rule)//向尾节点添加一个子节点
{
    Node *node = new Node;
    this->analyse_rule(rule, node);
    WNHDEBUG("node->value:" << node->value << ", node->value1:" << node->value1);
    return list.add_end(node->value, node->value1);
}

bool wnh_string_rule_one_list::add_head_only(string rule)//向头节点添加一个唯一的子节点
{
    Node *node = new Node;
    this->analyse_rule(rule, node);
    WNHDEBUG("node->value:" << node->value << ", node->value1:" << node->value1);
    return list.add_head_only(node->value, node->value1);
}

bool wnh_string_rule_one_list::add_end_only(string rule)//向尾节点添加一个唯一的子节点
{
    Node *node = new Node;
    this->analyse_rule(rule, node);
    WNHDEBUG("node->value:" << node->value << ", node->value1:" << node->value1);
    return list.add_end_only(node->value, node->value1);
}

bool wnh_string_rule_one_list::find_list_exist(string rule)//查找链表内容
{
    Node *node = new Node;
    this->analyse_rule(rule, node);
    WNHDEBUG("node->value:" << node->value << ", node->value1:" << node->value1);
    return list.find_list_exist(node->value, node->value1);
}

bool wnh_string_rule_one_list::find_list_delete(string rule)//查找链表内容,将节点删除
{
    Node *node = new Node;
    this->analyse_rule(rule, node);
    WNHDEBUG("node->value:" << node->value << ", node->value1:" << node->value1);
    return list.find_list_delete(node->value, node->value1);
}

bool wnh_string_rule_one_list::is_match_rule(string event)//判断目标是否为匹配的规则
{
    //使用结果寄存器记录上一次通配的结果
    if(matsh_register.value == event)
    {
        WNHDEBUG("event=" << event << " 寄存器匹配到 is_match=" << matsh_register.is_match);
        return matsh_register.is_match;
    }
    matsh_register.value = event;
    Node *t = list.head;
    while(t != nullptr)
    {
        if(t->value1.empty())
        {
            if( t->value == event)
            {
                WNHDEBUG("event=" << event << " 完全匹配到规则 rule=" << t->value);
                matsh_register.is_match = true;
                return true;
            }
        }
        else if(t->value == "*")
        {
            if(event.substr(event.length() - t->value1.length()) == t->value1)
            {
                WNHDEBUG("event=" << event << " 模糊匹配到规则 rule=" << t->value << t->value1);
                matsh_register.is_match = true;
                return true;
            }
        }
        else if(t->value1 == "*")
        {
            if(event.substr(0, t->value.length()) == t->value)
            {
                WNHDEBUG("event=" << event << " 模糊匹配到规则 rule=" << t->value << t->value1);
                matsh_register.is_match = true;
                return true;
            }
        }
        else if(event.substr(event.length() - t->value1.length()) == t->value1 && event.substr(0, t->value.length()) == t->value)
        {
            WNHDEBUG("event=" << event << " 模糊匹配到规则 rule=" << t->value << "*" << t->value1);
            matsh_register.is_match = true;
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
    WNHDEBUG("event=" << event << " 没有匹配的规则");
    matsh_register.is_match = false;
    return false;
}


