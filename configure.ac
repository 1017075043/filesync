#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
# AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_INIT(filesync,1.0,[])
AM_INIT_AUTOMAKE(filesync,1.0)

AC_CONFIG_SRCDIR([src/filesync.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h])

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
