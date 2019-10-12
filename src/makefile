#set your own environment option
CC=g++
CC_FLAG= -g -Wall -std=c++11 -O3

#set your inc and lib
INC=-lstdc+ -lcrypto
LIB=-pthread -lcrypto `mysql_config --cflags --libs` -lsqlite3

CFLAGS=

SRCS=filesync.cpp\
include/wnh_tcp_client/wnh_tcp_client.cpp\
include/wnh_tcp_server/wnh_tcp_server.cpp\
include/wnh_sqlite/wnh_sqlite.cpp\
include/wnh_inotify_use_sqlite/wnh_inotify_use_sqlite.cpp\
include/wnh_inotify_use_sqlite/wnh_inotify_use_sqlite_sql.cpp\
include/wnh_filesync_init/wnh_filesync_init.cpp\
include/wnh_inotify_use_mysql/wnh_inotify_use_mysql.cpp\
include/wnh_inotify_use_mysql/wnh_inotify_use_mysql_sql.cpp\
include/wnh_base_class/wnh_base_class.cpp\
include/wnh_string_one_list/wnh_string_one_list.cpp\
include/wnh_int_string_one_list/wnh_int_string_one_list.cpp\
include/wnh_string_string_one_list/wnh_string_string_one_list.cpp\
include/wnh_string_rule_one_list/wnh_string_rule_one_list.cpp\
include/wnh_system_operation/wnh_system_operation.cpp\
include/wnh_inotify/wnh_inotify.cpp\
include/wnh_config/wnh_config.cpp\
include/wnh_inotify_ex/wnh_inotify_ex.cpp\
include/wnh_int_double_string_one_list/wnh_int_double_string_one_list.cpp\
include/wnh_mysql/wnh_mysql.cpp\
include/wnh_check_string/wnh_check_string.cpp\
include/wnh_hash/wnh_hash.cpp\
include/wnh_config_ini/wnh_config_ini.cpp\
include/wnh_filesync_client/wnh_filesync_client.cpp\
include/wnh_filesync_server/wnh_filesync_server.cpp\

OBJS=$(SRCS:.cpp=.o)

EXEC=filesync

.cpp.o:
$(CC) $(CC_FLAG) -o $@ $(INC) -c $< $(CFLAGS)

start: $(OBJS)
$(CC) $(CC_FLAG) -o $(EXEC) $(OBJS) $(LIB)

clean:
rm -rf $(OBJS)

install:
rm -rf $(OBJS)
./$(EXEC) filesync.conf
