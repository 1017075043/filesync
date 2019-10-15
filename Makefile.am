# autoscan && aclocal && libtoolize && autoconf && autoheader && automake --add-missing

AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = filesync

AM_CXXFLAGS=-g -Wall -std=c++11 -O3

filesync_LDFLAGS = -lcrypto -lsqlite3

SUBDIRS = src/include/wnh_base_class \
src/include/wnh_config \
src/include/wnh_filesync_init \
src/include/wnh_check_string \
src/include/wnh_config_ini \
src/include/wnh_filesync_client \
src/include/wnh_filesync_server \
src/include/wnh_filesync_control \
src/include/wnh_tcp_client \
src/include/wnh_tcp_server \
src/include/wnh_inotify_use_sqlite \
src/include/wnh_sqlite \
src/include/wnh_hash \
src/include/wnh_system_operation \
src/include/wnh_int_double_string_one_list \
src/include/wnh_int_string_one_list \
src/include/wnh_unsigned_long_string_one_list \
src/include/wnh_string_one_list \
src/include/wnh_string_rule_one_list \
src/include/wnh_string_string_one_list \
src/include/wnh_config_ini \
src/include/wnh_jwsmtp \
src/include/wnh_license

filesync_SOURCES = src/filesync.cpp

filesynct_CPPFLAGS = -DCONFIG_DIR=\"$(sysconfdir)\" -DLIBRARY_DIR=\"$(pkglibdir)\"

noinst_HEADERS = src/filesync.h

filesync_LDADD = src/include/wnh_base_class/lib_wnh_base_class.la \
src/include/wnh_config/lib_wnh_config.la \
src/include/wnh_filesync_init/lib_wnh_filesync_init.la \
src/include/wnh_check_string/lib_wnh_check_string.la \
src/include/wnh_filesync_client/lib_wnh_filesync_client.la \
src/include/wnh_filesync_server/lib_wnh_filesync_server.la \
src/include/wnh_filesync_control/lib_wnh_filesync_control.la \
src/include/wnh_tcp_client/lib_wnh_tcp_client.la \
src/include/wnh_tcp_server/lib_wnh_tcp_server.la \
src/include/wnh_inotify_use_sqlite/lib_wnh_inotify_use_sqlite.la \
src/include/wnh_sqlite/lib_wnh_sqlite.la \
src/include/wnh_hash/lib_wnh_hash.la \
src/include/wnh_system_operation/lib_wnh_system_operation.la \
src/include/wnh_int_double_string_one_list/lib_wnh_int_double_string_one_list.la \
src/include/wnh_int_string_one_list/lib_wnh_int_string_one_list.la \
src/include/wnh_unsigned_long_string_one_list/lib_wnh_unsigned_long_string_one_list.la \
src/include/wnh_string_one_list/lib_wnh_string_one_list.la \
src/include/wnh_string_rule_one_list/lib_wnh_string_rule_one_list.la \
src/include/wnh_string_string_one_list/lib_wnh_string_string_one_list.la \
src/include/wnh_config_ini/lib_wnh_config_ini.la \
src/include/wnh_jwsmtp/lib_wnh_jwsmtp.la \
src/include/wnh_license/lib_wnh_license.la
