AM_CXXFLAGS=-g -Wall -std=c++11 -O3

noinst_LTLIBRARIES = lib_wnh_jwsmtp.la
noinst_HEADERS = jwsmtp.h mailer.h compat.h base64.h
lib_wnh_jwsmtp_la_SOURCES = mailer.cpp compat.cpp base64.cpp
lib_wnh_jwsmtp_la_CPPFLAGS = -DSOMPLE_LOGS
lib_wnh_jwsmtp_la_LIBADD = @LDFLAGS@
