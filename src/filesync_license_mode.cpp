#include "filesync.h"

void filesync::license_mode()
{
    wnh_license license;
    if(server_serial_number != "" && validity_time != 0)
    {
        string license_file = license.create_license_file(server_serial_number, validity_time);
        WNHINFO("许可文件生成成功:" << license_file);
    }
    else if(license_file != "")
    {
        //WNHINFO("查看许可文件: " << license_file);
        license.check_license_file_effectiveness(license_file);
    }
}
