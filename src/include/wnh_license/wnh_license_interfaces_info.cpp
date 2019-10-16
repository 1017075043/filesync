#include "wnh_license.h"

string wnh_license::get_interfaces_info() //获取网卡信息
{
    int fd, interface;
    struct ifreq buf[MAX_INTERFACES_NUM];
    struct ifconf ifc;
    char mac[32] = {0};
    string interfaces_info;
    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
        int i = 0;
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
        {
            interface = ifc.ifc_len / sizeof(struct ifreq);
            interfaces_info = interfaces_info + "interface_num=" + to_string(interface) + "\n";
            //printf("interface num is %d\n", interface);
            while (i < interface)
            {
                //printf("net device %s\n", buf[i].ifr_name);
                interfaces_info = interfaces_info + "interface_device_name=" + buf[i].ifr_name + "\n";
                if (!(ioctl(fd, SIOCGIFHWADDR, (char *)&buf[i])))
                {
                    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[0],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[1],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[2],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[3],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[4],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[5]);
                    interfaces_info = interfaces_info + "interface_mac=" + mac + "\n";
                    //printf("HWaddr %s\n", mac);
                }
                //printf("\n");
                i++;
            }
        }
    }
    WNHDEBUG("interfaces_info=" << interfaces_info);
    return interfaces_info;
}
