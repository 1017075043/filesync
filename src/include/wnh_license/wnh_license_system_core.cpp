#include "wnh_license.h"

string wnh_license::get_sysntem_core_info() //获取linux操作系统内核信息
{
    string sysntem_core_info;
    struct utsname uts;
    if(uname(&uts) >= 0) {
        //            char sysname[_UTSNAME_SYSNAME_LENGTH];
        //            char nodename[_UTSNAME_NODENAME_LENGTH];
        //            char release[_UTSNAME_RELEASE_LENGTH];
        //            char version[_UTSNAME_VERSION_LENGTH];
        //            char machine[_UTSNAME_MACHINE_LENGTH];
        //printf("The version is %s\n", uts.release);
        sysntem_core_info = sysntem_core_info + "sysname=" + uts.sysname + "\n";
        sysntem_core_info = sysntem_core_info + "nodename=" + uts.nodename + "\n";
        sysntem_core_info = sysntem_core_info + "release=" + uts.release + "\n";
        sysntem_core_info = sysntem_core_info + "version=" + uts.version + "\n";
        sysntem_core_info = sysntem_core_info + "machine=" + uts.machine + "\n";
        WNHDEBUG("sysntem_core_info=" << sysntem_core_info);
    }
    return sysntem_core_info;
}
