#include "wnh_string_one_list.h"

wnh_string_one_list::wnh_string_one_list()
{
    WNHDEBUG("wnh_string_one_list 构造");
    head = nullptr;
    s = nullptr;
    num = 0;
}

wnh_string_one_list::~wnh_string_one_list()
{
    WNHDEBUG("~wnh_string_one_list 析构");
    this->delete_list();
}

void wnh_string_one_list::add_end(const char *data)
{
    //向列表的末尾插入一个节点
    Node *node = new Node;
    node->value = data;
    node->next = nullptr;
    //如果是添加第一个节点
    if(head == nullptr)
    {
        head = node;
        s = node;
        WNHDEBUG("向列表的末尾插入一个节点完成,这是列表中的第一个节点 data=" << s->value << ", num=" << num+1);
    }
    else
        //如果不是添加第一个节点
    {
        s->next = node;
        s = node;
        WNHDEBUG("向列表的末尾插入一个节点完成,这是列表中的第一个节点 data=" << s->value << ", num=" << num+1);
    }
    num ++;
}

void wnh_string_one_list::add_end(string data)
{
    //添加一个子节点
    return this->add_end(data.c_str());
}

bool wnh_string_one_list::add_end_only(const char *data)
{
    //向列表的末尾插入一个唯一的子节点
    if(find_list(data))
    {
        WNHWARN("添加一个唯一的子节点失败,该节点已经存在 " << num << "=" << s->value);
        return false;
    }
    this->add_end(data);
    return true;
}

bool wnh_string_one_list::add_end_only(string data)
{
    //添加一个唯一的子节点
    return this->add_end_only(data.c_str());
}

void wnh_string_one_list::show_list()
{
    //显示链表内容
    Node *t = head;
    int i = 0;
    while(t != nullptr)
    {
        WNHDEBUG("显示链表内容 data=" << t->value << ", i=" << i++);
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

string wnh_string_one_list::del_head()
{
    //删除一个头节点,并返回头结点的值
    Node *t = head;
    string temp;
    if(t != nullptr)
    {
        temp = t->value;
        if(t->next != nullptr)
        {
            head = t->next;
        }
        else
        {
            head = nullptr;
            s = nullptr;
        }
        WNHDEBUG("获取头结点的值 data=" << t->value << ", 删除头节点成功");
        delete t;
        t = nullptr;
        num --;
    }
    return temp;
}

string wnh_string_one_list::get_unit(int a)
{
    //获取指定节点
    int b = 0;
    Node *t = head;
    while(t != nullptr)
    {
        if(b == a)
        {
            WNHDEBUG("获取指定节点的值 data=" << t->value);
            return t->value;
        }
        if(t->next != nullptr)
        {
            t = t->next;
        }
        else
        {
            t = nullptr;
        }
        b++;
    }
    WNHDEBUG("获取不到指定节点的值 data=nullptr");
    return "nullptr";
}


bool wnh_string_one_list::find_list(const char *data)
{
    //查找链表内容
    Node *t = head;
    while(t != nullptr)
    {
        if(t->value == data)
        {
            WNHDEBUG("查找链表内容存在值 data=" << data);
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
    WNHDEBUG("查找链表内容不存在值 data=" << data);
    return false;
}

bool wnh_string_one_list::find_list(string data)
{
    //查找链表内容
    return this->find_list(data.c_str());
}

void wnh_string_one_list::delete_list()
{
    //删除链表
    Node *t = head;
    Node *now;
    while(t != nullptr)
    {
        if(t->next != nullptr)
        {
            now = t;
            t = t->next;
            WNHDEBUG("销毁链表,删除节点 " << num << "=" << now->value);
            num --;
            delete now;
            now = nullptr;
        }
        else
        {
            WNHDEBUG("销毁链表,删除节点 " << num << "=" << t->value);
            num = 0;
            delete t;
            head = t = nullptr;
        }
    }
}
