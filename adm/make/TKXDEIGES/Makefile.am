# Makefile.am for Open Cascade toolkit TKXDEIGES
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/IGESCAFControl : @top_srcdir@/src/IGESCAFControl


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/IGESCAFControl -I@top_srcdir@/src/IGESCAFControl


lib_LTLIBRARIES=libTKXDEIGES.la

libTKXDEIGES_la_LIBADD = \
../TKernel/libTKernel.la \
../TKXCAF/libTKXCAF.la \
../TKLCAF/libTKLCAF.la \
../TKXSBase/libTKXSBase.la \
../TKBRep/libTKBRep.la \
../TKIGES/libTKIGES.la \
../TKG2d/libTKG2d.la \
../TKMath/libTKMath.la \
../TKCDF/libTKCDF.la \
$(STLPort_LIB) 

libTKXDEIGES_la_SOURCES = \
@top_srcdir@/src/IGESCAFControl/IGESCAFControl.cxx \
@top_srcdir@/src/IGESCAFControl/IGESCAFControl_Reader.cxx \
@top_srcdir@/src/IGESCAFControl/IGESCAFControl_Writer.cxx

