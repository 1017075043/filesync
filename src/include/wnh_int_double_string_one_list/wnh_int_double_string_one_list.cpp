#include "wnh_int_double_string_one_list.h"

wnh_int_double_string_one_list::wnh_int_double_string_one_list()
{
    head = nullptr;
    end = nullptr;
    now = nullptr;
    num = 0;
    get_now_temp = true;
}

wnh_int_double_string_one_list::~wnh_int_double_string_one_list()
{
    this->delete_list();
}

void wnh_int_double_string_one_list::add_head_son(Node *unit)//向头节点添加一个子节点
{
    //如果是添加第一个节点
    if(head == nullptr && end == nullptr)
    {
        head = unit;
        end = unit;
        unit->next = nullptr;
        WNHDEBUG("向头节点添加一个子节点完成 value=" << unit->value << ", key=" << unit->key << ", num=" << num << ",添加是的第一个节点");
    }
    else
    {
        unit->next = head;
        head = unit;
        WNHDEBUG("向头节点添加一个子节点完成 value=" << unit->value << ", key=" << unit->key << ", num=" << num);
    }
    num ++;
}

void wnh_int_double_string_one_list::add_head(int key)//向头节点添加一个子节点
{
    return this->add_head(key, 0, "");
}

void wnh_int_double_string_one_list::add_head(double key1)//向头节点添加一个子节点
{
    return this->add_head(0, key1, "");
}

void wnh_int_double_string_one_list::add_head(string value)//向头节点添加一个子节点
{
    return this->add_head(0, 0, value);
}

void wnh_int_double_string_one_list::add_head(int key, double key1)//向头节点添加一个子节点
{
    return this->add_head(key, key1, "");
}

void wnh_int_double_string_one_list::add_head(int key, string value)//向头节点添加一个子节点
{
    return this->add_head(key, 0, value);
}

void wnh_int_double_string_one_list::add_head(double key1, string value)//向头节点添加一个子节点
{
    return this->add_head(0, key1, value);
}

void wnh_int_double_string_one_list::add_head(int key, double key1, string value)//向头节点添加一个子节点
{
    Node *node = new Node;
    node->key = key;
    node->key1 = key1;
    node->value = value;
    this->add_head_son(node);
}

bool wnh_int_double_string_one_list::add_head_only(int key)//向头节点添加一个唯一的子节点
{
    return this->add_head_only(key, 0, "");
}

bool wnh_int_double_string_one_list::add_head_only(double key1)//向头节点添加一个唯一的子节点
{
    return this->add_head_only(0, key1, "");
}

bool wnh_int_double_string_one_list::add_head_only(string value)//向头节点添加一个唯一的子节点
{
    return this->add_head_only(0, 0, value);
}

bool wnh_int_double_string_one_list::add_head_only(int key, double key1)//向头节点添加一个唯一的子节点
{
    return this->add_head_only(key, key1, "");
}

bool wnh_int_double_string_one_list::add_head_only(int key, string value)//向头节点添加一个唯一的子节点
{
    return this->add_head_only(key, 0, value);
}

bool wnh_int_double_string_one_list::add_head_only(double key1, string value)//向头节点添加一个唯一的子节点
{
    return this->add_head_only(0, key1, value);
}

bool wnh_int_double_string_one_list::add_head_only(int key, double key1, string value)//向头节点添加一个唯一的子节点
{
    if(this->find_list_exist(key, key1, value))
    {
        WNHERROR("向头节点添加一个唯一的子节点失败,已经存在一个 key=" << key <<  ", value=" << value << " 的节点");
        return false;
    }
    this->add_head(key, key1, value);
    return true;
}

void wnh_int_double_string_one_list::add_end_son(Node *unit)//向尾节点添加一个子节点
{
    //如果是添加第一个节点
    unit->next = nullptr;
    if(head == nullptr && end == nullptr)
    {
        head = unit;
        end = unit;
        WNHDEBUG("向尾节点添加一个子节点完成 value=" << unit->value << ", key=" << unit->key << ", num=" << num << ",添加是的第一个节点");
    }
    else
    {
        end->next = unit;
        end = unit;
        WNHDEBUG("向尾节点添加一个子节点完成 value=" << unit->value << ", key=" << unit->key << ", num=" << num);
    }
    num ++;
}

void wnh_int_double_string_one_list::add_end(int key)//向尾节点添加一个子节点
{
    return this->add_end(key, 0, "");
}

void wnh_int_double_string_one_list::add_end(double key1)//向尾节点添加一个子节点
{
    return this->add_end(0, key1, "");
}

void wnh_int_double_string_one_list::add_end(string value)//向尾节点添加一个子节点
{
    return this->add_end(0, 0, value);
}

