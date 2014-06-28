AM_CXXFLAGS = -g -I$(top_srcdir)/src -I/src/threadsyncocl -std=c++0x @AM_CXXFLAGS@

TEST = test_fs

check_PROGRAMS = test_fs

test_fs_SOURCES = test_fs.cpp \
environment_test.hpp

test_fs_LDADD = -L/home/chatsiri/workspacecpp/pthread_sync_ocl/src/threadsyncocl \
 -lthreadsyncocl -lgtest -lgtest_main -L/home/chatsiri/workspacecpp/pthread_sync_ocl/src/filestructure \
 -lfilestructure -L/home/chatsiri/workspacecpp/pthread_sync_ocl/src/utils -lutils \
 -L/home/chatsiri/workspacecpp/pthread_sync_ocl/src/exception -lexception $(AM_LDFLAGS)
