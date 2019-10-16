#include "wnh_unsigned_long_string_one_list.h"

wnh_unsigned_long_string_one_list::wnh_unsigned_long_string_one_list()
{
    WNHDEBUG("wnh_unsigned_long_string_one_list 构造");
    head = nullptr;
    end = nullptr;
    now = nullptr;
    jcq = nullptr;
    num = 0;
}

wnh_unsigned_long_string_one_list::~wnh_unsigned_long_string_one_list()
{
    WNHDEBUG("~wnh_unsigned_long_string_one_list 析构");
    this->delete_list();
}

void wnh_unsigned_long_string_one_list::add_head_son(Node *&unit)//向头节点添加一个子节点
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

void wnh_unsigned_long_string_one_list::add_head(int key)//向头节点添加一个子节点
{
    return this->add_head(key, "");
}

void wnh_unsigned_long_string_one_list::add_head(string value)//向头节点添加一个子节点
{
    return this->add_head(0, value);
}

void wnh_unsigned_long_string_one_list::add_head(int key, string value)//向头节点添加一个子节点
{
    Node *node = new Node;
    node->key = key;
    node->value = value;
    this->add_head_son(node);
}

bool wnh_unsigned_long_string_one_list::add_head_only(int key)//向头节点添加一个唯一的子节点
{
    return this->add_head_only(key, "");
}

bool wnh_unsigned_long_string_one_list::add_head_only(string value)//向头节点添加一个唯一的子节点
{
    return this->add_head_only(0, value);
}

bool wnh_unsigned_long_string_one_list::add_head_only(int key, string value)//向头节点添加一个唯一的子节点
{
    if(this->find_list_exist(key, value))
    {
        WNHERROR("向头节点添加一个唯一的子节点失败,已经存在一个 key=" << key <<  ", value=" << value << " 的节点");
        return false;
    }
    this->add_head(key, value);
    return true;
}

void wnh_unsigned_long_string_one_list::add_end_son(Node *&unit)//向尾节点添加一个子节点
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

void wnh_unsigned_long_string_one_list::add_end(int key)//向尾节点添加一个子节点
{
    return this->add_end(key, "");
}

void wnh_unsigned_long_string_one_list::add_end(string value)//向尾节点添加一个子节点
{
    return this->add_end(0, value);
}

void wnh_unsigned_long_string_one_list::add_end(int key, string value)//向尾节点添加一个子节点
{
    Node *node = new Node;
    node->key = key;
    node->value = value;
    this->add_end_son(node);
}

bool wnh_unsigned_long_string_one_list::add_end_only(int key)//向尾节点添加一个唯一的子节点
{
    return this->add_end_only(key, "");
}

bool wnh_unsigned_long_string_one_list::add_end_only(string value)//向尾节点添加一个唯一的子节点
{
    return this->add_end_only(0, value);
}

bool wnh_unsigned_long_string_one_list::add_end_only(int key, string value)//向尾节点添加一个唯一的子节点
{
    if(this->find_list_exist(key, value))
    {
        WNHERROR("向尾节点添加一个唯一的子节点失败,已经存在一个 key=" << key <<  " , value=" << value << " 的节点");
        return false;
    }
    this->add_end(key, value);
    return true;
}

void wnh_unsigned_long_string_one_list::show_list()//显示链表内容
{
    Node *t = head;
    while(t != nullptr)
    {
        WNHINFO("显示链表内容 value=" << t->value << ", key=" << t->key << ", num=" << num);
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

bool wnh_unsigned_long_string_one_list::find_list_exist(int key)//查找链表内容
{
    return this->find_list_exist(key, "");
}

bool wnh_unsigned_long_string_one_list::find_list_exist(string value)//查找链表内容
{
    return this->find_list_exist(0, value);
}

bool wnh_unsigned_long_string_one_list::find_list_exist(int key, string value)//查找链表内容
{
    if(jcq != nullptr && (key == 0 || jcq->key == key) && (value == "" || jcq->value == value))
    {
        WNHDEBUG("查找寄存器指针中存在值 " << " value=" << jcq->value << ", key=" << jcq->key << ", num=" << num);
        return true;
    }
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (value == "" || t->value == value))
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key);
            jcq = t;
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=" << key);
    return false;
}

