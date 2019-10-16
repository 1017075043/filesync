#include "wnh_license.h"

string wnh_license::get_server_serial_number() //获取服务器序列号
{
    string interfase_info = get_interfaces_info();
    string system_core_info = get_sysntem_core_info();
    string uuid_temp = get_uuid();
    string uuid;
    uuid = uuid_temp.substr(9, 4) + uuid_temp.substr(14, 4) + uuid_temp.substr(24);
    ofstream file_open;
    file_open.open(SERVER_SERIAL_NUMBER_TEMP_FILE, ios::out | ios::trunc);
    if(!file_open.is_open())
    {
        WNHERROR("打开文件" << SERVER_SERIAL_NUMBER_TEMP_FILE <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
        return "";
    }
    file_open << interfase_info << endl;
    file_open << system_core_info << endl;
    file_open << uuid << endl;
    file_open.close();
    wnh_openssl hash;
    string server_serial_number = hash.get_file_md5(SERVER_SERIAL_NUMBER_TEMP_FILE);
    if(unlink(SERVER_SERIAL_NUMBER_TEMP_FILE) != 0)
    {
        WNHWARN("临时文件," << SERVER_SERIAL_NUMBER_TEMP_FILE << ", 删除失败, errno=" << errno << ", mesg=" << strerror(errno));
    }
    WNHINFO("服务器序列号: " << server_serial_number);
    //string license_file = create_license_file(server_serial_number, 10);
    //check_license_file_effectiveness(server_serial_number + LICENSE_FILE_SUFFIX);
    //string jia_mi_des_encrypt = hash.des_encrypt(server_serial_number, DES_SYMMETRIC_ENCRYPTION_KEY);
    //string jie_mi_des_encrypt = hash.des_decrypt(jia_mi_des_encrypt, DES_SYMMETRIC_ENCRYPTION_KEY);
    ////ofstream file_open;
    //file_open.open(SERVER_SERIAL_NUMBER_TEMP_FILE, ios::out | ios::trunc);
    //if(!file_open.is_open())
    //{
    //    WNHERROR("打开文件" << SERVER_SERIAL_NUMBER_TEMP_FILE <<  "失败, errno=" << errno << ", mesg=" << strerror(errno));
    //    return "";
    //}
    //file_open << jia_mi_des_encrypt;
    //file_open.close();
    //ifstream t(SERVER_SERIAL_NUMBER_TEMP_FILE);
    //stringstream buffer;
    //buffer << t.rdbuf();
    //string contents(buffer.str());
    //string jie_mi_des_encrypt_1 = hash.des_decrypt(contents, DES_SYMMETRIC_ENCRYPTION_KEY);
    //WNHINFO("jia_mi_des_encrypt: " << jia_mi_des_encrypt);
    //WNHINFO("jie_mi_des_encrypt: " << jie_mi_des_encrypt);
    //WNHINFO("jie_mi_des_encrypt_1: " << jie_mi_des_encrypt_1);

    return server_serial_number;
}
