#include "wnh_filesync_server.h"

bool wnh_filesync_server::email_client_offline_alert_info(const vector<string> & offline_client_ip, const vector<string> & begin_connect_time, const vector<string> & last_connect_time, const vector<string> & complete_task_num, const vector<string> & unfinished_task_num, const vector<string> & fail_task_num) //邮件发送告警信息
{
    WNHINFO("开始发送客户端离线告警信息");
    for(unsigned int i = 0; i < offline_client_ip.size(); i++)
    {
        WNHINFO("离线客户端端IP:" << offline_client_ip[i] << ", 启动时间:" << begin_connect_time[i] << ", 离线时间:" << last_connect_time[i] << ", 已完成任务数:" << complete_task_num[i] << ", 未完成任务数" << unfinished_task_num[i] << ", 失败任务数" << fail_task_num[i]);
    }
    string subject; // 主题
    subject = subject + "[" + PROGRAM_NAME + " alter] [client offline:";
    for(unsigned int i = 0; i < offline_client_ip.size() && i < 6; i++)
    {
        subject = subject + offline_client_ip[i] + ",";
    }
    if(offline_client_ip.size() >= 6)
    {
        subject = subject + "...";
    }
    else
    {
        subject = subject.substr(0, subject.length()-1);
    }
    subject = subject + "]";

    jwsmtp::mailer email(""/*接收者*/, email_info.sender_email_address.c_str()/*发送者*/, subject.c_str()/*主题*/,
                         ""/*内容*/, email_info.email_server_address.c_str()/*邮件服务器地址*/,
                         jwsmtp::mailer::SMTP_PORT, false);

    //添加多个接收者
    string recipient_email_address_temp = "";
    for(unsigned int i = 0; i < email_info.recipient_email_address.size(); i++)
    {
        recipient_email_address_temp = recipient_email_address_temp + email_info.recipient_email_address[i] + ", ";
        email.addrecipient(email_info.recipient_email_address[i].c_str());
    }

    //添加HTML的发送内容，它会替换构造函数中的“这里填写邮件内容”
    string html_file = create_email_client_offline_content_html(offline_client_ip, begin_connect_time, last_connect_time, complete_task_num, unfinished_task_num, fail_task_num);
    email.setmessageHTML(html_file);
    // 添加多个附件
    email.attach(conf_path);
    //m.attach("autoscan.log");

    //经过测试，163/126支持的auth认证是PLAIN模式
    email.authtype(jwsmtp::mailer::PLAIN);

    //这里输入认证用户名，注意哦，需要是***@163.com的用户名
    email.username(email_info.email_server_user.c_str());

    //这里输入密码
    email.password(email_info.email_server_password.c_str());

    WNHINFO("客户端离线告警邮件:邮件主题:" << subject);
    WNHINFO("客户端离线告警邮件:发件人邮箱地址:" << email_info.sender_email_address);
    WNHINFO("客户端离线告警邮件:收件人邮箱地址:" << recipient_email_address_temp);
    WNHINFO("客户端离线告警邮件:邮件服务器地址:" << email_info.email_server_address);
    WNHINFO("客户端离线告警邮件:邮件服务器登录帐户:" << email_info.email_server_user);
    WNHINFO("客户端离线告警邮件:邮件服务器登录帐户密码:" << email_info.email_server_password);
    WNHINFO("客户端离线告警邮件:邮件内容:" << html_file);

    email.send(); // 这里发送邮件，需要注意的是，这里是同步模式哦！

    //std ::cout << email.response() << std::endl;//这里如果展示的是250，代表发送邮件成功

    string email_result = email.response();
    if(email_result.substr(0, 3) == "250")
    {
        WNHINFO(email_result << ", 邮件发送成功");
    }
    else
    {
        WNHWARN(email_result << ", 邮件发送失败");
    }

    return true;
}

string wnh_filesync_server::create_email_client_offline_content_html(const vector<string> & offline_client_ip, const vector<string> & begin_connect_time, const vector<string> & last_connect_time, const vector<string> & complete_task_num, const vector<string> & unfinished_task_num, const vector<string> & fail_task_num) //创建邮件告警信息内容
{
#define CONTENT(...) email_client_offline_content = email_client_offline_content + __VA_ARGS__ + "\n";
    char timestring[20] = "";
    time_t t = 0;
    string email_client_offline_content = "";
    CONTENT("<!DOCTYPE html>");
    CONTENT("<html lang=\"zh-CN\">");
    CONTENT("<head>");
    CONTENT("<meta charset=\"utf-8\" />");
    CONTENT("<title>" + PROGRAM_NAME + "</title>");

    CONTENT("<style type=\"text/css\">");
    CONTENT("table { border-collapse:collapse; margin:0 auto; text-align:center; }");
    CONTENT("table td,table th { border:1px solid #cad9ea; color:#666; height:30px; }");
    CONTENT("table thead th { background-color:#CCE8EB; width:100px; }");
    CONTENT("table tr:nth-child(odd) { background:#fff; }");
    CONTENT("table tr:nth-child(even) { background:#F5FAFA; }");
    CONTENT("</style>");

    CONTENT("</head>");
    CONTENT("<body>");
    //CONTENT("<p>Dear user, hello</p>");
    CONTENT("<table width=\"90%\">");
    CONTENT("<caption>");
    CONTENT("<h2>offline client info</h2>");
    CONTENT("</caption>");
    CONTENT("<thead>");
    CONTENT("<tr>");
    CONTENT("<th>offline client ip</th>");
    CONTENT("<th>begin connect time</th>");
    CONTENT("<th>last connect time</th>");
    CONTENT("<th>complete task num</th>");
    CONTENT("<th>unfinished task num</th>");
    CONTENT("<th>fail task num</th>");
    CONTENT("</tr>");
    CONTENT("</thead>");
    for(unsigned int i = 0; i < offline_client_ip.size(); i++)
    {
        CONTENT("<tr>");
        CONTENT("<td>" + offline_client_ip[i] + "</td>");
        t = (time_t)stoul(begin_connect_time[i], 0, 10);
        strftime(timestring, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
        CONTENT("<td>" + timestring + "</td>");

        t = (time_t)stoul(last_connect_time[i], 0, 10);
        strftime(timestring, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&t));
        CONTENT("<td>" + timestring + "</td>");

        CONTENT("<td>" + complete_task_num[i] + "</td>");
        CONTENT("<td>" + unfinished_task_num[i] + "</td>");
        CONTENT("<td>" + fail_task_num[i] + "</td>");
        CONTENT("</tr>");
    }
    CONTENT("</table>");
    //CONTENT("<br>");
    //CONTENT("<br>");
    //CONTENT("<br>");
    //CONTENT("<br>");
    //CONTENT("<br>");
    //CONTENT("<p width=\"90%\" style=\"color:red;text-align=center;\">" + WNH_FILESYNC_USE_HELP + "</p>");
    //CONTENT("<p width=\"90%\" style=\"color:red;text-align=center;\">" + WNH_FILESYNC_COPYRIGHT + "</p>");

    CONTENT("</table>");
    CONTENT("</body>");
    CONTENT("</html>");
    return email_client_offline_content;
}

