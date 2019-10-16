#ifndef __wnh_string_rule_one_list__
#define __wnh_string_rule_one_list__

#include <iostream>
#include <string.h>

using namespace std;

#include "../wnh_string_string_one_list/wnh_string_string_one_list.h"

class wnh_string_rule_one_list : public wnh_string_string_one_list
{
private:
protected:
    struct matsh_node{
        string value;
        bool is_match;
    };
    matsh_node matsh_register;

    wnh_string_string_one_list list;

public:
    wnh_string_rule_one_list();
    ~wnh_string_rule_one_list();
    void analyse_rule(string rule, Node *&unit);//分析一个rule,将结果存放在Node中
    void add_head(string rule);//向头节点添加一个子节点
    void add_end(string rule);//向尾节点添加一个子节点
    bool add_head_only(string rule);//向头节点添加一个唯一的子节点
    bool add_end_only(string rule);//向尾节点添加一个唯一的子节点
    bool find_list_exist(string rule);//查找链表内容
    bool find_list_delete(string rule);//查找链表内容,将节点删除
    bool is_match_rule(string event);//判断目标是否为匹配的规则
};

#endif
