//------------------------------------------------------------------------------------------------------------------
//获取CPUID：
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <string>
#include <fstream>
#include <cpuid.h>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>

static bool get_cpu_id_by_asm(std::string & cpu_id)
{
    cpu_id.clear();

    unsigned int s1 = 0;
    unsigned int s2 = 0;
    asm volatile
            (
                "movl $0x01, %%eax; \n\t"
                "xorl %%edx, %%edx; \n\t"
                "cpuid; \n\t"
                "movl %%edx, %0; \n\t"
                "movl %%eax, %1; \n\t"
                : "=m"(s1), "=m"(s2)
                );

    if (0 == s1 && 0 == s2)
    {
        return(false);
    }

    char cpu[32] = { 0 };
    snprintf(cpu, sizeof(cpu), "%08X%08X", htonl(s2), htonl(s1));
    std::string(cpu).swap(cpu_id);

    return(true);
}

static void parse_cpu_id(const char * file_name, const char * match_words, std::string & cpu_id)
{
    cpu_id.c_str();

    std::ifstream ifs(file_name, std::ios::binary);
    if (!ifs.is_open())
    {
        return;
    }

    char line[4096] = { 0 };
    while (!ifs.eof())
    {
        ifs.getline(line, sizeof(line));
        if (!ifs.good())
        {
            break;
        }

        const char * cpu = strstr(line, match_words);
        if (NULL == cpu)
        {
            continue;
        }
        cpu += strlen(match_words);

        while ('\0' != cpu[0])
        {
            if (' ' != cpu[0])
            {
                cpu_id.push_back(cpu[0]);
            }
            ++cpu;
        }

        if (!cpu_id.empty())
        {
            break;
        }
    }

    ifs.close();
}

static bool get_cpu_id_by_system(std::string & cpu_id)
{
    cpu_id.c_str();

    const char * dmidecode_result = ".dmidecode_result.txt";
    char command[512] = { 0 };
    snprintf(command, sizeof(command), "dmidecode -t 4 | grep ID > %s", dmidecode_result);

    if (0 == system(command))
    {
        parse_cpu_id(dmidecode_result, "ID:", cpu_id);
    }

    unlink(dmidecode_result);

    return(!cpu_id.empty());
}

static bool get_cpu_id(std::string & cpu_id)
{
    if (get_cpu_id_by_asm(cpu_id))
    {
        return(true);
    }
    if (0 == getuid())
    {
        if (get_cpu_id_by_system(cpu_id))
        {
            return(true);
        }
    }
    return(false);
}

static void test_1()
{
    std::string cpu_id;
    if (get_cpu_id(cpu_id))
    {
        printf("cpu_id: [%s]\n", cpu_id.c_str());
    }
    else
    {
        printf("can not get cpu id\n");
    }
}

static void test_2()
{
    {
        std::string cpu_id;
        if (get_cpu_id_by_asm(cpu_id))
        {
            printf("cpu_id_by_asm: [%s]\n", cpu_id.c_str());
        }
        else
        {
            printf("can not get cpu id\n");
        }
    }
    {
        std::string cpu_id;
        if (get_cpu_id_by_system(cpu_id))
        {
            printf("cpu_id_by_sys: [%s]\n", cpu_id.c_str());
        }
        else
        {
            printf("can not get cpu id\n");
        }
    }
}

int main(int argc, char* argv[])
{
    test_1();
    test_2();
    return(0);
}

//获取网卡名称以及网卡MAC地址
//#include <stdio.h>
//#include <sys/ioctl.h>
//#include <net/if.h>
//#include <string.h>
//void getmac();
//int main()
//{
//    getmac();
//    return 0;
//}
//
//void getmac()
//{
//#define MAXINTERFACES 16
//    int fd, interface;
//    struct ifreq buf[MAXINTERFACES];
//    struct ifconf ifc;
//    char mac[32] = {0};
//
//    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
//    {
//        int i = 0;
//        ifc.ifc_len = sizeof(buf);
//        ifc.ifc_buf = (caddr_t)buf;
//        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
//        {
//            interface = ifc.ifc_len / sizeof(struct ifreq);
//            printf("interface num is %d\n", interface);
//            while (i < interface)
//            {
//                printf("net device %s\n", buf[i].ifr_name);
//                if (!(ioctl(fd, SIOCGIFHWADDR, (char *)&buf[i])))
//                {
//                    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
//                            (unsigned char)buf[i].ifr_hwaddr.sa_data[0],
//                            (unsigned char)buf[i].ifr_hwaddr.sa_data[1],
//                            (unsigned char)buf[i].ifr_hwaddr.sa_data[2],
//                            (unsigned char)buf[i].ifr_hwaddr.sa_data[3],
//                            (unsigned char)buf[i].ifr_hwaddr.sa_data[4],
//                            (unsigned char)buf[i].ifr_hwaddr.sa_data[5]);
//                    printf("HWaddr %s\n", mac);
//                }
//                printf("\n");
//                i++;
//            }
//        }
//    }
//}
