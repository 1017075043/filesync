#include "wnh_tcp_server.h"
#include "wnh_tcp_server_base.cpp"
#include "wnh_tcp_server_accept_file.cpp"
#include "wnh_tcp_server_send_file.cpp"


bool wnh_tcp_server::accept_start_session_info(const int nfp, const string info) //接收开始会话信息
{
    if(info == WNH_TCP_START_SESSION_INFO)
    {
        if(send_info(nfp, WNH_TCP_START_SESSION_INFO))
        {
            WNHDEBUG("nfp:" << nfp << ", 接收到开始会话信息,并正常回复");
            return true;
        }
        WNHERROR("nfp:" << nfp << ", 接收到开始会话信息,但是回复时失败了");
    }
    return false;
}

bool wnh_tcp_server::accept_end_session_info(const int nfp, const string info) //接收结束会话信息
{
    if(info == WNH_TCP_END_SESSION_INFO)
    {
        WNHDEBUG("nfp:" << nfp << ", 接收到结束会话信息,即将关闭会话句柄数nfp=" << nfp);
        close_session(nfp, false);
        return true;
    }
    return false;
}

bool wnh_tcp_server::creat_session_pthread(const int nfp) //创建会话线程
{
    WNHDEBUG("nfp:" << nfp << ", 请求创建新的会话线程, 等待线程分配, 当前已经创建的会话线程数量:" << tcp_listen_conturrent_now_num);
    while(tcp_listen_conturrent_now_num >= TCP_LISTEN_CONCURRENT_MAX_NUM)
    {
        usleep(1000);
    }
    thread start_build_session(&wnh_tcp_server::build_session, this, nfp);
    start_build_session.detach();
    add_session(&start_build_session, nfp);
    add_tcp_listen_conturrent_now_num();
    WNHDEBUG("nfp:" << nfp << ", 新的会话线程创建成功, 当前已经创建的会话线程数量:" << tcp_listen_conturrent_now_num);
    return true;
}

bool wnh_tcp_server::add_session(thread *session, const int nfp) //将一个会话添加进入会话记录列表
{
    for(int i = 0; i < TCP_LISTEN_CONCURRENT_MAX_NUM; i ++)
    {
        if(session_info[i].status)
        {
            session_info[i].session = session;
            session_info[i].nfp = nfp;
            session_info[i].start_time = LOCALTIMENUM;
            session_info[i].last_update_time = LOCALTIMENUM;
            session_info[i].status = false;
            WNHDEBUG("新的会话已经成功加入会话管理列表, 使用下标:" << i << ", nfp:" << nfp << ", 客户端IP:" << session_info[i].client_ip << ", 临时端口:" << session_info[i].client_port << ", 第一次连接时间:" << session_info[i].start_time << ", 最后一次链接时间:" << session_info[i].last_update_time);
            return true;
        }
    }
    WNHERROR("nfp:" << nfp << ", 新的会话加入会话管理列表失败了, 会话管理列表已满,程序存在异常");
    return false;
}

bool wnh_tcp_server::sub_session(const int nfp) //将一个会话从会话记录列表中删除
{
    for(int i = 0; i < TCP_LISTEN_CONCURRENT_MAX_NUM; i ++)
    {
        if(session_info[i].nfp == nfp)
        {
            session_info[i].session = nullptr;
            session_info[i].nfp = 0;
            session_info[i].start_time = 0;
            session_info[i].last_update_time = 0;
            session_info[i].status = true;
            WNHDEBUG("会话从会话记录列表中删除成功, 使用下标:" << i << ", nfp:" << nfp << ", 客户端IP:" << session_info[i].client_ip << ", 临时端口:" << session_info[i].client_port << ", 第一次连接时间:" << session_info[i].start_time << ", 最后一次链接时间:" << session_info[i].last_update_time);
            return true;
        }
    }
    WNHERROR("nfp:" << nfp << ", 会话从会话记录列表中删除失败了, 会话管理列表没有该记录");
    return false;
}

bool wnh_tcp_server::close_session(const int nfp, const bool status = false) //关闭一个会话
{
    if(!status)
    {
        dec_tcp_listen_conturrent_now_num(); //当前创建的会话线程数量-1,使用互斥
        sub_session(nfp);
    }
    close(nfp);
    return true;
}

bool wnh_tcp_server::update_session_last_update_time(const int nfp) //更新一个会话的最后连接时间
{
    static int subscript_temp = -1;
    if(subscript_temp != -1 && session_info[subscript_temp].nfp == nfp)
    {
        session_info[subscript_temp].last_update_time = LOCALTIMENUM;
        WNHDEBUG("nfp:" << nfp << ", 更新会话最后连接时间(寄存器匹配), nfp:" << session_info[subscript_temp].nfp << ", 客户端IP:" << session_info[subscript_temp].client_ip << ", 临时端口:" << session_info[subscript_temp].client_port << ", 第一次连接时间:" << session_info[subscript_temp].start_time << ", 最后一次链接时间:" << session_info[subscript_temp].last_update_time);
        return true;
    }
    for(int i = 0; i < TCP_LISTEN_CONCURRENT_MAX_NUM; i ++)
    {
        if(session_info[i].nfp == nfp)
        {
            session_info[i].last_update_time = LOCALTIMENUM;
            subscript_temp = i;
            WNHDEBUG("nfp:" << nfp << ", 更新会话最后连接时间, nfp:" << session_info[i].nfp << ", 客户端IP:" << session_info[i].client_ip << ", 临时端口:" << session_info[i].client_port << ", 第一次连接时间:" << session_info[i].start_time << ", 最后一次链接时间:" << session_info[i].last_update_time);
            return true;
        }
    }
    WNHERROR("nfp:" << nfp << ", 更新一个会话的最后连接时间失败了, 会话管理列表没有该记录");
    return false;
}

