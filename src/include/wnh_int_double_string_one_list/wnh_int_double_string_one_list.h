#ifndef __wnh_int_double_string_one_list__
#define __wnh_int_double_string_one_list__

#include <iostream>
#include <string.h>

using namespace std;

#include "../wnh_base_class/wnh_base_class.h"

class wnh_int_double_string_one_list : public wnh_base_class
{
public:
    struct Node{
        int key;
        double key1;
        string value;
        Node * next;
    };

protected:
    Node *head;//指向链表头节点
    Node *end;//指向链表尾节点
    Node *now;//指向当前节点

    bool get_now_temp;

public:
    double num;//当前链表的长度

    wnh_int_double_string_one_list();
    ~wnh_int_double_string_one_list();

    void add_head_son(Node *unit);//向头节点添加一个子节点
    void add_head(int key);//向头节点添加一个子节点
    void add_head(double key1);//向头节点添加一个子节点
    void add_head(string value);//向头节点添加一个子节点
    void add_head(int key, double key1);//向头节点添加一个子节点
    void add_head(int key, string value);//向头节点添加一个子节点
    void add_head(double key1, string value);//向头节点添加一个子节点
    void add_head(int key, double key1, string value);//向头节点添加一个子节点

    bool add_head_only(int key);//向头节点添加一个唯一的子节点
    bool add_head_only(double key1);//向头节点添加一个唯一的子节点
    bool add_head_only(string value);//向头节点添加一个唯一的子节点
    bool add_head_only(int key, double key1);//向头节点添加一个唯一的子节点
    bool add_head_only(int key, string value);//向头节点添加一个唯一的子节点
    bool add_head_only(double key1, string value);//向头节点添加一个唯一的子节点
    bool add_head_only(int key, double key1, string value);//向头节点添加一个唯一的子节点

    void add_end_son(Node *unit);//向尾节点添加一个子节点
    void add_end(int key);//向尾节点添加一个子节点
    void add_end(double key1);//向尾节点添加一个子节点
    void add_end(string value);//向尾节点添加一个子节点
    void add_end(int key, double key1);//向尾节点添加一个子节点
    void add_end(int key, string value);//向尾节点添加一个子节点
    void add_end(double key1, string value);//向尾节点添加一个子节点
    void add_end(int key, double key1, string value);//向尾节点添加一个子节点

    bool add_end_only(int key);//向尾节点添加一个唯一的子节点
    bool add_end_only(double key1);//向尾节点添加一个唯一的子节点
    bool add_end_only(string value);//向尾节点添加一个唯一的子节点
    bool add_end_only(int key, double key1);//向尾节点添加一个唯一的子节点
    bool add_end_only(int key, string value);//向尾节点添加一个唯一的子节点
    bool add_end_only(double key1, string value);//向尾节点添加一个唯一的子节点
    bool add_end_only(int key, double key1, string value);//向尾节点添加一个唯一的子节点

    void show_list();//显示链表内容

    bool find_list_exist(int key);//查找链表内容
    bool find_list_exist(double key1);//查找链表内容
    bool find_list_exist(string value);//查找链表内容
    bool find_list_exist(int key, double key1);//查找链表内容
    bool find_list_exist(int key, string value);//查找链表内容
    bool find_list_exist(double key1, string value);//查找链表内容
    bool find_list_exist(int key, double key1, string value);//查找链表内容

    bool find_list_exist(int key, Node *unit);//查找链表内容
    bool find_list_exist(double key1, Node *unit);//查找链表内容
    bool find_list_exist(string value, Node *unit);//查找链表内容
    bool find_list_exist(int key, double key1, Node *unit);//查找链表内容
    bool find_list_exist(int key, string value, Node *unit);//查找链表内容
    bool find_list_exist(double key1, string value, Node *unit);//查找链表内容
    bool find_list_exist(int key, double key1, string value, Node *unit);//查找链表内容

    void delete_unit(Node *t);//删除一个节点

    bool find_list_delete(int key);//删除节点
    bool find_list_delete(double key1);//删除节点
    bool find_list_delete(string value);//删除节点
    bool find_list_delete(int key, double key1);//删除节点
    bool find_list_delete(int key, string value);//删除节点
    bool find_list_delete(double key1, string value);//删除节点
    bool find_list_delete(int key, double key1, string value);//删除节点

    bool find_list_delete(int key, Node *unit);//删除节点
    bool find_list_delete(double key1, Node *unit);//删除节点
    bool find_list_delete(string value, Node *unit);//删除节点
    bool find_list_delete(int key, double key1, Node *unit);//删除节点
    bool find_list_delete(int key, string value, Node *unit);//删除节点
    bool find_list_delete(double key1, string value, Node *unit);//删除节点
    bool find_list_delete(int key, double key1, string value, Node *unit);//删除节点

    bool update_list(int key, Node *unit);//修改链表内容
    bool update_list(double key1, Node *unit);//修改链表内容
    bool update_list(string value, Node *unit);//修改链表内容
    bool update_list(int key, double key1, Node *unit);//修改链表内容
    bool update_list(int key, string value, Node *unit);//修改链表内容
    bool update_list(double key1, string value, Node *unit);//修改链表内容
    bool update_list(int key, double key1, string value, Node *unit);//修改链表内容

    void delete_list();//删除链表

    bool del_head();//删除头节点
    bool del_head(Node *unit);//删除头节点

    bool del_end();//删除尾节点
    bool del_end(Node *unit);//删除尾节点

    void set_now_to_head();//设置指向当前节点的指针指向头节点
    void set_now_to_end();//设置指向当前节点的指针指向尾节点
    bool get_now(Node *unit);//获取now指向节点的值
};

#endif