void wnh_int_double_string_one_list::add_end(int key, double key1)//向尾节点添加一个子节点
{
    return this->add_end(key, key1, "");
}

void wnh_int_double_string_one_list::add_end(int key, string value)//向尾节点添加一个子节点
{
    return this->add_end(key, 0, value);
}

void wnh_int_double_string_one_list::add_end(double key1, string value)//向尾节点添加一个子节点
{
    return this->add_end(0, key1, value);
}

void wnh_int_double_string_one_list::add_end(int key, double key1, string value)//向尾节点添加一个子节点
{
    Node *node = new Node;
    node->key = key;
    node->key1 = key1;
    node->value = value;
    this->add_end_son(node);
}

bool wnh_int_double_string_one_list::add_end_only(int key)//向尾节点添加一个唯一的子节点
{
    return this->add_end_only(key, 0, "");
}

bool wnh_int_double_string_one_list::add_end_only(double key1)//向尾节点添加一个唯一的子节点
{
    return this->add_end_only(0, key1, "");
}

bool wnh_int_double_string_one_list::add_end_only(string value)//向尾节点添加一个唯一的子节点
{
    return this->add_end_only(0, 0, value);
}

bool wnh_int_double_string_one_list::add_end_only(int key, double key1)//向尾节点添加一个唯一的子节点
{
    return this->add_end_only(key, key1, "");
}

bool wnh_int_double_string_one_list::add_end_only(int key, string value)//向尾节点添加一个唯一的子节点
{
    return this->add_end_only(key, 0, value);
}

bool wnh_int_double_string_one_list::add_end_only(double key1, string value)//向尾节点添加一个唯一的子节点
{
    return this->add_end_only(0, key1, value);
}

bool wnh_int_double_string_one_list::add_end_only(int key, double key1, string value)//向尾节点添加一个唯一的子节点
{
    if(this->find_list_exist(key, key1, value))
    {
        WNHERROR("向尾节点添加一个唯一的子节点失败,已经存在一个 key=" << key <<  " , value=" << value << " 的节点");
        return false;
    }
    this->add_end(key, key1, value);
    return true;
}

void wnh_int_double_string_one_list::show_list()//显示链表内容
{
    Node *t = head;
    while(t != nullptr)
    {
        WNHDEBUG("显示链表内容 value=" << t->value << ", key=" << t->key << ", key1=" << t->key1 << ", num=" << num);
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

bool wnh_int_double_string_one_list::find_list_exist(int key)//查找链表内容
{
    return this->find_list_exist(key, 0, "");
}

bool wnh_int_double_string_one_list::find_list_exist(double key1)//查找链表内容
{
    return this->find_list_exist(0, key1, "");
}

bool wnh_int_double_string_one_list::find_list_exist(string value)//查找链表内容
{
    return this->find_list_exist(0, 0, value);
}

bool wnh_int_double_string_one_list::find_list_exist(int key, double key1)//查找链表内容
{
    return this->find_list_exist(key, key1, "");
}

bool wnh_int_double_string_one_list::find_list_exist(int key, string value)//查找链表内容
{
    return this->find_list_exist(key, 0, value);
}

bool wnh_int_double_string_one_list::find_list_exist(double key1, string value)//查找链表内容
{
    return this->find_list_exist(0, key1, value);
}

bool wnh_int_double_string_one_list::find_list_exist(int key, double key1, string value)//查找链表内容
{
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (key1 == 0 || t->key1 == key1) && (value == "" || t->value == value))
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key << ", key1=" << t->key1);
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=" << key << " && key1=" << key1);
    return false;
}

bool wnh_int_double_string_one_list::find_list_exist(int key, Node *unit)//查找链表内容
{
    return this->find_list_exist(key, 0, "", unit);
}

bool wnh_int_double_string_one_list::find_list_exist(double key1, Node *unit)//查找链表内容
{
    return this->find_list_exist(0, key1, "", unit);
}

bool wnh_int_double_string_one_list::find_list_exist(string value, Node *unit)//查找链表内容
{
    return this->find_list_exist(0, 0, value, unit);
}

bool wnh_int_double_string_one_list::find_list_exist(int key, double key1, Node *unit)//查找链表内容
{
    return this->find_list_exist(key, key1, "", unit);
}

bool wnh_int_double_string_one_list::find_list_exist(int key, string value, Node *unit)//查找链表内容
{
    return this->find_list_exist(key, 0, value, unit);
}

bool wnh_int_double_string_one_list::find_list_exist(double key1, string value, Node *unit)//查找链表内容
{
    return this->find_list_exist(0, key1, value, unit);
}

