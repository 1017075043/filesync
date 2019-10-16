#include "wnh_license.h"

string wnh_license::get_sysntem_core_info() //获取linux操作系统内核信息
{
    struct utsname uts;
    if(uname(&uts) >= 0) {
        //            char sysname[_UTSNAME_SYSNAME_LENGTH];
        //            char nodename[_UTSNAME_NODENAME_LENGTH];
        //            char release[_UTSNAME_RELEASE_LENGTH];
        //            char version[_UTSNAME_VERSION_LENGTH];
        //            char machine[_UTSNAME_MACHINE_LENGTH];
        //printf("The version is %s\n", uts.release);
        WNHINFO("sysname=" << uts.sysname);
        WNHINFO("nodename=" << uts.nodename);
        WNHINFO("release=" << uts.release);
        WNHINFO("version=" << uts.version);
        WNHINFO("machine=" << uts.machine);
    }
    return "";
}
