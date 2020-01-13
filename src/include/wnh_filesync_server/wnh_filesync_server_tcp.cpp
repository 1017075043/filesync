#include "wnh_filesync_server.h"

bool wnh_filesync_server::build_session(const int & nfp, const CONNECT_INFO & CONNECT_INFO) //建立一个会话
{
    string info;
    string accept_file_name;
    while(survival_id)
    {
        if(accept_info(nfp, info))
        {
            if(accept_start_session_info(nfp, info)) //接收开始会话信息
            {
                WNHINFO(CONNECT_INFO_LOGS << "会话开始");
                continue;
            }
            if(accept_if_allow_connect(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_online_signal(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_task_num(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_task_list(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_task_complete_v1(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_task_fail_v1(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            switch(accept_file(nfp, info, accept_file_name, CONNECT_INFO))
            {
                case WNH_TCP_SUCCESS_RESULTS:
                {
                    WNHINFO(CONNECT_INFO_LOGS << "文件名:" << accept_file_name << ", 接收成功");
                    continue;
                    break;
                }
                case WNH_TCP_FAIL_RESULTS:
                {
                    WNHINFO(CONNECT_INFO_LOGS << "文件名:" << accept_file_name << ", 接收失败");
                    continue;
                    break;
                }
            }
            switch(accept_apply_downinfo_file_info(nfp, info, accept_file_name, CONNECT_INFO))
            {
                case WNH_TCP_SUCCESS_RESULTS:
                {
                    WNHINFO(CONNECT_INFO_LOGS << "文件名:" << accept_file_name << ", 发送成功");
                    continue;
                    break;
                }
                case WNH_TCP_FAIL_RESULTS:
                {
                    WNHINFO(CONNECT_INFO_LOGS << "文件名:" << accept_file_name << ", 发送失败");
                    continue;
                    break;
                }
            }
            if(accept_get_server_status_info_v1(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_client_status_info(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_sync_rule_info(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_license_info(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_sync_transfer_info(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_sync_fail_task_list_info(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_sync_complete_task_list_info(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_get_wait_sync_task_list_info(nfp, info, CONNECT_INFO))
            {
                continue;
            }
            if(accept_end_session_info(nfp, info))//接收结束会话信息
            {
                WNHINFO(CONNECT_INFO_LOGS << "会话结束");
                return true;
            }
            if(info.empty())
            {
                WNHERROR(CONNECT_INFO_LOGS << "会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
                close_session(nfp, CONNECT_INFO, false);
                return false;
            }
            if(info == WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID)
            {
                WNHERROR(CONNECT_INFO_LOGS ", 等待超时或者会话异常, 接收到信息错误, 会话异常结束" << ", errno=" << errno << ", mesg=" << strerror(errno));
                close_session(nfp, CONNECT_INFO, false);
                return false;
            }
            WNHWARN(CONNECT_INFO_LOGS << "接收到无法识别的信息:" << info);
            if(!send_info(nfp, info)) //实收到其他信息
            {
                return true;
            }
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 客户端IP:" << CONNECT_INFO.client_ip << ", 会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
            close_session(nfp, CONNECT_INFO, false);
            return false;
        }
    }
    return false;
}

void wnh_filesync_server::tcp_core() //tcp核心服务
{
    thread start_manage_session_pthread(&wnh_filesync_server::manage_session_pthread, this);
    start_manage_session_pthread.detach();

    wnh_system_operation sys_oper;
    if(!sys_oper.is_dir(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH))
    {
        if(!sys_oper.create_dirs(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH))
        {
            WNHERROR("任务列表存放目录创建失败:" << WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH);
            exit(1);
        }
    }
    sys_oper.chmod_wnh(WNH_FILESYNC_DEFAULT_TASK_LIST_DIR_PATH, "755");

    if(create_socket())
    {
        WNHINFO("创建TCP SOCKET完成");
    }
    else
    {
        exit(0);
    }
    set_server_address(port);
    if(server_bind())
    {
        WNHINFO("与TCP端口" << port << "绑定完成");
    }
    else
    {
        exit(0);
    }
    if(server_listen(TCP_LISTEN_CONCURRENT_MAX_NUM))
    {
        WNHINFO("开始进行端口监听,并发数:" << TCP_LISTEN_CONCURRENT_MAX_NUM);
    }
    else
    {
        exit(0);
    }

    while(survival_id)
    {
        CONNECT_INFO CONNECT_INFO = server_accept_v1();
        WNHDEBUG("确定接收客户端的连接,获得新的临时句柄数nfp=" << CONNECT_INFO.client_nfp << ", 客户端的IP:" << CONNECT_INFO.client_ip << ", 使用的临时端口:" << CONNECT_INFO.client_port);
        int nfp = CONNECT_INFO.client_nfp;
        if(nfp != -1)
        {
            creat_session_pthread(nfp, CONNECT_INFO);
        }
        else
        {
            WNHERROR("nfp:" << nfp << ", 会话异常, 忽略该会话, errno=" << errno << ", mesg=" << strerror(errno));
            close_session(nfp, CONNECT_INFO, true);
        }
    }
}

int wnh_filesync_server::server_accept() //等待客户端的连接
{
    struct sockaddr_in client_address;
    sin_size = sizeof(struct sockaddr_in);
    int nfp = accept(socket_num, (struct sockaddr *)(&client_address), &sin_size);
    if(-1 == nfp)
    {
        WNHERROR("等待客户端的连接失败了, errno=" << errno << ", mesg=" << strerror(errno));
        return -1;
    }
    WNHDEBUG("确定接收客户端的连接,获得新的临时句柄数nfp=" << nfp << ", 客户端的IP:" << inet_ntoa(client_address.sin_addr) << ", 使用的临时端口:" << ntohs(client_address.sin_port));
    return nfp;
}

wnh_filesync_server::CONNECT_INFO wnh_filesync_server::server_accept_v1() //等待客户端的连接
{
    wnh_filesync_server::CONNECT_INFO CONNECT_INFO;
    struct sockaddr_in client_address;
    sin_size = sizeof(struct sockaddr_in);
    int nfp = accept(socket_num, (struct sockaddr *)(&client_address), &sin_size);
    if(-1 == nfp)
    {
        WNHERROR("等待客户端的连接失败了, errno=" << errno << ", mesg=" << strerror(errno));
        CONNECT_INFO.client_nfp = -1;
        return CONNECT_INFO;
    }
    CONNECT_INFO.client_ip = inet_ntoa(client_address.sin_addr);
    CONNECT_INFO.client_nfp = nfp;
    CONNECT_INFO.client_port = ntohs(client_address.sin_port);
    WNHDEBUG("确定接收客户端的连接,获得新的临时句柄数nfp=" << CONNECT_INFO.client_nfp << ", 客户端的IP:" << CONNECT_INFO.client_ip << ", 使用的临时端口:" << CONNECT_INFO.client_port);
    return CONNECT_INFO;
}

bool wnh_filesync_server::accept_start_session_info(const int nfp, const string info) //接收开始会话信息
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

bool wnh_filesync_server::close_session(const int nfp, const CONNECT_INFO & CONNECT_INFO, const bool status = false) //关闭一个会话
{
    watch.update_task_sync_lock_status(CONNECT_INFO.client_ip, "0");
    WNHERROR("解开任务同步锁, 关闭临时句柄数nfp=" << CONNECT_INFO.client_nfp << ", 客户端的IP:" << CONNECT_INFO.client_ip << ", 使用的临时端口:" << CONNECT_INFO.client_port);
    return close_session(nfp, false);
}

bool wnh_filesync_server::close_session(const int nfp, const bool status = false) //关闭一个会话
{
    if(!status)
    {
        dec_tcp_listen_conturrent_now_num(); //当前创建的会话线程数量-1,使用互斥
        sub_session(nfp);
    }
    close(nfp);
    return true;
}

bool wnh_filesync_server::accept_end_session_info(const int nfp, const string info) //接收结束会话信息
{
    if(info == WNH_TCP_END_SESSION_INFO)
    {
        WNHDEBUG("nfp:" << nfp << ", 接收到结束会话信息,即将关闭会话句柄数nfp=" << nfp);
        close_session(nfp, false);
        return true;
    }
    return false;
}

bool wnh_filesync_server::creat_session_pthread(const int & nfp, const CONNECT_INFO & CONNECT_INFO) //创建会话线程
{
    WNHDEBUG(CONNECT_INFO_LOGS << "请求创建新的会话线程, 等待线程分配, 当前已经创建的会话线程数量:" << tcp_listen_conturrent_now_num);
    while(tcp_listen_conturrent_now_num >= TCP_LISTEN_CONCURRENT_MAX_NUM)
    {
        usleep(1000);
    }
    thread start_build_session(&wnh_filesync_server::build_session, this, nfp, CONNECT_INFO);
    start_build_session.detach();
    add_session(&start_build_session, nfp, CONNECT_INFO);
    add_tcp_listen_conturrent_now_num();
    WNHINFO(CONNECT_INFO_LOGS << "新的会话线程创建成功, 当前已经创建的会话线程数量:" << tcp_listen_conturrent_now_num);
    return true;
}

int wnh_filesync_server::accept_file(const int nfp, const string info, string & accept_file_name, const CONNECT_INFO & CONNECT_INFO) //接收一个文件
{
    if(!accept_start_send_file_info(nfp, info))//判断是否为接收文件的标识语
    {
        return WNH_TCP_IGNORE_RESULTS;
    }
    else
    {
        WNHINFO(CONNECT_INFO_LOGS << "客户端请求上传文件,开始接收");
    }
    //开始接收文件信息
    string name = "";
    long long file_size = -1;
    while(survival_id)
    {
        string info;
        if(accept_info(nfp, info))//接收信息
        {
            if(accept_end_send_file_info(nfp, info))//如果是接收到文件发送结束的标识语，就结束文件的接收
            {
                return WNH_TCP_SUCCESS_RESULTS;
            }
            if(accept_file_size_info(nfp, info, file_size))
            {
                WNHINFO(CONNECT_INFO_LOGS << "接收文件大小:" << file_size);
                continue;
            }
            if(accept_file_name_info(nfp, info, name))
            {
                WNHINFO(CONNECT_INFO_LOGS << "接收文件名:" << name);
                continue;
            }
            if(accept_file_content(nfp, info, name, file_size))
            {
                accept_file_name = name;
                name = "";
                file_size = -1;
                continue;
            }
            if(info.empty())
            {
                return WNH_TCP_FAIL_RESULTS;
            }
            if(info == WNH_TCP_EXCLUSIVE_SESSION_TIMEOUT_ID)
            {
                WNHERROR(CONNECT_INFO_LOGS ", 等待超时或者会话异常, 接收到信息错误, 会话异常结束" << ", errno=" << errno << ", mesg=" << strerror(errno));
                return false;
            }
            WNHDEBUG(CONNECT_INFO_LOGS << "接收到无法识别的信息:" << info);
            if(!send_info(nfp, info))
            {
                return WNH_TCP_FAIL_RESULTS;
            }
        }
        else
        {
            WNHERROR(CONNECT_INFO_LOGS << "会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
            return WNH_TCP_FAIL_RESULTS;
        }
    }
    return WNH_TCP_FAIL_RESULTS;
}

int wnh_filesync_server::accept_apply_downinfo_file_info(const int nfp, const string info, string & accept_file_name, const CONNECT_INFO & CONNECT_INFO) //接收请求文件下载信息
{
    string file_name;
    if(!accept_apply_downinfo_file_name_info(nfp, info, file_name))
    {
        return WNH_TCP_IGNORE_RESULTS;
    }
    else
    {
        WNHINFO(CONNECT_INFO_LOGS << "客户端请求下载文件, 文件名:" << file_name << ", 开始发送文件");
    }
    if(file_name.empty())
    {
        WNHERROR(CONNECT_INFO_LOGS << "接收请求文件下载信息失败了, 文件名为空");
        return WNH_TCP_FAIL_RESULTS;
    }
    unsigned long file_size;
    if(!reply_downinfo_file_size_info(nfp, file_name, file_size))
    {
        accept_file_name = file_name;
        return WNH_TCP_FAIL_RESULTS;
    }
    else
    {
        WNHINFO(CONNECT_INFO_LOGS << "发送文件大小:" << file_size);
    }
    if(file_size != (unsigned long)0)
    {
        if(!send_reply_downinfo_file_content(nfp, file_name, file_size))
        {
            return WNH_TCP_FAIL_RESULTS;
        }
    }
    if(send_reply_downinfo_file_complete_info(nfp))
    {
        accept_file_name = file_name;
        return WNH_TCP_SUCCESS_RESULTS;
    }
    else
    {
        WNHERROR(CONNECT_INFO_LOGS << "会话异常结束, errno=" << errno << ", mesg=" << strerror(errno));
        close_session(nfp, CONNECT_INFO, false);
    }
    return WNH_TCP_FAIL_RESULTS;
}

bool wnh_filesync_server::add_session(thread *session, const int nfp, const CONNECT_INFO & CONNECT_INFO) //将一个会话添加进入会话记录列表
{
    for(int i = 0; i < TCP_LISTEN_CONCURRENT_MAX_NUM; i ++)
    {
        if(session_info[i].status)
        {
            session_info[i].session = session;
            session_info[i].nfp = nfp;
            session_info[i].client_ip = CONNECT_INFO.client_ip;
            session_info[i].client_port = CONNECT_INFO.client_port;
            session_info[i].start_time = LOCALTIMENUM;
            session_info[i].last_update_time = LOCALTIMENUM;
            session_info[i].status = false;
            WNHDEBUG(CONNECT_INFO_LOGS  << "新的会话已经成功加入会话管理列表, 使用下标:" << i << ", nfp:" << session_info[i].nfp << ", 客户端IP:" << session_info[i].client_ip  << ", 临时端口:" << session_info[i].client_port << ", 第一次连接时间:" << session_info[i].start_time << ", 最后一次链接时间:" << session_info[i].last_update_time);
            return true;
        }
    }
    WNHERROR(CONNECT_INFO_LOGS << "新的会话加入会话管理列表失败了, 会话管理列表已满,程序存在异常");
    return false;
}

bool wnh_filesync_server::sub_session(const int nfp) //将一个会话从会话记录列表中删除
{
    for(int i = 0; i < TCP_LISTEN_CONCURRENT_MAX_NUM; i ++)
    {
        if(session_info[i].nfp == nfp)
        {
            WNHDEBUG("会话从会话记录列表中删除成功, 使用下标:" << i << ", nfp:" << nfp << ", 客户端IP:" << session_info[i].client_ip << ", 临时端口:" << session_info[i].client_port << ", 第一次连接时间:" << session_info[i].start_time << ", 最后一次链接时间:" << session_info[i].last_update_time);
            session_info[i].session = nullptr;
            session_info[i].nfp = 0;
            session_info[i].client_ip = "";
            session_info[i].client_port = 0;
            session_info[i].start_time = 0;
            session_info[i].last_update_time = 0;
            session_info[i].status = true;
            return true;
        }
    }
    WNHERROR("nfp:" << nfp << ", 会话从会话记录列表中删除失败了, 会话管理列表没有该记录");
    return false;
}

bool wnh_filesync_server::manage_session_pthread() //管理会话线程
{
    WNHINFO("管理会话线程启动成功");
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
                WNHINFO("nfp:" << session_info[i].nfp << ", 客户端IP:" << session_info[i].client_ip << ", 临时端口:" << session_info[i].client_port << ", 第一次连接时间:" << session_info[i].start_time << ", 最后一次链接时间:" << session_info[i].last_update_time << ", 该会话已经保持了" << LOCALTIMENUM - session_info[i].start_time << "秒, 使用下标:" << i);
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
