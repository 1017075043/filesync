#include "wnh_filesync_server.h"

void wnh_filesync_server::get_conf(const string &conf_path)
{
    conf.read_config_ini(conf_path);
    conf.show_configure_ini();
    vector<string> value;
    value = conf.get_conf("system_configure", "port");
    if(value.size() == 1)
    {
        port = atoi(value[0].c_str());
        WNHDEBUG("获取到系统配置system_configure.port=" << port);
    }
    else
    {
        WNHERROR("获取到系统配置.服务端使用的端口(system_configure.port)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("system_configure", "network_timeout");
    if(value.size() == 1)
    {
        network_timeout = atoi(value[0].c_str());
        WNHDEBUG("获取到系统配置system_configure.network_timeout=" << network_timeout);
    }
    else
    {
        WNHERROR("获取到系统配置.网络超时时间(system_configure.network_timeout)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("system_configure", "auto_restore_fail_task");
    if(value.size() == 1)
    {
        auto_restore_fail_task = atoi(value[0].c_str());
        WNHDEBUG("获取到系统配置system_configure.auto_restore_fail_task=" << auto_restore_fail_task);
    }
    else
    {
        WNHERROR("获取到系统配置.自动恢复失败任务(system_configure.auto_restore_fail_task)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("system_configure", "persistence_task");
    if(value.size() == 1)
    {
        persistence_task = atoi(value[0].c_str());
        WNHDEBUG("获取到系统配置system_configure.persistence_task=" << persistence_task);
    }
    else
    {
        WNHERROR("获取到系统配置.是否启动持久化(system_configure.persistence_task)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("email", "status");
    if(value.size() == 1)
    {
        value[0] == "1" ? email_info.status = true : email_info.status = false;
    }
    else
    {
        WNHERROR("获取到系统配置.是否启用邮件报警(email.status)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("email", "sender_email_address");
    if(value.size() == 1)
    {
        email_info.sender_email_address = value[0].c_str();
    }
    else
    {
        WNHERROR("获取到系统配置.发件人邮箱地址(email.sender_email_address)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("email", "recipient_email_address");
    if(value.size() >= 1)
    {
        email_info.recipient_email_address = value;
    }
    else
    {
        WNHERROR("获取到系统配置.收件人邮箱地址(email.recipient_email_address)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("email", "email_server_address");
    if(value.size() == 1)
    {
        email_info.email_server_address = value[0].c_str();
    }
    else
    {
        WNHERROR("获取到系统配置.邮件服务器地址(email.email_server_address)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("email", "email_server_user");
    if(value.size() == 1)
    {
        email_info.email_server_user = value[0].c_str();
    }
    else
    {
        WNHERROR("获取到系统配置.邮件服务器登录帐户(email.email_server_user)失败,不存在或者存在多个");
        exit(0);
    }
    value = conf.get_conf("email", "email_server_password");
    if(value.size() == 1)
    {
        email_info.email_server_password = value[0].c_str();
    }
    else
    {
        WNHERROR("获取到系统配置.邮件服务器登录帐户密码(email.email_server_password)失败,不存在或者存在多个");
        exit(0);
    }
    get_rule_conf();
}

void wnh_filesync_server::get_rule_conf()
{
    wnh_system_operation wnh_sys_op;
    vector<string> all_unit_name = conf.get_all_unit_name();
    for(int i = 0; i < (int)all_unit_name.size(); i++)
    {
        if(all_unit_name[i].substr(0, rule_identification.length()) == rule_identification)
        {
            rule_num++;
        }
    }
    WNHDEBUG("同步规则数量rule_num=" << rule_num);
    rule=new RULE[rule_num];
    int j = 0;
    for(int i = 0; i < (int)all_unit_name.size(); i++)
    {
        if(all_unit_name[i].substr(0, rule_identification.length()) == rule_identification)
        {
            (rule+j)->rule_name = all_unit_name[i].substr(rule_identification.length());
            WNHDEBUG("获取到同步规则的名称rule_name=" << (rule+j)->rule_name);
            vector<string> value;
            value = conf.get_conf(all_unit_name[i], "src_dir");
            if(value.size() == 1)
            {
                delete_last_char(value[0], '/');
                (rule+j)->src_dir = value[0].c_str();
                if(!wnh_sys_op.file_or_dir_exist((rule+j)->src_dir))
                {
                    WNHERROR("同步规则" << (rule+j)->rule_name << ".src_dir=" << (rule+j)->src_dir << ", 配置错误, 路径不存在");
                    exit(0);
                }
                WNHDEBUG("获取到同步规则" << (rule+j)->rule_name << ".src_dir=" << (rule+j)->src_dir);
            }
            else
            {
                WNHERROR("同步规则" << (rule+j)->rule_name << ".src_dir配置错误");
                exit(0);
            }
            value = conf.get_conf(all_unit_name[i], "dst_dir");
            if(value.size() >= 1)
            {
                delete_last_char(value[0], '/');
                (rule+j)->dst_dir = value;
                for(int n = 0; n < (int)(rule+j)->dst_dir.size(); n++)
                {
                    WNHDEBUG("获取到同步规则" << (rule+j)->rule_name << ".dst_dir=" << (rule+j)->dst_dir[0]);
                }
            }
            else
            {
                WNHERROR("同步规则" << (rule+j)->rule_name << ".dst_dir配置错误");
                exit(0);
            }
            value = conf.get_conf(all_unit_name[i], "dst_ip");
            if(value.size() >= 1)
            {
                (rule+j)->dst_ip = value;
                for(int n = 0; n < (int)(rule+j)->dst_ip.size(); n++)
                {
                    WNHDEBUG("获取到同步规则" << (rule+j)->rule_name << ".dst_ip=" << (rule+j)->dst_ip[n]);
                }
            }
            else
            {
                WNHERROR("同步规则" << (rule+j)->rule_name << ".dst_ip配置错误");
                exit(0);
            }
            value = conf.get_conf(all_unit_name[i], "ignore_rule");
            if(value.size() >= 1)
            {
                (rule+j)->ignore_rule = value;
                for(int n = 0; n < (int)(rule+j)->ignore_rule.size(); n++)
                {
                    WNHDEBUG("获取到同步规则" << (rule+j)->rule_name << ".ignore_rule=" << (rule+j)->ignore_rule[n]);
                }
            }
            value = conf.get_conf(all_unit_name[i], "ignore_dir");
            if(value.size() >= 1)
            {
                (rule+j)->ignore_dir = value;
                for(int n = 0; n < (int)(rule+j)->ignore_dir.size(); n++)
                {
                    if(!wnh_sys_op.file_or_dir_exist((rule+j)->ignore_dir[n]))
                    {
                        WNHERROR("获取到同步规则" << (rule+j)->rule_name << ".ignore_dir=" << (rule+j)->ignore_dir[n] << ", 配置错误, 路径不存在");
                        exit(0);
                    }
                    delete_last_char((rule+j)->ignore_dir[n], '/');
                    WNHDEBUG("获取到同步规则" << (rule+j)->rule_name << ".ignore_dir=" << (rule+j)->ignore_dir[n]);
                }
            }
            value = conf.get_conf(all_unit_name[i], "rule_status");
            if(value.size() == 1)
            {
                (rule+j)->rule_status = atoi(value[0].c_str());
                WNHDEBUG("获取到同步规则" << (rule+j)->rule_name << ".rule_status=" << (rule+j)->rule_status);
            }
            else
            {
                WNHERROR("同步规则" << (rule+j)->rule_name << ".rule_status配置错误");
                exit(0);
            }
            j ++;
        }
    }
}

void wnh_filesync_server::rectification_rule_conf() //整理规则配置
{
    set<string> src_dir_set; //使用set容器实现对规则的去重
    for(int j = 0; j < rule_num; j ++)
    {
        if((rule+j)->rule_status == false)
        {
            continue;
        }
        src_dir_set.insert((rule+j)->src_dir);
    }
    sync_rule = new SYNC_RULE[src_dir_set.size()];
    set<string>::iterator it; //定义前向迭代器
    int i = 0;
    for(it = src_dir_set.begin(); it != src_dir_set.end(); it++)
    {
        sync_rule[i].src_dir = *it;
        //WNHINFO("整理后的同步规则:sync_rule[" << i << "].src_dir=" << sync_rule[i].src_dir);
        i++;
    }
    sync_rule_num = i;
    for(int i = 0; i < sync_rule_num; i++)
    {
        for(int j = 0; j < rule_num; j ++)
        {
            if((rule+j)->rule_status && (rule+j)->src_dir == sync_rule[i].src_dir)
            {
                for(unsigned int a = 0; a < (rule+j)->dst_ip.size(); a++)
                {
                    for(unsigned int b = 0; b < (rule+j)->dst_dir.size(); b++)
                    {
                        sync_rule[i].dst_dir.push_back((rule+j)->dst_dir[b]);
                        sync_rule[i].dst_ip.push_back((rule+j)->dst_ip[a]);
                        //WNHINFO("整理后的同步规则:sync_rule[" << i << "].dst_dir=" << (rule+j)->dst_dir[b]);
                        //WNHINFO("整理后的同步规则:sync_rule[" << i << "].dst_ip=" << (rule+j)->dst_ip[a]);
                    }
                }
                for(int n = 0; n < (int)(rule+j)->ignore_rule.size(); n++)
                {
                    sync_rule[i].ignore_rule.insert((rule+j)->ignore_rule[n]);
                    //WNHINFO("整理后的同步规则:sync_rule[" << i << "].ignore_rule=" << (rule+j)->ignore_rule[n]);
                }
                for(int n = 0; n < (int)(rule+j)->ignore_dir.size(); n++)
                {
                    sync_rule[i].ignore_dir.insert((rule+j)->ignore_dir[n]);
                    //WNHINFO("整理后的同步规则:sync_rule[" << i << "].ignore_dir=" << (rule+j)->ignore_dir[n]);
                }
            }
        }
    }
    for(int i = 0; i < sync_rule_num; i++)
    {
        WNHINFO("整理后的同步规则:sync_rule[" << i << "].src_dir=" << sync_rule[i].src_dir);
        for(int n = 0; n < (int)sync_rule[i].dst_dir.size(); n++)
        {
            WNHINFO("整理后的同步规则:sync_rule[" << i << "].dst_ip:dst_dir=" << sync_rule[i].dst_ip[n] << ":" << sync_rule[i].dst_dir[n]);
        }
        for(it = sync_rule[i].ignore_rule.begin(); it != sync_rule[i].ignore_rule.end(); it++)
        {
            WNHINFO("整理后的同步规则:sync_rule[" << i << "].ignore_rule=" << *it);
        }
        for(it = sync_rule[i].ignore_dir.begin(); it != sync_rule[i].ignore_dir.end(); it++)
        {
            WNHINFO("整理后的同步规则:sync_rule[" << i << "].ignore_dir=" << *it);
        }
    }
}

void wnh_filesync_server::show_rule_conf()
{
    WNHINFO("系统配置system_configure.port=" << port);
    WNHINFO("系统配置system_configure.network_timeout=" << network_timeout);
    WNHINFO("系统配置system_configure.auto_restore_fail_task=" << auto_restore_fail_task);
    WNHINFO("系统配置system_configure.persistence_task=" << persistence_task);

    WNHINFO("邮件配置email.status=" << email_info.status);
    WNHINFO("邮件配置email.sender_email_address=" << email_info.sender_email_address);
    for(unsigned int i = 0; i < email_info.recipient_email_address.size(); i++)
    {
        WNHINFO("邮件配置email.recipient_email_address=" << email_info.recipient_email_address[i]);
    }
    WNHINFO("邮件配置email.email_server_address=" << email_info.email_server_address);
    WNHINFO("邮件配置email.email_server_user=" << email_info.email_server_user);
    WNHINFO("邮件配置email.email_server_password=" << email_info.email_server_password);

    for(int j = 0; j < rule_num; j ++)
    {
        WNHINFO("同步规则名称rule_name=" << (rule+j)->rule_name);
        WNHINFO("同步规则" << (rule+j)->rule_name << ".src_dir=" << (rule+j)->src_dir);
        for(int n = 0; n < (int)(rule+j)->dst_dir.size(); n++)
        {
            WNHINFO("同步规则" << (rule+j)->rule_name << ".dst_dir=" << (rule+j)->dst_dir[n]);
        }
        for(int n = 0; n < (int)(rule+j)->dst_ip.size(); n++)
        {
            WNHINFO("同步规则" << (rule+j)->rule_name << ".dst_ip=" << (rule+j)->dst_ip[n]);
        }
        for(int n = 0; n < (int)(rule+j)->ignore_rule.size(); n++)
        {
            WNHINFO("同步规则" << (rule+j)->rule_name << ".ignore_rule=" << (rule+j)->ignore_rule[n]);
        }
        for(int n = 0; n < (int)(rule+j)->ignore_dir.size(); n++)
        {
            WNHINFO("同步规则" << (rule+j)->rule_name << ".ignore_dir=" << (rule+j)->ignore_dir[n]);
        }
        WNHINFO("同步规则" << (rule+j)->rule_name << ".rule_status=" << (rule+j)->rule_status);
    }
}
