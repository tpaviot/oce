# Makefile.am for Open Cascade toolkit TKXDEIGES
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/IGESCAFControl : @top_srcdir@/src/IGESCAFControl


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/IGESCAFControl -I@top_srcdir@/src/IGESCAFControl


lib_LTLIBRARIES=libTKXDEIGES.la

libTKXDEIGES_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKXSBase/libTKXSBase.la \
../TKCDF/libTKCDF.la \
../TKLCAF/libTKLCAF.la \
../TKG2d/libTKG2d.la \
../TKXCAF/libTKXCAF.la \
../TKIGES/libTKIGES.la \
$(STLPort_LIB) 

libTKXDEIGES_la_SOURCES = \
@top_srcdir@/src/IGESCAFControl/IGESCAFControl.cxx \
@top_srcdir@/src/IGESCAFControl/IGESCAFControl_Reader.cxx \
@top_srcdir@/src/IGESCAFControl/IGESCAFControl_Writer.cxx

