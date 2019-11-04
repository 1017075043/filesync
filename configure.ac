#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# autoconf版本
AC_PREREQ([2.63])

# 初始化包信息，将会自动生成PACKAGE_NAME、PACKAGE_VERSION、PACKAGE_BUGREPORT宏
# AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_INIT(filesync,1.0,[filesync_maintail@163.com])

AM_INIT_AUTOMAKE(filesync,1.0)

# 通过检测目录中必定存在的文件来判断目录是否存在
AC_CONFIG_SRCDIR([src/filesync.cpp])

# 生成config.h文件保存configure.ac定义的宏，此文件可被源文件包含
AC_CONFIG_HEADERS([config.h])

# 初始化automake
AM_INIT_AUTOMAKE([subdir-objects -Wno-portability])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([vector iostream fstream string.h thread errno.h stdio.h stdlib.h fcntl.h sys/types.h unistd.h sys/wait.h signal.h sys/stat.h sstream mutex list time.h string sys/inotify.h algorithm sys/socket.h netdb.h netinet/in.h arpa/inet.h sys/ioctl.h net/if.h cstdio cstring cstdlib cpuid.h map sys/utsname.h uuid/uuid.h cassert openssl/md5.h openssl/sha.h openssl/des.h openssl/rsa.h openssl/pem.h sqlite3.h dirent.h pwd.h grp.h assert.h iterator future sys/select.h set functional])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([bzero inet_ntoa memset select socket strerror strtoull])

AC_OUTPUT(Makefile
src/include/wnh_base_class/Makefile
src/include/wnh_filesync_init/Makefile
src/include/wnh_inotify_use_sqlite/Makefile
src/include/wnh_int_double_string_one_list/Makefile
src/include/wnh_int_string_one_list/Makefile
src/include/wnh_unsigned_long_string_one_list/Makefile
src/include/wnh_sqlite/Makefile
src/include/wnh_string_one_list/Makefile
src/include/wnh_string_rule_one_list/Makefile
src/include/wnh_string_string_one_list/Makefile
src/include/wnh_system_operation/Makefile
src/include/wnh_tcp_client/Makefile
src/include/wnh_tcp_server/Makefile
src/include/wnh_check_string/Makefile
src/include/wnh_openssl/Makefile
src/include/wnh_filesync_client_concurrent/Makefile
src/include/wnh_filesync_client/Makefile
src/include/wnh_filesync_server/Makefile
src/include/wnh_filesync_control/Makefile
src/include/wnh_config_ini/Makefile
src/include/wnh_config/Makefile
src/include/wnh_jwsmtp/Makefile
src/include/wnh_license/Makefile)
