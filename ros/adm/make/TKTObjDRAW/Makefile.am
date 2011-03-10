# Makefile.am for Open Cascade toolkit TKTObjDRAW
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/TObjDRAW : @top_srcdir@/src/TObjDRAW


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/TObjDRAW -I@top_srcdir@/src/TObjDRAW


lib_LTLIBRARIES=libTKTObjDRAW.la

libTKTObjDRAW_la_LIBADD = \
../TKTObj/libTKTObj.la \
../TKMath/libTKMath.la \
../TKDCAF/libTKDCAF.la \
../TKLCAF/libTKLCAF.la \
../TKCDF/libTKCDF.la \
../TKernel/libTKernel.la \
../TKDraw/libTKDraw.la \
$(STLPort_LIB) 

libTKTObjDRAW_la_SOURCES = \
@top_srcdir@/src/TObjDRAW/TObjDRAW.cxx

