# Makefile.am for Open Cascade toolkit TKTObj
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/TObj : @top_srcdir@/src/TObj


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/TObj -I@top_srcdir@/src/TObj


lib_LTLIBRARIES=libTKTObj.la

libTKTObj_la_LIBADD = $(CSF_OPT_LIBS) \
../TKCDF/libTKCDF.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKLCAF/libTKLCAF.la


libTKTObj_la_SOURCES = \
@top_srcdir@/src/TObj/TObj_Application.cxx \
@top_srcdir@/src/TObj/TObj_Assistant.cxx \
@top_srcdir@/src/TObj/TObj_CheckModel.cxx \
@top_srcdir@/src/TObj/TObj_HiddenPartition.cxx \
@top_srcdir@/src/TObj/TObj_LabelIterator.cxx \
@top_srcdir@/src/TObj/TObj_Model.cxx \
@top_srcdir@/src/TObj/TObj_ModelIterator.cxx \
@top_srcdir@/src/TObj/TObj_Object.cxx \
@top_srcdir@/src/TObj/TObj_ObjectIterator.cxx \
@top_srcdir@/src/TObj/TObj_OcafObjectIterator.cxx \
@top_srcdir@/src/TObj/TObj_Partition.cxx \
@top_srcdir@/src/TObj/TObj_Persistence.cxx \
@top_srcdir@/src/TObj/TObj_ReferenceIterator.cxx \
@top_srcdir@/src/TObj/TObj_SequenceIterator.cxx \
@top_srcdir@/src/TObj/TObj_SequenceOfObject.cxx \
@top_srcdir@/src/TObj/TObj_TIntSparseArray.cxx \
@top_srcdir@/src/TObj/TObj_TModel.cxx \
@top_srcdir@/src/TObj/TObj_TNameContainer.cxx \
@top_srcdir@/src/TObj/TObj_TObject.cxx \
@top_srcdir@/src/TObj/TObj_TReference.cxx \
@top_srcdir@/src/TObj/TObj_TXYZ.cxx

