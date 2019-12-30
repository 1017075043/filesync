#include "wnh_license.h"
#include "wnh_license_cpu_info.cpp"
#include "wnh_license_interfaces_info.cpp"
#include "wnh_license_system_core.cpp"
#include "wnh_license_server_serial_number.cpp"

wnh_license::wnh_license()
{
    WNHDEBUG("wnh_license 构造");
}

wnh_license::~wnh_license()
{
    WNHDEBUG("~wnh_license 析构");
}

string wnh_license::create_license_file(const string & server_serial_number,const unsigned long & validity_time) //创建许可文件
{
    string server_serial_number_temp = server_serial_number;
    string server_serial_file = server_serial_number_temp + LICENSE_FILE_SUFFIX;
    wnh_openssl des;
    if(server_serial_number_temp == GENERIC_LICENSE_SERIAL_NUMBER_GENERATES_SECRET_KEY)
    {
        server_serial_file = "";
        server_serial_file = server_serial_file + GENERAL_LICENSE_FILE_NAME + LICENSE_FILE_SUFFIX;
        server_serial_number_temp = GENERAL_LICENSE_SERIAL_NUMBER;
    }
    string license_info = server_serial_number_temp + "," + to_string(LOCALTIMENUM + validity_time * 24 * 60 * 60) + "," + to_string(validity_time) + "," + DES_ENCRYPTION_INTERFERENCE_VALUE;
    string des_encrypt_info = des.des_encrypt(license_info, DES_SYMMETRIC_ENCRYPTION_KEY);
    ofstream file_open;
    file_open.open(server_serial_file, ios::out | ios::trunc);
    if(!file_open.is_open())
    {
        WNHERROR("打开文件" << server_serial_file <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
        return "";
    }
    file_open << des_encrypt_info;
    file_open.close();
    WNHINFO("license文件生产成功: " << server_serial_file);
    return server_serial_file;
}

unsigned long wnh_license::check_license_file_effectiveness(const string & license_file) //检查许可的有效性
{
    wnh_openssl des;
    ifstream file_read(license_file);
    string license_num = get_server_serial_number();
    if(!file_read.is_open())
    {
        WNHWARN(license_file << ", 许可文件不存在");
        WNHWARN("尊敬的用户, 您好! 若您还没有获取到许可文件, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        return (unsigned long)0;
    }
    stringstream license_info_temp;
    license_info_temp << file_read.rdbuf();
    file_read.close();
    string license_info(license_info_temp.str());
    string license = des.des_decrypt(license_info, DES_SYMMETRIC_ENCRYPTION_KEY);
    string server_serial_number = license.substr(0, license.find(","));
    WNHINFO("获取到许可号: " << server_serial_number);
    if(license_num != server_serial_number && server_serial_number != GENERAL_LICENSE_SERIAL_NUMBER)
    {
        WNHWARN(license_file << "该许可无效");
        WNHWARN("尊敬的用户, 您好! 您当前的产品许可为无效的许可, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        return (unsigned long)0;
    }
    license = license.substr(license.find(",")+1);
    string end_effectiveness_time = license.substr(0, license.find(","));
    license = license.substr(license.find(",")+1);
    string all_effectiveness_time = license.substr(0, license.find(","));

    time_t end_effectiveness_time_long = stoul(end_effectiveness_time, 0, 10);
    end_effectiveness_time_long = end_effectiveness_time_long - 8 * 60 * 60; //使用strftime格式化的时候,总是会多出8个小时

    char end_effectiveness_time_str[LOCALTIMELENGTH];
    strftime(end_effectiveness_time_str, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&end_effectiveness_time_long));

    time_t all_effectiveness_time_long = stoul(all_effectiveness_time, 0, 10);

    time_t begin_effectiveness_time_long = end_effectiveness_time_long - (all_effectiveness_time_long * 24 * 60 * 60);
    char begin_effectiveness_time_str[LOCALTIMELENGTH];

    strftime(begin_effectiveness_time_str, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&begin_effectiveness_time_long));
    unsigned long remaining_effectiveness_time = (unsigned long)end_effectiveness_time_long + (8 * 60 * 60) > LOCALTIMENUM ? (end_effectiveness_time_long + (8 * 60 * 60) - LOCALTIMENUM) / (24 * 60 * 60) : 0;

    //WNHINFO("许可开始时间: " << begin_effectiveness_time_str);
    //WNHINFO("许可结束时间: " << end_effectiveness_time_str);
    //WNHINFO("许可有效期: " << all_effectiveness_time << "天");
    //WNHINFO("许可剩余期: " << remaining_effectiveness_time << "天");

    WNHINFO("许可文件：" << license_file << ", 产品序列号:" << license_num << ", 许可开始时间: " << begin_effectiveness_time_str << ", 许可结束时间: " << end_effectiveness_time_str << ", 许可有效期: " << all_effectiveness_time << "天, 许可剩余期: " << remaining_effectiveness_time << "天");
    if(remaining_effectiveness_time == 0)
    {
        WNHWARN("尊敬的用户,您好! 您当前的产品许可已经过期, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
    }
    else if(remaining_effectiveness_time < 7)
    {
        WNHWARN("尊敬的用户, 您好! 您当前的产品许可即将过期, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
    }
    return remaining_effectiveness_time;
}

bool wnh_license::get_license_file_effectiveness(const string & license_file, string & begin_time, string & end_time, unsigned long & all_time, unsigned long & remaining_time, string & serial_number) //获取许可的信息
{
    wnh_openssl des;
    ifstream file_read(license_file);
    string license_num = get_server_serial_number();
    if(!file_read.is_open())
    {
        WNHWARN(license_file << ", 许可文件不存在");
        //WNHWARN("尊敬的用户, 您好! 若您还没有获取到许可文件, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        return false;
    }
    stringstream license_info_temp;
    license_info_temp << file_read.rdbuf();
    file_read.close();
    string license_info(license_info_temp.str());
    string license = des.des_decrypt(license_info, DES_SYMMETRIC_ENCRYPTION_KEY);
    string server_serial_number = license.substr(0, license.find(","));
    WNHINFO("获取到许可号: " << server_serial_number);
    if(license_num != server_serial_number && server_serial_number != GENERAL_LICENSE_SERIAL_NUMBER)
    {
        WNHWARN(license_file << "该许可无效");
        //WNHWARN("尊敬的用户, 您好! 您当前的产品许可为无效的许可, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        return false;
    }
    license = license.substr(license.find(",")+1);
    string end_effectiveness_time = license.substr(0, license.find(","));
    license = license.substr(license.find(",")+1);
    string all_effectiveness_time = license.substr(0, license.find(","));

    time_t end_effectiveness_time_long = stoul(end_effectiveness_time, 0, 10);
    end_effectiveness_time_long = end_effectiveness_time_long - 8 * 60 * 60; //使用strftime格式化的时候,总是会多出8个小时

    char end_effectiveness_time_str[LOCALTIMELENGTH];
    strftime(end_effectiveness_time_str, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&end_effectiveness_time_long));

    time_t all_effectiveness_time_long = stoul(all_effectiveness_time, 0, 10);

    time_t begin_effectiveness_time_long = end_effectiveness_time_long - (all_effectiveness_time_long * 24 * 60 * 60);
    char begin_effectiveness_time_str[LOCALTIMELENGTH];

    strftime(begin_effectiveness_time_str, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&begin_effectiveness_time_long));
    unsigned long remaining_effectiveness_time = (unsigned long)end_effectiveness_time_long + (8 * 60 * 60) > LOCALTIMENUM ? (end_effectiveness_time_long + (8 * 60 * 60) - LOCALTIMENUM) / (24 * 60 * 60) : 0;

    //WNHINFO("许可开始时间: " << begin_effectiveness_time_str);
    //WNHINFO("许可结束时间: " << end_effectiveness_time_str);
    //WNHINFO("许可有效期: " << all_effectiveness_time << "天");
    //WNHINFO("许可剩余期: " << remaining_effectiveness_time << "天");

    WNHINFO("许可文件：" << license_file << ", 产品序列号:" << license_num << ", 许可开始时间: " << begin_effectiveness_time_str << ", 许可结束时间: " << end_effectiveness_time_str << ", 许可有效期: " << all_effectiveness_time << "天, 许可剩余期: " << remaining_effectiveness_time << "天");

    begin_time = begin_effectiveness_time_str;
    end_time = end_effectiveness_time_str;
    all_time = all_effectiveness_time_long;
    remaining_time = remaining_effectiveness_time;
    serial_number = license_num;

    //if(remaining_effectiveness_time == 0)
    //{
    //    WNHWARN("尊敬的用户,您好! 您当前的产品许可已经过期, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
    //}
    //else if(remaining_effectiveness_time < 7)
    //{
    //    WNHWARN("尊敬的用户, 您好! 您当前的产品许可即将过期, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
    //}
    return true;
}

bool wnh_license::get_license_file_effectiveness(const string & license_file, string & begin_time, string & end_time, unsigned long & all_time, unsigned long & remaining_time) //获取许可的信息
{
    wnh_openssl des;
    ifstream file_read(license_file);
    string license_num = get_server_serial_number();
    if(!file_read.is_open())
    {
        WNHWARN(license_file << ", 许可文件不存在");
        //WNHWARN("尊敬的用户, 您好! 若您还没有获取到许可文件, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        return false;
    }
    stringstream license_info_temp;
    license_info_temp << file_read.rdbuf();
    file_read.close();
    string license_info(license_info_temp.str());
    string license = des.des_decrypt(license_info, DES_SYMMETRIC_ENCRYPTION_KEY);
    string server_serial_number = license.substr(0, license.find(","));
    WNHINFO("获取到许可号: " << server_serial_number);
    if(license_num != server_serial_number && server_serial_number != GENERAL_LICENSE_SERIAL_NUMBER)
    {
        WNHWARN(license_file << "该许可无效");
        //WNHWARN("尊敬的用户, 您好! 您当前的产品许可为无效的许可, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        return false;
    }
    license = license.substr(license.find(",")+1);
    string end_effectiveness_time = license.substr(0, license.find(","));
    license = license.substr(license.find(",")+1);
    string all_effectiveness_time = license.substr(0, license.find(","));

    time_t end_effectiveness_time_long = stoul(end_effectiveness_time, 0, 10);
    end_effectiveness_time_long = end_effectiveness_time_long - 8 * 60 * 60; //使用strftime格式化的时候,总是会多出8个小时

    char end_effectiveness_time_str[LOCALTIMELENGTH];
    strftime(end_effectiveness_time_str, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&end_effectiveness_time_long));

    time_t all_effectiveness_time_long = stoul(all_effectiveness_time, 0, 10);

    time_t begin_effectiveness_time_long = end_effectiveness_time_long - (all_effectiveness_time_long * 24 * 60 * 60);
    char begin_effectiveness_time_str[LOCALTIMELENGTH];

    strftime(begin_effectiveness_time_str, LOCALTIMELENGTH, TIMEDISPLAYFORMAT, localtime(&begin_effectiveness_time_long));
    unsigned long remaining_effectiveness_time = (unsigned long)end_effectiveness_time_long + (8 * 60 * 60) > LOCALTIMENUM ? (end_effectiveness_time_long + (8 * 60 * 60) - LOCALTIMENUM) / (24 * 60 * 60) : 0;

    //WNHINFO("许可开始时间: " << begin_effectiveness_time_str);
    //WNHINFO("许可结束时间: " << end_effectiveness_time_str);
    //WNHINFO("许可有效期: " << all_effectiveness_time << "天");
    //WNHINFO("许可剩余期: " << remaining_effectiveness_time << "天");

    WNHINFO("许可文件：" << license_file << ", 产品序列号:" << license_num << ", 许可开始时间: " << begin_effectiveness_time_str << ", 许可结束时间: " << end_effectiveness_time_str << ", 许可有效期: " << all_effectiveness_time << "天, 许可剩余期: " << remaining_effectiveness_time << "天");

    begin_time = begin_effectiveness_time_str;
    end_time = end_effectiveness_time_str;
    all_time = all_effectiveness_time_long;
    remaining_time = remaining_effectiveness_time;

    //if(remaining_effectiveness_time == 0)
    //{
    //    WNHWARN("尊敬的用户,您好! 您当前的产品许可已经过期, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
    //}
    //else if(remaining_effectiveness_time < 7)
    //{
    //    WNHWARN("尊敬的用户, 您好! 您当前的产品许可即将过期, 发送您的产品序列号: " << license_num << " 至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
    //}
    return true;
}
