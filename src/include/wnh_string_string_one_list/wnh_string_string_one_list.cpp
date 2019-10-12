#include "wnh_string_string_one_list.h"

wnh_string_string_one_list::wnh_string_string_one_list()
{
    head = nullptr;
    end = nullptr;
    num = 0;
}

wnh_string_string_one_list::~wnh_string_string_one_list()
{
    this->delete_list();
}

void wnh_string_string_one_list::add_head_son(Node *&unit)//向头节点添加一个子节点
{
    //如果是添加第一个节点
    if(head == nullptr && end == nullptr)
    {
        head = unit;
        end = unit;
        unit->next = nullptr;
        WNHDEBUG("向头节点添加一个子节点完成 value=" << unit->value << ", value1=" << unit->value1 << ", num=" << num << ",添加是的第一个节点");
    }
    else
    {
        unit->next = head;
        head = unit;
        WNHDEBUG("向头节点添加一个子节点完成 value=" << unit->value << ", value1=" << unit->value1 << ", num=" << num);
    }
    num ++;
}

void wnh_string_string_one_list::add_head(string value, string value1)//向头节点添加一个子节点
{
    Node *node = new Node;
    node->value = value;
    node->value1 = value1;
    this->add_head_son(node);
}

bool wnh_string_string_one_list::add_head_only(string value, string value1)//向头节点添加一个唯一的子节点
{
    if(this->find_list_exist(value, value1))
    {
        WNHERROR("向头节点添加一个唯一的子节点失败,已经存在一个 value=" << value <<  ", value1=" << value1 << " 的节点");
        return false;
    }
    this->add_head(value, value1);
    return true;
}

void wnh_string_string_one_list::add_end_son(Node *&unit)//向尾节点添加一个子节点
{
    //如果是添加第一个节点
    unit->next = nullptr;
    if(head == nullptr && end == nullptr)
    {
        head = unit;
        end = unit;
        WNHDEBUG("向尾节点添加一个子节点完成 value=" << unit->value << ", value1=" << unit->value1 << ", num=" << num << ",添加是的第一个节点");
    }
    else
    {
        end->next = unit;
        end = unit;
        WNHDEBUG("向尾节点添加一个子节点完成 value=" << unit->value << ", value1=" << unit->value1 << ", num=" << num);
    }
    num ++;
}

void wnh_string_string_one_list::add_end(string value, string value1)//向尾节点添加一个子节点
{
    Node *node = new Node;
    node->value = value;
    node->value1 = value1;
    this->add_end_son(node);
}

bool wnh_string_string_one_list::add_end_only(string value, string value1)//向尾节点添加一个唯一的子节点
{
    if(this->find_list_exist(value, value1))
    {
        WNHERROR("向尾节点添加一个唯一的子节点失败,已经存在一个 value=" << value <<  ", value1=" << value1 << " 的节点");
        return false;
    }
    this->add_end(value, value1);
    return true;
}

void wnh_string_string_one_list::show_list()//显示链表内容
{
    Node *t = head;
    while(t != nullptr)
    {
        WNHDEBUG("显示链表内容 value=" << t->value << ", value1=" << t->value1 << ", num=" << num);
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

bool wnh_string_string_one_list::find_list_exist(string value, string value1)//查找链表内容
{
    Node *t = head;
    while(t != nullptr)
    {
        if(t->value == value && t->value1 == value1)
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", value1=" << t->value1);
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && value1=" << value1);
    return false;
}

bool wnh_string_string_one_list::find_list_delete(string value, string value1)//查找链表内容,将节点删除
{
    Node *t = head;
    while(t != nullptr)
    {
        if(t->value == value && t->value1 == value1)
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", value1=" << t->value1 << ", num=" << num);
            this->delete_unit(t);
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && value1=" << value1);
    return false;
}

void wnh_string_string_one_list::delete_unit(Node *t)//删除一个节点
{
    //如果是head节点
    if(t == head)
    {
        //如果只有head一个节点
        if(head->next == nullptr)
        {
            WNHDEBUG("删除的是head节点,且现在只有一个节点 value=" << head->value << ", value1=" << head->value1);
            delete head;
            head = nullptr;
            end = nullptr;
        }
        else
        {
            head = head->next;
            delete t;
            t = nullptr;
            WNHDEBUG("删除的是head节点,但现在有多个节点,下一个节点 value=" << head->value << ", value1=" << head->value1);
        }
    }
    //如果找到的是最后的一个节点
    else if(t->next == nullptr)
    {
        WNHDEBUG("删除的是最后的一个节点");
        Node *s = head;
        while(s != nullptr)
        {
            if(s->next == t)
            {
                WNHDEBUG("删除的是最后的一个节点,找到倒数第二个节点,现在将它的next指向nullptr");
                s->next = nullptr;
                end = s;
                break;
            }
            if(s->next != nullptr)
            {
                s = s->next;
            }
            else
            {
                s = nullptr;
            }
        }
        delete t;
        t = nullptr;
    }
    //如果找到的是中间的节点
    else
    {
        WNHDEBUG("删除的是中间的节点");
        Node *s = t->next;
        t->value = t->next->value;
        t->value1 = t->next->value1;
        t->next = t->next->next;
        delete s;

    }
    num --;
}

void wnh_string_string_one_list::delete_list()//删除链表
{
    Node *t = head;
    Node *now;
    while(t != nullptr)
    {
        if(t->next != nullptr)
        {
            now = t;
            t = t->next;
            WNHDEBUG("销毁链表,删除节点 value=" << now->value << ", value1=" << now->value1 << ", num=" << num);
            num --;
            delete now;
            now = nullptr;
        }
        else
        {
            WNHDEBUG("销毁链表,删除节点 value=" << t->value << ", value1=" << t->value1 << ", num=" << num);
            num = 0;
            delete t;
            head = t = nullptr;
        }
    }
    head = nullptr;
    end = nullptr;
}

