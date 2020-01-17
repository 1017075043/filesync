#include "wnh_filesync_control.h"

void wnh_filesync_control::get_sync_fail_task_list_info() //获取同步失败任务列表信息
{
    cout << endl;
    if(!unblock_connect(ip, to_string(port)))
    {
        WNHERROR(ip << ":" << port << ", 无法链接, 服务端不在线");
        close(socket_num);
        return;
    }
    if(!send_start_session_info())
    {
        close(socket_num);
        return;
    }
    string sync_fail_task_list_file_path;
    bool is_first = true;
    while(1)
    {
        if(!send_get_fail_task_list_info(sync_fail_task_list_file_path))
        {
            close(socket_num);
            return;
        }
        if(sync_fail_task_list_file_path != WNH_FILESYNC_NOT_OR_FAIL_SYNC_FAIL_TASk_LIST_INFO)
        {
            if(!download_file(sync_fail_task_list_file_path, sync_fail_task_list_file_path + SYNC_FAIL_TASK_LIST_INFO_FILE_SUFFIX))
            {
                close(socket_num);
                return;
            }
            show_sync_fail_task_list_info(sync_fail_task_list_file_path + SYNC_FAIL_TASK_LIST_INFO_FILE_SUFFIX); //显示同步失败任务数据信息
        }
        else
        {
            if(is_first == true)
            {
                WNHINFO("当前没有同步失败任务");
                break;
            }
            fail_task_list_info_page = fail_task_list_info_page - SYNC_FAIL_TASK_LIST_INFO_LINE_NUM;
        }
        if(get_direction_keyboard_input_update_page(fail_task_list_info_page, SYNC_FAIL_TASK_LIST_INFO_LINE_NUM) == false) //同步失败任务列表信号换页选择
        {
            break;
        }
        is_first = false;
    }
    send_end_session_info();
    return;
}

bool wnh_filesync_control::send_get_fail_task_list_info(string & sync_fail_task_list_file_path) //向服务器发送获取同步失败任务列表信号, 且获取同步失败任务列表文件路径
{
    string info;
    info = info + WNH_FILESYNC_SYNC_FAIL_TASkK_LIST_INFO + to_string(fail_task_list_info_page) + "," + to_string(SYNC_FAIL_TASK_LIST_INFO_LINE_NUM);
    if(send_info(info.c_str()))
    {
        if(!accept_info(info))
        {
            WNHERROR(SERVER_INFO_LOGS << ", 向服务器请求获取同步失败任务列表信息失败了" << ", errno=" << errno << ", mesg=" << strerror(errno));
            return false;
        }
        if(info.substr(0, strlen(WNH_FILESYNC_SYNC_FAIL_TASkK_LIST_INFO)) == WNH_FILESYNC_SYNC_FAIL_TASkK_LIST_INFO)
        {
            sync_fail_task_list_file_path = info.substr(strlen(WNH_FILESYNC_SYNC_FAIL_TASkK_LIST_INFO));
            WNHDEBUG(SERVER_INFO_LOGS <<  "向服务器请求获取同步失败任务列表信息成功, 同步传输过程信息文件路径:" << sync_fail_task_list_file_path);
            return true;
        }
        else
        {
            WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取同步失败任务列表信息, 但是并没得到得到的正常回复");
            return false;
        }
    }
    WNHERROR(SERVER_INFO_LOGS << "向服务器请求获取同步失败任务列表信息, errno=" << errno << ", mesg=" << strerror(errno));
    return false;
}

