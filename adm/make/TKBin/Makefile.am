# Makefile.am for Open Cascade toolkit TKBin
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BinDrivers : @top_srcdir@/src/BinDrivers: \
@top_srcdir@/drv/BinMDataXtd : @top_srcdir@/src/BinMDataXtd: \
@top_srcdir@/drv/BinMPrsStd : @top_srcdir@/src/BinMPrsStd: \
@top_srcdir@/drv/BinMNaming : @top_srcdir@/src/BinMNaming: \
@top_srcdir@/drv/BinTools : @top_srcdir@/src/BinTools


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BinDrivers -I@top_srcdir@/src/BinDrivers \
-I@top_srcdir@/drv/BinMDataXtd -I@top_srcdir@/src/BinMDataXtd \
-I@top_srcdir@/drv/BinMPrsStd -I@top_srcdir@/src/BinMPrsStd \
-I@top_srcdir@/drv/BinMNaming -I@top_srcdir@/src/BinMNaming \
-I@top_srcdir@/drv/BinTools -I@top_srcdir@/src/BinTools


lib_LTLIBRARIES=libTKBin.la

libTKBin_la_LIBADD = \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKBinL/libTKBinL.la \
../TKLCAF/libTKLCAF.la \
../TKG2d/libTKG2d.la \
../TKCAF/libTKCAF.la \
../TKV3d/libTKV3d.la \
../TKBRep/libTKBRep.la \
../TKG3d/libTKG3d.la \
../TKCDF/libTKCDF.la \
$(STLPort_LIB) 

libTKBin_la_SOURCES = \
@top_srcdir@/src/BinDrivers/BinDrivers.cxx \
@top_srcdir@/src/BinDrivers/BinDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/BinDrivers/BinDrivers_DocumentStorageDriver.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd_AxisDriver.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd_ConstraintDriver.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd_GeometryDriver.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd_PatternStdDriver.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd_PlacementDriver.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd_PlaneDriver.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd_PointDriver.cxx \
@top_srcdir@/src/BinMDataXtd/BinMDataXtd_ShapeDriver.cxx \
@top_srcdir@/src/BinMNaming/BinMNaming.cxx \
@top_srcdir@/src/BinMNaming/BinMNaming_NamedShapeDriver.cxx \
@top_srcdir@/src/BinMNaming/BinMNaming_NamingDriver.cxx \
@top_srcdir@/src/BinMPrsStd/BinMPrsStd.cxx \
@top_srcdir@/src/BinMPrsStd/BinMPrsStd_AISPresentationDriver.cxx \
@top_srcdir@/src/BinMPrsStd/BinMPrsStd_PositionDriver.cxx \
@top_srcdir@/src/BinTools/BinTools.cxx \
@top_srcdir@/src/BinTools/BinTools_Curve2dSet.cxx \
@top_srcdir@/src/BinTools/BinTools_CurveSet.cxx \
@top_srcdir@/src/BinTools/BinTools_LocationSet.cxx \
@top_srcdir@/src/BinTools/BinTools_ShapeSet.cxx \
@top_srcdir@/src/BinTools/BinTools_SurfaceSet.cxx

