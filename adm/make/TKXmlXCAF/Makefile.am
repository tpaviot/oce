# Makefile.am for Open Cascade toolkit TKXmlXCAF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XmlXCAFDrivers : @top_srcdir@/src/XmlXCAFDrivers: \
@top_srcdir@/drv/XmlMXCAFDoc : @top_srcdir@/src/XmlMXCAFDoc


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XmlXCAFDrivers -I@top_srcdir@/src/XmlXCAFDrivers \
-I@top_srcdir@/drv/XmlMXCAFDoc -I@top_srcdir@/src/XmlMXCAFDoc


lib_LTLIBRARIES=libTKXmlXCAF.la

libTKXmlXCAF_la_LIBADD = \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKLCAF/libTKLCAF.la \
../TKG2d/libTKG2d.la \
../TKXmlL/libTKXmlL.la \
../TKBRep/libTKBRep.la \
../TKG3d/libTKG3d.la \
../TKXCAF/libTKXCAF.la \
../TKCAF/libTKCAF.la \
../TKCDF/libTKCDF.la \
../TKGeomBase/libTKGeomBase.la \
../TKXml/libTKXml.la \
$(STLPort_LIB) 

libTKXmlXCAF_la_SOURCES = \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_AreaDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_CentroidDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_ColorDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_ColorToolDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_DatumDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_DimTolDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_DimTolToolDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_DocumentToolDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_GraphNodeDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_LayerToolDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_LocationDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_MaterialDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_MaterialToolDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_ShapeToolDriver.cxx \
@top_srcdir@/src/XmlMXCAFDoc/XmlMXCAFDoc_VolumeDriver.cxx \
@top_srcdir@/src/XmlXCAFDrivers/XmlXCAFDrivers.cxx \
@top_srcdir@/src/XmlXCAFDrivers/XmlXCAFDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/XmlXCAFDrivers/XmlXCAFDrivers_DocumentStorageDriver.cxx

libTKXmlXCAF_laLDFLAGS = -version-info @oce_version_info@

