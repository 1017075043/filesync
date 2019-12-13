#set your own environment option
CC=g++
CC_FLAG= -g -Wall -std=c++11 -O3

#set your inc and lib
INC=-lstdc+ -lcrypto
LIB=-pthread -lcrypto -lsqlite3 -luuid

#CFLAGS=-DSOMPLE_LOGS -DDEBUG_MODE_LOGS
CFLAGS=-DDEBUG_MODE_LOGS

SRCS=include/wnh_base_class/wnh_base_class.cpp \
include/wnh_filesync_init/wnh_filesync_init.cpp \
include/wnh_check_string/wnh_check_string.cpp \
include/wnh_filesync_client_concurrent/wnh_filesync_client_concurrent.cpp \
include/wnh_filesync_client/wnh_filesync_client.cpp \
include/wnh_filesync_server/wnh_filesync_server.cpp \
include/wnh_filesync_control/wnh_filesync_control.cpp \
include/wnh_tcp_client/wnh_tcp_client.cpp \
include/wnh_tcp_server/wnh_tcp_server.cpp \
include/wnh_inotify_use_sqlite/wnh_inotify_use_sqlite.cpp \
include/wnh_inotify_use_sqlite/wnh_inotify_use_sqlite_sql.cpp \
include/wnh_sqlite/wnh_sqlite.cpp \
include/wnh_openssl/wnh_openssl.cpp \
include/wnh_system_operation/wnh_system_operation.cpp \
include/wnh_int_double_string_one_list/wnh_int_double_string_one_list.cpp \
include/wnh_int_string_one_list/wnh_int_string_one_list.cpp \
include/wnh_unsigned_long_string_one_list/wnh_unsigned_long_string_one_list.cpp \
include/wnh_string_one_list/wnh_string_one_list.cpp \
include/wnh_string_rule_one_list/wnh_string_rule_one_list.cpp \
include/wnh_string_string_one_list/wnh_string_string_one_list.cpp \
include/wnh_config_ini/wnh_config_ini.cpp \
include/wnh_config/wnh_config.cpp \
include/wnh_jwsmtp/mailer.cpp \
include/wnh_jwsmtp/compat.cpp \
include/wnh_jwsmtp/base64.cpp \
include/wnh_license/wnh_license.cpp \
include/wnh_shell_tables/wnh_shell_tables.cpp \
filesync.cpp

OBJS=$(SRCS:.cpp=.o)

EXEC=filesync

.cpp.o:
	$(CC) $(CC_FLAG) -o $@ $(INC) -c $< $(CFLAGS)

start: $(OBJS)
	$(CC) $(CC_FLAG) -o $(EXEC) $(OBJS) $(LIB)

clean:
	rm -rf $(OBJS)

install:
	./$(EXEC) filesync.conf