bool wnh_unsigned_long_string_one_list::find_list_exist(string value, Node *unit)//查找链表内容
{
    return this->find_list_exist(0, value, unit);
}

bool wnh_unsigned_long_string_one_list::find_list_exist(int key, Node *unit)//查找链表内容
{
    return this->find_list_exist(key, "", unit);
}

bool wnh_unsigned_long_string_one_list::find_list(string value, int & key)//查找链表内容
{
    int temp;
    if(jcq != nullptr && jcq->value == value)
    {
        key = temp = jcq->key;
        WNHDEBUG("查找寄存器指针中存在值 " << " value=" << jcq->value << ", key=" << jcq->key << ", num=" << num);
        return true;
    }
    Node *t = head;
    while(t != nullptr)
    {
        if(t->value == value)
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key);
            key = temp = t->key;
            jcq = t;
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=0");
    return false;
}

bool wnh_unsigned_long_string_one_list::update_list_key(const string & value, const int & key)//更新列表key值
{
    Node *t = head;
    while(t != nullptr)
    {
        if(t->value == value)
        {
            t->key = key;
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << "更新key=" << t->key);
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=0");
    return false;
}

bool wnh_unsigned_long_string_one_list::find_list(int key, string &value)//查找链表内容
{
    string temp;
    if(jcq != nullptr && jcq->key == key)
    {
        value = temp = jcq->value;
        WNHDEBUG("查找寄存器指针中存在值 " << " value=" << jcq->value << ", key=" << jcq->key << ", num=" << num);
        return true;
    }
    Node *t = head;
    while(t != nullptr)
    {
        if(t->key == key)
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key);
            value = temp = t->value;
            jcq = t;
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
    WNHDEBUG("查找链表内容不存在值 value=nullptr && key=" << key);
    return false;
}

bool wnh_unsigned_long_string_one_list::find_list_exist(int key, string value, Node *unit)//查找链表内容
{
    if(jcq != nullptr && (key == 0 || jcq->key == key) && (value == "" || jcq->value == value))
    {
        unit->key = jcq->key;
        unit->value = jcq->value;
        WNHDEBUG("查找寄存器指针中存在值 " << " value=" << jcq->value << ", key=" << jcq->key << ", num=" << num);
        return true;
    }
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (value == "" || t->value == value))
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key);
            unit->key = t->key;
            unit->value = t->value;
            jcq = t;
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
    WNHDEBUG("查找链表内容不存在值 value=" << value << " && key=" << key);
    return false;
}

bool wnh_unsigned_long_string_one_list::find_list_delete(string value)//查找链表内容,返回key,并将节点删除
{
    return this->find_list_delete(0, value);
}

bool wnh_unsigned_long_string_one_list::find_list_delete(int key)//查找链表内容,返回value,并将节点删除
{
    return this->find_list_delete(key, "");
}

bool wnh_unsigned_long_string_one_list::find_list_delete(int key, string value)//查找链表内容,将节点删除
{
    if(jcq != nullptr && (key == 0 || jcq->key == key) && (value == "" || jcq->value == value))
    {
        WNHDEBUG("查找寄存器指针中存在值 " << " value=" << jcq->value << ", key=" << jcq->key << ", num=" << num);
        this->delete_unit(jcq);
        jcq = nullptr;
        return true;
    }
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (value == "" || t->value == value))
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key << ", num=" << num);
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
    WNHDEBUG("查找链表内容不存在值 key=" << key << " , value=" << value);
    return false;
}

bool wnh_unsigned_long_string_one_list::find_list_delete(string value, Node *unit)//查找链表内容,返回key,并将节点删除
{
    return this->find_list_delete(0, value, unit);
}

bool wnh_unsigned_long_string_one_list::find_list_delete(int key, Node *unit)//查找链表内容,返回value,并将节点删除
{
    return this->find_list_delete(key, "", unit);
}

