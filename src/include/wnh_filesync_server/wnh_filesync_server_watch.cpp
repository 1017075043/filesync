#include "wnh_filesync_server.h"

void wnh_filesync_server::watch_core() //使用wnh_inotify_use_sqlite进行目录监控
{
    watch.init();
    watch.create();
    for(int j = 0; j < rule_num; j ++)
    {
        if((rule+j)->rule_status)
        {
            watch.add_watch_dir((rule+j)->src_dir); //添加同步目录
        }
    }
    for(int j = 0; j < rule_num; j ++)
    {
        if((rule+j)->rule_status)
        {
            for(int n = 0; n < (int)(rule+j)->ignore_dir.size(); n++)
            {
                watch.add_ignore_watch_dir((rule+j)->ignore_dir[n]);//删除不同步目录
            }
        }
    }
    for(int j = 0; j < rule_num; j ++)
    {
        if((rule+j)->rule_status)
        {
            for(int n = 0; n < (int)(rule+j)->ignore_rule.size(); n++)
            {
                watch.add_ignore_rule((rule+j)->ignore_rule[n]);//添加忽略同步规则
            }
        }
    }
    watch.start_watch(wnh_inotify_use_sqlite::USE_MODE::back_record);

    thread start_event_into_task_pthread(&wnh_filesync_server::event_into_task, this);
    start_event_into_task_pthread.detach();
    thread start_again_created_event_pthread(&wnh_filesync_server::again_created_event, this);
    start_again_created_event_pthread.detach();
}

void wnh_filesync_server::watch_core_v1() //使用wnh_inotify_use_sqlite进行目录监控,v1版本
{
    watch.init();
    watch.create();
    set<string>::iterator it; //定义前向迭代器
    for(int i = 0; i < sync_rule_num; i++)
    {
        watch.add_watch_dir(sync_rule[i].src_dir); //添加同步目录
    }

    set<string> rule_temp;
    for(int i = 0; i < sync_rule_num; i++)
    {
        for(it = sync_rule[i].ignore_rule.begin(); it != sync_rule[i].ignore_rule.end(); it++)
        {
            rule_temp.insert(*it);
        }
    }
    for(it = rule_temp.begin(); it != rule_temp.end(); it++)
    {
        watch.add_ignore_rule(*it);//添加忽略同步规则
    }

    rule_temp.clear();
    for(int i = 0; i < sync_rule_num; i++)
    {
        for(it = sync_rule[i].ignore_dir.begin(); it != sync_rule[i].ignore_dir.end(); it++)
        {
            rule_temp.insert(*it);
        }
    }
    for(it = rule_temp.begin(); it != rule_temp.end(); it++)
    {
        watch.add_ignore_watch_dir(*it);//删除不同步目录
    }
    rule_temp.clear();

    watch.start_watch(wnh_inotify_use_sqlite::USE_MODE::back_record);

    thread start_event_into_task_pthread(&wnh_filesync_server::event_into_task, this);
    start_event_into_task_pthread.detach();
    thread start_again_created_event_pthread(&wnh_filesync_server::again_created_event, this);
    start_again_created_event_pthread.detach();
}

void wnh_filesync_server::event_into_task() //将事件转换成任务
{
    WNHINFO("事件转换成任务线程启动成功");
    while(survival_id)
    {
        sleep(EVENT_TRANSITION_TIME_INTERVAL);
        for(int i = 0; i < sync_rule_num; i++)
        {
            watch.event_into_task(sync_rule[i].src_dir, sync_rule[i].dst_dir, sync_rule[i].dst_ip);
        }
    }
}

void wnh_filesync_server::again_created_event() //再次创建事件
{
    WNHINFO("再次创建事件线程启动成功");
    while(survival_id)
    {
        watch.again_created_event();
        sleep(AGAIN_CREATED_EVENT_TIME_INTERVAL);
    }
}



