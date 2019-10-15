#include "wnh_license.h"

wnh_license::wnh_license()
{
    WNHINFO("wnh_license");
}

wnh_license::~wnh_license()
{
    WNHINFO("~wnh_license");
}

string wnh_license::get_interfaces_info() //获取网卡信息
{
    int fd, interface;
    struct ifreq buf[MAX_INTERFACES_NUM];
    struct ifconf ifc;
    char mac[32] = {0};

    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
        int i = 0;
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
        {
            interface = ifc.ifc_len / sizeof(struct ifreq);
            printf("interface num is %d\n", interface);
            while (i < interface)
            {
                printf("net device %s\n", buf[i].ifr_name);
                if (!(ioctl(fd, SIOCGIFHWADDR, (char *)&buf[i])))
                {
                    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[0],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[1],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[2],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[3],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[4],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[5]);
                    printf("HWaddr %s\n", mac);
                }
                printf("\n");
                i++;
            }
        }
    }
    return mac;
}


string wnh_license::get_cpu_id_by_asm() //获取cpu信息
{

    string cpu_id;

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
        return cpu_id;
    }

    char cpu[32] = { 0 };
    snprintf(cpu, sizeof(cpu), "%08X%08X", htonl(s2), htonl(s1));
    std::string(cpu).swap(cpu_id);
    cout << "cpu:" << cpu << ", cpu_id:" << cpu_id << endl;

    return cpu_id;
}