bool wnh_tcp_server::build_session(const int nfp) //建立一个会话
{
    string info;
    while(survival_id)
    {
        if(accept_info(nfp, info))
        {
            if(accept_start_session_info(nfp, info))
            {
                continue;
            }
            if(accept_file(nfp, info))
            {
                continue;
            }
            if(accept_apply_downinfo_file_info(nfp, info))
            {
                continue;
            }
            if(accept_end_session_info(nfp, info))
            {
                return true;
            }
            if(info.empty())
            {
                WNHERROR("nfp:" << nfp << ", 会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
                return false;
            }
            if(info == WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID)
            {
                WNHERROR("nfp:" << nfp << ", 等待超时或者会话异常, 接收到信息错误, 会话异常结束" << ", errno=" << errno << ", mesg=" << strerror(errno));
                close_session(nfp, false);
                return false;
            }
            WNHDEBUG("nfp:" << nfp << ", 接收到无法识别的信息:" << info);
            if(!send_info(nfp, info))
            {
                return true;
            }
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
            close_session(nfp, false);
            return false;
        }
    }
    return false;
}

bool wnh_tcp_server::manage_session_pthread() //管理会话线程
{
    WNHDEBUG("管理会话线程启动成功");
    for(int i = 0; i < TCP_LISTEN_CONCURRENT_MAX_NUM; i ++)
    {
        session_info[i].status = true;
    }
    while(survival_id)
    {
        for(int i = 0; i < TCP_LISTEN_CONCURRENT_MAX_NUM; i ++)
        {
            if(!session_info[i].status)
            {
                WNHDEBUG("nfp:" << session_info[i].nfp << ", 客户端IP:" << session_info[i].client_ip << ", 临时端口:" << session_info[i].client_port << ", 第一次连接时间:" << session_info[i].start_time << ", 最后一次链接时间:" << session_info[i].last_update_time << ", 该会话已经保持了" << LOCALTIMENUM - session_info[i].start_time << "秒, 使用下标:" << i);
                //if(LOCALTIMENUM - session_info[i].last_update_time > WNH_TCP_MAXIMUM_TIMEOUT_EXCLUSIVE_SESSION)
                //{
                //    WNHWARN("超过独占会话最大超时时间, 判定为独占会话, 强制终止会话, nfp:" << session_info[i].nfp << ", 客户端IP:" << session_info[i].client_ip << ", 临时端口:" << session_info[i].client_port << ", 第一次连接时间:" << session_info[i].start_time << ", 最后一次链接时间:" << session_info[i].last_update_time);
                //    close_session(session_info[i].nfp, false);
                //}
            }
        }
        sleep(10);
    }
    return true;
}

bool wnh_tcp_server::add_tcp_listen_conturrent_now_num() //当前创建的会话线程数量+1,使用互斥
{
    tcp_listen_conturrent_now_num ++;
    WNHDEBUG("当前创建的会话线程数量+1, 当前创建的会话线程数量:" << tcp_listen_conturrent_now_num);
    return true;
}

bool wnh_tcp_server::dec_tcp_listen_conturrent_now_num() //当前创建的会话线程数量-1,使用互斥
{
    if(tcp_listen_conturrent_now_num > 0)
    {
        tcp_listen_conturrent_now_num --;
        WNHDEBUG("当前创建的会话线程数量-1, 当前创建的会话线程数量:" << tcp_listen_conturrent_now_num);
        return true;
    }
    else
    {
        WNHERROR("当前创建的会话线程数量存在异常,当前创建的会话线程数量已经小于或者等于0, 无法在进行减1, 当前创建的会话线程数量:" << tcp_listen_conturrent_now_num);
        return false;
    }
}

int wnh_tcp_server::test()
{
    thread start_manage_session_pthread(&wnh_tcp_server::manage_session_pthread, this);
    start_manage_session_pthread.detach();

    create_socket();
    set_server_address(10051);
    server_bind();
    server_listen(TCP_LISTEN_CONCURRENT_MAX_NUM);

    while(survival_id)
    {
        int nfp = server_accept();
        if(nfp != -1)
        {
            creat_session_pthread(nfp);
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 会话异常, 忽略该会话, errno=" << errno << ", mesg=" << strerror(errno));
            close_session(nfp, true);
        }
    }
    return 0;
}
