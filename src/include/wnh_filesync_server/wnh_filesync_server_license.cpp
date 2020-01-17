#include "wnh_filesync_server.h"

unsigned long wnh_filesync_server::get_license_info() //获取许可信息
{
    //get_license_file_effectiveness(const string & license_file, string & begin_time, string & end_time, unsigned long & all_time, unsigned long & remaining_time) //获取许可的信息
    //license_remaining_effectiveness_time = license.check_license_file_effectiveness(lic.file_path);
    license.get_license_file_effectiveness(lic.file_path, lic.begin_time, lic.end_time, lic.all_time, lic.remaining_time, lic.serial_number);
    WNHINFO("lic.file_path:" << lic.file_path << ", lic.begin_time:" << lic.begin_time << ", lic.end_time:" << lic.end_time << ", lic.all_time" << lic.all_time << ", lic.remaining_time:" << lic.remaining_time << "天, lic.serial_number:" <<  lic.serial_number);
    //WNHINFO("license_remaining_effectiveness_time=" << license_remaining_effectiveness_time);
    return lic.remaining_time;
}