vector<string> wnh_filesync_control::get_sync_fail_task_list_info(const string & sync_fail_task_list_file_path) //获取同步失败任务列表信息
{
    vector<string> values_ss_temp;
    sync_fail_task_list_info.read_config_ini(sync_fail_task_list_file_path, false);
    for(int i = 0; i < sync_fail_task_list_info.config_unit_num - 1; i ++)
    {
        if(sync_fail_task_list_info.config_unit[i].name.substr(0, strlen(WNH_FILESYNC_FAIL_TASK_LIST_ID)) == WNH_FILESYNC_FAIL_TASK_LIST_ID)
        {
            string client_ip = sync_fail_task_list_info.get_conf_one(i, "client_ip");
            string event_id = sync_fail_task_list_info.get_conf_one(i, "event_id");
            string src_path = sync_fail_task_list_info.get_conf_one(i, "src_path");
            string dst_path = sync_fail_task_list_info.get_conf_one(i, "dst_path");
            string update_date = sync_fail_task_list_info.get_conf_one(i, "update_date");
            values_ss_temp.push_back(client_ip);
            values_ss_temp.push_back(event_id);
            values_ss_temp.push_back(src_path);
            values_ss_temp.push_back(dst_path);
            values_ss_temp.push_back(update_date);
            WNHDEBUG("client_ip=" << client_ip << ", event_id=" << event_id << ", src_path" << src_path << ", dst_path=" << dst_path << ", update_date=" << update_date);
            //cout << WNH_FONT_COLOR_CYAN << update_date << WNH_FONT_COLOR_RED << " " << client_ip <<  WNH_FONT_COLOR_BLUE << " " << event_id << WNH_FONT_COLOR_YELLOW << " " << src_path  << WNH_FONT_COLOR_YELLOW << " " << dst_path << WNH_FONT_COLOR_RESET << endl;
        }
    }
    string total_sync_fail_task_list_line_num = sync_fail_task_list_info.get_conf_one(WNH_FILESYNC_FAIL_TASK_LIST_NUM_ID, "num");
    values_ss_temp.push_back(total_sync_fail_task_list_line_num);
    //WNHINFO("total_sync_fail_task_list_line_num=" << total_sync_fail_task_list_line_num);
    if(unlink(sync_fail_task_list_file_path.c_str()) != 0)
    {
        WNHWARN("临时文件," << sync_fail_task_list_file_path << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    return values_ss_temp;
}

bool wnh_filesync_control::show_sync_fail_task_list_info(const string & sync_fail_task_list_file_path) //显示同步失败任务列表信息
{
    static int temp_num = 0;
    vector<string> values_ss_temp = get_sync_fail_task_list_info(sync_fail_task_list_file_path);
    show_sync_fail_task_list_info_son(values_ss_temp);

    int num = shell_tables.get_display_line_num();
    string empty_temp_string;
    empty_temp_string = format_string_right_fill(empty_temp_string, (unsigned int)134, ' ');
    if(temp_num != 0)
    {
        WNH_DISPLAY_STYLE_MOVEUP(temp_num + 2);
        cout << empty_temp_string << endl;
        for(int i = 0; i < temp_num - num ; i++)
        {
            //打印32为空白符
            cout << empty_temp_string << endl;
        }
    }
    if(num > temp_num )
    {
        temp_num = num;
    }

    WNH_DISPLAY_STYLE_HIDE_CURSOR();
    shell_tables.show_tables();
    shell_tables.clear();
    WNH_DISPLAY_STYLE_SHOW_CURSOR_S();

    return true;
}

bool wnh_filesync_control::show_sync_fail_task_list_info_son(const vector<string> & values_ss_temp) //显示同步失败任务列表信息
{
    vector<string> values;
    vector<WNH_SHELL_TABLES_FONT_STYLE> color;
    vector<WNH_SHELL_TABLES_ALIGN_MODE> align;
    vector<unsigned int> values_width;
    vector<bool> separator_format;

    string str_temp;
    str_temp = str_temp + PROGRAM_NAME + " 同步失败任务列表信息显示";
    set_vector_values(true, values, str_temp);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDMAGENTA);
    set_vector_values(true, values_width, 132);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, values, "客户端IP", "动作", "源路径", "目标路径", "失败时间");
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN);
    set_vector_values(true, values_width, 15, 10, 42, 42, 19);
    shell_tables.add_unit(values, color, values_width);

    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDGREEN, WNH_SHELL_TABLES_FONT_STYLE::BOLDCYAN, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::BOLDBLUE);
    //set_vector_values(true, separator_format, true, true, true, true, true);
    for(unsigned int i = 0; i < (values_ss_temp.size() - 1) / 5; i ++)
    {
        WNHDEBUG("client_ip=" << values_ss_temp[i * 5 + 0] << ", event_id=" << values_ss_temp[i * 5 + 1] << ", src_path" << values_ss_temp[i * 5 + 2] << ", dst_path=" << values_ss_temp[i * 5 + 3] << ", update_date=" << values_ss_temp[i * 5 + 4]);
        set_vector_values(true, values, values_ss_temp[i * 5 + 0], values_ss_temp[i * 5 + 1], values_ss_temp[i * 5 + 2], values_ss_temp[i * 5 + 3], values_ss_temp[i * 5 + 4]);
        shell_tables.add_unit(values, color, values_width);
        //shell_tables.set_unit(shell_tables.line_num - 1, separator_format);
    }
    string local_page_num = to_string((fail_task_list_info_page/SYNC_FAIL_TASK_LIST_INFO_LINE_NUM) + 1);
    unsigned long tatal_page_num_temp = stoul(values_ss_temp[values_ss_temp.size()-1], 0 , 10) % SYNC_FAIL_TASK_LIST_INFO_LINE_NUM;
    if(tatal_page_num_temp == 0)
    {
        tatal_page_num_temp = stoul(values_ss_temp[values_ss_temp.size()-1], 0 , 10) / SYNC_FAIL_TASK_LIST_INFO_LINE_NUM;
    }
    else
    {
        tatal_page_num_temp = stoul(values_ss_temp[values_ss_temp.size()-1], 0 , 10) / SYNC_FAIL_TASK_LIST_INFO_LINE_NUM + 1;
    }
    string total_page_num;
    total_page_num = total_page_num + "共" + to_string(tatal_page_num_temp) + "页, " + values_ss_temp[values_ss_temp.size()-1] + "条记录";
    set_vector_values(true, values, "当前页数:", local_page_num, total_page_num,"按向上键或者W键, 查看上一页,按向下键或者S键, 查看下一页, 按其他键退出");
    set_vector_values(true, values_width, 10, 4, 24, 91);
    set_vector_values(true, color, WNH_SHELL_TABLES_FONT_STYLE::RESET, WNH_SHELL_TABLES_FONT_STYLE::BOLDRED, WNH_SHELL_TABLES_FONT_STYLE::RESET, WNH_SHELL_TABLES_FONT_STYLE::RESET);
    set_vector_values(true, align, WNH_SHELL_TABLES_ALIGN_MODE::right, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::left, WNH_SHELL_TABLES_ALIGN_MODE::right);
    shell_tables.add_unit(values, color, align, values_width);
    set_vector_values(true, separator_format, false, false, false, true);
    shell_tables.set_unit(shell_tables.line_num - 1, separator_format);
    return true;
}
