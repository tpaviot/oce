# Makefile.am for Open Cascade toolkit TKTObjDRAW
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/TObjDRAW : @top_srcdir@/src/TObjDRAW


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/TObjDRAW -I@top_srcdir@/src/TObjDRAW


lib_LTLIBRARIES=libTKTObjDRAW.la

libTKTObjDRAW_la_LIBADD = $(CSF_OPT_LIBS) \
../TKernel/libTKernel.la \
../TKCDF/libTKCDF.la \
../TKLCAF/libTKLCAF.la \
../TKTObj/libTKTObj.la \
../TKMath/libTKMath.la \
../TKDraw/libTKDraw.la \
../TKDCAF/libTKDCAF.la


libTKTObjDRAW_la_SOURCES = \
@top_srcdir@/src/TObjDRAW/TObjDRAW.cxx

