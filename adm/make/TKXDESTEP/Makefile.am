# Makefile.am for Open Cascade toolkit TKXDESTEP
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/STEPCAFControl : @top_srcdir@/src/STEPCAFControl


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/STEPCAFControl -I@top_srcdir@/src/STEPCAFControl


lib_LTLIBRARIES=libTKXDESTEP.la

libTKXDESTEP_la_LIBADD = \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKXCAF/libTKXCAF.la \
../TKLCAF/libTKLCAF.la \
../TKXSBase/libTKXSBase.la \
../TKSTEPBase/libTKSTEPBase.la \
../TKG2d/libTKG2d.la \
../TKSTEP/libTKSTEP.la \
../TKBRep/libTKBRep.la \
../TKG3d/libTKG3d.la \
../TKCAF/libTKCAF.la \
../TKSTEPAttr/libTKSTEPAttr.la \
../TKCDF/libTKCDF.la \
$(STLPort_LIB) 

libTKXDESTEP_la_SOURCES = \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfLabelExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfLabelShape_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfPDExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfSDRExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfShapePD_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfShapeSDR_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfLabelExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfLabelShape_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfPDExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfSDRExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfShapePD_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfShapeSDR_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapOfLabelExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapOfLabelShape_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapOfPDExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapOfSDRExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapOfShapePD_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DataMapOfShapeSDR_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_DictionaryOfExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_IteratorOfDictionaryOfExternFile_0.cxx \
@top_srcdir@/drv/STEPCAFControl/STEPCAFControl_StackItemOfDictionaryOfExternFile_0.cxx \
@top_srcdir@/src/STEPCAFControl/STEPCAFControl_ActorWrite.cxx \
@top_srcdir@/src/STEPCAFControl/STEPCAFControl_Controller.cxx \
@top_srcdir@/src/STEPCAFControl/STEPCAFControl_ExternFile.cxx \
@top_srcdir@/src/STEPCAFControl/STEPCAFControl_Reader.cxx \
@top_srcdir@/src/STEPCAFControl/STEPCAFControl_Writer.cxx

libTKXDESTEP_laLDFLAGS = -version-info @oce_version_info@