bool wnh_unsigned_long_string_one_list::find_list_delete(int key, string value, Node *unit)//查找链表内容,将节点删除
{
    if(jcq != nullptr && (key == 0 || jcq->key == key) && (value == "" || jcq->value == value))
    {
        unit->key = jcq->key;
        unit->value = jcq->value;
        WNHDEBUG("查找寄存器指针中存在值 " << " value=" << jcq->value << ", key=" << jcq->key << ", num=" << num);
        this->delete_unit(jcq);
        jcq = nullptr;
        return true;
    }
    Node *t = head;
    while(t != nullptr)
    {
        if((key == 0 || t->key == key) && (value == "" || t->value == value))
        {
            WNHDEBUG("查找链表内容存在值 " << " value=" << t->value << ", key=" << t->key << ", num=" << num);
            unit->key = t->key;
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
    WNHDEBUG("查找链表内容不存在值 key=" << key << " , value=" << value);
    return false;
}

void wnh_unsigned_long_string_one_list::delete_unit(Node *t)//删除一个节点
{
    //如果是head节点
    if(t == head)
    {
        //如果只有head一个节点
        if(head->next == nullptr)
        {
            WNHDEBUG("删除的是head节点,且现在只有一个节点 value=" << head->value << ", key=" << head->key);
            delete head;
            head = nullptr;
            end = nullptr;
        }
        else
        {
            head = head->next;
            delete t;
            t = nullptr;
            WNHDEBUG("删除的是head节点,但现在有多个节点,下一个节点 value=" << head->value << ", key=" << head->key);
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
        t->key = t->next->key;
        t->next = t->next->next;
        delete s;

    }
    num --;
}

void wnh_unsigned_long_string_one_list::delete_list()//删除链表
{
    Node *t = head;
    Node *now;
    while(t != nullptr)
    {
        if(t->next != nullptr)
        {
            now = t;
            t = t->next;
            WNHDEBUG("销毁链表,删除节点 value=" << now->value << ", key=" << now->key << ", num=" << num);
            num --;
            delete now;
            now = nullptr;
        }
        else
        {
            WNHDEBUG("销毁链表,删除节点 value=" << t->value << ", key=" << t->key << ", num=" << num);
            num = 0;
            delete t;
            head = t = nullptr;
        }
    }
    head = nullptr;
    end = nullptr;
}

string wnh_unsigned_long_string_one_list::del_head()//删除头节点
{
    if(head == nullptr)
    {
        WNHWARN("当前列表为空,删除头节点失败");
        return "";
    }
    Node *unit = new Node;
    string temp = head->value;
    unit->key = head->key;
    unit->value = head->value;
    delete_unit(head);
    WNHDEBUG("删除头节点成功 key=" << unit->key << ", value=" << unit->value);
    delete unit;
    unit = nullptr;
    return temp;
}

bool wnh_unsigned_long_string_one_list::del_head(Node *unit)//删除头节点
{
    if(head == nullptr)
    {
        WNHWARN("当前列表为空,删除头节点失败");
        return false;
    }
    unit->key = head->key;
    unit->value = head->value;
    delete_unit(head);
    WNHDEBUG("删除头节点成功 key=" << unit->key << ", value=" << unit->value);
    return true;
}

string wnh_unsigned_long_string_one_list::del_end()//删除尾节点
{
    if(end == nullptr)
    {
        WNHWARN("当前列表为空,删除尾节点失败");
        return "";
    }
    Node *unit = new Node;
    string temp = head->value;
    unit->value = end->value;
    unit->key = end->key;
    delete_unit(end);
    WNHDEBUG("删除尾节点成功 key=" << unit->key << ", value=" << unit->value);
    delete unit;
    unit = nullptr;
    return temp;
}

bool wnh_unsigned_long_string_one_list::del_end(Node *unit)//删除尾节点
{
    if(end == nullptr)
    {
        WNHWARN("当前列表为空,删除尾节点失败");
        return false;
    }
    unit->value = end->value;
    unit->key = end->key;
    delete_unit(end);
    WNHDEBUG("删除尾节点成功 key=" << unit->key << ", value=" << unit->value);
    return true;
}

void wnh_unsigned_long_string_one_list::set_now_to_head()//设置指向当前节点的指针指向头节点
{
    now = head;
}

void wnh_unsigned_long_string_one_list::set_now_to_end()//设置指向当前节点的指针指向尾节点
{
    now = end;
}

bool wnh_unsigned_long_string_one_list::get_now(int &key)//获取now指向节点的值
{
    static bool temp = true;
    key = now->key;
    //获取非最后一个节点的数据
    if(now->next != nullptr)
    {
        //WNHDEBUG("获取到now节点的数据成功 key=" << now->key << ", value=" << now->value << ", 非最后一个节点的数据");
        now = now->next;
        return true;
    }
    //获取最后一个节点的数据
    if(temp && now == end)
    {
        temp = false;
        //WNHDEBUG("获取到now节点的数据成功 key=" << now->key << ", value=" << now->value << ", 最后一个节点的数据");
        return true;
    }
    temp = true;
    return false;
}

bool wnh_unsigned_long_string_one_list::get_now(string &value)//获取now指向节点的值
{
    static bool temp = true;
    value = now->value;
    //获取非最后一个节点的数据
    if(now->next != nullptr)
    {
        //WNHDEBUG("获取到now节点的数据成功 key=" << now->key << ", value=" << now->value << ", 非最后一个节点的数据");
        now = now->next;
        return true;
    }
    //获取最后一个节点的数据
    if(temp && now == end)
    {
        temp = false;
        //WNHDEBUG("获取到now节点的数据成功 key=" << now->key << ", value=" << now->value << ", 最后一个节点的数据");
        return true;
    }
    temp = true;
    return false;
}

bool wnh_unsigned_long_string_one_list::get_now(int &key, string &value)//获取now指向节点的值
{
    static bool temp = true;
    key = now->key;
    value = now->value;
    //获取非最后一个节点的数据
    if(now->next != nullptr)
    {
        //WNHDEBUG("获取到now节点的数据成功 key=" << now->key << ", value=" << now->value << ", 非最后一个节点的数据");
        now = now->next;
        return true;
    }
    //获取最后一个节点的数据
    if(temp && now == end)
    {
        temp = false;
        //WNHDEBUG("获取到now节点的数据成功 key=" << now->key << ", value=" << now->value << ", 最后一个节点的数据");
        return true;
    }
    temp = true;
    return false;
}

bool wnh_unsigned_long_string_one_list::get_now(Node *unit)//获取now指向节点的值
{
    static bool temp = true;
    unit->key = now->key;
    unit->value = now->value;
    //获取非最后一个节点的数据
    if(now->next != nullptr)
    {
        now = now->next;
        //WNHDEBUG("获取到now节点的数据成功 key=" << unit->key << ", value=" << unit->value << ", 非最后一个节点的数据");
        return true;
    }
    //获取最后一个节点的数据
    if(temp && now == end)
    {
        temp = false;
        //WNHDEBUG("获取到now节点的数据成功 key=" << unit->key << ", value=" << unit->value << ", 最后一个节点的数据");
        return true;
    }
    temp = true;
    return false;
}

vector<string> wnh_unsigned_long_string_one_list::get_value()
{
    vector<string> all_value;
    Node *t = head;
    int num = 0;
    while(t != nullptr)
    {
        all_value.push_back(t->value);
        WNHDEBUG("将链表内容压入容器all_value=" << all_value[num]);
        if(t->next != nullptr)
        {
            t = t->next;
        }
        else
        {
            t = nullptr;
        }
        num ++;
    }
    return all_value;
}

vector<int> wnh_unsigned_long_string_one_list::get_key()
{
    vector<int> all_key;
    Node *t = head;
    int num = 0;
    while(t != nullptr)
    {
        all_key.push_back(t->key);
        WNHDEBUG("将链表内容压入容器all_key=" << all_key[num]);
        if(t->next != nullptr)
        {
            t = t->next;
        }
        else
        {
            t = nullptr;
        }
        num ++;
    }
    return all_key;
}


