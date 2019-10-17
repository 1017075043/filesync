#include "filesync.h"

void filesync::create_license_mode() //许可创建模式
{
    wnh_license license;
    string license_file = license.create_license_file(server_serial_number, validity_time);
    WNHINFO("许可文件生成成功:" << license_file);
}
