#include "wnh_filesync_server.h"

bool wnh_filesync_server::accept_task_fail_v1(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收任务执行失败信息
{
    if(info.substr(0, strlen(WNH_FILESYNC_TASK_FAIL_SIGNAL)) == WNH_FILESYNC_TASK_FAIL_SIGNAL)
    {
        string event_temp = info.substr(strlen(WNH_FILESYNC_TASK_FAIL_SIGNAL));
        string event_id = event_temp.substr(0, 1);
        string src_path = event_temp.substr(1);
        if(send_info(nfp, WNH_FILESYNC_TASK_FAIL_SIGNAL));
        {
            string info_temp;
            if(accept_info(nfp, info_temp))
            {
                if(info_temp.substr(0, strlen(WNH_FILESYNC_TASK_FAIL_SIGNAL)) == WNH_FILESYNC_TASK_FAIL_SIGNAL)
                {
                    string dst_path = info_temp.substr(strlen(WNH_FILESYNC_TASK_FAIL_SIGNAL));
                    if(!watch.add_fail_task_info(CONNECT_INFO.client_ip, event_id, src_path, dst_path))
                    {
                        WNHERROR(CONNECT_INFO_LOGS << "任务执行失败, 同时将失败任务添加进数据库时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path << ", 目标文件:" << dst_path);
                    }
                    else
                    {
                        add_fail_task_num_for_client_info(nfp, CONNECT_INFO);
                    }
                    if(send_info(nfp, WNH_FILESYNC_TASK_FAIL_SIGNAL))
                    {
                        WNHINFO(CONNECT_INFO_LOGS << "接收任务执行失败信息, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path << ", 目标文件:" << dst_path);
                        return true;
                    }
                    WNHERROR(CONNECT_INFO_LOGS << "回复接收任务执行失败信息时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path << ", 目标文件:" << dst_path);
                    return true;
                }
                else
                {
                    WNHERROR(CONNECT_INFO_LOGS << "接收任务执行失败信息, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path << ", 但是在接收目标文件路径的时候失败了");
                    return true;
                }
            }
            WNHERROR(CONNECT_INFO_LOGS << "回复接收任务执行失败信息时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收任务执行失败信息时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::accept_task_fail(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收任务执行失败信息
{
    if(info.substr(0, strlen(WNH_FILESYNC_TASK_FAIL_SIGNAL)) == WNH_FILESYNC_TASK_FAIL_SIGNAL)
    {
        string event_temp = info.substr(strlen(WNH_FILESYNC_TASK_FAIL_SIGNAL));
        string event_id = event_temp.substr(0, 1);
        string src_path = event_temp.substr(1);
        add_fail_task_num_for_client_info(nfp, CONNECT_INFO);
        if(!watch.add_fail_task_info(CONNECT_INFO.client_ip, event_id, src_path))
        {
            WNHERROR(CONNECT_INFO_LOGS << "任务执行失败, 同时将失败任务添加进数据库时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
        }
        if(send_info(nfp, WNH_FILESYNC_TASK_FAIL_SIGNAL));
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收任务执行失败信息, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复任务执行失败信息时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::accept_task_complete_v1(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收任务完成信息
{
    if(info.substr(0, strlen(WNH_FILESYNC_TASK_COMPLETE_SIGNAL)) == WNH_FILESYNC_TASK_COMPLETE_SIGNAL)
    {
        string event_temp = info.substr(strlen(WNH_FILESYNC_TASK_COMPLETE_SIGNAL));
        string event_id = event_temp.substr(0, 1);
        string src_path = event_temp.substr(1);
        if(send_info(nfp, WNH_FILESYNC_TASK_COMPLETE_SIGNAL));
        {
            string info_temp;
            if(accept_info(nfp, info_temp))
            {
                if(info_temp.substr(0, strlen(WNH_FILESYNC_TASK_COMPLETE_SIGNAL)) == WNH_FILESYNC_TASK_COMPLETE_SIGNAL)
                {
                    string dst_path = info_temp.substr(strlen(WNH_FILESYNC_TASK_COMPLETE_SIGNAL));
                    if(!watch.delete_one_task(CONNECT_INFO.client_ip, event_id, src_path, dst_path))
                    {
                        WNHERROR(CONNECT_INFO_LOGS << "完成一个任务,但是将任务从数据库从删除时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path << ", 目标文件:" << dst_path);
                    }
                    else
                    {
                        add_task_num_for_client_info(nfp, CONNECT_INFO);
                    }
                    if(send_info(nfp, WNH_FILESYNC_TASK_COMPLETE_SIGNAL))
                    {
                        WNHINFO(CONNECT_INFO_LOGS << "接收任务完成信息, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path << ", 目标文件:" << dst_path);
                        return true;
                    }
                    WNHERROR(CONNECT_INFO_LOGS << "回复接收任务完成信息时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path << ", 目标文件:" << dst_path);
                    return true;
                }
                else
                {
                    WNHERROR(CONNECT_INFO_LOGS << "接收任务完成信息, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path << ", 但是在接收目标文件路径的时候失败了");
                    return true;
                }
            }
            WNHERROR(CONNECT_INFO_LOGS << "回复接收任务完成信息时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收任务完成信息时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::accept_task_complete(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收任务完成信息
{
    if(info.substr(0, strlen(WNH_FILESYNC_TASK_COMPLETE_SIGNAL)) == WNH_FILESYNC_TASK_COMPLETE_SIGNAL)
    {
        string event_temp = info.substr(strlen(WNH_FILESYNC_TASK_COMPLETE_SIGNAL));
        string event_id = event_temp.substr(0, 1);
        string src_path = event_temp.substr(1);
        add_task_num_for_client_info(nfp, CONNECT_INFO);
        if(!watch.delete_one_task(CONNECT_INFO.client_ip, event_id, src_path))
        {
            WNHERROR(CONNECT_INFO_LOGS << "完成一个任务,但是将任务从数据库从删除时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
        }
        if(send_info(nfp, WNH_FILESYNC_TASK_COMPLETE_SIGNAL));
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收任务完成信息, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收任务完成信息时失败了, 动作:"<< watch.event_transform(event_id) << ", 源文件:" << src_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::accept_get_task_list(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收请求获取任务列表
{
    if(info == WNH_FILESYNC_GET_TASK_LIST_SIGNAL)
    {
        string task_list_path;
        task_list_path = task_list_path + DEFAULT_TASK_LIST_PATH_FORMAT;
        if(!watch.create_task_list_file(CONNECT_INFO.client_ip, task_list_path, SINGLE_TASK_LIST_MAX_NUM))
        {
            task_list_path = "";
        }
        if(send_info(nfp, WNH_FILESYNC_GET_TASK_LIST_SIGNAL + task_list_path));
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收请求获取任务列表, 任务列表路径:" << task_list_path);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收请求获取任务列表时失败了, 任务列表路径:" << task_list_path);
        return true;
    }
    return false;
}

bool wnh_filesync_server::accept_get_task_num(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收请求获取任务数
{
    if(info == WNH_FILESYNC_GET_TASK_NUM_SIGNAL)
    {
        unsigned long task_num;
        if(license_remaining_effectiveness_time == (unsigned long)0)
        {
            task_num = 0;
        }
        else if(!watch.query_task_num(CONNECT_INFO.client_ip, task_num))
        {
            task_num = 0;
        }
        if(send_info(nfp, WNH_FILESYNC_GET_TASK_NUM_SIGNAL + to_string(task_num)))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收请求获取任务数, 返回任务数:" << task_num);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收请求获取任务数时失败了, 任务数:" << task_num);
        return true;
    }
    return false;
}

bool wnh_filesync_server::accept_online_signal(const int & nfp, const string & info, const CONNECT_INFO & CONNECT_INFO) //接收在线信号
{
    if(info == WNH_FILESYNC_ONLINE_SIGNAL)
    {
        if(send_info(nfp, WNH_FILESYNC_ONLINE_SIGNAL))
        {
            WNHINFO(CONNECT_INFO_LOGS << "接收在线信号");
            update_client_info_status(nfp, CONNECT_INFO);
            return true;
        }
        WNHERROR(CONNECT_INFO_LOGS << "回复接收到在线信号时失败了");
        return true;
    }
    return false;
}

bool wnh_filesync_server::accept_if_allow_connect(const int & nfp, const string & info,  const CONNECT_INFO & CONNECT_INFO) //接收检查客户端IP是否为允许连接信息
{
    if(info == WNH_FILESYNC_IF_ALLOW_CONNECT)
    {
        if(check_target_ip(CONNECT_INFO.client_ip))
        {
            if(send_info(nfp, WNH_FILESYNC_IF_ALLOW_CONNECT_YES))
            {
                WNHINFO(CONNECT_INFO_LOGS << "允许连接");
                return true;
            }
            WNHERROR(CONNECT_INFO_LOGS << "回复允许连接时失败了");
            return true;
        }
        else
        {
            if(send_info(nfp, WNH_FILESYNC_IF_ALLOW_CONNECT_NO))
            {
                WNHINFO(CONNECT_INFO_LOGS << "不允许连接");
                return true;
            }
            WNHERROR(CONNECT_INFO_LOGS << "回复不允许连接时失败了");
            return true;
        }
    }
    return false;
}


bool wnh_filesync_server::check_target_ip(const string & client_ip) //检查客户端IP是否为允许连接
{
    for(int j = 0; j < rule_num; j ++)
    {
        for(int n = 0; n < (int)(rule+j)->dst_ip.size(); n++)
        {
            if(client_ip == (rule+j)->dst_ip[n])
            {
                //WNHINFO("允许IP为" << client_ip << "的客户端 连接");
                return true;
            }
        }
    }
    //WNHWARN("不允许IP为" << client_ip << "的客户端 连接");
    return false;
}
