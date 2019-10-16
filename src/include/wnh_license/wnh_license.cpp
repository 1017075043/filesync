#include "wnh_license.h"
#include "wnh_license_cpu_info.cpp"
#include "wnh_license_interfaces_info.cpp"
#include "wnh_license_system_core.cpp"
#include "wnh_license_uuid.cpp"
#include "wnh_license_server_serial_number.cpp"

wnh_license::wnh_license()
{
    WNHDEBUG("wnh_license 构造");
}

wnh_license::~wnh_license()
{
    WNHDEBUG("~wnh_license 析构");
}
