#include "wnh_openssl.h"

#define ngx_hash(key, c) ((u_int) key * 31 + c)
unsigned int wnh_openssl::ngx_hash_key(const string& data)//nginx中使用的simpleHash算法
{
    size_t len = data.size();
    unsigned int  i, key;
    key = 0;
    for (i = 0; i < len; i++)
    {
        key = ngx_hash(key, data[i]);
    }
    WNHDEBUG("获取字符串:" << data << ",hash:" << key);
    return key;
}

unsigned int wnh_openssl::pub_inthash(const char *str) //经典字符串Hash函数
{
    register unsigned int h;
    register unsigned char *p;
    for(h=0, p = (unsigned char *)str; *p ; p++)
    {
        h = 31 * h + *p;
    }
    WNHDEBUG("获取字符串:" << str << ",hash:" << h);
    return h;
}

unsigned long wnh_openssl::php_longhashpjw(const char* str) //PHP中出现的字符串Hash函数
{
    unsigned long h = 0, g;
    char *p;
    for(h=0, p = (char *)str; *p ; p++)
    {
        h = (h << 4) + *p++;
        if ((g = (h & 0xF0000000)))
        {
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }
    WNHDEBUG("获取字符串:" << str << ",hash:" << h);
    return h;
}

unsigned int wnh_openssl::OpenSSL_strhash1(const char *str) //OpenSSL中出现的字符串Hash函数
{
    int i,l;
    unsigned int ret=0;
    unsigned short *s;

    if (str == nullptr) return(0);
    l=(strlen(str)+1)/2;
    s=(unsigned short *)str;
    for (i=0; i <l; ++i)
    {
        ret^=(s[i]<<(i&0x0f));
    }
    WNHDEBUG("获取字符串:" << str << ",hash:" << ret);
    return ret;
}

unsigned int wnh_openssl::mysql_hashnr1(const char *key,unsigned int length) //MySql中出现的字符串Hash函数
{
    register unsigned int nr=1, nr2=4;
    while (length--)
    {
        nr^= (((nr & 63)+nr2)*((unsigned int) (unsigned char) *key++))+ (nr << 8);
        nr2+=3;
    }
    WNHDEBUG("获取字符串:" << key << ",hash:" << nr);
    return((unsigned int) nr);
}

unsigned int wnh_openssl::mysql_hashnr_caseup1(const char *key,unsigned int length) //MySql中出现的字符串Hash函数
{
    register unsigned int nr=1, nr2=4;
    while (length--)
    {
        nr^= (((nr & 63)+nr2)*((unsigned int) (unsigned char) toupper(*key++)))+ (nr << 8);
        nr2+=3;
    }
    WNHDEBUG("获取字符串:" << key << ",hash:" << nr);
    return((unsigned int) nr);
}

unsigned int wnh_openssl::mysql_hashnr2(const char *key, unsigned int len) //MySql中出现的字符串Hash函数
{
    const char *end=key+len;
    unsigned int hash;
    for (hash= 0; key < end; key++)
    {
        hash*= 16777619;
        hash^= (unsigned int) *(unsigned char*) key;
    }
    WNHDEBUG("获取字符串:" << key << ",hash:" << hash);
    return hash;
}

unsigned int wnh_openssl::mysql_hashnr_caseup2(const char *key, unsigned int len) //MySql中出现的字符串Hash函数
{
    const char *end=key+len;
    unsigned int hash;
    for (hash= 0; key < end; key++)
    {
        hash*= 16777619;
        hash^= (unsigned int) (unsigned char) toupper(*key);
    }
    WNHDEBUG("获取字符串:" << key << ",hash:" << hash);
    return hash;
}

int wnh_openssl::additiveHash(const string& key, int prime) //加法hash
{
    unsigned int hash, i;
    for (hash = key.size(), i = 0; i < key.size(); i++)
    {
        hash += key[i];
    }
    WNHDEBUG("获取字符串:" << key << ",hash:" << hash % prime);
    return (hash % prime);
}

int wnh_openssl::rotatingHash(const string& key, int prime) //旋转hash
{
    unsigned int hash, i;
    for (hash=key.size(), i=0; i<key.size(); ++i)
    {
        hash = (hash<<4)^(hash>>28)^key[i];
    }
    WNHDEBUG("获取字符串:" << key << ",hash:" << hash % prime);
    return (hash % prime);
}

int wnh_openssl::oneByOneHash(const string& key) //一次一个hash
{
    unsigned int hash, i;
    for (hash=0, i=0; i<key.size(); ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    WNHDEBUG("获取字符串:" << key << ",hash:" << hash);
    return hash;
}

int wnh_openssl::bernstein(const string& key) //Bernstein's hash
{
    unsigned int hash = 0;
    unsigned int i;
    for (i=0; i<key.size(); ++i)
    {
        hash = 33*hash + key[i];
    }
    WNHDEBUG("获取字符串:" << key << ",hash:" << hash);
    return hash;
}

unsigned int wnh_openssl::RSHash(const string& str) //RS算法hash
{
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;

    for(unsigned int i = 0; i < str.size(); i++)
    {
        hash = hash * a + str[i];
        a    = a * b;
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (hash & 0x7FFFFFFF));
    return (hash & 0x7FFFFFFF);
}

int wnh_openssl::JSHash(const string& str) //JS算法
{
    int hash = 1315423911;

    for(unsigned int i = 0; i < str.size(); i++)
    {
        hash ^= ((hash << 5) + str[i] + (hash >> 2));
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (hash & 0x7FFFFFFF));
    return (hash & 0x7FFFFFFF);
}

int wnh_openssl::PJWHash(const string& str) //PJW算法
{
    int BitsInUnsignedInt = 32;
    int ThreeQuarters     = (BitsInUnsignedInt * 3) / 4;
    int OneEighth         = BitsInUnsignedInt / 8;
    int HighBits          = 0xFFFFFFFF << (BitsInUnsignedInt - OneEighth);
    int hash              = 0;
    int test              = 0;

    for(unsigned int i = 0; i < str.size(); i++)
    {
        hash = (hash << OneEighth) + str[i];

        if((test = hash & HighBits) != 0)
        {
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (hash & 0x7FFFFFFF));
    return (hash & 0x7FFFFFFF);
}

int wnh_openssl::ELFHash(const string& str) //ELF算法
{
    int hash = 0;
    int x    = 0;

    for(unsigned int i = 0; i < str.size(); i++)
    {
        hash = (hash << 4) + str[i];
        if((x = (int)(hash & 0xF0000000L)) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (hash & 0x7FFFFFFF));
    return (hash & 0x7FFFFFFF);
}

uint32_t wnh_openssl::BKDRHash32(const string& str)
{
    uint32_t seed = 131; // 31 131 1313 13131 131313 etc..
    uint32_t hash = 0;
    for(unsigned int i = 0; i < str.size(); ++i)
    {
        hash = (hash * seed) + str[i];
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (uint32_t)hash);
    return (uint32_t)hash;
}

uint64_t wnh_openssl::BKDRHash64(const string& str)
{
    uint64_t seed = 131; // 31 131 1313 13131 131313 etc..
    uint64_t hash = 0;
    for(unsigned int i = 0; i < str.size(); ++i)
    {
        hash = (hash * seed) + str[i];
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (uint64_t)hash);
    return (uint64_t)hash;
}

int wnh_openssl::SDBMHash(const string& str) //SDBM算法
{
    int hash = 0;

    for(unsigned int i = 0; i < str.size(); i++)
    {
        hash = str[i] + (hash << 6) + (hash << 16) - hash;
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (hash & 0x7FFFFFFF));
    return (hash & 0x7FFFFFFF);
}

unsigned int wnh_openssl::DJBHash(const string& str) //DJB算法
{
    unsigned int hash = 5381;

    for(unsigned int i = 0; i < str.size(); i++)
    {
        hash = ((hash << 5) + hash) + str[i];
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (hash & 0x7FFFFFFF));
    return (hash & 0x7FFFFFFF);
}

int wnh_openssl::DEKHash(const string& str) //DEK算法
{
    int hash = str.size();

    for(unsigned int i = 0; i < str.size(); i++)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << (hash & 0x7FFFFFFF));
    return (hash & 0x7FFFFFFF);
}

int wnh_openssl::APHash(const string& str) //AP算法
{
    int hash = 0;

    for(unsigned int i = 0; i < str.size(); i++)
    {
        hash ^= ((i & 1) == 0) ? ( (hash << 7) ^ str[i] ^ (hash >> 3)) :
                                 (~((hash << 11) ^ str[i] ^ (hash >> 5)));
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << hash);
    return hash;
}

int wnh_openssl::java(const string& str) //JAVA自己带的算法
{
    int h = 0;
    int off = 0;
    unsigned int len = str.size();
    for (unsigned int i = 0; i < len; i++)
    {
        h = 31 * h + str[off++];
    }

    WNHDEBUG("获取字符串:" << str << ",hash:" << h);
    return h;
}
