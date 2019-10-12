#ifndef __wnh_hash__
#define __wnh_hash__

using namespace std;

//使用openssl需要先安装libssl-dev centos下使用命令:yum install -y openssl openssl-devel
//并且需要在编译和链接的时候加上动态链接库 -lcrypto
//例如:
//编译:$(CC) -o $@ -lstdc+ -lcrypto -c $< $(CFLAGS)
//链接:$(CC) -o $(EXEC) $(OBJS) $(LIB) -lcrypto


#include <openssl/md5.h>

#include "../wnh_base_class/wnh_base_class.h"

class wnh_hash : public wnh_base_class
{
public:
    wnh_hash();
    ~wnh_hash();

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
};
#endif
