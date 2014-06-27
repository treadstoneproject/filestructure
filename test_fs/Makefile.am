AM_CXXFLAGS = -g -I$(top_srcdir)/src -I/src/threadsyncocl -std=c++0x @AM_CXXFLAGS@

TEST = test_suite

check_PROGRAMS = test_suite

test_suite_SOURCES = test_fs.cpp \
environment_test.hpp

test_suite_LDADD = -L/home/chatsiri/workspacecpp/pthread_sync_ocl/src/threadsyncocl \
 -lthreadsyncocl -lgtest -lgtest_mai -L/home/chatsiri/workspacecpp/pthread_sync_ocl/src/filestructure \
 -lfilestructure $(AM_LDFLAGS)
