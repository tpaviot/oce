# Makefile.am for Open Cascade toolkit TKXml
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XmlDrivers : @top_srcdir@/src/XmlDrivers: \
@top_srcdir@/drv/XmlMDataXtd : @top_srcdir@/src/XmlMDataXtd: \
@top_srcdir@/drv/XmlMNaming : @top_srcdir@/src/XmlMNaming: \
@top_srcdir@/drv/XmlMPrsStd : @top_srcdir@/src/XmlMPrsStd


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XmlDrivers -I@top_srcdir@/src/XmlDrivers \
-I@top_srcdir@/drv/XmlMDataXtd -I@top_srcdir@/src/XmlMDataXtd \
-I@top_srcdir@/drv/XmlMNaming -I@top_srcdir@/src/XmlMNaming \
-I@top_srcdir@/drv/XmlMPrsStd -I@top_srcdir@/src/XmlMPrsStd


lib_LTLIBRARIES=libTKXml.la

libTKXml_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKCDF/libTKCDF.la \
../TKernel/libTKernel.la \
../TKV3d/libTKV3d.la \
../TKMath/libTKMath.la \
../TKBRep/libTKBRep.la \
../TKG2d/libTKG2d.la \
../TKGeomBase/libTKGeomBase.la \
../TKG3d/libTKG3d.la \
../TKLCAF/libTKLCAF.la \
../TKCAF/libTKCAF.la \
../TKXmlL/libTKXmlL.la \
$(STLPort_LIB) 

libTKXml_la_SOURCES = \
@top_srcdir@/drv/XmlMNaming/XmlMNaming_Array1OfShape1_0.cxx \
@top_srcdir@/src/XmlDrivers/XmlDrivers.cxx \
@top_srcdir@/src/XmlDrivers/XmlDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/XmlDrivers/XmlDrivers_DocumentStorageDriver.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd_AxisDriver.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd_ConstraintDriver.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd_GeometryDriver.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd_PatternStdDriver.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd_PlacementDriver.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd_PlaneDriver.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd_PointDriver.cxx \
@top_srcdir@/src/XmlMDataXtd/XmlMDataXtd_ShapeDriver.cxx \
@top_srcdir@/src/XmlMNaming/XmlMNaming.cxx \
@top_srcdir@/src/XmlMNaming/XmlMNaming_NamedShapeDriver.cxx \
@top_srcdir@/src/XmlMNaming/XmlMNaming_NamingDriver.cxx \
@top_srcdir@/src/XmlMNaming/XmlMNaming_Shape1.cxx \
@top_srcdir@/src/XmlMPrsStd/XmlMPrsStd.cxx \
@top_srcdir@/src/XmlMPrsStd/XmlMPrsStd_AISPresentationDriver.cxx \
@top_srcdir@/src/XmlMPrsStd/XmlMPrsStd_PositionDriver.cxx

