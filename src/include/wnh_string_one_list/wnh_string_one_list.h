#ifndef __wnh_string_one_list__
#define __wnh_string_one_list__

#include <iostream>
#include <string.h>

using namespace std;

#include "../wnh_base_class/wnh_base_class.h"

class wnh_string_one_list : public wnh_base_class
{
protected:
    struct Node{
        string value;
        Node * next;
    };

    Node *head;//指向链表头节点
    Node *s;//指向链表当前节点

public:
    double num;//当前链表的长度

    wnh_string_one_list();
    ~wnh_string_one_list();

    void add_end(const char *data);//添加一个子节点
    void add_end(string data);//添加一个子节点

    bool add_end_only(const char * data);//添加一个唯一的子节点
    bool add_end_only(string data);//添加一个唯一的子节点

    void show_list();//显示链表内容
    string del_head();//删除一个头节点,并返回头结点的值

    bool find_list(const char * data);//查找链表内容
    bool find_list(string data);//查找链表内容

    string get_unit(int a);//获取指定节点
    void delete_list();//删除链表
};

#endif
