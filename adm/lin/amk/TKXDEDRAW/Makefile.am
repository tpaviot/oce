# Makefile.am for Open Cascade toolkit TKXDEDRAW
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XDEDRAW : @top_srcdir@/src/XDEDRAW


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XDEDRAW -I@top_srcdir@/src/XDEDRAW


lib_LTLIBRARIES=libTKXDEDRAW.la

libTKXDEDRAW_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKCDF/libTKCDF.la \
../TKBRep/libTKBRep.la \
../TKXCAF/libTKXCAF.la \
../TKernel/libTKernel.la \
../TKIGES/libTKIGES.la \
../TKV3d/libTKV3d.la \
../TKMath/libTKMath.la \
../TKNIS/libTKNIS.la \
../TKService/libTKService.la \
../TKXSBase/libTKXSBase.la \
../TKG2d/libTKG2d.la \
../TKCAF/libTKCAF.la \
../TKDraw/libTKDraw.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKLCAF/libTKLCAF.la \
../TKG3d/libTKG3d.la \
../TKSTEPBase/libTKSTEPBase.la \
../TKSTEP/libTKSTEP.la \
../TKMesh/libTKMesh.la \
../TKXSDRAW/libTKXSDRAW.la \
../TKXDEIGES/libTKXDEIGES.la \
../TKXDESTEP/libTKXDESTEP.la \
../TKDCAF/libTKDCAF.la \
../TKViewerTest/libTKViewerTest.la \
$(STLPort_LIB) 

libTKXDEDRAW_la_SOURCES = \
@top_srcdir@/src/XDEDRAW/XDEDRAW.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Colors.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Common.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Layers.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Props.cxx \
@top_srcdir@/src/XDEDRAW/XDEDRAW_Shapes.cxx

