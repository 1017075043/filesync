#ifndef __wnh_string_string_one_list__
#define __wnh_string_string_one_list__

#include <iostream>
#include <string.h>

using namespace std;

#include "../wnh_base_class/wnh_base_class.h"

class wnh_string_string_one_list : public wnh_base_class
{
protected:

public:
    struct Node{
        string value;
        string value1;
        Node * next;
    } ;

    Node *head;//指向链表头节点
    Node *end;//指向链表尾节点

    double num;//当前链表的长度

    wnh_string_string_one_list();
    ~wnh_string_string_one_list();

    void add_head_son(Node *&unit);//向头节点添加一个子节点
    void add_head(string value, string value1);//向头节点添加一个子节点
    bool add_head_only(string value, string value1);//向头节点添加一个唯一的子节点

    void add_end_son(Node *&unit);//向尾节点添加一个子节点
    void add_end(string value, string value1);//向尾节点添加一个子节点
    bool add_end_only(string value, string value1);//向尾节点添加一个唯一的子节点

    void show_list();//显示链表内容

    bool find_list_exist(string value, string value1);//查找链表内容

    void delete_unit(Node *t);//删除一个节点
    bool find_list_delete(string value, string value1);//查找链表内容,将节点删除

    void delete_list();//删除链表

};

#endif
