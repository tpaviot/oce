# Makefile.am for Open Cascade toolkit TKXmlTObj
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XmlTObjDrivers : @top_srcdir@/src/XmlTObjDrivers


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XmlTObjDrivers -I@top_srcdir@/src/XmlTObjDrivers


lib_LTLIBRARIES=libTKXmlTObj.la

libTKXmlTObj_la_LIBADD = \
../TKernel/libTKernel.la \
../TKTObj/libTKTObj.la \
../TKMath/libTKMath.la \
../TKLCAF/libTKLCAF.la \
../TKXmlL/libTKXmlL.la \
../TKCDF/libTKCDF.la \
$(STLPort_LIB) 

libTKXmlTObj_la_SOURCES = \
@top_srcdir@/src/XmlTObjDrivers/XmlTObjDrivers.cxx \
@top_srcdir@/src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx \
@top_srcdir@/src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx \
@top_srcdir@/src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx \
@top_srcdir@/src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx \
@top_srcdir@/src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx \
@top_srcdir@/src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx

