# Makefile.am for Open Cascade toolkit TKXDEDRAW
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XDEDRAW : @top_srcdir@/src/XDEDRAW


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XDEDRAW -I@top_srcdir@/src/XDEDRAW


lib_LTLIBRARIES=libTKXDEDRAW.la

libTKXDEDRAW_la_LIBADD = \
../TKernel/libTKernel.la \
../TKLCAF/libTKLCAF.la \
../TKXSBase/libTKXSBase.la \
../TKXCAF/libTKXCAF.la \
../TKViewerTest/libTKViewerTest.la \
../TKXSDRAW/libTKXSDRAW.la \
../TKG3d/libTKG3d.la \
../TKCAF/libTKCAF.la \
../TKV3d/libTKV3d.la \
../TKService/libTKService.la \
../TKMath/libTKMath.la \
../TKCDF/libTKCDF.la \
../TKBRep/libTKBRep.la \
../TKDCAF/libTKDCAF.la \
../TKMesh/libTKMesh.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKG2d/libTKG2d.la \
../TKDraw/libTKDraw.la \
../TKSTEPBase/libTKSTEPBase.la \
../TKIGES/libTKIGES.la \
../TKXDESTEP/libTKXDESTEP.la \
../TKNIS/libTKNIS.la \
../TKSTEP/libTKSTEP.la \
../TKXDEIGES/libTKXDEIGES.la \
$(STLPort_LIB) 

libTKXDEDRAW_la_SOURCES = \
@top_srcdir@/src/XDEDRAW/XDEDRAW.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Colors.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Common.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Layers.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Props.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Shapes.cxx