bool wnh_int_double_string_one_list::find_list_exist(int key, double key1, string value, Node *unit)//查找链表内容
{
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (key1 == 0 || t->key1 == key1) && (value == "" || t->value == value))
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key << ", key1=" << t->key1);
            unit->key = t->key;
            unit->key1 = t->key1;
            unit->value = t->value;
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=" << key << " && key1=" << key1);
    return false;
}

bool wnh_int_double_string_one_list::update_list(int key, Node *unit)//修改链表内容
{
    return this->update_list(key, 0, "", unit);
}

bool wnh_int_double_string_one_list::update_list(double key1, Node *unit)//修改链表内容
{
    return this->update_list(0, key1, "", unit);
}

bool wnh_int_double_string_one_list::update_list(string value, Node *unit)//修改链表内容
{
    return this->update_list(0, 0, value, unit);
}

bool wnh_int_double_string_one_list::update_list(int key, double key1, Node *unit)//修改链表内容
{
    return this->update_list(key, key1, "", unit);
}

bool wnh_int_double_string_one_list::update_list(int key, string value, Node *unit)//修改链表内容
{
    return this->update_list(key, 0, value, unit);
}

bool wnh_int_double_string_one_list::update_list(double key1, string value, Node *unit)//修改链表内容
{
    return this->update_list(0, key1, value, unit);
}

bool wnh_int_double_string_one_list::update_list(int key, double key1, string value, Node *unit)//修改链表内容
{
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (key1 == 0 || t->key1 == key1) && (value == "" || t->value == value))
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key << ", key1=" << t->key1 << ", 更新值" << " value=" << unit->value << ", key=" << unit->key << ", key1=" << unit->key1 );
            t->key = unit->key;
            t->key1 = unit->key1;
            t->value = unit->value;
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=" << key << " && key1=" << key1);
    return false;
}

void wnh_int_double_string_one_list::delete_unit(Node *t)//删除一个节点
{
    //如果是head节点
    if(t == head)
    {
        //如果只有head一个节点
        if(head->next == nullptr)
        {
            WNHDEBUG("删除的是head节点,且现在只有一个节点 value=" << head->value << ", key=" << head->key << ", key1=" << head->key1);
            delete head;
            head = nullptr;
            end = nullptr;
        }
        else
        {
            WNHDEBUG("删除的是head节点 value=" << t->value << ", key=" << t->key << ", key1=" << t->key1);
            head = head->next;
            delete t;
            t = nullptr;
            WNHDEBUG("删除的是head节点,但现在有多个节点,下一个节点 value=" << head->value << ", key=" << head->key << ", key1=" << head->key1);
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
                WNHDEBUG("删除的是最后的一个节点,找到倒数第二个节点,现在将它的next指向nullptr value=" << s->value << ", key=" << s->key << ", key1=" << s->key1);
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
        WNHDEBUG("删除的是end节点 value=" << t->value << ", key=" << t->key << ", key1=" << t->key1);
        delete t;
        t = nullptr;
    }
    //如果找到的是中间的节点
    else
    {
        WNHDEBUG("删除的是中间的节点 value=" << t->value << ", key=" << t->key << ", key1=" << t->key1);
        Node *s = t->next;
        t->value = t->next->value;
        t->key = t->next->key;
        t->key1 = t->next->key1;
        t->next = t->next->next;
        delete s;
        s = nullptr;
    }
    num --;
}

bool wnh_int_double_string_one_list::find_list_delete(int key)//删除节点
{
    return this->find_list_delete(key, 0, "");
}

bool wnh_int_double_string_one_list::find_list_delete(double key1)//删除节点
{
    return this->find_list_delete(0, key1, "");
}

bool wnh_int_double_string_one_list::find_list_delete(string value)//删除节点
{
    return this->find_list_delete(0, 0, value);
}

bool wnh_int_double_string_one_list::find_list_delete(int key, string value)//删除节点
{
    return this->find_list_delete(key, 0, value);
}

bool wnh_int_double_string_one_list::find_list_delete(double key1, string value)//删除节点
{
    return this->find_list_delete(0, key1, value);
}

bool wnh_int_double_string_one_list::find_list_delete(int key, double key1, string value)//删除节点
{
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (key1 == 0 || t->key1 == key1) && (value == "" || t->value == value))
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key << ", key1=" << t->key1);
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=" << key << " && key1=" << key1);
    return false;
}

bool wnh_int_double_string_one_list::find_list_delete(int key, Node *unit)//删除节点
{
    return this->find_list_delete(key, 0, "", unit);
}

bool wnh_int_double_string_one_list::find_list_delete(double key1, Node *unit)//删除节点
{
    return this->find_list_delete(0, key1, "", unit);
}

bool wnh_int_double_string_one_list::find_list_delete(string value, Node *unit)//删除节点
{
    return this->find_list_delete(0, 0, value, unit);
}

