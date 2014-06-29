# debug, optimized
AM_CXXFLAGS   = -I$(top_srcdir)/src/ -std=c++0x @AM_CXXFLAGS@

# Make src file 
# libarries for read and handle file structure.
lib_LIBRARIES = libfilestructure.a

#@install header to system
libfilestructure_adir = $(includedir)/filestructure

#Header
libfilestructure_a_HEADERS = layout_controller.hpp \
pe_layout_controller.hpp \
logger/logging.hpp \
logger/stringprintf.hpp

# library
libfilestructure_a_SOURCES = $(libfilestructure_a_HEADERS) pe_layout_controller.cpp \
logger/logging.cpp \
logger/stringprintf.cpp
