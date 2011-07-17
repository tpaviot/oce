# Makefile.am for Open Cascade toolkit TKBinXCAF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BinXCAFDrivers : @top_srcdir@/src/BinXCAFDrivers: \
@top_srcdir@/drv/BinMXCAFDoc : @top_srcdir@/src/BinMXCAFDoc


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BinXCAFDrivers -I@top_srcdir@/src/BinXCAFDrivers \
-I@top_srcdir@/drv/BinMXCAFDoc -I@top_srcdir@/src/BinMXCAFDoc


lib_LTLIBRARIES=libTKBinXCAF.la

libTKBinXCAF_la_LIBADD = \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKLCAF/libTKLCAF.la \
../TKG2d/libTKG2d.la \
../TKBinL/libTKBinL.la \
../TKBRep/libTKBRep.la \
../TKBin/libTKBin.la \
../TKG3d/libTKG3d.la \
../TKXCAF/libTKXCAF.la \
../TKCAF/libTKCAF.la \
../TKCDF/libTKCDF.la \
$(STLPort_LIB) 

libTKBinXCAF_la_SOURCES = \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_AreaDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_CentroidDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_ColorDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_ColorToolDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_DatumDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_DimTolDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_DimTolToolDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_DocumentToolDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_GraphNodeDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_LayerToolDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_LocationDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_MaterialDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_MaterialToolDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_ShapeToolDriver.cxx \
@top_srcdir@/src/BinMXCAFDoc/BinMXCAFDoc_VolumeDriver.cxx \
@top_srcdir@/src/BinXCAFDrivers/BinXCAFDrivers.cxx \
@top_srcdir@/src/BinXCAFDrivers/BinXCAFDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/BinXCAFDrivers/BinXCAFDrivers_DocumentStorageDriver.cxx

