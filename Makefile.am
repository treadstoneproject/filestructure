# debug, optimized
AM_CXXFLAGS   = -I$(top_srcdir)/src/ @AM_CXXFLAGS@

# Make src file 
# libarries for read and handle file structure.
lib_LIBRARIES = libfilestructure.a

#@install header to system
libfilestructure_adir = $(includedir)/filestructure

#Header
libfilestructure_a_HEADERS = layout_controller.hpp \
pe_layout_controller.hpp \
elf_layout_controller.hpp


# library
libfilestructure_a_SOURCES = $(libfilestructure_a_HEADERS) pe_layout_controller.cpp \
elf_layout_controller.cpp

