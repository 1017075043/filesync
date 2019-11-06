#include "wnh_filesync_server.h"

unsigned long wnh_filesync_server::get_license_info() //获取许可信息
{
    license_remaining_effectiveness_time = license.check_license_file_effectiveness(license_file);
    //WNHINFO("license_remaining_effectiveness_time=" << license_remaining_effectiveness_time);
    return license_remaining_effectiveness_time;
}