bool wnh_int_double_string_one_list::find_list_delete(int key, string value, Node *unit)//删除节点
{
    return this->find_list_delete(key, 0, value, unit);
}

bool wnh_int_double_string_one_list::find_list_delete(double key1, string value, Node *unit)//删除节点
{
    return this->find_list_delete(0, key1, value, unit);
}

bool wnh_int_double_string_one_list::find_list_delete(int key, double key1, string value, Node *unit)//删除节点
{
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (key1 == 0 || t->key1 == key1) && (value == "" || t->value == value))
        {
            //WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key << ", key1=" << t->key1);
            unit->key = t->key;
            unit->key1 = t->key1;
            unit->value = t->value;
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=" << key << " && key1=" << key1);
    return false;
}

void wnh_int_double_string_one_list::delete_list()//删除链表
{
    Node *t = head;
    Node *now;
    while(t != nullptr)
    {
        if(t->next != nullptr)
        {
            now = t;
            t = t->next;
            WNHDEBUG("销毁链表,删除节点 value=" << now->value << ", key=" << now->key << ", key1=" << now->key1 << ", num=" << num);
            num --;
            delete now;
            now = nullptr;
        }
        else
        {
            WNHDEBUG("销毁链表,删除节点 value=" << t->value << ", key=" << t->key << ", key1=" << t->key1 << ", num=" << num);
            num = 0;
            delete t;
            head = t = nullptr;
        }
    }
    head = nullptr;
    end = nullptr;
}

bool wnh_int_double_string_one_list::del_head()//删除头节点
{
    if(head == nullptr)
    {
        WNHWARN("当前列表为空,删除头节点失败");
        return false;
    }
    Node *unit = new Node;
    unit->key = head->key;
    unit->key1 = head->key1;
    unit->value = head->value;
    this->delete_unit(head);
    WNHDEBUG("删除头节点成功 key=" << unit->key << ", key1=" << unit->key1 << ", value=" << unit->value);
    delete unit;
    unit = nullptr;
    return true;
}

bool wnh_int_double_string_one_list::del_head(Node *unit)//删除头节点
{
    if(head == nullptr)
    {
        WNHWARN("当前列表为空,删除头节点失败");
        return false;
    }
    unit->key = head->key;
    unit->key1 = head->key1;
    unit->value = head->value;
    this->delete_unit(head);
    WNHDEBUG("删除头节点成功 key=" << unit->key << ", key1=" << unit->key1 << ", value=" << unit->value);
    return true;
}

bool wnh_int_double_string_one_list::del_end()//删除尾节点
{
    if(end == nullptr)
    {
        WNHWARN("当前列表为空,删除尾节点失败");
        return false;
    }
    Node *unit = new Node;
    unit->key = end->key;
    unit->key1 = end->key1;
    unit->value = end->value;
    delete_unit(end);
    WNHDEBUG("删除尾节点成功 key=" << unit->key << ", key1=" << unit->key1 << ", value=" << unit->value);
    delete unit;
    unit = nullptr;
    return true;
}

bool wnh_int_double_string_one_list::del_end(Node *unit)//删除尾节点
{
    if(end == nullptr)
    {
        WNHWARN("当前列表为空,删除尾节点失败");
        return false;
    }
    unit->key = end->key;
    unit->key1 = end->key1;
    unit->value = end->value;
    delete_unit(end);
    WNHDEBUG("删除尾节点成功 key=" << unit->key << ", key1=" << unit->key1 << ", value=" << unit->value);
    return true;
}

void wnh_int_double_string_one_list::set_now_to_head()//设置指向当前节点的指针指向头节点
{
    now = head;
    get_now_temp = true;
}

void wnh_int_double_string_one_list::set_now_to_end()//设置指向当前节点的指针指向尾节点
{
    now = end;
    get_now_temp = true;
}

bool wnh_int_double_string_one_list::get_now(Node *unit)//获取now指向节点的值
{
    unit->key = now->key;
    unit->key1 = now->key1;
    unit->value = now->value;
    //获取非最后一个节点的数据
    if(now->next != nullptr)
    {
        now = now->next;
        WNHDEBUG("获取到now节点的数据成功 key=" << unit->key << ", key1=" << unit->key1 << ", value=" << unit->value << ", 非最后一个节点的数据");
        return true;
    }
    //获取最后一个节点的数据
    if(get_now_temp && now == end)
    {
        get_now_temp = false;
        WNHDEBUG("获取到now节点的数据成功 key=" << unit->key << ", key1=" << unit->key1 << ", value=" << unit->value << ", 最后一个节点的数据");
        return true;
    }
    get_now_temp = true;
    return false;
}
