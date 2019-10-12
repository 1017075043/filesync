#include "wnh_filesync_client.h"

bool wnh_filesync_client::send_task_fail(const string & task_src_path, const string & task_dst_path, const string & event_id) //向服务器发送任务执行失败信息
{
    if(send_info(WNH_FILESYNC_TASK_FAIL_SIGNAL + event_id + task_src_path))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器发送任务执行失败信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info == WNH_FILESYNC_TASK_FAIL_SIGNAL)
        {
            if(send_info(WNH_FILESYNC_TASK_FAIL_SIGNAL + task_dst_path))
            {
                if(!accept_info(info))
                {
                    WNHERROR(SERVER_INFO_LOGS << ", 向服务器发送任务执行失败信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
                    return false;
                }
                if(info == WNH_FILESYNC_TASK_FAIL_SIGNAL)
                {
                    WNHINFO(SERVER_INFO_LOGS <<  "向服务器发送任务执行失败信息成功, 任务信息:" << task_src_path << ", " << task_dst_path);
                    return true;
                }
                else
                {
                    WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务执行失败信息, 但是并没得到得到的正常回复, 任务信息:" << task_src_path << ", " << task_dst_path);
                    return false;
                }
            }
            WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务执行失败信息, errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务执行失败信息, 但是并没得到得到的正常回复, 任务信息:" << task_src_path);
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务执行失败信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_task_fail(const string & task_src_path, const string & event_id) //向服务器发送任务执行失败信息
{
    if(send_info(WNH_FILESYNC_TASK_FAIL_SIGNAL + event_id + task_src_path))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器发送任务执行失败信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info == WNH_FILESYNC_TASK_FAIL_SIGNAL)
        {
            WNHINFO(SERVER_INFO_LOGS <<  "向服务器发送任务执行失败信息成功, 任务信息:" << task_src_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务执行失败信息, 但是并没得到得到的正常回复, 任务信息:" << task_src_path);
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务执行失败信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_task_complete(const string & task_src_path, const string & task_dst_path, const string & event_id) //向服务器发送任务完成信息
{
    if(send_info(WNH_FILESYNC_TASK_COMPLETE_SIGNAL + event_id + task_src_path))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器发送任务完成信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info == WNH_FILESYNC_TASK_COMPLETE_SIGNAL)
        {
            if(send_info(WNH_FILESYNC_TASK_COMPLETE_SIGNAL + task_dst_path))
            {
                if(!accept_info(info))
                {
                    WNHERROR(SERVER_INFO_LOGS << ", 向服务器发送任务完成信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
                    return false;
                }
                if(info == WNH_FILESYNC_TASK_COMPLETE_SIGNAL)
                {
                    WNHINFO(SERVER_INFO_LOGS <<  "向服务器发送任务完成信息成功, 任务信息:" << task_src_path << ", " << task_dst_path);
                    return true;
                }
                else
                {
                    WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务完成信息, 但是并没得到得到的正常回复, 任务信息:" << task_src_path << ", " << task_dst_path);
                    return false;
                }
            }
            WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务完成信息, errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务完成信息, 但是并没得到得到的正常回复, 任务信息:" << task_src_path);
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务完成信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_task_complete(const string & task_src_path, const string & event_id) //向服务器发送任务完成信息
{
    if(send_info(WNH_FILESYNC_TASK_COMPLETE_SIGNAL + event_id + task_src_path))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器发送任务完成信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info == WNH_FILESYNC_TASK_COMPLETE_SIGNAL)
        {
            WNHINFO(SERVER_INFO_LOGS <<  "向服务器发送任务完成信息成功, 任务信息:" << task_src_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务完成信息, 但是并没得到得到的正常回复, 任务信息:" << task_src_path);
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器发送任务完成信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_get_task_list(string & task_list_path) //向服务器请求获取任务列表
{
    if(send_info(WNH_FILESYNC_GET_TASK_LIST_SIGNAL))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取任务列表失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_GET_TASK_LIST_SIGNAL)) == WNH_FILESYNC_GET_TASK_LIST_SIGNAL)
        {
            task_list_path = info.substr(strlen(WNH_FILESYNC_GET_TASK_LIST_SIGNAL));
            //task_num = strtoull(info.substr(strlen(WNH_FILESYNC_GET_TASK_LIST_SIGNAL)).c_str(), nullptr, 10);
            WNHINFO(SERVER_INFO_LOGS <<  "向服务器请求获取任务列表成功, 任务列表路径:" << task_list_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取任务列表, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取任务列表, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_get_task_num(unsigned long & task_num) //向服务器请求获取任务数
{
    if(send_info(WNH_FILESYNC_GET_TASK_NUM_SIGNAL))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取任务数失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_GET_TASK_NUM_SIGNAL)) == WNH_FILESYNC_GET_TASK_NUM_SIGNAL)
        {
            task_num = strtoull(info.substr(strlen(WNH_FILESYNC_GET_TASK_NUM_SIGNAL)).c_str(), nullptr, 10);
            WNHINFO(SERVER_INFO_LOGS <<  "向服务器请求获取任务数成功, 任务数:" << task_num);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取任务数, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取任务数, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_if_allow_connect() //向服务端请求是否允许链接
{
    if(send_info(WNH_FILESYNC_IF_ALLOW_CONNECT))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务端请求是否允许链接失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info == WNH_FILESYNC_IF_ALLOW_CONNECT_YES)
        {
            WNHINFO(SERVER_INFO_LOGS <<  "接受连接");
            return true;
        }
        else if(info == WNH_FILESYNC_IF_ALLOW_CONNECT_NO)
        {
            WNHINFO(SERVER_INFO_LOGS <<  "拒接连接");
            return false;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务端请求是否允许链接, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务端请求是否允许链接, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_online_signal_v1() //向服务端发送在线信号
{
    if(send_info(WNH_FILESYNC_ONLINE_SIGNAL))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务端发送在线信号失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info == WNH_FILESYNC_ONLINE_SIGNAL)
        {
            WNHINFO(SERVER_INFO_LOGS <<  "在线信号发送成功");
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS <<  "向服务端发送在线信号, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS <<  "向服务端发送在线信号, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_online_signal() //向服务端发送在线信号
{
    static unsigned int long time = 0;
    if(LOCALTIMENUM - time < ONLINE_MESSAGE_SENDING_INTERVAL)
    {
        return true;
    }
    time = LOCALTIMENUM;
    if(send_info(WNH_FILESYNC_ONLINE_SIGNAL))
    {
        string info;
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务端发送在线信号失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info == WNH_FILESYNC_ONLINE_SIGNAL)
        {
            WNHINFO(SERVER_INFO_LOGS <<  "在线信号发送成功");
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS <<  "向服务端发送在线信号, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS <<  "向服务端发送在线信号, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::send_end_session_info() //发送结束会话信息
{
    usleep(100);
    if(send_info(WNH_TCP_END_SESSION_INFO))
    {
        close(socket_num);
        WNHINFO(SERVER_INFO_LOGS <<  "成功发出结束会话信息, 即将关闭会话句柄数socket_num=" << socket_num);
        return true;
    }
    close(socket_num);
    WNHDEBUG(SERVER_INFO_LOGS <<  "发出结束会话信息失败了, 即将关闭会话句柄数socket_num=" << socket_num << ", errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

bool wnh_filesync_client::download_file(const string file_name, const string temp_file_name) //下载文件
{
    WNHINFO(SERVER_INFO_LOGS <<  "开始尝试向服务器请求下载文件:" << file_name << ", 并将其保存到:" << temp_file_name);
    if(!send_apply_download_file_info(file_name))
    {
        return false;
    }
    string info;
    unsigned long file_size;
    while(1)
    {
        if(accept_info(info))
        {
            if(accept_download_file_error_stop_info(info))
            {
                WNHINFO(SERVER_INFO_LOGS <<  file_name << ", 下载失败");
                return false;
            }
            if(accept_download_file_size_info(info, file_size))
            {
                if(file_size == (unsigned long)0)
                {
                    ofstream file_info(temp_file_name.c_str(), ios::out | ios::binary);
                    if(!file_info.is_open())
                    {
                        WNHERROR("文件创建失败, 文件名称:" << temp_file_name << ", errno=" << errno << ", mesg=" << strerror(errno));
                    }
                    else
                    {
                        WNHDEBUG("文件创建成功, 文件名称:" << temp_file_name);
                    }
                    file_info.close();
                }
                continue;
            }
            if(accept_download_file_content_info(info, file_size, temp_file_name))
            {
                continue;
            }
            if(accept_download_file_complete_info(info))
            {
                WNHINFO(SERVER_INFO_LOGS << "文件:" << file_name << ", 下载成功,保存到:" << temp_file_name);
                return true;
            }
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << ", 下载文件失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return true;
        }
    }
    return true;
}
