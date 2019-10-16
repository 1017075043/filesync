#ifndef __wnh_openssl__
#define __wnh_openssl__

using namespace std;

//使用openssl需要先安装libssl-dev centos下使用命令:yum install -y openssl openssl-devel
//并且需要在编译和链接的时候加上动态链接库 -lcrypto
//例如:
//编译:$(CC) -o $@ -lstdc+ -lcrypto -c $< $(CFLAGS)
//链接:$(CC) -o $(EXEC) $(OBJS) $(LIB) -lcrypto
//在ubantu系统下,会由于缺少libcrypto.so.10 这个动态链接库导致程序无法启动，需要将目录中的libcrypto.so.10放至/usr/lib/x86_64-linux-gnu/目录下


#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/des.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#include "../wnh_base_class/wnh_base_class.h"

class wnh_openssl : public wnh_base_class
{
public:
    wnh_openssl();
    ~wnh_openssl();

    const int M_MASK = 0x8765fed1; //MASK值，随便找一个值，最好是质数
    const int M_SHIFT = 0;//32位FNV算法

    string get_file_md5(const string &file_name); //使用openssl的md5函数生成文件md5
    bool get_file_md5(const string &file_name, string &md5_value); //使用openssl的md5函数生成文件md5
    unsigned int ngx_hash_key(const string& data);//nginx中使用的simpleHash算法
    unsigned int pub_inthash(const char *str);//经典字符串Hash函数
    unsigned long php_longhashpjw(const char* str);//PHP中出现的字符串Hash函数
    unsigned int OpenSSL_strhash1(const char *str);//OpenSSL中出现的字符串Hash函数
    unsigned int mysql_hashnr1(const char *key,unsigned int length);//MySql中出现的字符串Hash函数
    unsigned int mysql_hashnr_caseup1(const char *key,unsigned int length);//MySql中出现的字符串Hash函数
    unsigned int mysql_hashnr2(const char *key, unsigned int len);//MySql中出现的字符串Hash函数
    unsigned int mysql_hashnr_caseup2(const char *key, unsigned int len);//MySql中出现的字符串Hash函数
    int additiveHash(const string& key, int prime);//加法hash
    int rotatingHash(const string& key, int prime);//旋转hash
    int oneByOneHash(const string& key);//一次一个hash
    int bernstein(const string& key);//Bernstein's hash
    unsigned int RSHash(const string& str);//RS算法hash
    int JSHash(const string& str);//JS算法
    int PJWHash(const string& str);//PJW算法
    int ELFHash(const string& str);//ELF算法
    uint64_t BKDRHash64(const string& str);//BKDR算法
    uint32_t BKDRHash32(const string& str);//BKDR算法
    int SDBMHash(const string& str);//SDBM算法
    unsigned int DJBHash(const string& str);//DJB算法
    int DEKHash(const string& str);//DEK算法
    int APHash(const string& str);//AP算法
    int java(const string& str);//JAVA自己带的算法

    string des_encrypt(const string &clearText, const string &key); // 加密 ecb模式, des对称加解密
    string des_decrypt(const string &cipherText, const string &key); // 解密 ecb模式, des对称加解密
};
#endif
