#ifndef __wnh_tcp_client__
#define __wnh_tcp_client__

using namespace std;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <future>
#include <cstring>
#include <netdb.h>
#include <sys/select.h>


#include "../wnh_define/wnh_tcp_define.h"
#include "../wnh_base_class/wnh_base_class.h"
#include "../wnh_system_operation/wnh_system_operation.h"

class wnh_tcp_client : public wnh_base_class
{
protected:
    int socket_num; //socket句柄数
    struct sockaddr_in teraccept_address; //服务器地址信息
    string ip; //服务器IP地址
    unsigned short portnum;  //服务器端口
    int display_transfer_logs; //是否显示数据传输过程日志

protected:
    bool cheack_seesion_info_read(); //检查会话信息读取情况
    bool cheack_seesion_info_read(const int & nfp); //检查会话信息读取情况

    bool send_start_send_file_info(); //发送开始发送文件信息
    bool send_end_send_file_info(); //发送结束发送文件信息

    bool send_start_send_file_content_info(); //发送开始发送文件内容信息
    bool send_end_send_file_content_info(); //发送结束发送文件内容信息

    bool accept_send_file_content_result(); //接收发送文件内容结果
    bool send_file_size_info(unsigned long file_size); //发送文件大小信息
    bool send_file_name_info(const string name); //发送文件名称信息

    bool send_file_content(const string file_name); //发送一个文件的内容
    bool send_file_content(const string file_name, const unsigned long & file_size); //发送一个文件的内容
    bool send_file_content_v1(const string file_name, const unsigned long & file_size); //发送一个文件的内容

public:
    wnh_tcp_client();
    ~wnh_tcp_client();

    int set_non_blocking(int fd);
    bool create_socket(); //创建一个socket,返回句柄数
    void set_teraccept_address(string ip, int portnum); //设置目标服务器的地址信息
    bool unblock_connect(int time); //非阻塞的连接
    bool unblock_connect(const string & ip, const string & port); //非阻塞的连接
    bool block_connect(); //阻塞的连接

    string is_port_open(const string & domain, const string & port); //检查端口是否在监听
    bool is_listening(const string & ip, const string & port); //检查端口是否在监听

    bool send_info(const string info); //发出一条信息
    bool send_info(const char info[TCP_INFO_SZIE]); //发出一条信息
    bool send_info(const string info, const int size); //发出一条信息
    bool send_info(const char info[TCP_INFO_SZIE], const int size); //发出一条信息

    bool accept_info(string & info); //接收一条信息
    bool accept_info(char * & info); //接收一条信息
    bool accept_info(string & info, int & size); //接收一条信息
    bool accept_info(char * & info, int & size); //接收一条信息

    bool send_end_session_info(); //发送结束信息
    bool send_start_session_info(); //发送开始会话信息

    bool send_file(const string name); //发送一个文件

    bool download_file(const string file_name, const string temp_file_name); //下载文件
    bool send_apply_download_file_info(const string name); //发送请求文件下载信息
    bool accept_download_file_error_stop_info(const string info); //接收下载文件错误结束信息
    bool accept_download_file_size_info(const string info, unsigned long & file_size); //接收下载文件大小信息
    bool accept_download_file_complete_info(const string info); //接收下载文件完成信息

    bool accept_download_file_content_info(const string file_name, const unsigned long & file_size, const string & temp_file_name); //接收下载文件内容信息
    bool accept_download_file_content_start_info(const string info); //接收开始下载文件内容信息
    bool accept_download_file_content_stop_info(const string info); //接收结束下载文件内容信息


    int test();
    int test(const string & ip);
};

#endif
