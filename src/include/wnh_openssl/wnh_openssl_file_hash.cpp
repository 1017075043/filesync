#include "wnh_openssl.h"

string wnh_openssl::get_file_md5(const string &file_name) //使用openssl的md5函数生成文件md5
{
    string md5_value;
    ifstream file(file_name.c_str(), ifstream::binary);
    if (!file)
    {
        WNHERROR("打开文件失败, errno=" << errno << ", mesg=" << strerror(errno));
        return "";
    }

    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    char buf[1024 * 16];
    while (file.good())
    {
        file.read(buf, sizeof(buf));
        MD5_Update(&md5Context, buf, file.gcount());
    }

    unsigned char result[MD5_DIGEST_LENGTH];
    MD5_Final(result, &md5Context);

    char hex[35];
    memset(hex, 0, sizeof(hex));
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        sprintf(hex + i * 2, "%02x", result[i]);
    }
    hex[32] = '\0';
    md5_value = string(hex);

    WNHDEBUG("获取" << file_name << "文件md5值成功,md5_value:" << md5_value);
    return md5_value;
}

bool wnh_openssl::get_file_md5(const string &file_name, string &md5_value) //使用openssl的md5函数生成文件md5
{
    md5_value.clear();

    ifstream file(file_name.c_str(), ifstream::binary);
    if (!file)
    {
        WNHERROR("打开文件失败, errno=" << errno << ", mesg=" << strerror(errno));
        return false;
    }

    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    char buf[1024 * 16];
    while (file.good())
    {
        file.read(buf, sizeof(buf));
        MD5_Update(&md5Context, buf, file.gcount());
    }

    unsigned char result[MD5_DIGEST_LENGTH];
    MD5_Final(result, &md5Context);

    char hex[35];
    memset(hex, 0, sizeof(hex));
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        sprintf(hex + i * 2, "%02x", result[i]);
    }
    hex[32] = '\0';
    md5_value = string(hex);

    WNHDEBUG("获取" << file_name << "文件md5值成功,md5_value:" << md5_value);
    return true;
}
