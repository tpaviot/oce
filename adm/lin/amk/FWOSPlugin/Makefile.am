# Makefile.am for Open Cascade toolkit FWOSPlugin
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/FWOSDriver : @top_srcdir@/src/FWOSDriver


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/FWOSDriver -I@top_srcdir@/src/FWOSDriver


lib_LTLIBRARIES=libFWOSPlugin.la

libFWOSPlugin_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKCDF/libTKCDF.la \
$(STLPort_LIB) 

libFWOSPlugin_la_SOURCES = \
@top_srcdir@/src/FWOSDriver/FWOSDriver.cxx \
@top_srcdir@/src/FWOSDriver/FWOSDriver_DriverFactory.cxx

