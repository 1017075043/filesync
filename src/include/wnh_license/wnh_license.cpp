#include "wnh_license.h"
#include "wnh_license_cpu_info.cpp"
#include "wnh_license_interfaces_info.cpp"
#include "wnh_license_system_core.cpp"
#include "wnh_license_uuid.cpp"
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
    wnh_openssl des;
    string server_serial_file = server_serial_number + LICENSE_FILE_SUFFIX;
    string license_info = server_serial_number + "," + to_string(LOCALTIMENUM + validity_time * 24 * 60 * 60) + "," + to_string(validity_time) + "," + DES_ENCRYPTION_INTERFERENCE_VALUE;
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
        WNHWARN("尊敬的用户, 您好! 若您还没有获取到许可文件, 发送您的产品序列号:" << license_num << "至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        return (unsigned long)0;
    }
    stringstream license_info_temp;
    license_info_temp << file_read.rdbuf();
    file_read.close();
    string license_info(license_info_temp.str());
    string license = des.des_decrypt(license_info, DES_SYMMETRIC_ENCRYPTION_KEY);
    string server_serial_number = license.substr(0, license.find(","));
    if(license_num != server_serial_number)
    {
        WNHWARN(license_file << "该许可无效");
        WNHWARN("尊敬的用户, 您好! 您当前的产品许可为无效的许可, 发送您的产品序列号:" << license_num << "至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        return (unsigned long)0;
    }

    license = license.substr(license.find(",")+1);
    string effectiveness_time = license.substr(0, license.find(","));
    license = license.substr(license.find(",")+1);
    unsigned long remaining_effectiveness_time = stoul(effectiveness_time, 0, 10);

    unsigned long effectiveness_time_temp = stoul(license.substr(0, license.find(",")+1), 0, 10);
    remaining_effectiveness_time > LOCALTIMENUM ? remaining_effectiveness_time = remaining_effectiveness_time - LOCALTIMENUM : remaining_effectiveness_time = 0;

    remaining_effectiveness_time > 24 * 60 * 60 ? remaining_effectiveness_time = remaining_effectiveness_time / (24 * 60 * 60) + 1 : remaining_effectiveness_time == 0 ? remaining_effectiveness_time = 0 : remaining_effectiveness_time = 1;
    if(remaining_effectiveness_time == 0)
    {
        WNHINFO("许可文件：" << license_file << ", 产品序列号:" << license_num << ", 产品有效期:" << effectiveness_time_temp << "天, 产品剩余有效期:" << remaining_effectiveness_time << "天");
        WNHWARN("尊敬的用户,您好! 您当前的产品许可已经过期, 发送您的产品序列号:" << license_num << "至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
    }
    else
    {
        WNHINFO("许可文件：" << license_file << ", 产品序列号:" << license_num << ", 产品有效期:" << effectiveness_time_temp << "天, 产品剩余有效期:" << remaining_effectiveness_time << "天");
        if(remaining_effectiveness_time < 7)
        {
            WNHWARN("尊敬的用户, 您好! 您当前的产品许可即将过期, 发送您的产品序列号:" << license_num << "至邮箱" << APPLY_LICENSE_EMAIL << ", 即可获取新的许可");
        }
    }
    return remaining_effectiveness_time;
}
