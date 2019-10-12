#ifndef __wnh_tcp_server__
#define __wnh_tcp_server__

using namespace std;

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "unistd.h"
#include "errno.h"
#include <arpa/inet.h> //for inet_ntoa
#include <set>
#include <functional>

#include "../wnh_define/wnh_tcp_define.h"
#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_system_operation/wnh_system_operation.h"

class wnh_tcp_server : public wnh_base_class
{
protected:
    struct session_node{ //记录一个会话的信息
        thread *session; //会话
        int nfp; //临时的会话句柄数
        string client_ip; //客户端IP
        int client_port; //使用的临时端口
        unsigned long start_time; //创建时间
        unsigned long last_update_time; //最后一次更新时间
        bool status; //使用状态
    };

protected:
    int socket_num; //socket句柄数
    struct sockaddr_in server_address; //服务器地址信息
    socklen_t sin_size; //服务器地址信息使用大小
    unsigned short portnum; //服务器将要监听的端口号
    int tcp_listen_conturrent_now_num; //当前创建的会话线程数量
    session_node session_info[TCP_LISTEN_CONCURRENT_MAX_NUM]; //会话的信息数组
    bool survival_id; //存活标志
    int display_transfer_logs; //是否显示数据传输过程日志

protected:
    bool accept_start_send_file_info(const int nfp, const string info); //接收开始发送文件信息
    bool accept_end_send_file_info(const int nfp, const string info); //接收结束发送文件信息

    bool accept_start_send_file_content_info(const int nfp, const string info); //接收开始发送文件内容信息
    bool accept_end_send_file_content_info(const int nfp, const string info); //接收结束发送文件内容信息

    bool accept_file_size_info(const int nfp, const string info, long long & file_size); //接收文件大小信息
    bool accept_file_name_info(const int nfp, const string info, string & name); //接收文件名字信息

public:
    wnh_tcp_server();
    wnh_tcp_server(bool inherit);
    ~wnh_tcp_server();

    bool create_socket(); //创建一个socket,返回句柄数
    void set_server_address(int portnum); //设置服务器地址信息
    bool server_bind(); //将进程与端口进行绑定
    bool server_listen(int concurrent_num); //开始监听端口
    int server_accept(); //等待客户端的连接

    bool send_info(const int nfp, const string info); //发出一条信息
    bool send_info(const int nfp,const char info[TCP_INFO_SZIE]); //发出一条信息
    bool send_info(const int nfp, const string info, const int size); //发出一条信息
    bool send_info(const int nfp,const char info[TCP_INFO_SZIE], const int size); //发出一条信息

    bool accept_info(const int nfp, string & info); //接收一条信息
    bool accept_info(const int nfp, char * & info); //接收一条信息
    bool accept_info(const int nfp, string & info, int & size); //接收一条信息
    bool accept_info(const int nfp, char * & info, int & size); //接收一条信息

    bool accept_start_session_info(const int nfp, const string info); //接收开始会话信息
    bool accept_end_session_info(const int nfp, const string info); //接收结束会话信息

    bool accept_file_content(const int nfp, const string info, const string file_name); //接收一个文件内容
    bool accept_file_content(const int nfp, const string info, const string file_name, const long long & file_size); //接收一个文件内容
    bool accept_file_content_v1(const int nfp, const string info, const string file_name, const long long & file_size); //接收一个文件内容

    int accept_file(const int nfp, const string info); //接收一个文件

    bool creat_session_pthread(const int nfp); //创建会话线程
    bool build_session(const int nfp); //建立一个会话
    bool close_session(const int nfp, const bool status); //关闭一个会话

    bool add_session(thread *session, const int nfp); //将一个会话添加进入会话记录列表
    bool sub_session(const int nfp); //将一个会话从会话记录列表中删除
    bool update_session_last_update_time(const int nfp); //更新一个会话的最后连接时间
    bool manage_session_pthread(); //管理会话线程

    bool add_tcp_listen_conturrent_now_num(); //当前创建的会话线程数量+1,使用互斥
    bool dec_tcp_listen_conturrent_now_num(); //当前创建的会话线程数量-1,使用互斥

    int accept_apply_downinfo_file_info(const int nfp, const string info); //接收请求文件下载信息
    bool accept_apply_downinfo_file_name_info(const int nfp, const string info, string & file_name); //接收请求文件下载的文件名字信息

    bool reply_downinfo_file_size_info(const int nfp, const string file_name, unsigned long & file_size); //回复请求文件下载文件大小
    bool send_reply_downinfo_file_error_stop_info(const int nfp); //发送回复下载文件错误停止信息
    bool send_reply_downinfo_file_szie_info(const int nfp, const unsigned long file_size); //发送回复下载文件大小信息
    bool send_reply_downinfo_file_complete_info(const int nfp); //发送回复下载文件完成信息
    bool send_reply_downinfo_file_content(const int nfp, const string file_name, const unsigned long file_size); //接收请求文件下载的文件内容信息
    bool send_reply_downinfo_file_content_start(const int nfp); //发送回复下载文件开始发送文件信息
    bool send_reply_downinfo_file_content_stop(const int nfp); //发送回复下载文件结束发送文件信息
    bool accept_downinfo_file_content_result(const int nfp); //接收下载文件成功接收一行文件内容信息结果
    int test();
};

#endif
