#include "wnh_filesync_server.h"

void wnh_filesync_server::add_client_info()//添加客户端信息
{
    vector<string> client_ip_temp;;
    for(int j = 0; j < rule_num; j ++)
    {
        if((rule+j)->rule_status)
        {
            for(int n = 0; n < (int)(rule+j)->dst_ip.size(); n++)
            {
                bool temp = true;
                for(unsigned int k = 0; k < client_ip_temp.size(); k ++)
                {
                    if(client_ip_temp[k] == (rule+j)->dst_ip[n])
                    {
                        temp = false;
                        break;
                    }
                }
                if(temp)
                {
                    client_ip_temp.push_back((rule+j)->dst_ip[n]);
                    WNHDEBUG("client_ip_temp:" << client_ip_temp[client_ip_temp.size()-1]);
                }
            }
        }
    }
    client_num = client_ip_temp.size();
    client_info = new CLIENT_INFO[client_num];
    for(unsigned int i = 0; i < client_num; i ++)
    {
        (client_info+i)->client_ip = client_ip_temp[i];
        (client_info+i)->begin_connect_time = 0;
        (client_info+i)->last_connect_time = 0;
        (client_info+i)->status = false;
        (client_info+i)->task_num = 0;
        (client_info+i)->fail_task_num = 0;
        (client_info+i)->is_email = 0;
    }
}

void wnh_filesync_server::show_client_info()//显示客户端信息
{
    for(unsigned int i= 0; i < client_num; i ++)
    {
        WNHDEBUG("(client_info+" << i << ")->client_ip=" << (client_info+i)->client_ip);
        WNHDEBUG("(client_info+" << i << ")->begin_connect_time=" << (client_info+i)->begin_connect_time);
        WNHDEBUG("(client_info+" << i << ")->last_connect_time=" << (client_info+i)->last_connect_time);
        WNHDEBUG("(client_info+" << i << ")->status=" << (client_info+i)->status);
        WNHDEBUG("(client_info+" << i << ")->task_num=" << (client_info+i)->task_num);
        WNHDEBUG("(client_info+" << i << ")->fail_task_num=" << (client_info+i)->fail_task_num);
    }
}

void wnh_filesync_server::update_client_info_status(const int & nfp, const CONNECT_INFO & CONNECT_INFO)//更新客户端状态信息
{
    for(unsigned int i= 0; i < client_num; i ++)
    {
        if(CONNECT_INFO.client_ip == (client_info+i)->client_ip)
        {
            if(!(client_info+i)->status)
            {
                (client_info+i)->begin_connect_time = LOCALTIMENUM;
                (client_info+i)->status = true;
                (client_info+i)->is_email = 1;
                WNHINFO(CONNECT_INFO_LOGS << "更新开始连接时间:" << (client_info+i)->begin_connect_time);
                WNHINFO(CONNECT_INFO_LOGS << "更新状态=online");
            }
            (client_info+i)->last_connect_time = LOCALTIMENUM;
            WNHINFO(CONNECT_INFO_LOGS << "更新最后连接时间:" << (client_info+i)->last_connect_time);
        }
    }
}
void wnh_filesync_server::add_task_num_for_client_info(const int & nfp, const CONNECT_INFO & CONNECT_INFO)//更新客户端状态信息
{
    for(unsigned int i= 0; i < client_num; i ++)
    {
        if(CONNECT_INFO.client_ip == (client_info+i)->client_ip)
        {
            (client_info+i)->task_num++;
            //(client_info+i)->last_connect_time = LOCALTIMENUM;
            WNHINFO(CONNECT_INFO_LOGS << "同步完成任务数:" << (client_info+i)->task_num);
            //WNHINFO(CONNECT_INFO_LOGS << "更新最后连接时间:" << (client_info+i)->last_connect_time);
        }
    }
}

void wnh_filesync_server::add_fail_task_num_for_client_info(const int & nfp, const CONNECT_INFO & CONNECT_INFO)//更新客户端状态信息
{
    for(unsigned int i= 0; i < client_num; i ++)
    {
        if(CONNECT_INFO.client_ip == (client_info+i)->client_ip)
        {
            (client_info+i)->fail_task_num++;
            //(client_info+i)->last_connect_time = LOCALTIMENUM;
            WNHINFO(CONNECT_INFO_LOGS << "同步失败任务数:" << (client_info+i)->fail_task_num);
            //WNHINFO(CONNECT_INFO_LOGS << "更新最后连接时间:" << (client_info+i)->last_connect_time);
        }
    }
}

void wnh_filesync_server::check_client_info_status()//检查更新客户端状态信息
{
    WNHINFO("检查更新客户端状态信息线程启动成功");
    vector<string> offline_client_ip;
    vector<string> begin_connect_time;
    vector<string> last_connect_time;
    vector<string> task_num;
    vector<string> complete_task_num;
    vector<string> fail_task_num;
    while(1)
    {
        for(unsigned int i= 0; i < client_num; i ++)
        {
            if((client_info+i)->status)
            {
                if((client_info+i)->last_connect_time + network_timeout < LOCALTIMENUM)
                {
                    (client_info+i)->status = false;
                    if((client_info+i)->is_email == 1)
                    {
                        (client_info+i)->is_email = 2;
                        offline_client_ip.push_back((client_info+i)->client_ip);
                        begin_connect_time.push_back(to_string((client_info+i)->begin_connect_time));
                        last_connect_time.push_back(to_string((client_info+i)->last_connect_time));
                        task_num.push_back(to_string((client_info+i)->task_num));
                        complete_task_num.push_back(to_string(watch.get_task_list_num((client_info+i)->client_ip)));
                        fail_task_num.push_back(to_string((client_info+i)->fail_task_num));

                    }
                    WNHWARN("客户端IP:" << (client_info+i)->client_ip << ", 已经离线, 最后在线时间:" << (client_info+i)->last_connect_time);
                }
            }
        }
        if(offline_client_ip.size() != 0)
        {
            email_client_offline_alert_info(offline_client_ip, begin_connect_time, last_connect_time, task_num, complete_task_num, fail_task_num);
            offline_client_ip.clear();
            begin_connect_time.clear();
            last_connect_time.clear();
            task_num.clear();
            complete_task_num.clear();
            fail_task_num.clear();
        }
        sleep(network_timeout);
    }
}
