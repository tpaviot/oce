# Makefile.am for Open Cascade toolkit TKBinTObj
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BinTObjDrivers : @top_srcdir@/src/BinTObjDrivers


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BinTObjDrivers -I@top_srcdir@/src/BinTObjDrivers


lib_LTLIBRARIES=libTKBinTObj.la

libTKBinTObj_la_LIBADD = $(CSF_OPT_LIBS) \
../TKCDF/libTKCDF.la \
../TKernel/libTKernel.la \
../TKTObj/libTKTObj.la \
../TKMath/libTKMath.la \
../TKLCAF/libTKLCAF.la \
../TKBinL/libTKBinL.la


libTKBinTObj_la_SOURCES = \
@top_srcdir@/src/BinTObjDrivers/BinTObjDrivers.cxx \
@top_srcdir@/src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx \
@top_srcdir@/src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx \
@top_srcdir@/src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx \
@top_srcdir@/src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx \
@top_srcdir@/src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx \
@top_srcdir@/src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx

