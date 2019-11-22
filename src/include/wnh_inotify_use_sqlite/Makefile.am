AM_CXXFLAGS=-g -Wall -std=c++11 -O3

noinst_LTLIBRARIES = lib_wnh_inotify_use_sqlite.la
noinst_HEADERS = wnh_inotify_use_sqlite.h
lib_wnh_inotify_use_sqlite_la_SOURCES = wnh_inotify_use_sqlite.cpp wnh_inotify_use_sqlite_sql.cpp
lib_wnh_inotify_use_sqlite_la_CPPFLAGS = -DSOMPLE_LOGS -DDEBUG_MODE_LOGS
lib_wnh_inotify_use_sqlite_la_LIBADD = @LDFLAGS@
